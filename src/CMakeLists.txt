add_library(cliargs "")

target_sources(
        cliargs
        PRIVATE
        AnyOf.cpp
        Argument.cpp
        Argument_p.h
        CommandLine.cpp
        Constraint.cpp
        exceptions.cpp
        GroupConstraint.cpp
        OneOf.cpp
        ParserUtils.cpp
        ParserUtils.h
        validators.h
        validators.cpp
        VisitorUtils.cpp
        VisitorUtils.h
)

target_include_directories(cliargs PUBLIC include)