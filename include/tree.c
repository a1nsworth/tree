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

void setValueTreeByIndex(tree *t, size_t i, T value) {
    assert(i < getSizeTree(*t));

    setValueNode(t->data + i, value);
}

void setRoot(tree *t, T value) {
    assert(!emptyTree(*t));

    setValueTreeByIndex(t, 0, value);
    includeNode(getLinkNodeTreeByIndex(t, 0));
}

node *getLinkNodeTreeByIndex(tree *t, size_t i) {
    assert(i < getSizeTree(*t));

    return t->data + i;
}

node *getLinkCurrentNodeTree(tree *t) {
    return getLinkNodeTreeByIndex(t, getCurrentIndex(*t));
}

void moveCurrentIndexToNext(tree *t) {
    setCurrentIndexNode(t, getCurrentIndex(*t) + 1);
}

tree *unionTreesByRoot(tree leftTree, tree rightTree, T root) {
    static size_t leftIndices[100] = {1};
    static size_t rightIndices[100] = {2};
    writeIndices(leftIndices, getSizeTree(leftTree));
    writeIndices(rightIndices, getSizeTree(rightTree));

    size_t maxSizeLeftTree = findMax(leftTree.data, leftIndices, getSizeTree(leftTree));
    size_t maxSizeRightTree = findMax(rightTree.data, rightIndices, getSizeTree(rightTree));
    size_t size = maxSizeLeftTree > maxSizeRightTree ? maxSizeLeftTree : maxSizeRightTree;
    size++;

    size_t i = 0, j = 0;
    tree *resultUnion = allocateMemoryForTree(size);
    setRoot(resultUnion, root);
    while (getCurrentIndex(leftTree) < getSizeTree(leftTree) || getCurrentIndex(rightTree) < getSizeTree(rightTree)) {
        if (getCurrentIndex(leftTree) < getSizeTree(leftTree)) {
            resultUnion->data[leftIndices[i++]] = getCurrentNodeTree(leftTree);
            moveCurrentIndexToNext(&leftTree);
        }
        if (getCurrentIndex(rightTree) < getSizeTree(rightTree)) {
            resultUnion->data[rightIndices[j++]] = getCurrentNodeTree(rightTree);
            moveCurrentIndexToNext(&rightTree);
        }
    }

    return resultUnion;
}

bool isEqualTrees(tree t1, tree t2) {
    if (getSizeTree(t1) != getSizeTree(t2))
        return false;
    if (emptyTree(t1) && emptyTree(t2))
        return true;
    if (emptyTree(t1) ^ emptyTree(t2))
        return false;

    for (register size_t i = 0; i < getSizeTree(t1); ++i) {
        if (isBelong(getCurrentNodeTree(t1)) ^ isBelong(getCurrentNodeTree(t2))) {
            return false;
        } else if (isBelong(getCurrentNodeTree(t1)) && isBelong(getCurrentNodeTree(t2))) {
            if (getCurrentNodeTree(t1).value != getCurrentNodeTree(t2).value)
                return false;
        }

        moveCurrentIndexToNext(&t1);
        moveCurrentIndexToNext(&t2);
    }

    return true;
}

tree *createTreeFromArrayNodes(node *a, size_t n) {
    tree *t = allocateMemoryForTree(n);

    for (register size_t i = 0; i < n; ++i) {
        t->data[i] = a[i];
    }

    return t;
}

void writeIndices(size_t *a, size_t n) {
    size_t totalElements = 2;
    size_t counter = 0;
    for (register size_t i = 1; i < n;) {
        counter++;
        if (counter < totalElements) {
            if (i & 1)
                a[i] = (a[i >> 1] << 1) + 1;
            else
                a[i] = (a[(i - 1) >> 1] << 1) + 2;

            i++;
        } else {
            counter = 0;
            totalElements <<= 1;
        }
    }
}

size_t findMax(node *source, size_t *other, int n) {
    for (register int i = n - 1; i >= 0; --i) {
        if (isBelong(source[i])) {
            return other[i];
        }
    }

    return 0;
}
