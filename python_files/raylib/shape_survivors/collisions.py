from enum import IntEnum

import components as c
import systems
from bullet_manager import BulletManager
from drop_manager import DropManager
from enemy_manager import Enemy, EnemyManager
from player import Player
from settings import MAX_HIT_TIMER


class CollisionType(IntEnum):
    check = 0
    one_way = 1
    two_way = 2


# in one way collision: 1 is mobile and 2 is stationary
def aabb_collision(
    collision_type: CollisionType,
    position1: c.PositionComponent,
    half_w1: float,
    half_h1: float,
    position2: c.PositionComponent,
    half_w2: float,
    half_h2: float,
) -> bool:

    # distance
    dx: float = position2.x - position1.x
    dy: float = position2.y - position1.y

    total_half_w: float = half_w1 + half_w2
    total_half_h: float = half_h1 + half_h2

    # penetration
    px: float = total_half_w - abs(dx)
    py: float = total_half_h - abs(dy)

    if px > 0 and py > 0:
        if collision_type == CollisionType.check:
            return True

        if px < py:
            if dx > 0:
                match collision_type:
                    case CollisionType.one_way:
                        position1.x -= px
                    case CollisionType.two_way:
                        position1.x -= px / 2.0
                        position2.x += px / 2.0
            else:
                match collision_type:
                    case CollisionType.one_way:
                        position1.x += px
                    case CollisionType.two_way:
                        position1.x += px / 2.0
                        position2.x -= px / 2.0
        else:
            if dy > 0:
                match collision_type:
                    case CollisionType.one_way:
                        position1.y -= py
                    case CollisionType.two_way:
                        position1.y -= py / 2.0
                        position2.y += py / 2.0
            else:
                match collision_type:
                    case CollisionType.one_way:
                        position1.y += py
                    case CollisionType.two_way:
                        position1.y += py / 2.0
                        position2.y -= py / 2.0

        return True

    return False


def player_collision_enemy(player: Player, enemy_manager: EnemyManager) -> None:
    total_damage: int = 0

    for enemy in enemy_manager.enemies:
        if (
            aabb_collision(
                CollisionType.two_way,
                player.position,
                player.rect.width / 2.0,
                player.rect.height / 2.0,
                enemy.position,
                enemy.rect.width / 2.0,
                enemy.rect.height / 2.0,
            )
            and player.animation.hit_timer <= 0
        ):
            total_damage += enemy.damage.amount

    if total_damage > 0:
        player.health.hp -= total_damage
        player.animation.hit_timer = MAX_HIT_TIMER


def player_collision_drop(player: Player, drop_manager: DropManager) -> None:
    for drop in drop_manager.drops:
        if aabb_collision(
            CollisionType.check,
            player.position,
            player.rect.width / 2.0,
            player.rect.height / 2.0,
            drop.position,
            drop.circle.radius,
            drop.circle.radius,
        ):
            systems.add_xp(player.level, player.xp, drop.drop)
            drop.state.active = False


def bullet_collision_enemy(
    bullet_manager: BulletManager, enemy_manager: EnemyManager
) -> None:
    for bullet in bullet_manager.bullets:
        for enemy in enemy_manager.enemies:
            if (
                aabb_collision(
                    CollisionType.check,
                    bullet.position,
                    bullet.circle.radius,
                    bullet.circle.radius,
                    enemy.position,
                    enemy.rect.width / 2.0,
                    enemy.rect.height / 2.0,
                )
                and enemy.animation.hit_timer <= 0
            ):
                enemy.health.hp -= bullet.damage.amount
                enemy.animation.hit_timer = MAX_HIT_TIMER

                bullet.lifetime.remaining = 0
                break


def enemy_collision_enemy(enemy_manager: EnemyManager) -> None:
    for i, enemy1 in enumerate(enemy_manager.enemies):
        for j in range(i + 1, len(enemy_manager.enemies)):
            enemy2: Enemy = enemy_manager.enemies[j]

            aabb_collision(
                CollisionType.two_way,
                enemy1.position,
                enemy1.rect.width / 2.0,
                enemy1.rect.height / 2.0,
                enemy2.position,
                enemy2.rect.width / 2.0,
                enemy2.rect.height / 2.0,
            )
