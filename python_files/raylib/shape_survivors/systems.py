import math

import pyray as p

import components
import utils
from settings import MAP_SIZE


# XP + LEVELUPS
def get_xp_next(level: components.Level) -> int:
    return 10 + ((level.level**2) * 2)


def add_xp(level: components.Level, xp: components.Xp, amount: int) -> None:
    xp.xp += amount

    while xp.xp >= xp.xp_next:
        xp.xp -= xp.xp_next
        level.level += 1
        xp.pending_levelups += 1

        xp.xp_next = get_xp_next(level)


def consume_levelups(xp: components.Xp) -> None:
    if xp.pending_levelups > 0:
        xp.pending_levelups += 1
        return


# RENDER
def draw_background_grid() -> None:
    thickness: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_size: int = 400

    for x in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_SIZE), thickness, color)
    for y in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_SIZE, y), thickness, color)


def get_dest_rect(position: components.Position, rect: components.Rect) -> p.Rectangle:
    return p.Rectangle(position.x, position.y, rect.width, rect.height)


def draw_rect(
    position: components.Position,
    rect: components.Rect,
    rotation: components.Rotation,
    color: components.Color,
    animation: components.Animation,
) -> None:
    dest: p.Rectangle = get_dest_rect(position, rect)
    origin: p.Vector2 = p.Vector2(dest.width / 2.0, dest.height / 2.0)

    tint: p.Color = p.RED if animation.hit_timer > 0 else color.tint

    p.draw_rectangle_pro(dest, origin, rotation.angle, tint)


def draw_circle(
    position: components.Position, circle: components.Circle, color: components.Color
) -> None:
    p.draw_circle_v(p.Vector2(position.x, position.y), circle.radius, color.tint)


def draw_centered_text(text: components.Text, bounds_rect: p.Rectangle) -> None:
    utils.center_and_draw_text(
        utils.OriginType.CENTER,
        text.text,
        bounds_rect,
        text.font_size,
        text.spacing,
        text.tint,
    )


# MOVEMENT
def set_direction(
    position: components.Position, move: components.Move, target_pos: p.Vector2
) -> None:
    dx: float = target_pos.x - position.x
    dy: float = target_pos.y - position.y
    distance: float = math.sqrt(dx**2 + dy**2)
    if distance > 0:
        move.direction = p.Vector2(dx / distance, dy / distance)


def move(position: components.Position, move: components.Move, dt: float) -> None:
    position.x += move.direction.x * move.speed * dt
    position.y += move.direction.y * move.speed * dt


def set_bounds(
    position: components.Position,
    half_w: float,
    half_h: float,
    bounds_rect: p.Rectangle,
) -> None:

    position.x = max(
        bounds_rect.x + half_w, min(position.x, bounds_rect.width - half_w)
    )
    position.y = max(
        bounds_rect.y + half_h, min(position.y, bounds_rect.height - half_h)
    )


# UPDATE
def update_lifetime(lifetime: components.Lifetime, dt: float) -> None:
    lifetime.remaining -= dt
    if lifetime.remaining <= 0:
        lifetime.remaining = 0


def update_animation(animation: components.Animation, dt: float) -> None:
    animation.hit_timer -= dt
    if animation.hit_timer <= 0:
        animation.hit_timer = 0
