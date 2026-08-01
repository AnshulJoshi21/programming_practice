#pragma once

#include <raylib.h>

enum class SkillBehaviour {
    PROJECTILE, // Moves independently
    ORBITAL,    // Circles around owner
    AREA,       // Stationary or targeted AoE
    BEAM,       // Continuous laser
    AURA,       // Follows owner, constant radius
    SUMMON,     // Spawns an allied entity
    DASH,       // Moves the caster
    TRAP,       // Waits for activation
    CHAIN,      // Jumps between targets
    BUFF,       // Applies effects to allies/self
    DEBUFF,     // Applies effects to enemies
    COUNT,
};

enum class DamageMode {
    INSTANT_HIT,  // Damage once on contact
    TICK,         // Damage over time
    ON_EXPIRE,    // Damage when destroyed/expires
    ON_ENTER,     // First enters area
    ON_EXIT,      // Leaves area
    ON_COLLISION, // Every collision
    NONE,         // Utility skills
    COUNT,
};

// -------------------------------------
// Projectile Variants
// -------------------------------------

enum class ProjectileType {
    BASIC,
    PIERCING,
    BOUNCING,
    HOMING,
    SPLITTING,
    EXPLODING,
    BOOMERANG,
    ARCING,
    LASER_BOLT,
    SHOTGUN_PELLET,
    COUNT,
};

// -------------------------------------
// Orbital Variants
// -------------------------------------

enum class OrbitalType {
    STATIC,      // Fixed distance
    EXPANDING,   // Radius increases
    CONTRACTING, // Radius decreases
    OSCILLATING, // Radius pulses
    HOMING,      // Leaves orbit to attack
    SHIELD,      // Blocks projectiles
    DAMAGE_RING,
    COUNT,
};

// -------------------------------------
// Area Variants
// -------------------------------------

enum class AreaType {
    CIRCLE,
    CONE,
    RECTANGLE,
    LINE,
    RING,
    NOVA,
    PERSISTENT_FIELD,
    EXPLOSION,
    COUNT,
};
