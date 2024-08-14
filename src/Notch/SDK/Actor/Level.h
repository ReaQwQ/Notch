#pragma once

#include <iostream>
#include <optional>
#include "Actor.h"
class Level {
public:
    virtual std::vector<Actor*, std::allocator<Actor*>> getRuntimeActorList() {
        static uintptr_t func = (*reinterpret_cast<uintptr_t**>(this))[278];
        static auto getRuntimeActorList = *(decltype(&Level::getRuntimeActorList)*)&func;
        return (this->*getRuntimeActorList)();
    };
};
