/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rb_tree.h
 * Author: Benjamin
 *
 * Created on April 28, 2017, 11:09 AM
 */

#include <stdbool.h>
#include <stdlib.h>

#ifndef RB_TREE_H
#define RB_TREE_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* RB_TREE_H */
enum compare_result {
    LESS_THAN,
    GREATER_THAN,
    EQUAL_TO
};

struct rb_tree_node_t {
    void *key;
    void *value;
    bool color;
    struct rb_tree_node_t *left; 
    struct rb_tree_node_t *right;
};

struct rb_tree_t{
    struct rb_tree_node_t *root;
    enum compare_result (*rb_comparison_function)(void*, void*);
    size_t size;
};

//iterate function, should move left to right accross the tree
void iterate_tree(struct rb_tree_t*, void (*fn)(void*));

//creates and returns a new empty red black tree
struct rb_tree_t* rb_new(enum compare_result (*compare_value)(void*, void*));

//creates and returns a new node
struct rb_tree_node_t *create_node(void *key, void *value, struct rb_tree_node_t *left, struct rb_tree_node_t *right);

//inserts a new value in sorted order into the red black tree
void rb_insert(struct rb_tree_t*, void *key, void *value);

struct rb_tree_node_t *insert_helper(struct rb_tree_node_t *node, void *key, void *value, enum compare_result (*compare_value)(void*, void*));

//if the value exists in the tree, deletes that value from the tree


//returns true if value is found in tree
bool rb_search(struct rb_tree_t*, void *value);

//checks if node is red
bool is_red(struct rb_tree_node_t *node);

//rotates a node to the left
struct rb_tree_node_t *rotate_left(struct rb_tree_node_t *base);

//rotates a node to the right
struct rb_tree_node_t *rotate_right(struct rb_tree_node_t *base);

//flips colors
void flip_colos(struct rb_tree_node_t *node);

//key, value functions
void *rb_get(struct rb_tree_t*, void *key);

void rb_put(struct rb_tree_t*, void *key, void *value);

void rb_delete(struct rb_tree_t*, void *key);

void *rb_keys(struct rb_tree_t*);

void *rb_values(struct rb_tree_t*);