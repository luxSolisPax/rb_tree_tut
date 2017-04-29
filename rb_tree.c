/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include "rb_tree.h"

struct rb_tree_node_t *create_node(int value, struct rb_tree_node_t *left, struct rb_tree_node_t *right){
    struct rb_tree_node_t *new_node = (struct rb_tree_node_t *) malloc(sizeof(struct rb_tree_node_t));
    new_node->value = value;
    new_node->left = left;
    new_node->right = right;
    new_node->color = true;
    return new_node;
}

struct rb_tree_t *rb_new(){
    struct rb_tree_t *ret = (struct rb_tree_t *) malloc(sizeof(struct rb_tree_t));
    ret->root = NULL;
    ret->size = 0;
    return ret;
}



bool rb_search(struct rb_tree_t *tree, int value){
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

void rb_insert(struct rb_tree_t *tree, int value){
    tree->root = insert_helper(tree->root, value);
}

struct rb_tree_node_t *insert_helper(struct rb_tree_node_t *node, int value){
    if(node == NULL){
        return create_node(value, NULL, NULL);
    }
    if(value < node->value){
        node->left = insert_helper(node->left, value);
    } else if (value > node->value){
        node->right = insert_helper(node->right, value);
    }
    
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