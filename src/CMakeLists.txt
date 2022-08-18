add_library(cliargs "")

target_sources(
        cliargs
        PRIVATE
        Constraint.cpp
        CommandLine.cpp
        Argument.cpp
        Argument_p.h
        AnyOf.cpp
        GroupConstraint.cpp
        OneOf.cpp
        exceptions.cpp
        VisitorUtils.cpp
        VisitorUtils.h
        ParserUtils.cpp
        ParserUtils.h
)

target_include_directories(cliargs PUBLIC include)