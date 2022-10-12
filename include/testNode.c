//
// Created by xed22 on 07.10.2022.
//

#include "node.h"

void test_createEmpty() {
    // Arrange
    node expected = {0, false};

    // Act
    node actual = createEmptyNode();

    // Asserts
    assert(actual.value == expected.value);
    assert(actual.isBelong == expected.isBelong);
}

void test_createWithValueAndInclude() {
    // Arrange
    node expected = {42, true};

    // Act
    node actual = createWithValueAndInclude(42);

    // Asserts
    assert(actual.value == expected.value);
    assert(actual.isBelong == expected.isBelong);
}

void test_createWithValueWithoutInclude() {
    // Arrange
    node expected = {42, false};

    // Act
    node actual = createWithValueWithoutInclude(42);

    // Asserts
    assert(actual.value == expected.value);
    assert(actual.isBelong == expected.isBelong);
}

void test_node() {
    test_createEmpty();
    test_createWithValueAndInclude();
    test_createWithValueWithoutInclude();
}