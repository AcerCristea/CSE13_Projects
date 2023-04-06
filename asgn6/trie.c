#include "trie.h"
#include "code.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

TrieNode *trie_node_create(uint16_t index) {

    TrieNode *n = (TrieNode *) malloc(sizeof(TrieNode));

    n->code = index;

    //    printf("n->code %hu\n", n->code);

    //printf("n->code = %hu\n\n\n", n->code);

    for (int i = 0; i < ALPHABET; i++) {
        n->children[i] = NULL;
    }
    return n;

    //Constructor for a TrieNode. The node’s code is set to code. Make sure each of the children node pointers are NULL.
}

void trie_node_delete(TrieNode *n) {

    if (n != NULL) {
        for (uint16_t i = 0; i < ALPHABET - 1; i++) {
            trie_node_delete(n->children[i]);
        }
        free(n);
    }
}

TrieNode *trie_create(void) {

    TrieNode *trie = trie_node_create(EMPTY_CODE);

    return trie;

    //Initializes a trie: a root TrieNode with the code EMPTY_CODE. Returns the root, a TrieNode *, if successful, NULL otherwise
}

void trie_reset(TrieNode *root) {

    if (root == NULL) { // if tree is empty
        return;
    }

    for (int i = 0; i < ALPHABET; i++) {

        if (root->children[i] != NULL) {

            //  trie_reset(root->children[i]);
            trie_node_delete(root->children[i]);
            root->children[i] = NULL;
        }
    }

    //Resets a trie to just the root TrieNode. Since we are working with finite codes, eventually we will arrive at the end of the available codes (MAX_CODE). At that point, we must reset the trie by deleting its children so that we can continue compressing/decompressing the file. Make sure that each of the root’s children nodes are NULL.
}

void trie_delete(TrieNode *n) {

    for (int i = 0; i < ALPHABET; i++) {

        if (n->children[i] != NULL) {

            trie_delete(n->children[i]);
            //trie_node_delete(n->children[i]);
            n->children[i] = NULL;
        }
    }

    free(n);
    n = NULL;
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {

    TrieNode *trie = n->children[sym];

    if (trie == NULL) {
        return NULL;
    } else {
        return trie;
    }
}
