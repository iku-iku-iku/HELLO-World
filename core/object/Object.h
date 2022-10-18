//
// Created by iku-iku-iku on 2022/10/17.
//


#pragma once

#include "vector"
#include <memory>
#include "component/Component.h"

namespace core {

    class Object {
    public:
        template<typename Comp, typename... Args>
        Comp* AddComponent(Args... args) {
            Comp* t = new Comp(args...);
            m_Components.push_back(std::unique_ptr<Component>(t));
            return t;
        }

        template<typename Comp>
        Comp *GetComponent() {
            for (const auto &item: m_Components) {
                Comp *ret = dynamic_cast<Comp *>(item.get());
                if (ret != nullptr) {
                    return ret;
                }
            }
            return nullptr;
        }

    private:
        std::vector<std::unique_ptr<Component>> m_Components;
    };
}
