#include "io.h"
#include "endian.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "code.h"

static uint8_t buffer[BLOCK]; // 4096

static uint8_t word_buffer[BLOCK];

static uint64_t bit_index = 0; // keep state of bit

static uint32_t byte_index = 0; // for read sym

static uint32_t symbol_track = 0;

uint64_t total_bits = 0;

uint64_t total_syms = 0;

int read_bytes(int infile, uint8_t *buf, int to_read) {

    //write a wrapper function to loop calls to read() until we have either read all the bytes that were specified
    //(to_read), or there are no more bytes to read. The number of bytes that were read are returned.

    //  printf("total_bits %lu\n", total_bits);

    int bytes_read = 0;

    while (to_read > 0) {

        int n = read(infile, buf + bytes_read, to_read);

        if (n == -1) {

            return 0; //Error
        }

        if (n == 0) {

            break;
        }

        to_read -= n;
        bytes_read += n;
    }

    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {

    //we loop until we have either written out all the bytes specified, or no bytes were written. The number of bytes written out is returned.
    int bytes_w = 0;

    total_bits = total_bits + to_write;

    while (to_write > 0) {

        int n = write(outfile, buf + bytes_w, to_write);

        if (n == -1) {

            return 0; //Error
        }

        if (n == 0) { //nothing left to read

            break;
        }

        to_write -= n;
        bytes_w += n;
    }

    return bytes_w;
}

void read_header(int infile, FileHeader *header) {

    int read = sizeof(FileHeader);

    // fprintf(stderr, "Read = %d \n\n", read);

    read_bytes(infile, (uint8_t *) header, read);

    total_syms += read * 8;

    if (big_endian()) {

        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }

    if (header->magic != MAGIC) {

        fprintf(stderr, "Incorrect Magic Number\n");
        exit(1);
    }
}

void write_header(int outfile, FileHeader *header) {

    int write = sizeof(FileHeader);

    if (little_endian() == big_endian()) {

        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }

    write_bytes(outfile, (uint8_t *) header, write);

    //bytes supplied from header

    //Writes sizeof(FileHeader) bytes to the output file. These bytes are from the supplied header. Endianness is swapped if byte order isn’t little endian.
}

bool read_sym(int infile, uint8_t *sym) {

    if (byte_index != symbol_track) {

        *sym = word_buffer[byte_index];

        byte_index = byte_index + 1;

        total_syms += 1;

    }

    else {

        symbol_track = read_bytes(infile, word_buffer, 4096);

        if (symbol_track == 0) {

            return false;
        }

        byte_index = 0;
        *sym = word_buffer[byte_index];
        byte_index = byte_index + 1;

        total_syms += 1;
    }

    return true;
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {

    int check = 0;

    uint8_t code_mask = 1;

    uint8_t sym_mask = 1;

    for (int j = 0; j < bitlen; j++) {

        if (bit_index / 8 >= 4096) { //buffer is full do this

            //    printf("AT THE MAX\n\n");

            check = write_bytes(outfile, buffer, BLOCK);
            bit_index = 0;

            if (check == 0) {

                return;
            }
        }

        uint16_t result_code = code & (code_mask << j);

        // printf("Result_code = %d\n\n", result_code);

        if (result_code == 0) { // gets whether it's a zero or one

            //buffer[byte_index] |= (1 << j);
            //printf("0");
            buffer[bit_index / 8] &= ~(code_mask << (bit_index % 8)); // if there's a 0 in bit

        }

        else {
            // printf("1");
            //buffer[byte_index] &= ~(1 << j);
            buffer[bit_index / 8] |= code_mask << (bit_index % 8);
        }

        bit_index++;
    }

    //sym portion

    for (int i = 0; i < 8; i++) {

        uint8_t result = sym & (sym_mask << i);

        if (bit_index >= 32768) { //buffer is full do this

            //    printf("AT THE MAX\n\n");

            check = write_bytes(outfile, buffer, BLOCK);
            bit_index = 0;

            if (check == 0) {

                return;
            }
        }

        if (result == 0) {

            // printf("0");

            buffer[bit_index / 8] &= ~(sym_mask << (bit_index % 8));

        } else {
            // printf("1");
            buffer[bit_index / 8] |= sym_mask << (bit_index % 8);
        }

        bit_index++;
    }
}

void flush_pairs(int outfile) {

    uint8_t mask = 1;

    while (bit_index % 8 != 0) {

        buffer[bit_index / 8]
            &= ~(mask << (bit_index % 8)); // need to padd the remaining bits if there are any

        bit_index += 1;
    }

    write_bytes(outfile, buffer, bit_index / 8);

    bit_index = 0;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {

    int check = 0;

    if (bit_index == 0) {

        //   printf("WOWOWOWOW MAX\n\n");

        check = read_bytes(infile, buffer, 4096);

        bit_index = 0;

        if (check == 0) {
            return false;
        }
    }

    *code = 0;
    *sym = 0;

    uint8_t sym_mask = 1;
    uint16_t code_mask = 1;

    for (int j = 0; j < bitlen; j++) {

        uint16_t result_code
            = buffer[bit_index / 8]
              & (code_mask << bit_index
                                  % 8); //have to do the opposite in masking that I did in write

        if (bit_index >= 32768) {

            //    printf("WOWOWOWOW MAX\n\n");

            check = read_bytes(infile, buffer, BLOCK);

            bit_index = 0;

            if (check == 0) {
                return false;
            }
        }

        if (result_code == 0) { // gets whether it's a zero or one

            *code &= ~(code_mask << j); // easier than I thought?

        }

        else {

            *code |= code_mask << j; // clears --> needed?
        }

        bit_index++;

        total_syms++;
    }

    for (int i = 0; i < 8; i++) {

        uint8_t result = buffer[bit_index / 8] & (sym_mask << bit_index % 8);

        if (bit_index / 8 >= 4096) {

            printf("WOWOWOWOW MAX\n\n");

            check = read_bytes(infile, buffer, BLOCK);

            bit_index = 0;

            if (check == 0) {
                return false;
            }
        }

        if (result == 0) {

            *sym &= ~(sym_mask << (i % 8)); // sets

        } else { // clear

            *sym |= sym_mask << i % 8;
        }

        bit_index++;

        total_syms++;
    }

    if (*code == STOP_CODE) {

        return false; //need to stop if we reached the end
    }

    return true;
}

void write_word(int outfile, Word *w) {

    for (uint32_t i = 0; i < w->len; i++) {

        if (byte_index >= BLOCK) { // buffer is full

            write_bytes(outfile, word_buffer, byte_index);
            byte_index = 0;
        }

        word_buffer[byte_index] = w->syms[i];

        byte_index++;
    }
}

void flush_words(int outfile) {

    write_bytes(outfile, word_buffer, byte_index);
    byte_index = 0;
}
