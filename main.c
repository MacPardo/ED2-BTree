#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T; //grau mínimo de um bloco

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
void print_tree(block * tree);

int main(void) {
    int opcao, value;

    block * tree = initialize();

    printf("Valor a ser usado para T: ");
    scanf("%d", &T);

    do {
        printf("\n1 - Inserir um elemento\n");
        printf("2 - Listar os elementos\n");
        printf("0 - Sair do programa\n");

        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Valor a ser inserido: ");
            scanf("%d", &value);

            tree = insert(tree, value);
        }
        else if (opcao == 2) {
            print_tree(tree);
        }
    } while (opcao);
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

void swap(int * key_a, block ** block_a, int * key_b, block ** block_b) {
    int key_aux;
    block * block_aux;

    key_aux = *key_a;
    *key_a = *key_b;
    *key_b = key_aux;

    block_aux = *block_a;
    *block_a = *block_b;
    *block_b = block_aux;
}

void insert_in_block(block * tree, promote_info promote_receive) {
    //só entra nesta função quando o grau de tree é menor que 2T
    int i;

    tree->keys[tree->degree - 1] = promote_receive.promoted_key;
    tree->children[tree->degree] = promote_receive.new_child;

    for (i = tree->degree; i >= 1 && tree->keys[i - 2] > tree->keys[i - 1]; i--) {
        //se a key que está sendo inserida é menor que a anterior, elas devem ser trocadas
        //juntamente com o ponteiro para o filho da direita

        //index do filho à direita da key = i (tree->children)
        //index da key = i - 1 (tree->keys)

        swap(&tree->keys[i - 1], &tree->children[i], &tree->keys[i - 2], &tree->children[i - 1]);
    }

    tree->degree++;
}

promote_info _insert(block * tree, int val) {

    promote_info promote_receive, promote_send;
    block * aux_tree;
    int i;

    promote_send.new_child = NULL;

    for (i = 0; i < tree->degree - 1; i++) { //se a key já existir, retorna um promote_info vazio
        if (tree->keys[i] == val) {
            return promote_send;
        }
    }

    if (tree->children[0] != NULL) {
        //se este bloco não é uma folha

        for (i = 0; i < tree->degree - 1 && val > tree->keys[i]; i++);

        promote_receive = _insert(tree->children[i], val);

        if (promote_receive.new_child != NULL) {
            //TODO
            //tem que fazer promote do filho:(

            if (tree->degree == 2 * T) {
                //tem que fazer split e promote deste bloco
                //a key promovida vai ser a de índice T


            }
            //não tem que fazer split e promote
        }

        promote_send.new_child = NULL;
        return promote_send;
    }

    //se for uma folha ou se a raiz não tiver filhos

    if (tree->degree == 2 * T) {// vai ter que fazer promote
        promote_send.new_child = initialize();

        //copia todos as keys depois da key promovida para o novo nodo à direita
        for (i = T - 1; i < 2 * T - 1; i++) {
            promote_send.new_child->keys[i - T + 1] = tree->keys[i];
            promote_send.promoted_key = tree->keys[T];
        }

        if (val < promote_send.promoted_key) aux_tree = tree;
        else aux_tree = promote_send.new_child;

        aux_tree->degree++;
        aux_tree->keys[T - 1] = val;

        return promote_send;
    }

    //não vai ter que fazer promote

    //printf("tree->degree - 1 = %d\n", tree->degree - 1);
    //tree->keys[tree->degree - 1] = val;
    //tree->degree++;
    
    promote_receive.promoted_key = val;
    promote_receive.new_child = NULL;
    insert_in_block(tree, promote_receive);

    return promote_send;
}
block * insert(block * tree, int val) {
    promote_info pr = _insert(tree, val); //possível nova raiz

    if (pr.new_child != NULL) { //tem que criar uma nova raiz
        block * new_root = (block *) malloc(sizeof(block));
        new_root->degree = 2;
        new_root->children[0] = tree;
        new_root->children[1] = pr.new_child;
        new_root->keys[0] = pr.promoted_key;

        return new_root;
    }

    //não tem nova raiz
    return tree;
}

void _print_tree(block * tree, int level) {
    if (tree == NULL) return;
    for (int i = 0; i < tree->degree - 1; i++) {
        _print_tree(tree->children[i], level + 1);
        printf("%d\n", tree->keys[i]);
    }
    _print_tree(tree->children[tree->degree - 1], level + 1);
}
void print_tree(block * tree) { _print_tree(tree, 0); }
