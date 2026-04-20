import math

import pyray as p

import components as c
import utils


def get_xp_next(level: c.LevelComponent) -> int:
    return 10 + (level.current**2 * 2)


def add_xp(level: c.LevelComponent, xp: c.XpComponent, drop: c.DropComponent) -> None:
    xp.xp += drop.amount

    while xp.xp >= xp.xp_next:
        xp.xp -= xp.xp_next
        level.current += 1
        level.pending += 1

        xp.xp_next = get_xp_next(level)


def consume_levelup(level: c.LevelComponent) -> None:
    if level.pending > 0:
        level.pending -= 1
        return


def get_dest_rect(position: c.PositionComponent, rect: c.RectComponent) -> p.Rectangle:
    return p.Rectangle(position.x, position.y, rect.width, rect.height)


def draw_rect(
    position: c.PositionComponent,
    rect: c.RectComponent,
    rotation: c.RotationComponent,
    color: c.ColorComponent,
    animation: c.AnimationComponent,
) -> None:

    dest: p.Rectangle = get_dest_rect(position, rect)
    origin: p.Vector2 = p.Vector2(dest.width / 2.0, dest.height / 2.0)

    tint: p.Color = p.RED if (animation.hit_timer > 0) else color.tint

    p.draw_rectangle_pro(dest, origin, rotation.angle, tint)


def draw_circle(
    position: c.PositionComponent, circle: c.CircleComponent, color: c.ColorComponent
) -> None:
    p.draw_circle_v(p.Vector2(position.x, position.y), circle.radius, color.tint)


def draw_centered_text(
    text: c.TextComponent,
    bounds_rect: p.Rectangle,
    font_size: float,
    spacing: float,
    tint: p.Color,
) -> None:

    utils.center_and_draw_text(
        utils.OriginType.center, text.string, bounds_rect, font_size, spacing, tint
    )


def set_direction(
    position: c.PositionComponent, move: c.MoveComponent, target_pos: p.Vector2
) -> None:
    dx: float = target_pos.x - position.x
    dy: float = target_pos.y - position.y

    distance: float = math.sqrt(dx**2 + dy**2)
    if distance > 0:
        move.direction = p.Vector2(dx / distance, dy / distance)


def move_entity(
    position: c.PositionComponent, move: c.MoveComponent, dt: float
) -> None:
    position.x += move.direction.x * move.speed * dt
    position.y += move.direction.y * move.speed * dt


def set_bounds(
    position: c.PositionComponent,
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


def update_lifetime(lifetime: c.LifetimeComponent, dt: float) -> None:
    lifetime.remaining -= dt
    if lifetime.remaining <= 0:
        lifetime.remaining = 0


def update_hit_timer(animation: c.AnimationComponent, dt: float) -> None:
    animation.hit_timer -= dt
    if animation.hit_timer <= 0:
        animation.hit_timer = 0
