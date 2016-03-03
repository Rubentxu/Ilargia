#ifndef BlackBoard_H
#define BlackBoard_H

#include <string>
#include <map>
#include <set>
#include <memory>
#include <boost/any.hpp>

namespace bt {
    using Memory = std::map<std::string, boost::any>;

    struct TreeMemory : public Memory {
        std::map<std::string, Memory> nodeMemories;
        int traversalDepth = 0;
        int traversalCycle = 0;
    };

    class BlackBoard {
        Memory baseMemory;
        std::map<std::string, TreeMemory> treeMemories;

        TreeMemory &getTreeMemory(std::string treeScope);

        Memory &getNodeMemory(std::map<std::string, Memory> &nodeMemories, std::string nodeScope);

    public:
        BlackBoard() { };

        Memory &getMemory(std::string treeScope = "", std::string nodeScope = "");

        template<typename T>
        T& getParam(std::string name, std::string treeScope = "", std::string nodeScope = "") {
            auto &memory = getMemory(treeScope, nodeScope);
            auto it = memory.lower_bound(name);
            if (it == memory.end() || it->first != name || it->second.type() != typeid(T)) {
                auto it2 = memory.insert(it, std::make_pair(name, T{}));
                return boost::any_cast<T&>(it2->second);

            }
            return boost::any_cast<T&>(it->second);

        }

        template<class T>
        void setParam(std::string name, T &&value, std::string treeScope = "", std::string nodeScope = "") {
            auto &memory = getMemory(treeScope, nodeScope);
            auto it = memory.lower_bound(name);
            if (it == memory.end() || (it->first != name && it->second.type() != typeid(T))) {
                memory.insert(it, std::make_pair(name, value));
            } else if (it->second.type() == typeid(T)) {
                it->second = value;
                //OnPropertyChanged(name);
            }
        }


    };



};
#endif //BlackBoard_H
