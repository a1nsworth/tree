//
// Created by xed22 on 06.10.2022.
//

#include "node.h"

bool isBelong(node n) {
    return n.isBelong;
}

void excludeNode(node *n) {
    n->isBelong = false;
}

void includeNode(node *n) {
    n->isBelong = true;
}

T getValueNode(node n) {
    return n.value;
}

void setValueNode(node *n, T value) {
    n->value = value;
}

node createEmptyNode() {
    return (node) {0, false};
}

node createWithValueWithoutInclude(T value) {
    return (node) {value, false};
}

node createWithValueAndInclude(T value) {
    return (node){value,true};
}
