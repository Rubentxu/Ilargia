#include "Context.h"

using namespace bt;

void Context::enterNode(NodePtr node) {
    _openNodes.insert(node);
}

void Context::exitNode(NodePtr node) {}

void Context::openNode(NodePtr node) {}

void Context::closeNode(NodePtr node) {
    _openNodes.erase(node);
}

void  Context::tickNode(NodePtr node) {}
