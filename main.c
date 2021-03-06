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

//#include <cstdlib>
#include <stdio.h>
#include "rb_tree.h"

//using namespace std;

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
        printf("%p: ", n->key);
        printf("%p\n", n->value);
        subtree_print(n->right);
    }
}

enum compare_result compare_value(void *left, void *right){
    int ret = strcmp((char*) left, (char*) right);
    if(ret < 0){
        return LESS_THAN;
    } else if(ret > 0){
        return GREATER_THAN;
    } else {
        return EQUAL_TO;
    }
}

void print_string_nl(void *str){
    printf("value: %s\n", (char*) str);
}

void print_string(void *str){
    printf("value: %s; ", (char*) str);
}

void print_node(struct rb_tree_node_t *n) {
    printf("key: %s; ", (char*) n->key);
    printf("value: %d\n", (int) n->value);
}

int main(int argc, char** argv) {
    struct rb_tree_t *t = rb_new(compare_value);
    rb_insert(t, "peas", 1);
    rb_insert(t, "squash", 2);
    rb_insert(t, "lettuce", 3);
    rb_insert(t, "carrot", 4);
    rb_insert(t, "potato", 5);
    rb_insert(t, "yam", 6);
    rb_insert(t, "Celery", 7);

    iterate_tree(t, print_node);
    printf("value: %d\n", (int) rb_get(t, "Celery"));
    //printf(t->root->value);

    void test[t->size] = keys(t);
    
    for(int i=0; i<t->size; i++){
        print_string_nl(testArray[i]);
    }
    
    return 0;
}
