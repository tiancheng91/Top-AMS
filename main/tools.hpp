#pragma once
#include <chrono>
#include <thread>
#include <atomic>
// #define NO_DEBUG

#ifndef NO_DEBUG
// #include <WString.h>
#include <iostream>
#endif// !NO_DEBUG



namespace mstd {

#ifdef NO_DEBUG
    template <typename T, typename... V>
    inline constexpr void fpr(T&& a, V&&... v) {}// fpr
#else
    template <typename T>
    inline constexpr void fpr(T&& x) {
        std::cout << std::forward<T>(x) << std::endl;
    }
    template <typename T, typename... V>
    inline constexpr void fpr(T&& a, V&&... v) {
        std::cout << std::forward<T>(a);
        fpr(std::forward<V>(v)...);
    }// fpr

    inline constexpr void fpr(const String& x) {
        std::cout << x.c_str() << std::endl;
    }
    inline constexpr void fpr(String&& x) {
        std::cout << x.c_str() << std::endl;
    }

    // 未来可考虑扩展到web前端输出
#endif// NO_DEBUG




    template <typename T>
    inline void delay(const T& t) {
        std::this_thread::sleep_for(t);
    }

    inline void delay(const int& t) {
        std::this_thread::sleep_for(std::chrono::milliseconds(t));// 整数类型，假设是毫秒
    }

    struct call_once {
        template <typename F, typename... V>
        call_once(const F& f, V&&... v) { f(std::forward<V>(v)...); }
    };


    template <typename T>
    void atomic_wait_un(std::atomic<T>& value, T target) {//@_@可以考虑加入mstd
        auto old_value = value.load();
        while (old_value != target) {
            value.wait(old_value);
            old_value = value;
        }
    }

    // 带超时的atomic_wait_un，防止永久等待导致死锁
    template <typename T, typename Rep, typename Period>
    bool atomic_wait_un_timeout(std::atomic<T>& value, T target, const std::chrono::duration<Rep, Period>& timeout) {
        auto deadline = std::chrono::steady_clock::now() + timeout;
        auto old_value = value.load();
        while (old_value != target) {
            auto remaining = deadline - std::chrono::steady_clock::now();
            if (remaining <= std::chrono::duration<Rep, Period>::zero()) {
                return false; // 超时
            }
            // 使用wait_for等待，返回值表示是否在超时前被唤醒
            // 即使被唤醒，也需要重新检查值是否等于目标值
            value.wait_for(old_value, remaining);
            old_value = value.load();
            // 如果已经超时，退出循环
            if (std::chrono::steady_clock::now() >= deadline) {
                return false; // 超时
            }
        }
        return true; // 成功等待到目标值
    }

}// mstd

using mstd::fpr;
using namespace std::literals::chrono_literals;
