//
// Created by xed22 on 06.10.2022.
//

#ifndef LABA7_TREE_H
#define LABA7_TREE_H

#include "node.h"

#define GET_INDEX_LEFT_CHILD(root) ((root << 1) + 1)
#define GET_INDEX_RIGHT_CHILD(root) ((root << 1) + 2)
#define LEFT_CHILD_STEP 1
#define RIGHT_CHILD_STEP 2

typedef struct tree {
    node *data;
    size_t currentIndexElement;
    size_t size;
} tree;

bool emptyTree(tree t);

size_t getCurrentIndex(tree t);

void setCurrentIndexNode(tree *t, size_t newIndex);

size_t getSizeTree(tree t);

tree createEmptyTree();

tree *allocateMemoryForTree(size_t n);

void freeTreeMemory(tree *t);

void reallocateMemory(tree *t, size_t n);

node getNodeTreeByIndex(tree t, size_t i);

node getCurrentNodeTree(tree t);

void moveCurrentIndexToRightChild(tree *t);

void moveCurrentIndexToLeftChild(tree *t);

bool existLeftSon(tree t, size_t indexParent);

bool existRightSon(tree t, size_t indexParent);

tree *createTreeFromArray(T *a, size_t n);

void backToParentFromLeftChild(tree *t);

void backToParentFromRightChild(tree *t);

void backToParentFromCurrent(tree *t);

void backToRootTree(tree *t);

void excludeNodeByIndex(tree *t, size_t i);

void excludeCurrentNodeTree(tree *t);

node *getData(tree *t);

#endif //LABA7_TREE_H
