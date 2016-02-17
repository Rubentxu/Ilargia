#include "BlackBoard.h"
#include <boost/any.hpp>


TreeMemory& BlackBoard::getTreeMemory(std::string treeScope) {
    auto treeMemory =  treeMemories.find(treeScope);
    if(treeMemory == treeMemories.end()) {
        treeMemories.insert(std::make_pair(treeScope, TreeMemory{}));
        return treeMemories.find(treeScope)->second;
    }
    return treeMemory->second;
}

Memory& BlackBoard::getNodeMemory(TreeMemory &treeMemory, std::string nodeScope) {
    return treeMemory.nodeMemory;
}

Memory& BlackBoard::getMemory(std::string treeScope, std::string nodeScope) {
    Memory &memory = baseMemory;
    if (!treeScope.empty()) {
        TreeMemory &treeMemory = getTreeMemory(treeScope);
        if (!nodeScope.empty()) {
            return getNodeMemory(treeMemory, nodeScope);
        }
        return treeMemory;
    }
    return memory;
}
