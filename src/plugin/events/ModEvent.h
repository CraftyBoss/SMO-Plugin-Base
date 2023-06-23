#pragma once

// Event Holder types for events that are triggered by the main plugin loader (ex: debug drawing)

// EventHolderMod      - Event Holder for events with no return type and no arguments
// EventHolderModArgsR - Event holder for events with a return type and arguments
// EventHolderModArgs  - Event holder for events with no return type and arguments
// EventHolderModR     - Event holder for events with a return type and no arguments
// Note: this isn't the most preferable solution to how I'd like to go about this, but it works well enough for now.

template <typename Derived>
struct EventHolderMod {
protected:
    using BaseEventFunc = void();
};

template<typename Derived, typename T, typename ...Args>
struct EventHolderModArgsR {
protected:
    using BaseEventFunc = bool(T& returnValue, Args... args);
};

template<typename Derived, typename ...Args>
struct EventHolderModArgs {
protected:
    using BaseEventFunc = void(Args... args);
};

template<typename Derived, typename R>
struct EventHolderModR {
protected:
    using BaseEventFunc = void(R& returnValue);
};