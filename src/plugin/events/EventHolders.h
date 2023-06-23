#pragma once

#include "ModEvent.h"
#include "HookEvent.h"

#define CREATE_HOOK_EVENT(Name, HookVal) \
struct Name : public EventHolderHook<Name> { \
    static EXPORT_SYM bool addEvent(EventHolderHook<Name>::PrefixFuncType prefixFunc, EventHolderHook<Name>::PostfixFuncType postfixFunc);   \
};

#define CREATE_HOOK_EVENT_ARGSR(Name, HookVal, ReturnType, ...) \
struct Name : public EventHolderHookArgsR<Name, ReturnType, __VA_ARGS__> { \
    static bool addEvent(EventHolderHookArgsR<Name, ReturnType, __VA_ARGS__>::PrefixFuncType prefixFunc,          \
                             EventHolderHookArgsR<Name, ReturnType, __VA_ARGS__>::PostfixFuncType postfixFunc);   \
};

#define CREATE_HOOK_EVENT_ARGS(Name, HookVal, ...) \
struct Name : public EventHolderHookArgs<Name, __VA_ARGS__> { \
    static bool addEvent(EventHolderHookArgs<Name, __VA_ARGS__>::PrefixFuncType prefixFunc, EventHolderHookArgs<Name, __VA_ARGS__>::PostfixFuncType postfixFunc); \
};

#define CREATE_HOOK_EVENT_R(Name, HookVal, ReturnType) \
struct Name : public EventHolderHookR<Name, ReturnType> { \
    static EXPORT_SYM bool addEvent(EventHolderHookR<Name, ReturnType>::PrefixFuncType prefixFunc, EventHolderHookR<Name, ReturnType>::PostfixFuncType postfixFunc);   \
};

#define CREATE_MOD_EVENT(Name) \
struct Name : public EventHolderMod<Name> { \
    static EXPORT_SYM bool addEvent(EventHolderMod<Name>::BaseEventFunc event); \
};

#define CREATE_MOD_EVENT_ARGSR(Name, ReturnType, ...) \
struct Name : public EventHolderModArgsR<Name, ReturnType, __VA_ARGS__> { \
    static bool addEvent(EventHolderModArgsR<Name, ReturnType, __VA_ARGS__>::BaseEventFunc& event); \
};

#define CREATE_MOD_EVENT_ARGS(Name, ...) \
struct Name : public EventHolderModArgs<Name, __VA_ARGS__> { \
    static bool addEvent(EventHolderModArgs<Name, __VA_ARGS__>::BaseEventFunc& event); \
};

#define CREATE_MOD_EVENT_R(Name, ReturnType) \
struct Name : public EventHolderModR<Name, ReturnType> { \
    static bool addEvent(EventHolderModR<Name, ReturnType>::BaseEventFunc& event); \
};
