/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <string.h>
#include "rb_tree.h"

//todo:

 //put(key, value)
 //delete(key)
 //keys(map) -> list(keys)
 //values(map) -> list(values)



struct rb_tree_node_t *create_node(void *key, void *value, struct rb_tree_node_t *left, struct rb_tree_node_t *right, struct rb_tree_t *tree){
    struct rb_tree_node_t *new_node = (struct rb_tree_node_t *) malloc(sizeof(struct rb_tree_node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->left = left;
    new_node->right = right;
    new_node->color = true;
    tree->size++;
    return new_node;
}

struct rb_tree_t *rb_new(enum compare_result (*compare_value)(void*, void*)){
    struct rb_tree_t *ret = (struct rb_tree_t *) malloc(sizeof(struct rb_tree_t));
    ret->root = NULL;
    ret->size = 0;
    ret->rb_comparison_function = compare_value;
    return ret;
}


void iterate_subtree(struct rb_tree_node_t* node, void (*fn)(void*)){
    if(node != NULL){
        iterate_subtree(node->left, fn);
        fn(node);
        iterate_subtree(node->right, fn);
    }
}

void iterate_tree(struct rb_tree_t* tree, void (*fn)(void*)){
    iterate_subtree(tree->root, fn);
}


bool rb_search(struct rb_tree_t *tree, void *value){
    struct rb_tree_node_t *search_node = tree->root;
    while(search_node != NULL){
        if(value < search_node->value) {
            search_node = search_node->left;
        }
        if(value > search_node->value){
            search_node = search_node->right;
        }
        if(value == search_node->value){
            return true;
        }
    }
    return false;
}

bool is_red(struct rb_tree_node_t *node){
    if(node != NULL){
        return node->color;
    } else {
        return false;
    }

}

void rb_insert(struct rb_tree_t *tree, void *key, void *value){
    tree->root = insert_helper(tree->root, key, value, tree->rb_comparison_function, tree);
}

//inserts a new node into tree; disallows duplicate values
struct rb_tree_node_t *insert_helper(struct rb_tree_node_t *node, void *key, void *value, enum compare_result (*compare_value)(void*, void*), struct rb_tree_t *tree){
    if(node == NULL){
        return create_node(key, value, NULL, NULL, tree);
    }

    if(compare_value(key, node->key) == LESS_THAN){
        node->left = insert_helper(node->left, key, value, compare_value);
    } else if (compare_value(key, node->key) == GREATER_THAN){
        node->right = insert_helper(node->right, key, value, compare_value);
    }
    //if equal, do nothing

    if(is_red(node->right) && !is_red(node->left)) {
        node = rotate_left(node);
    }
    if(is_red(node->left) && !is_red(node->right)) {
        node = rotate_right(node);
    }
    if (is_red(node->left) && is_red(node->right)) {
        flip_colors(node);
    }
    
    return node;
}

struct rb_tree_node_t *rotate_left(struct rb_tree_node_t *base) {
    if(base->right->color){
        struct rb_tree_node_t *x = base->right;
        base->right = x->left;
        x->left = base;
        x->color = base->color;
        base->color = true;
        return x;
    }
}

struct rb_tree_node_t *rotate_right(struct rb_tree_node_t *base) {
    if(base->left->color){
        struct rb_tree_node_t *x = base->left;
        base->left = x->right;
        x->right = base;
        x->color = base->color;
        base->color = true;
        return x;
    }
}

void flip_colors(struct rb_tree_node_t *node){
    if(!is_red(node) && is_red(node->left) && is_red(node->right)){
        node->color = true;
        node->left->color = false;
        node->right->color = false;
    }
}

void *rb_get(struct rb_tree_t *tree, void *key){
    struct rb_tree_node_t *node = tree->root;
    while (node != NULL){
        if(compare_value(key, node->key) == LESS_THAN) {
            node = node->left;
        }
        if(compare_value(key, node->key) == GREATER_THAN) {
            node = node->right;
        }
        if(compare_value(key, node->key) == EQUAL_TO){
            return node->value;
        }
    }
    return false;
}

bool rb_put(struct rb_tree_t *tree, void *key, void *val) {
    struct rb_tree_node_t *node = tree->root;
    while (node != NULL) {
        if (compare_value(key, node->key) == LESS_THAN) {
            node = node->left;
        }
        if (compare_value(key, node->key) == GREATER_THAN) {
            node = node->right;
        }
        if (compare_value(key, node->key) == EQUAL_TO) {
            node->value = val;
            return true;
        }
    }
    return false;
}

//todo:

 //put(key, value)
 //delete(key)
 //keys(map) -> list(keys)
 //values(map) -> list(values)

bool rb_delete(struct rb_tree_t *tree, void *key) {
    //how should I merge the children of a deleted node?
}

void *keys(struct rb_tree_t *tree){
    void retArray[tree->size] = {};
    struct rb_tree_node_t *node = tree->root;
    int counter = 0;
    keyHelper(node, retArray, counter);
    return retArray;
}

void keyHelper(struct rb_tree_node_t *node, void *array, int counter){
    if(node != NULL) {
        keyHelper(node->left, array, counter);
        array[counter] = node->key;
        counter++;
        keyHelper(node->right, array, counter);
    }
}

void *values(struct rb_tree_t *tree){
    void retArray[tree->size] = {};
    struct rb_tree_node_t *node = tree->root;
    int counter = 0;
    valueHelper(node, retArray, counter);
    return retArray;
}

void valueHelper(struct rb_tree_node_t *node, void *array, int counter){
    if(node != NULL) {
        keyHelper(node->left, array, counter);
        array[counter] = node->value;
        counter++;
        keyHelper(node->right, array, counter);
    }
}