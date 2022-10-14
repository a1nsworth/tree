//
// Created by xed22 on 07.10.2022.
//

#include "tree.h"

#define IS_EQUAL(a, b) a==b

void test_emptyTree() {
    // Arrange
    tree expected = {NULL, 0, 0};

    // Act
    tree actual = createEmptyTree();

    // Asserts
    assert(IS_EQUAL(getData(&actual), getData(&expected)));
    assert(IS_EQUAL(getSizeTree(actual), getSizeTree(expected)));
    assert(IS_EQUAL(getCurrentIndex(actual), getCurrentIndex(expected)));
}

void test_setCurrentIndexNode() {
    // Arrange
    tree expected = {NULL, 1, 0};
    tree actual = createEmptyTree();

    // Act
    setCurrentIndexNode(&actual, 1);

    // Asserts
    assert(IS_EQUAL(getData(&actual), getData(&expected)));
    assert(IS_EQUAL(getSizeTree(actual), getSizeTree(expected)));
    assert(IS_EQUAL(getCurrentIndex(actual), getCurrentIndex(expected)));
}

void test_allocateMemoryForTree() {
    // Arrange
    node *data = (node *) malloc(10 * sizeof(node));
    tree expected = {data, 0, 10};

    // Act
    tree *actual = allocateMemoryForTree(10);

    // Asserts
    assert(IS_EQUAL(getSizeTree(*actual), getSizeTree(expected)));
    assert(IS_EQUAL(getCurrentIndex(*actual), getCurrentIndex(expected)));
    for (register size_t i = 0; i < getSizeTree(*actual); ++i) {
        assert(IS_EQUAL(getNodeTreeByIndex(*actual, i).isBelong, false));
        assert(IS_EQUAL(getNodeTreeByIndex(*actual, i).value, 0));
    }

    freeTreeMemory(actual);
    freeTreeMemory(&expected);
}

void test_reallocateMemory() {
    // Arrange
    tree *expected = allocateMemoryForTree(5);
    tree *actual = allocateMemoryForTree(10);

    // Act
    reallocateMemory(actual, 5);

    // Asserts
    assert(IS_EQUAL(getSizeTree(*actual), getSizeTree(*expected)));
    assert(IS_EQUAL(getCurrentIndex(*actual), getCurrentIndex(*expected)));
    for (register size_t i = 0; i < getSizeTree(*actual); ++i) {
        assert(IS_EQUAL(getNodeTreeByIndex(*actual, i).isBelong, getNodeTreeByIndex(*expected, i).isBelong));
        assert(IS_EQUAL(getNodeTreeByIndex(*actual, i).value, getNodeTreeByIndex(*expected, i).value));
    }

    freeTreeMemory(actual);
    freeTreeMemory(expected);
}

void test_createTreeFromArray() {
    // Arrange

    // Act
    tree *actual = createTreeFromArray((int[]) {1, 2, 3, 4, 5}, 5);

    // Asserts
    assert(IS_EQUAL(getSizeTree(*actual), 5));
    assert(IS_EQUAL(getCurrentIndex(*actual), 0));
    for (register size_t i = 0; i < getSizeTree(*actual); ++i) {
        assert(IS_EQUAL(getNodeTreeByIndex(*actual, i).isBelong, true));
        assert(IS_EQUAL(getNodeTreeByIndex(*actual, i).value, i + 1));
    }

    freeTreeMemory(actual);
}

void test_getCurrentNodeTree_end() {
    // Arrange
    tree *t = createTreeFromArray((int[]) {1, 2, 3, 4, 5}, 5);
    setCurrentIndexNode(t, getSizeTree(*t) - 1);
    node expected = {5, true};

    // Act
    node actual = getCurrentNodeTree(*t);

    // Asserts
    assert(IS_EQUAL(actual.value, expected.value));
    assert(IS_EQUAL(actual.isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_getCurrentNodeTree_begin() {
    // Arrange
    tree *t = createTreeFromArray((int[]) {1, 2, 3, 4, 5}, 5);
    node expected = {1, true};

    // Act
    node actual = getCurrentNodeTree(*t);

    // Asserts
    assert(IS_EQUAL(actual.value, expected.value));
    assert(IS_EQUAL(actual.isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToRightChild_moveFromRoot() {
    // Arrange
    tree *t = createTreeFromArray((int[]) {1, 2, 3, 4, 5}, 5);
    node expected = {3, true};

    // Act
    moveCurrentIndexToRightChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToRightChild_moveFromRoot2() {
    // Arrange
    tree *t = createTreeFromArray((int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}, 17);
    node expected = {7, true};

    // Act
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToRightChild_moveFromRoot3() {
    // Arrange
    tree *t = createTreeFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27},
            27);
    node expected = {15, true};

    // Act
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToRightChild_moveToLastRightChild() {
    // Arrange
    tree *t = createTreeFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                     28,
                     29, 30, 31}, 31);
    node expected = {31, true};

    // Act
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToLeftChild_moveFromRoot() {
    // Arrange
    tree *t = createTreeFromArray((int[]) {1, 2, 3, 4, 5}, 5);
    node expected = {2, true};

    // Act
    moveCurrentIndexToLeftChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToLeftChild_moveFromRoot2() {
    // Arrange
    tree *t = createTreeFromArray((int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17}, 17);
    node expected = {4, true};

    // Act
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToLeftChild_moveLeftRoot3() {
    // Arrange
    tree *t = createTreeFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27},
            27);
    node expected = {8, true};

    // Act
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToLeftChild_moveToLastLeftChild() {
    // Arrange
    tree *t = createTreeFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                     28,
                     29, 30, 31}, 31);
    node expected = {16, true};

    // Act
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_moveCurrentIndexToRightChild() {
    test_moveCurrentIndexToRightChild_moveFromRoot();
    test_moveCurrentIndexToRightChild_moveFromRoot2();
    test_moveCurrentIndexToRightChild_moveFromRoot3();
    test_moveCurrentIndexToRightChild_moveToLastRightChild();
}

void test_moveCurrentIndexToLeftChild() {
    test_moveCurrentIndexToLeftChild_moveFromRoot();
    test_moveCurrentIndexToLeftChild_moveFromRoot2();
    test_moveCurrentIndexToLeftChild_moveLeftRoot3();
    test_moveCurrentIndexToLeftChild_moveToLastLeftChild();
}

void test_backToRoot() {
    // Arrange
    tree *t = createTreeFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                     28, 29, 30, 31}, 31);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);

    node expected = {1, true};

    // Act
    backToRootTree(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_backToParentFromCurrent_fromLeftChild() {
    // Arrange
    tree *t = createTreeFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                     28, 29, 30, 31}, 31);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    moveCurrentIndexToLeftChild(t);
    node expected = {8, true};

    // Act
    backToParentFromCurrent(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_backToParentFromCurrent_fromRightChild() {
    // Arrange
    tree *t = createTreeFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                     28, 29, 30, 31}, 31);
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);
    moveCurrentIndexToRightChild(t);
    node expected = {15, true};

    // Act
    backToParentFromCurrent(t);

    // Asserts
    assert(IS_EQUAL(getCurrentNodeTree(*t).value, expected.value));
    assert(IS_EQUAL(getCurrentNodeTree(*t).isBelong, expected.isBelong));

    freeTreeMemory(t);
}

void test_backToParentFromCurrent() {
    test_backToParentFromCurrent_fromLeftChild();
    test_backToParentFromCurrent_fromRightChild();
}

void test_isEqualsTrees_twoEmpty() {
    // Arrange
    tree a = createEmptyTree();
    tree b = createEmptyTree();
    bool expected = true;

    // Act
    bool actual = isEqualTrees(a, b);

    // Asserts
    assert(IS_EQUAL(actual, expected));
}

void test_isEqualsTrees_beginNotEqual() {
    // Arrange
    tree *a = createTreeFromArrayNodes((node[]) {{1, true},
                                                 {2, false},
                                                 {3, true},
                                                 {4, false},
                                                 {5, true},
                                                 {6, false}}, 6);
    tree *b = createTreeFromArrayNodes((node[]) {{0, true},
                                                 {2, false},
                                                 {3, true},
                                                 {4, false},
                                                 {5, true},
                                                 {6, false}}, 6);
    bool expected = false;

    // Act
    bool actual = isEqualTrees(*a, *b);

    // Asserts
    assert(IS_EQUAL(actual, expected));
}

void test_isEqualsTrees_endNotEqual() {
    // Arrange
    tree *a = createTreeFromArrayNodes((node[]) {{1, true},
                                                 {2, false},
                                                 {3, true},
                                                 {4, false},
                                                 {5, true},
                                                 {6, true}}, 6);
    tree *b = createTreeFromArrayNodes((node[]) {{1,  true},
                                                 {2,  false},
                                                 {3,  true},
                                                 {4,  false},
                                                 {5,  true},
                                                 {10, true}}, 6);
    bool expected = false;

    // Act
    bool actual = isEqualTrees(*a, *b);

    // Asserts
    assert(IS_EQUAL(actual, expected));
}

void test_isEqualsTrees() {
    test_isEqualsTrees_twoEmpty();
    test_isEqualsTrees_beginNotEqual();
    test_isEqualsTrees_endNotEqual();
}

void test_unionTreesByRoot_twoEmpty() {
    // Arrange
    tree a = createEmptyTree();
    tree b = createEmptyTree();
    int root = 42;

    // Act
    tree *actual = unionTreesByRoot(a, b, root);

    // Asserts
    assert(IS_EQUAL(getSizeTree(*actual), 1));
    assert(IS_EQUAL(getCurrentNodeTree(*actual).value, root));
    assert(isBelong(getCurrentNodeTree(*actual)));

    freeTreeMemory(actual);
}

void test_unionTreesByRoot_rightTreeEmpty() {
    // Arrange
    tree *leftTree = createTreeFromArrayNodes((node[]) {{1, true},
                                                        {2, true},
                                                        {3, true}
    }, 3);
    tree rightTree = createEmptyTree();
    int root = 42;
    tree *expected = createTreeFromArrayNodes((node[]) {
            {root, true},
            {1,    true},
            {0,    false},
            {2,    true},
            {3,    true},}, 5);

    // Act
    tree *actual = unionTreesByRoot(*leftTree, rightTree, root);

    // Asserts
    assert(isEqualTrees(*actual, *expected));

    freeTreeMemory(actual);
    freeTreeMemory(expected);
    freeTreeMemory(leftTree);
}

void test_unionTreesByRoot_leftTreeEmpty() {
    // Arrange
    tree leftTree = createEmptyTree();
    tree *rightTree = createTreeFromArrayNodes((node[]) {{1, true},
                                                         {2, true},
                                                         {3, true},}, 4);
    int root = 42;
    tree *expected = createTreeFromArrayNodes((node[]) {
            {root, true},
            {0,    false},
            {1,    true},
            {0,    false},
            {0,    false},
            {2,    true},
            {3,    true},}, 7);

    // Act
    tree *actual = unionTreesByRoot(leftTree, *rightTree, root);

    // Asserts
    assert(isEqualTrees(*actual, *expected));

    freeTreeMemory(actual);
    freeTreeMemory(expected);
    freeTreeMemory(rightTree);
}

void test_unionTreesByRoot_twoWithOneElement() {
    // Arrange
    tree *leftTree = createTreeFromArray((int[]) {10}, 1);
    tree *rightTree = createTreeFromArray((int[]) {123}, 1);
    int root = 42;
    tree *expected = createTreeFromArray((int[]) {root, 10, 123}, 3);

    // Act
    tree *actual = unionTreesByRoot(*leftTree, *rightTree, root);

    // Asserts
    assert(isEqualTrees(*actual, *expected));

    freeTreeMemory(actual);
    freeTreeMemory(expected);
    freeTreeMemory(leftTree);
    freeTreeMemory(rightTree);
}

void test_unionTreesByRoot_rightWithOneElementAndLeftEmpty() {
    // Arrange
    tree leftTree = createEmptyTree();
    tree *rightTree = createTreeFromArray((int[]) {123}, 1);
    int root = 42;
    tree *expected = createTreeFromArrayNodes((node[]) {
            {root, true},
            {0,    false},
            {123,  true},
    }, 3);

    // Act
    tree *actual = unionTreesByRoot(leftTree, *rightTree, root);

    // Asserts
    assert(isEqualTrees(*actual, *expected));

    freeTreeMemory(actual);
    freeTreeMemory(expected);
    freeTreeMemory(rightTree);
}

void test_unionTreesByRoot_leftWithOneElementAndRightEmpty() {
    // Arrange
    tree *leftTree = createTreeFromArray((int[]) {123}, 1);
    tree rightTree = createEmptyTree();
    int root = 42;
    tree *expected = createTreeFromArray((int[]) {root, 123}, 2);

    // Act
    tree *actual = unionTreesByRoot(*leftTree, rightTree, root);

    // Asserts
    assert(isEqualTrees(*actual, *expected));

    freeTreeMemory(actual);
    freeTreeMemory(expected);
    freeTreeMemory(leftTree);
}

void test_unionTreesByRoot_twoLargeTree() {
    // Arrange
    tree *leftTree = createTreeFromArray((int[]) {0, 2, 4, 6, 8, 10, 12, 14, 16, 18}, 10);
    tree *rightTree = createTreeFromArray((int[]) {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 10);
    int root = 42;
    tree *expected = createTreeFromArrayNodes((node[]) {
            {root, true},
            {0,    true},
            {1,    true},
            {2,    true},
            {4,    true},
            {3,    true},
            {5,    true},
            {6,    true},
            {8,    true},
            {10,   true},
            {12,   true},
            {7,    true},
            {9,    true},
            {11,   true},
            {13,   true},
            {14,   true},
            {16,   true},
            {18,   true},
            {0,    false},
            {0,    false},
            {0,    false},
            {0,    false},
            {0,    false},
            {15,   true},
            {17,   true},
            {19,   true}
    }, 26);

    // Act
    tree *actual = unionTreesByRoot(*leftTree, *rightTree, root);

    // Asserts
    assert(isEqualTrees(*actual, *expected));

    freeTreeMemory(actual);
    freeTreeMemory(expected);
    freeTreeMemory(leftTree);
    freeTreeMemory(rightTree);
}

void test_unionTreesByRoot_leftLargeTreeRightWithOne() {
    // Arrange
    tree *leftTree = createTreeFromArray((int[]) {0, 2, 4, 6, 8, 10, 12, 14, 16, 18}, 10);
    tree *rightTree = createTreeFromArray((int[]) {99}, 1);
    int root = 42;
    tree *expected = createTreeFromArrayNodes((node[]) {
            {root, true},
            {0,    true},
            {99,   true},
            {2,    true},
            {4,    true},
            {0,    false},
            {0,    false},
            {6,    true},
            {8,    true},
            {10,   true},
            {12,   true},
            {0,    false},
            {0,    false},
            {0,    false},
            {0,    false},
            {14,   true},
            {16,   true},
            {18,   true}
    }, 18);

    // Act
    tree *actual = unionTreesByRoot(*leftTree, *rightTree, root);

    // Asserts
    assert(isEqualTrees(*actual, *expected));

    freeTreeMemory(actual);
    freeTreeMemory(expected);
    freeTreeMemory(leftTree);
    freeTreeMemory(rightTree);
}

void test_unionTreesByRoot() {
    test_unionTreesByRoot_twoEmpty();
    test_unionTreesByRoot_rightTreeEmpty();
    test_unionTreesByRoot_leftTreeEmpty();
    test_unionTreesByRoot_twoWithOneElement();
    test_unionTreesByRoot_rightWithOneElementAndLeftEmpty();
    test_unionTreesByRoot_leftWithOneElementAndRightEmpty();
    test_unionTreesByRoot_twoLargeTree();
    test_unionTreesByRoot_leftLargeTreeRightWithOne();
}

void test_tree() {
    test_emptyTree();
    test_setCurrentIndexNode();
    test_allocateMemoryForTree();
    test_reallocateMemory();
    test_createTreeFromArray();
    test_getCurrentNodeTree_begin();
    test_getCurrentNodeTree_end();
    test_moveCurrentIndexToLeftChild();
    test_moveCurrentIndexToRightChild();
    test_backToRoot();
    test_backToParentFromCurrent();
    test_isEqualsTrees();
    test_unionTreesByRoot();
}