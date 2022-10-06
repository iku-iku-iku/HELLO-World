//
// Created by iku-iku-iku on 2022/10/2.
//


#pragma once


#include <functional>
#include <vector>
#include <Editor/Input.h>

namespace core {
    template<typename ArgT>
    class Listener {
    public:
        typedef std::function<void (const ArgT &)> Handler;
        typedef unsigned int Id_T;

        typename Handler::result_type operator()(const ArgT &arg) const {
            m_Handler(arg);
        }

        explicit Listener(const Handler& handler) : m_Handler(handler) {
            static Id_T Idx = 0;
            m_Id = Idx++;
        }

        Listener() = default;

        template<typename OtherT>
        bool operator==(const Listener<OtherT> &rhs) {
            return m_Id == rhs.m_Id;
        }

    private:
        Handler m_Handler;
        Id_T m_Id{};
    };

    template<typename ArgT>
    class Event {
    public:
        typedef Listener<ArgT> Listener_T;

        void AddListener(const Listener_T &listener) { m_Listeners.push_back(listener); }

        bool RemoveListener(const Listener_T &listener) {
            int origin = m_Listeners.size();
            int after = std::remove(m_Listeners.begin(), m_Listeners.end(), listener) - m_Listeners.begin();
            return origin > after;
        }

        void Broadcast(const ArgT &keyStatus) {
            for (const auto &listener: m_Listeners) { listener(keyStatus); }
        }

        Event() = default;

    private:
        std::vector<Listener_T> m_Listeners;
    };
}
