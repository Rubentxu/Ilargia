#ifndef BlackBoard_H
#define BlackBoard_H

#include <string>
#include <map>
#include <set>
#include <memory>
#include <boost/any.hpp>

class Node;

using Memory = std::map<std::string, boost::any>;
using NodePtr = std::shared_ptr<Node>;

struct TreeMemory : public Memory {
    Memory nodeMemory;
    std::set<NodePtr> openNodes;
    int traversalDepth = 0;
    int traversalCycle = 0;
};

class BlackBoard {
    Memory baseMemory;
    std::map<std::string, TreeMemory> treeMemories;

    TreeMemory& getTreeMemory(std::string treeScope);

    Memory& getNodeMemory(TreeMemory &treeMemory, std::string nodeScope);

public:
    BlackBoard() { };

    BlackBoard(BlackBoard const &s) = delete;

    void operator=(BlackBoard const &x) = delete;

    Memory& getMemory(std::string treeScope = "", std::string nodeScope = "");

    template<typename T>
    T& getParam(std::string name, std::string treeScope = "", std::string nodeScope = "") {
        auto &memory = getMemory(treeScope, nodeScope);
        auto result = memory.find(name);
        if (result == memory.end() || result->second.type() != typeid(T) ) {
            T* val = new T{};
            return *val ;
        } else {
            return boost::any_cast<T &>(result->second);
        }

    }

    template<class ...Args>
    bool setParam(std::string name,  Args && ...value) {
        auto &memory = getMemory();
        return memory.emplace(std::string(name), boost::any(std::forward<Args>(value)...)).second;
        //OnPropertyChanged(name);
    }
};

#endif //BlackBoard_H
