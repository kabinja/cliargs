//
// Created by renau on 8/19/2022.
//

#include "validators.h"
#include "VisitorUtils.h"

cliargs::UniqueName::UniqueName(std::shared_ptr <OneOf> root){
    m_root = std::move(root);
}

void cliargs::UniqueName::validate() {
    CollectArgumentsVisitor visitor;

    for(const auto& constraint: *m_root){
        std::visit(visitor, asVariant(constraint));
    }
}