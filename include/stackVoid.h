//
// Created by xed22 on 14.10.2022.
//

#ifndef LABA7_STACKVOID_H
#define LABA7_STACKVOID_H

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>

typedef struct stackVoid {
    void **data;
    size_t capacity;
    size_t size;
    size_t indexForPush;
} stackVoid;

size_t getSize_stackVoid(stackVoid s);

bool empty_stackVoid(stackVoid s);

size_t getIndexForPush(stackVoid s);

size_t getCapacity_stackVoid(stackVoid s);

size_t full_stackVoid(stackVoid s);

stackVoid createEmpty_stackVoid();

stackVoid *create_stackVoid(size_t n);

void reallocate_stackVoid(stackVoid *s, size_t n);

void pushBack_stackVoid(stackVoid *s, void *value);

void popBack_stackVoid(stackVoid *s);

void clear_stackVoid(stackVoid *s);

void *top(stackVoid s);

#endif //LABA7_STACKVOID_H
