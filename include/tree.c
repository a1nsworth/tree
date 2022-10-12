//
// Created by xed22 on 06.10.2022.
//

#include "tree.h"

bool emptyTree(tree t) {
    return t.size == 0;
}

size_t getSizeTree(tree t) {
    return t.size;
}

tree createEmptyTree() {
    return (tree) {NULL, 0, 0};
}

tree *allocateMemoryForTree(size_t n) {
    tree *result = (tree *) malloc(sizeof(tree));
    result->data = (node *) malloc(n * sizeof(node));
    setCurrentIndexNode(result, 0);
    result->size = n;

    for (register size_t i = 0; i < n; ++i) {
        result->data[i] = createEmptyNode();
    }

    return result;
}

void freeTreeMemory(tree *t) {
    free(t->data);
    t->size = 0;
}

void reallocateMemory(tree *t, size_t n) {
    t->data = (node *) realloc(t->data, n * sizeof(node));
    t->size = n;
}

size_t getCurrentIndex(tree t) {
    return t.currentIndexElement;
}

void setCurrentIndexNode(tree *t, size_t newIndex) {
    t->currentIndexElement = newIndex;
}

void moveCurrentIndexToRightChild(tree *t) {
    assert(!emptyTree(*t));
    assert(isBelong(getNodeTreeByIndex(*t, getCurrentIndex(*t) + RIGHT_CHILD_STEP)));

    setCurrentIndexNode(t, GET_INDEX_RIGHT_CHILD(t->currentIndexElement));
}

void moveCurrentIndexToLeftChild(tree *t) {
    assert(!emptyTree(*t));
    assert(isBelong(getNodeTreeByIndex(*t, getCurrentIndex(*t) + LEFT_CHILD_STEP)));

    setCurrentIndexNode(t, GET_INDEX_LEFT_CHILD(t->currentIndexElement));
}

node getNodeTreeByIndex(tree t, size_t i) {
    assert(i < getSizeTree(t));

    return t.data[i];
}

node getCurrentNodeTree(tree t) {
    return getNodeTreeByIndex(t, getCurrentIndex(t));
}

bool existLeftSon(tree t, size_t indexParent) {
    assert(indexParent < getSizeTree(t));

    return isBelong(getNodeTreeByIndex(t, GET_INDEX_LEFT_CHILD(indexParent)));
}

bool existRightSon(tree t, size_t indexParent) {
    assert(indexParent < getSizeTree(t));

    return isBelong(getNodeTreeByIndex(t, GET_INDEX_RIGHT_CHILD(indexParent)));
}

tree *createTreeFromArray(T *a, size_t n) {
    tree *t = allocateMemoryForTree(n);

    for (register size_t i = 0; i < n; ++i) {
        t->data[i] = createWithValueAndInclude(a[i]);
    }

    return t;
}

void backToParentFromLeftChild(tree *t) {
    assert(getCurrentIndex(*t) != 0);
    assert(!emptyTree(*t));

    setCurrentIndexNode(t, t->currentIndexElement >> 1);
}

void backToParentFromRightChild(tree *t) {
    assert(getCurrentIndex(*t) != 0);
    assert(!emptyTree(*t));

    setCurrentIndexNode(t, (t->currentIndexElement - 1) >> 1);
}

void backToParentFromCurrent(tree *t) {
    if (t->currentIndexElement & 1)
        backToParentFromLeftChild(t);
    else
        backToParentFromRightChild(t);
}

void excludeNodeByIndex(tree *t, size_t i) {
    assert(i < getSizeTree(*t));

    excludeNode(t->data + i);
}

node *getData(tree *t) {
    return t->data;
}

void backToRootTree(tree *t) {
    assert(!emptyTree(*t));

    setCurrentIndexNode(t, 0);
}

void excludeCurrentNodeTree(tree *t) {
    assert(!emptyTree(*t));

    excludeNode(t->data + getCurrentIndex(*t));
}
