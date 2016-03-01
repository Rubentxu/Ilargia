#include "BlackBoard.h"

using namespace bt;


TreeMemory& BlackBoard::getTreeMemory(std::string treeScope) {
    auto it = treeMemories.lower_bound(treeScope);
    if (it == treeMemories.end() || it->first != treeScope){
        return treeMemories.insert(it, std::make_pair(treeScope, TreeMemory{}))->second;
    }
    return it->second;

}

Memory& BlackBoard::getNodeMemory(std::map<std::string, Memory> &nodeMemories, std::string nodeScope) {
    auto it = nodeMemories.lower_bound(nodeScope);
    if (it == nodeMemories.end() || it->first != nodeScope) {
        return nodeMemories.insert(it, std::make_pair(nodeScope, Memory{}))->second;
    }
    return it->second;
}

Memory& BlackBoard::getMemory(std::string treeScope, std::string nodeScope) {
    Memory &memory = baseMemory;
    if (!treeScope.empty()) {
        TreeMemory &treeMemory = getTreeMemory(treeScope);
        if (!nodeScope.empty()) {
            return getNodeMemory(treeMemory.nodeMemories, nodeScope);
        }
        return treeMemory;
    }
    return memory;
}
