//
// Created by renaud.rwemalika on 7/6/2022.
//

#ifndef CLIARGS_VISITOR_H
#define CLIARGS_VISITOR_H

namespace cliargs {

    /**
     * A base class that defines the interface for visitors.
     */
    class Visitor {
    public:
        Visitor() = default;
        virtual ~Visitor() = default;

        /**
         * Callback from the visited nodes to the visitor.
         */
        virtual void visit() = 0;
    };
}  // namespace Argument

#endif //CLIARGS_VISITOR_H
