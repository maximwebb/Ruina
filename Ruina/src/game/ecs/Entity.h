#pragma once

struct Entity {
//	inline Entity() : id(-1) {};

    inline Entity(int id) : id(id) {};

    int32_t id;

    operator int32_t () const {
        return id;
    }

    bool operator==(const Entity& other) const {
        return other.id == id;
    }
};

namespace std {
    template<> struct hash<Entity> {
        std::size_t operator()(Entity const& e) const noexcept {
            return e.id;
        }
    };
}