#pragma once

template<typename Derived>
struct EventHolderHook {
protected:
    using PrefixFuncType = bool(void);
    using PostfixFuncType = void(void);
};

template<typename Derived, typename T, typename ...Args>
struct EventHolderHookArgsR {
protected:
    using PrefixFuncType = bool(T& returnValue, Args... args);
    using PostfixFuncType = void(T& returnValue, Args... args);
};

template<typename Derived, typename ...Args>
struct EventHolderHookArgs {
protected:
    using PrefixFuncType = bool(Args... args);
    using PostfixFuncType = void(Args... args);
};

template<typename Derived, typename T>
struct EventHolderHookR {
protected:
    using PrefixFuncType = bool(T& returnValue);
    using PostfixFuncType = void(T& returnValue);
};