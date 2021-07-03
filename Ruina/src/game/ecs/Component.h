#pragma once
#include "Entity.h"

struct Component {
private:
    Entity entity_id = 0;

    friend class Manager;
};