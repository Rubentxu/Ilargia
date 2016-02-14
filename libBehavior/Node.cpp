#include "Node.h"


void Context::enterNode(Node &node)  {
    _nodeCount++;
    _openNodes[node.getId()] = node;
}

void Context::exitNode(Node &node) {/* TODO: call debug here*/}

void Context::openNode(Node &node) {/* TODO: call debug here*/}

void Context::closeNode(Node &node)  {
    _openNodes.erase(node.getId());
}

void Context::contextNode(Node &node) {/* TODO: call debug here*/}


