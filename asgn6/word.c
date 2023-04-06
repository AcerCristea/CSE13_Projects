#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "word.h"
#include "code.h"

Word *word_create(uint8_t *syms, uint32_t len) {

    Word *w = (Word *) malloc(sizeof(Word));

    w->len = len;

    w->syms = (uint8_t *) malloc(w->len * sizeof(uint8_t));

    for (uint32_t i = 0; i < len; i++) {

        w->syms[i] = syms[i];
    }
    return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {

    //    printf("entering word_append_sym\n");
    //   printf("w->len: %u\n", w->len);
    //   printf("sym: %u\n", sym);

    Word *new_word = (Word *) malloc(sizeof(Word));

    new_word->len = w->len + 1; // segfaults here

    new_word->syms = (uint8_t *) malloc(
        w->len + 1 * sizeof(uint8_t)); // probably makes this really inefficient but it works

    for (uint32_t i = 0; i < w->len; i++) {
        new_word->syms[i] = w->syms[i];
    }

    new_word->syms[w->len] = sym;

    return new_word;
}

WordTable *wt_create(void) {

    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(WordTable));

    uint8_t *sym = NULL; // unsigned char

    Word *empty_word = word_create(sym, 0); // empty word
    wt[EMPTY_CODE] = empty_word; // index 1 = empty word

    return wt;
}

void word_delete(Word *w) {

    if (w->syms != NULL) {
        free(w->syms);
    }

    if (w != NULL) {
        free(w);
    }
}

void wt_reset(WordTable *wt) {
    //Resets a WordTable, wt, to contain just the empty Word. Make sure all the other words in the table are NULL.

    for (int i = 2; i < MAX_CODE; i++) {

        if (wt[i] != NULL) {
            word_delete(wt[i]); //free
            wt[i] = NULL;
        }
    }
}

void wt_delete(WordTable *wt) {

    for (int i = 0; i < MAX_CODE; i++) {
        if (wt[i] != NULL) {
            word_delete(wt[i]);
            wt[i] = NULL;
        }
    }
    free(wt);
}
