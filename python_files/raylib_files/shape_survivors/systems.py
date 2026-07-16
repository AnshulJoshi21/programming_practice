import math

import pyray as p

import components
import utils
from settings import MAP_SIZE


# LEVEL + XP
def get_xp_next(level: components.Level) -> int:
    return 10 + ((level.current**2) * 2)


def add_xp(level: components.Level, xp: components.Xp, amount: int) -> None:
    xp.current += amount

    while xp.current >= xp.next:
        xp.current -= xp.next
        level.current += 1
        level.pending += 1
        xp.next = get_xp_next(level)


# RENDERING
def draw_background_grid() -> None:
    thickness: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_size: int = 100

    for x in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_SIZE), thickness, color)

    for y in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_SIZE, y), thickness, color)


def draw_rect(
    position: components.Position,
    rotation: components.Rotation,
    rect: components.Rect,
    color: components.Color,
    animation: components.Animation,
) -> None:
    dest: p.Rectangle = p.Rectangle(position.x, position.y, rect.width, rect.height)
    origin: p.Vector2 = p.Vector2(dest.width / 2.0, dest.height / 2.0)

    tint: p.Color = p.RED if animation.hit_timer > 0 else color.tint

    p.draw_rectangle_pro(dest, origin, rotation.angle, tint)


def draw_circle(
    position: components.Position, circle: components.Circle, color: components.Color
) -> None:
    p.draw_circle_v(p.Vector2(position.x, position.y), circle.radius, color.tint)


def draw_centered_text(
    position: components.Position, width: float, height: float, text: components.Text
) -> None:
    dest: p.Rectangle = p.Rectangle(position.x, position.y, width, height)

    utils.center_and_draw_text(
        utils.OriginType.CENTER,
        text.text,
        dest,
        text.font_size,
        text.spacing,
        text.tint,
    )


# MOVEMENT
def set_direction(
    position: components.Position, movement: components.Movement, target_pos: p.Vector2
) -> None:
    dx: float = target_pos.x - position.x
    dy: float = target_pos.y - position.y
    distance: float = math.sqrt(dx**2 + dy**2)
    if distance > 0:
        movement.direction = p.Vector2(dx / distance, dy / distance)


def move(
    position: components.Position, movement: components.Movement, dt: float
) -> None:
    position.x += movement.direction.x * movement.speed * dt
    position.y += movement.direction.y * movement.speed * dt


def set_bounds(
    position: components.Position, half_w: float, half_h: float, bounds: p.Rectangle
) -> None:
    position.x = max(bounds.x + half_w, min(position.x, bounds.width - half_w))
    position.y = max(bounds.y + half_h, min(position.y, bounds.height - half_h))


# UPDATES
def update_xp(level: components.Level, xp: components.Xp) -> None:
    if xp.current >= xp.next:
        xp.current -= xp.next
        level.current += 1
        level.pending += 1
        xp.next = get_xp_next(level)


def update_lifetime(lifetime: components.Lifetime, dt: float) -> None:
    lifetime.current -= dt
    if lifetime.current <= 0:
        lifetime.current = 0


def update_hit_timer(animation: components.Animation, dt: float) -> None:
    animation.hit_timer -= dt
    if animation.hit_timer <= 0:
        animation.hit_timer = 0


def update_health(health: components.Health) -> None:
    health.current = max(0, min(health.current, health.max))
