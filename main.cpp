/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Benjamin
 *
 * Created on April 25, 2017, 10:41 AM
 */

#include <cstdlib>
#include <stdio.h>
#include "rb_tree.c"

using namespace std;

/*
 * 
 */
void subtree_print(struct rb_tree_node_t *n);

void print_tree(struct rb_tree_t *tree){
    subtree_print(tree->root);
}

void subtree_print(struct rb_tree_node_t *n){
    if(n != NULL){
        subtree_print(n->left);
        printf("%d ", n->value);
        subtree_print(n->right);
    }
}

int main(int argc, char** argv) {
    struct rb_tree_t *t = rb_new();
    rb_insert(t, 1);
    rb_insert(t, 2);
    rb_insert(t, 3);
    rb_insert(t, 4);
    rb_insert(t, 5);
    
    print_tree(t);
    printf("%d ", t->root->value);
    
    return 0;
}

