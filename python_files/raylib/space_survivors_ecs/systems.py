from math import atan2, degrees, sqrt

import pyray as p

import components as C
from ecs import World
from settings import MAP_SIZE, ROTATION_OFFSET
from utils import utils_get_dest_rect


def system_draw(
    world: World, spritesheet: p.Texture, sprite_dict: dict[str, p.Rectangle]
) -> None:

    target_mask: int = (
        C.ComponentMask.TRANSFORM | C.ComponentMask.ANIMATION | C.ComponentMask.COLOR
    )

    for id in range(world.entity_count):
        if (world.mask_list[id] & target_mask) == target_mask:
            transform: C.TransformComponent = world.transform_list[id]
            animation: C.AnimationComponent = world.animation_list[id]
            color: C.ColorComponent = world.color_list[id]

            source: p.Rectangle = sprite_dict[animation.current_sprite]
            dest: p.Rectangle = utils_get_dest_rect(
                transform.pos, transform.scale, source
            )
            origin: p.Vector2 = p.Vector2(dest.width / 2.0, dest.height / 2.0)

            p.draw_texture_pro(
                spritesheet, source, dest, origin, transform.rotation, color.tint
            )


def system_handle_input(world: World) -> None:
    for id in range(world.entity_count):
        if (world.mask_list[id] & C.ComponentMask.PLAYER) == C.ComponentMask.PLAYER:
            move: C.MoveComponent = world.move_list[id]

            move.direction.x = int(p.is_key_down(p.KeyboardKey.KEY_D)) - int(
                p.is_key_down(p.KeyboardKey.KEY_A)
            )
            move.direction.y = int(p.is_key_down(p.KeyboardKey.KEY_S)) - int(
                p.is_key_down(p.KeyboardKey.KEY_W)
            )

            move.direction = p.vector2_normalize(move.direction)


def system_set_direction(world: World) -> None:
    target_mask: int = (
        C.ComponentMask.TRANSFORM | C.ComponentMask.MOVE | C.ComponentMask.TARGET
    )

    for id in range(world.entity_count):
        if world.mask_list[id] & C.ComponentMask.PLAYER:
            continue

        if (world.mask_list[id] & target_mask) == target_mask:
            transform: C.TransformComponent = world.transform_list[id]
            move: C.MoveComponent = world.move_list[id]
            target: C.TargetComponent = world.target_list[id]

            dx: float = target.pos.x - transform.pos.x
            dy: float = target.pos.y - transform.pos.y
            distance: float = sqrt(dx**2 + dy**2)
            if distance > 0:
                move.direction = p.Vector2(dx / distance, dy / distance)

            if target.track_once:
                world.mask_list[id] &= ~C.ComponentMask.TARGET


def system_rotate(world: World) -> None:
    target_mask: int = C.ComponentMask.TRANSFORM | C.ComponentMask.TARGET

    for id in range(world.entity_count):
        if (world.mask_list[id] & target_mask) == target_mask:
            transform: C.TransformComponent = world.transform_list[id]
            target: C.TargetComponent = world.target_list[id]

            dx: float = target.pos.x - transform.pos.x
            dy: float = target.pos.y - transform.pos.y
            transform.rotation = degrees(atan2(dy, dx)) + ROTATION_OFFSET

            if target.track_once:
                world.mask_list[id] &= ~C.ComponentMask.TARGET


def system_move(world: World, delta_time: float) -> None:
    target_mask: int = C.ComponentMask.TRANSFORM | C.ComponentMask.MOVE

    for id in range(world.entity_count):
        if (world.mask_list[id] & target_mask) == target_mask:
            transform: C.TransformComponent = world.transform_list[id]
            move: C.MoveComponent = world.move_list[id]

            transform.pos.x += move.direction.x * move.speed * delta_time
            transform.pos.y += move.direction.y * move.speed * delta_time


def system_set_bounds(world: World, sprite_dict: dict[str, p.Rectangle]) -> None:
    for id in range(world.entity_count):
        transform: C.TransformComponent = world.transform_list[id]
        animation: C.AnimationComponent = world.animation_list[id]

        source: p.Rectangle = sprite_dict[animation.current_sprite]
        dest: p.Rectangle = utils_get_dest_rect(transform.pos, transform.scale, source)

        half_w: float = dest.width / 2.0
        half_h: float = dest.height / 2.0

        transform.pos.x = max(half_w, min(transform.pos.x, MAP_SIZE - half_w))
        transform.pos.y = max(half_h, min(transform.pos.y, MAP_SIZE - half_h))


def system_despawn(world: World) -> None:
    for id in range(world.entity_count):
        if (world.mask_list[id] & C.ComponentMask.HEALTH) == C.ComponentMask.HEALTH:
            health: C.HealthComponent = world.health_list[id]

            if health.hp <= 0:
                world.delete_entity(id)
