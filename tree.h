#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef struct Tree{
    unsigned char elem;
    unsigned int code;
    int weight, size;
    struct Tree *left, *right;
} Tree;

typedef struct TreeList{
    int cnt;
    Tree *nodes[256];
} TreeList;

Tree *init_tree(int weight, int symbol);
TreeList *init_arr(void);
void destroy(Tree *node);
void init_queue(TreeList *arr, int *amount);
void enqueue(Tree *node, TreeList *arr);
Tree *dequeue(TreeList *arr);
Tree *huffman(int *amount);
Tree *find_code(Tree *tree, unsigned int buffer, unsigned int bufferSize, int level);
void make_code(Tree *node, Symbol **dict, unsigned int code, int lvl);
#endif