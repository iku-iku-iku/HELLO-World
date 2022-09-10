//
// Created by code4love on 2022/9/5.
//

#ifndef HELLO_TESTMENU_H
#define HELLO_TESTMENU_H

#include <memory>
#include <functional>
#include "Test.h"
#include "vector"

namespace test {

    class TestMenu : public Test {
    public:
        TestMenu() = default;

        ~TestMenu() override;

        void OnUpdate(float deltaTime) override;

        void OnRender(float currentTime) override;

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const char *name) {
            testOptions.template emplace_back(name, [] { return std::make_unique<T>(); });
        }

    private:
        std::unique_ptr<Test> currentTest;
        typedef std::pair<const char *, std::function<std::unique_ptr<Test>()>> Option;
        std::vector<Option> testOptions;
    };
}

#endif //HELLO_TESTMENU_H
