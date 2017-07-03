#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T;

typedef struct btree_block {
    int degree; // o grau do bloco
    int * keys; // receberá espaço de memória equivalente a 2T - 1
    struct btree_block ** children; // receberá espaço de memória equivalente a 2T
    struct btree_block * father;
} block;

typedef struct btree_promote_info {
    int promoted_key;
    block * new_child;
} promote_info;

block * initialize(void);
block * insert(block * tree, int val);

int main(void) {
    scanf("%d\n", &T);
    return 0;
}

block * initialize(void) {
    block * new_btree = (block *) malloc(sizeof(block));
    new_btree->degree = 1;

    new_btree->keys = (int *) malloc(sizeof(int) * (2 * T  - 1));

    new_btree->children = (block **) malloc(sizeof(block *) * 2 * T);
    memset(new_btree->children, 0, sizeof(block *) * 2 * T); // seta os ponteiros para os filhos como NULL

    new_btree->father = NULL;

    return new_btree;
}

promote_info * _insert(block * tree, int val) {

    promote_info promote_receive, promote_send;
    block * aux_tree;
    int i;

    for (i = 0; i < tree->degree - 1; i++) {
        if (tree->keys[i] == val) return;
    }

    if (tree->children[0] != NULL) {
        //se este bloco não é uma folha
        
        for (i = 0; i < tree->degree - 1 && val > tree->keys[i]; i++);

        promote_receive = _insert(tree->children[i], val);

        if (promote_receive->new_child != NULL) {
            //TODO
            //tem que fazer promote do filho:(
            
            if (tree->degree == 2 * T) {
                //tem que fazer split e promote deste bloco
                //a key promovida vai ser a de índice T
                

            }
            //não tem que fazer split e promote
        }

        promote->new_child = NULL;
        return promote;
    }

    //se for uma folha
    if (tree->degree == 2 * T) {
        //vai ter que fazer promote
        promote->new_child = initialize();
        
        //copia todos as keys depois da key promovida para o novo nodo à direita
        for (i = T - 1; i < 2 * T - 1; i++) {
            promote->new_child->keys[i - T + 1] = tree->keys[i];
            promote->promoted_key = tree->keys[T];
        }

        if (val < promote->promoted_key) aux_tree = tree;
        else aux_tree = promote->new_child;

        aux_tree->degree++;
        aux_tree[T - 1] = val;

        return promote;
    }

    tree->children[tree->degree - 1] = val;
    tree->degree++;

    return promote;
}
block * insert(block * tree, int val) {
    promote_info * pr = _insert(tree, val); //possível nova raiz

    if (pr->new_child != NULL) { //tem que criar uma nova raiz
        block * new_root = (block *) malloc(sizeof(block));
        block->degree = 2;
        block->children[0] = tree;
        block->children[1] = pr->new_child;
        block->keys[0] = pr->promoted_key;

        return new_root;
    }

    //não tem nova raiz
    return tree;
}

void _print_tree(block * tree, int level) {
    if (tree == NULL) return;
    for (int i = 0; i < tree->degree - 1; i++) {
        print_tree(tree->children[i], level + 1);
        printf("%d\n", tree->val[i]);
    }
    _print_tree(tree->children[degree - 1], level + 1);
}
void print_tree(block * tree) { _print_tree(tree, 0); }
