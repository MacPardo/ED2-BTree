#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 3

typedef struct btree_block {
    int degree; // o grau do bloco
    int * keys; // receberá espaço de memória equivalente a 2T - 1
    struct btree_block ** sons; // receberá espaço de memória equivalente a 2T
    struct btree_block * father;
} block;

block * initialize(void);

int main(void) {
    return 0;
}

block * initialize(void) {
    block * new_btree;
    new_btree->degree = 0;

    new_btree->keys = (int*) malloc(sizeof(int) * (2 * T  - 1));
    memset(new_btree->keys, 0, sizeof(int) * (2 * T - 1));

    new_btree->sons = (block**) malloc(sizeof(block) * 2 * T);
    memset(new_btree->sons, 0, sizeof(block) * 2 * T);

    new_btree->father = NULL;

    return new_btree;
}

block * insert(block * tree, int val) {

    if (tree->sons[0] != NULL) {
        //se este bloco não é uma folha

        for (int i = 0; i < tree->degree - 1; i++) {
            if (val < tree->keys[i]) {
                //tem que ser inserido no filho à esquerda de keys[i]

                tree
            }
        }

        // se passou do for tem que ser inserido no último filho
    }

    //se for uma folha
}
