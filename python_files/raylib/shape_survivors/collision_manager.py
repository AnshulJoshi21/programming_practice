from enum import IntEnum

import components
import systems
from bullet_manager import BulletManager
from drop_manager import DropManager
from enemy_manager import Enemy, EnemyManager
from player import Player


class CollisionType(IntEnum):
    CHECK = 0
    ONE_WAY = 1
    TWO_WAY = 2


# NOTE: in one way collision: 1 is mobile and 2 is stationary
def aabb_collision(
    type: CollisionType,
    position1: components.Position,
    half_w1: float,
    half_h1: float,
    position2: components.Position,
    half_w2: float,
    half_h2: float,
) -> bool:

    # change in distance
    dx: float = position2.x - position1.x
    dy: float = position2.y - position1.y

    total_half_w: float = half_w1 + half_w2
    total_half_h: float = half_h1 + half_h2

    # penetration
    px: float = total_half_w - abs(dx)
    py: float = total_half_h - abs(dy)

    if px > 0 and py > 0:
        if type == CollisionType.CHECK:
            return True

        if px < py:
            if dx > 0:
                match type:
                    case CollisionType.ONE_WAY:
                        position1.x -= px
                    case CollisionType.TWO_WAY:
                        position1.x -= px / 2.0
                        position2.x += px / 2.0
            else:
                match type:
                    case CollisionType.ONE_WAY:
                        position1.x += px
                    case CollisionType.TWO_WAY:
                        position1.x += px / 2.0
                        position2.x -= px / 2.0
        else:
            if dy > 0:
                match type:
                    case CollisionType.ONE_WAY:
                        position1.y -= py
                    case CollisionType.TWO_WAY:
                        position1.y -= py / 2.0
                        position2.y += py / 2.0
            else:
                match type:
                    case CollisionType.ONE_WAY:
                        position1.y += py
                    case CollisionType.TWO_WAY:
                        position1.y += py / 2.0
                        position2.y -= py / 2.0

        return True

    return False


class CollisionManager:
    def __init__(
        self,
        player: Player,
        enemy_manager: EnemyManager,
        bullet_manager: BulletManager,
        drop_manager: DropManager,
    ) -> None:
        self.player: Player = player
        self.enemy_manager: EnemyManager = enemy_manager
        self.bullet_manager: BulletManager = bullet_manager
        self.drop_manager: DropManager = drop_manager

    def player_vs_enemy(self) -> None:
        total_damage: int = 0

        for enemy in self.enemy_manager.enemies:
            if (
                aabb_collision(
                    CollisionType.TWO_WAY,
                    self.player.position,
                    self.player.rect.width / 2.0,
                    self.player.rect.height / 2.0,
                    enemy.position,
                    enemy.rect.width / 2.0,
                    enemy.rect.height / 2.0,
                )
                and self.player.animation.hit_timer <= 0
            ):
                total_damage += enemy.damage.amount

        if total_damage > 0:
            self.player.health.current -= total_damage
            self.player.animation.hit_timer = self.player.animation.max_hit_timer

    def player_vs_drop(self) -> None:
        for drop in self.drop_manager.drops:
            if not drop.state.active:
                continue

            if aabb_collision(
                CollisionType.CHECK,
                self.player.position,
                self.player.rect.width / 2.0,
                self.player.rect.height / 2.0,
                drop.position,
                drop.circle.radius,
                drop.circle.radius,
            ):
                systems.add_xp(self.player.level, self.player.xp, drop.drop.amount)
                drop.state.active = False

    def bullet_vs_enemy(self) -> None:
        for bullet in self.bullet_manager.bullets:
            for enemy in self.enemy_manager.enemies:
                if (
                    aabb_collision(
                        CollisionType.CHECK,
                        bullet.position,
                        bullet.circle.radius,
                        bullet.circle.radius,
                        enemy.position,
                        enemy.rect.width / 2.0,
                        enemy.rect.height / 2.0,
                    )
                    and enemy.animation.hit_timer <= 0
                ):
                    enemy.health.current -= bullet.damage.amount
                    enemy.animation.hit_timer = enemy.animation.max_hit_timer

                    bullet.lifetime.remaining = 0
                    break

    def enemy_vs_enemy(self) -> None:
        for i, enemy1 in enumerate(self.enemy_manager.enemies):
            for j in range(i + 1, len(self.enemy_manager.enemies)):
                enemy2: Enemy = self.enemy_manager.enemies[j]

                aabb_collision(
                    CollisionType.TWO_WAY,
                    enemy1.position,
                    enemy1.rect.width / 2.0,
                    enemy1.rect.height / 2.0,
                    enemy2.position,
                    enemy2.rect.width / 2.0,
                    enemy2.rect.height / 2.0,
                )
