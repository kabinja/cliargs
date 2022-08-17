//
// Created by renaud.rwemalika on 7/6/2022.
//

#ifndef CLIARGS_ARGUMENT_P_H
#define CLIARGS_ARGUMENT_P_H

#include <string>

namespace cliargs{
    class Argument::Impl {
    public:
        Impl(Argument* interface,
                   std::string flag,
                   std::string name,
                   std::string description);

        Argument* m_interface;

        /**
         * The single char flag used to identify the argument.
         * This value (preceded by a dash {-}), can be used to identify
         * an argument on the command line.  The _flag can be blank,
         * in fact this is how unlabeled args work.  Unlabeled args must
         * override appropriate functions to get correct handling. Note
         * that the _flag does NOT include the dash as part of the flag.
         */
        std::string m_flag;

        /**
         * A single word namd identifying the argument.
         * This value (preceded by two dashed {--}) can also be used
         * to identify an argument on the command line.  Note that the
         * _name does NOT include the two dashes as part of the _name. The
         * _name cannot be blank.
         */
        std::string m_name;

        /**
         * Description of the argument.
         */
        std::string m_description;

        /**
         * Indicating whether the argument is required.
         */
        bool m_required;

        /**
         * Label to be used in usage description.  Normally set to
         * "required", but can be changed when necessary.
         */
        std::string m_requireLabel;

        /**
         * Indicates whether a value is required for the argument.
         * Note that the value may be required but the argument/value
         * combination may not be, as specified by _required.
         */
        bool m_valueRequired;

        /**
         * Indicate weather this argument can accept more than one values
         */
        bool m_acceptsMultipleValues;

    private:
        std::weak_ptr<Argument> interface;
    };
}

#endif //CLIARGS_ARGUMENT_P_H
