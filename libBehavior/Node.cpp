#include "Node.h"


Status Node::execute(ContextPtr &context) {
    enter(context);

    //if(context->_blackBoard->getParam<bool>(std::string{"isOpen"},"",""));
}


/*    _execute: function(tick) {
      // ENTER
      this._enter(tick);

      // OPEN
      if (!tick.blackboard.get('isOpen', tick.tree.id, this.id)) {
          this._open(tick);
      }

      // TICK
      var status = this._tick(tick);

      // CLOSE
      if (status !== b3.RUNNING) {
          this._close(tick);
      }

      // EXIT
      this._exit(tick);

      return status;
    },
    */