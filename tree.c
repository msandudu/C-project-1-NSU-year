#include "tree.h"

Tree *init_tree(int weight, int symbol) {
    Tree *node = malloc(sizeof(Tree));
    node->elem = (unsigned char)symbol;
    node->weight = weight;
    node->size = 0;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

TreeList *init_arr(void) {
    TreeList *arr = malloc(sizeof(TreeList));
    arr->cnt = 0;
    for (int i = 0; i < 256; i++) {
        arr->nodes[i] = NULL;
    }
    return arr;
}

void destroy(Tree *node) {
    if (node != NULL) {
        destroy(node->left);
        destroy(node->right);
        free(node);
    }
}

void init_queue(TreeList *arr, int *amount) {
    for (int i = 0; i < 256; i++) {
        if (amount[i] > 0){
            Tree *tmp = init_tree(amount[i], i);
            enqueue(tmp, arr);
        }
    }
}

void enqueue(Tree *node, TreeList *arr) {
    int i;
    for (i = arr->cnt; i > 0 && (arr->nodes[i - 1]->weight < node->weight); i--){
        arr->nodes[i] = arr->nodes[i - 1];
    }
    arr->nodes[i] = node;
    arr->cnt++;
}

Tree *dequeue(TreeList *arr) {
    return arr->nodes[--(arr->cnt)];
}

Tree *huffman(int *amount) {
    TreeList *arr = init_arr();
    init_queue(arr, amount);
    
    while (arr->cnt > 1) {
        Tree *node = malloc(sizeof(Tree));
        node->left = dequeue(arr);
        node->right = dequeue(arr);
        node->weight = node->left->weight + node->right->weight;
        enqueue(node, arr);
    }
    
    Tree *tree = dequeue(arr);
    free(arr);
    
    return tree;
}

Tree *find_code(Tree *tree, unsigned int buffer, unsigned int buf_size, int lvl) {
    if (lvl > buf_size){
        return NULL;
    }
    if (tree->left == NULL && tree->right == NULL){
        return tree;
    }
    if (tree->left != NULL && !(buffer >> (buf_size - lvl - 1) & 1)){
        return find_code(tree->left, buffer, buf_size, lvl + 1);
    }
    if (tree->right != NULL && (buffer >> (buf_size - lvl - 1) & 1)){
        return find_code(tree->right, buffer, buf_size, lvl + 1);
    }

    return NULL;
}

void make_code(Tree *node, Symbol **dict, unsigned int code, int lvl){
    if (node->left == NULL && node->right == NULL) {
        node->code = code;
        node->size = lvl;
        dict[node->elem]->code = code;
        dict[node->elem]->size = lvl;
        return;
    }
    if (node->left != NULL) {
        make_code(node->left, dict, code << 1, lvl + 1);
    }
    if (node->right != NULL) {
        make_code(node->right, dict, (code << 1) + 1, lvl + 1);
    }
}
