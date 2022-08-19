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

    for(auto it1 = visitor.begin(); visitor.end() != it1; ++it1){
        auto it2 = it1;
        for(++it2; it2 != visitor.end(); ++it2){
            if(it1->get()->getName() == it2->get()->getName() || it1->get()->getFlag() == it2->get()->getFlag()){
                throw ValidationException("Duplicated identifier", it2->get()->toString());
            }
        }
    }
}