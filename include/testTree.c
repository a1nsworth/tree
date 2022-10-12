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
}