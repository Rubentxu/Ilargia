#include "BehaviorTree.h"

using namespace bt;


std::string generateUUID() {
    static boost::uuids::random_generator gen;
    auto id = gen();
    return boost::lexical_cast<std::string>(id);
}

BehaviorTree::BehaviorTree(NodePtr root, std::string title, std::string desc) {
    _id          = generateUUID();
    _title = title;
    _description = desc;
    _root        = root;
    _context->_behavior = shared_from_this();
}

Status BehaviorTree::tick(TargetPtr& target, BlackBoardPtr& blackBoard) {
    if(!blackBoard) {
        throw "The blackboard parameter is obligatory and must be an instance of b3.Blackboard";
    }

    _context->_target = target;
    _context->_blackBoard = blackBoard;

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
