from math import cos, pi, sin
from random import choice, randint, uniform

import pyray as p

import components as C
import settings as S
from ecs import World


def create_player(world: World) -> int:
    id: int = world.create_entity()

    world.mask_list[id] = (
        C.ComponentMask.PLAYER
        | C.ComponentMask.TRANSFORM
        | C.ComponentMask.ANIMATION
        | C.ComponentMask.COLOR
        | C.ComponentMask.MOVE
        | C.ComponentMask.HEALTH
        | C.ComponentMask.TARGET
    )

    transform: C.TransformComponent = world.transform_list[id]
    animation: C.AnimationComponent = world.animation_list[id]
    color: C.ColorComponent = world.color_list[id]
    move: C.MoveComponent = world.move_list[id]
    health: C.HealthComponent = world.health_list[id]
    target: C.TargetComponent = world.target_list[id]

    transform.pos = p.Vector2(S.MAP_SIZE / 2.0, S.MAP_SIZE / 2.0)
    transform.scale = p.Vector2(S.PLAYER_SCALE, S.PLAYER_SCALE)
    transform.rotation = 0.0

    animation.current_sprite = "playerShip1_blue.png"

    color.tint = p.WHITE

    move.speed = 200.0
    move.direction = p.Vector2(0, 0)

    health.max_hp = 100
    health.hp = health.max_hp

    target.pos = p.Vector2(0, 0)
    target.track_once = False

    return id


enemy_spritename_list: list[str] = [
    "enemyBlack1.png",
    "enemyBlack2.png",
    "enemyBlack3.png",
    "enemyBlack4.png",
    "enemyBlack5.png",
    "enemyBlue1.png",
    "enemyBlue2.png",
    "enemyBlue3.png",
    "enemyBlue4.png",
    "enemyBlue5.png",
    "enemyGreen1.png",
    "enemyGreen2.png",
    "enemyGreen3.png",
    "enemyGreen4.png",
    "enemyGreen5.png",
    "enemyRed1.png",
    "enemyRed2.png",
    "enemyRed3.png",
    "enemyRed4.png",
    "enemyRed5.png",
]


def create_enemy(world: World, target_pos: p.Vector2) -> int:
    id: int = world.create_entity()

    world.mask_list[id] = (
        C.ComponentMask.TRANSFORM
        | C.ComponentMask.ANIMATION
        | C.ComponentMask.COLOR
        | C.ComponentMask.MOVE
        | C.ComponentMask.HEALTH
        | C.ComponentMask.DAMAGE
        | C.ComponentMask.TARGET
    )

    transform: C.TransformComponent = world.transform_list[id]
    animation: C.AnimationComponent = world.animation_list[id]
    color: C.ColorComponent = world.color_list[id]
    move: C.MoveComponent = world.move_list[id]
    health: C.HealthComponent = world.health_list[id]
    damage: C.DamageComponent = world.damage_list[id]
    target: C.TargetComponent = world.target_list[id]

    random_angle: float = uniform(0, 2 * pi)
    random_distance: float = uniform(
        S.ENEMY_MIN_SPAWN_DISTANCE, S.ENEMY_MAX_SPAWN_DISTANCE
    )

    transform.pos = p.Vector2(
        cos(random_angle) * random_distance + target_pos.x,
        sin(random_angle) * random_distance + target_pos.y,
    )
    transform.scale = p.Vector2(S.ENEMY_SCALE, S.ENEMY_SCALE)
    transform.rotation = 0.0

    animation.current_sprite = choice(enemy_spritename_list)

    color.tint = p.WHITE

    move.speed = 100.0
    move.direction = p.Vector2(0, 0)

    health.max_hp = 10
    health.hp = health.max_hp

    damage.damage = randint(1, 3)

    target.pos = target_pos
    target.track_once = False

    return id
