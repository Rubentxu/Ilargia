#include "BlackBoard.h"
#include <boost/any.hpp>

using namespace bt;

TreeMemory& BlackBoard::getTreeMemory(std::string treeScope) {
  /*  auto treeMemory =  treeMemories.find(treeScope);
    if(treeMemory == treeMemories.end()) {
        return treeMemories.insert(std::make_pair(treeScope, TreeMemory{}));
        return treeMemories.find(treeScope)->second;
    }
    return treeMemory->second;*/
    auto it = treeMemories.lower_bound(treeScope);

    if (it == treeMemories.end() || it->first != treeScope) {
        return treeMemories.insert(it, std::make_pair(treeScope,TreeMemory{}))->second;
    }
    return it->second;

}

Memory& BlackBoard::getMemory(std::string treeScope, std::string nodeScope) {
    Memory &memory = baseMemory;
    if (!treeScope.empty()) {
        TreeMemory &treeMemory = getTreeMemory(treeScope);
        if (!nodeScope.empty()) {
            return treeMemory.nodeMemory;
        }
        return treeMemory;
    }
    return memory;
}
