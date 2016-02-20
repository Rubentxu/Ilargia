#include "Context.h"


void Context::enterNode(NodePtr node) {
    _nodeCount++;
    _openNodes.insert(node);
}

void Context::exitNode(NodePtr node) {}

void Context::openNode(NodePtr node) {}

void Context::closeNode(NodePtr node) {
    _nodeCount--;
    _openNodes.erase(node);
}

void  Context::tickNode(NodePtr node) {}
