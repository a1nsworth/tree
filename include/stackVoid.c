//
// Created by xed22 on 14.10.2022.
//

#include "stackVoid.h"

size_t getSize_stackVoid(stackVoid s) {
    return s.size;
}

bool empty_stackVoid(stackVoid s) {
    return getSize_stackVoid(s) == 0;
}

size_t getIndexForPush(stackVoid s) {
    return s.indexForPush;
}

size_t getCapacity_stackVoid(stackVoid s) {
    return s.capacity;
}

size_t full_stackVoid(stackVoid s) {
    return getIndexForPush(s) == getCapacity_stackVoid(s) && !empty_stackVoid(s);
}

stackVoid createEmpty_stackVoid() {
    return (stackVoid) {NULL, 0, 0, 0};
}

stackVoid *create_stackVoid(size_t n) {
    stackVoid *stack = (stackVoid *) malloc(sizeof(stackVoid));
    stack->data = (void **) malloc(sizeof(void *) * n);
    stack->capacity = n;
    stack->size = 0;
    stack->indexForPush = 0;

    return stack;
}


void pushBack_stackVoid(stackVoid *s, void *value) {
    if (full_stackVoid(*s)) {
        reallocate_stackVoid(s, s->size << 1);
    } else if (empty_stackVoid(*s)) {
        reallocate_stackVoid(s, 1);
    }

    s->data[getIndexForPush(*s)] = value;
    s->indexForPush++;
    s->size++;
}

void popBack_stackVoid(stackVoid *s) {
    assert(!empty_stackVoid(*s));

    s->indexForPush--;
    s->size--;
}

void reallocate_stackVoid(stackVoid *s, size_t n) {
    s->data = (void **) realloc(s->data, n * sizeof(void *));
    s->capacity = n;
}

void clear_stackVoid(stackVoid *s) {
    s->size = 0;
}

void *top(stackVoid s) {
    assert(!empty_stackVoid(s));
    return s.data[getIndexForPush(s) - 1];
}
