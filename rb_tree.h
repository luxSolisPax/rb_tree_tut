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

struct rb_tree_node_t {
    int value;
    bool color;
    struct rb_tree_node_t *left; 
    struct rb_tree_node_t *right;
};

struct rb_tree_t{
    struct rb_tree_node_t *root;
    size_t size;
};

//creates and returns a new empty red black tree
struct rb_tree_t* rb_new();

//creates and returns a new node
struct rb_tree_node_t *create_node(int value, struct rb_tree_node_t *left, struct rb_tree_node_t *right);

//inserts a new value in sorted order into the red black tree
void rb_insert(struct rb_tree_t*, int value);

struct rb_tree_node_t *insert_helper(struct rb_tree_node_t *node, int value);

//if the value exists in the tree, deletes that value from the tree
void rb_delete(struct rb_tree_t*, int value);

//returns true if value is found in tree
bool rb_search(struct rb_tree_t*, int value);

//checks if node is red
bool is_red(struct rb_tree_node_t *node);

//rotates a node to the left
struct rb_tree_node_t *rotate_left(struct rb_tree_node_t *base);

//rotates a node to the right
struct rb_tree_node_t *rotate_right(struct rb_tree_node_t *base);

//flips colors
void flip_colors(struct rb_tree_node_t *node);