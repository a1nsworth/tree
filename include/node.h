//
// Created by xed22 on 06.10.2022.
//

#ifndef LABA7_node_H
#define LABA7_node_H

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>

typedef char T;

int max_int(int a, int b);

typedef struct node {
    T value;
    bool isBelong;
} node;

bool isBelong(node n);

void excludeNode(node *n);

void includeNode(node *n);

T getValueNode(node n);

void setValueNode(node *n, T value);

node createEmptyNode();

node createWithValueWithoutInclude(T value);

node createWithValueAndInclude(T value);

void outputNode(node n);

#endif //LABA7_node_H
