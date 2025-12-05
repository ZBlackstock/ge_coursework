#include "ParticleSystem.hpp"

using ps = ParticleSystem;

b2WorldId ps::_world_id;

void ps::initialise() {
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = b2Vec2({ 0.0f, gravity });
    _world_id = b2CreateWorld(&world_def);
}

void ps::shutdown() {
    b2DestroyWorld(_world_id);
}

void ps::update(const float& time_step) {
    b2World_Step(_world_id, time_step, sub_step_count);
}

b2WorldId ps::get_world_id() {
    return _world_id;
}

b2ContactEvents ps::get_contact_events() {
    return b2World_GetContactEvents(_world_id);
}

//Convert from b2Vec2 to a Vector2f
const sf::Vector2f ps::bv2_to_sv2(const b2Vec2& in) {
    return sf::Vector2f(in.x * physics_scale, (in.y * physics_scale));
}
//Convert from Vector2f to a b2Vec2
const b2Vec2 ps::sv2_to_bv2(const sf::Vector2f& in) {
    return { in.x * physics_scale_inv, in.y * physics_scale_inv };
}
//Convert from screenspace.y to ps.y (as they are the other way around)
const sf::Vector2f ps::invert_height(const sf::Vector2f& in, const int& game_height) {
    return sf::Vector2f(in.x, game_height - in.y);
}