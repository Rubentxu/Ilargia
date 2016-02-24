#include "BehaviorTree.h"

using namespace bt;


std::string bt::generateUUID() {
    static boost::uuids::random_generator gen;
    auto id = gen();
    return boost::lexical_cast<std::string>(id);
}

BehaviorTree::BehaviorTree(NodePtr root, std::string title, std::string desc)
        : _title{title}, _description{desc}, _root{std::move(root)}{
    _id = generateUUID();
}

Status BehaviorTree::tick(TargetPtr& target, BlackBoardPtr& blackBoard) {
    if(!blackBoard) {
        throw "The blackboard parameter is obligatory and must be an instance of b3.Blackboard";
    }

   // Status state = _root->ex

}



/* CREATE A TICK OBJECT *//*


/* TICK NODE *//*

    var state = this.root._execute(tick);

    */
/* CLOSE NODES FROM LAST TICK, IF NEEDED *//*

    var lastOpenNodes = blackboard.get('openNodes', this.id);
    var currOpenNodes = tick._openNodes.slice(0);

    // does not close if it is still open in this tick
    var start = 0;
    var i;
    for (i=0; i<Math.min(lastOpenNodes.length, currOpenNodes.length); i++) {
        start = i+1;
        if (lastOpenNodes[i] !== currOpenNodes[i]) {
            break;
        }
    }

    // close the nodes
    for (i=lastOpenNodes.length-1; i>=start; i--) {
        lastOpenNodes[i]._close(tick);
    }

    */
/* POPULATE BLACKBOARD *//*

    blackboard.set('openNodes', currOpenNodes, this.id);
    blackboard.set('nodeCount', tick._nodeCount, this.id);

    return state;
}*/
