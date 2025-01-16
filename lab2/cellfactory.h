#pragma once

#include <memory>
#include <map>
#include <functional>
#include "cell.h"

template <typename AbstractProduct, typename IdentifierType, typename ProductCreator>
class CellFactory {
public:
    bool Register(const IdentifierType& id, ProductCreator creator) {
        return creators_.emplace(id, creator).second;
    }

    std::unique_ptr<AbstractProduct> Create(const IdentifierType& id) {
        auto it = creators_.find(id);
        if (it != creators_.end()) {
            return (it->second)();
        }
        return nullptr;
    }

private:
    std::map<IdentifierType, ProductCreator> creators_;
};
