from enum import Enum, auto

import components
from bullet_manager import BulletManager
from drop_manager import DropManager, DropType
from enemy_manager import Enemy, EnemyManager
from player import Player


class CollisionType(Enum):
    CHECK = auto()
    ONE_WAY = auto()
    TWO_WAY = auto()


def aabb(
    type: CollisionType,
    pos1: components.Position,
    half_w1: float,
    half_h1: float,
    pos2: components.Position,
    half_w2: float,
    half_h2: float,
) -> bool:
    # distance
    dx: float = pos2.x - pos1.x
    dy: float = pos2.y - pos1.y

    # total half size
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
                if type == CollisionType.ONE_WAY:
                    pos1.x -= px
                elif type == CollisionType.TWO_WAY:
                    pos1.x -= px / 2.0
                    pos2.x += px / 2.0
            else:
                if type == CollisionType.ONE_WAY:
                    pos1.x += px
                elif type == CollisionType.TWO_WAY:
                    pos1.x += px / 2.0
                    pos2.x -= px / 2.0
        else:
            if dy > 0:
                if type == CollisionType.ONE_WAY:
                    pos1.y -= py
                elif type == CollisionType.TWO_WAY:
                    pos1.y -= py / 2.0
                    pos2.y += py / 2.0
            else:
                if type == CollisionType.ONE_WAY:
                    pos1.y += py
                elif type == CollisionType.TWO_WAY:
                    pos1.y += py / 2.0
                    pos2.y -= py / 2.0

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
                aabb(
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
                total_damage += enemy.damage.current

        if total_damage > 0:
            self.player.health.current -= total_damage
            self.player.animation.hit_timer = self.player.animation.max_hit_timer

    def player_vs_drop(self) -> None:
        for drop in self.drop_manager.drops:
            if not drop.state.active:
                continue

            if aabb(
                CollisionType.CHECK,
                self.player.position,
                self.player.rect.width / 2.0,
                self.player.rect.height / 2.0,
                drop.position,
                drop.circle.radius,
                drop.circle.radius,
            ):
                # add drop value to player
                if drop.type == DropType.HP:
                    self.player.health.current += drop.amount
                elif drop.type == DropType.XP:
                    self.player.xp.current += drop.amount

                # despawn drop
                drop.state.active = False

    def bullet_vs_enemy(self) -> None:
        for bullet in self.bullet_manager.bullets:
            for enemy in self.enemy_manager.enemies:
                if (
                    aabb(
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
                    enemy.health.current -= bullet.damage.current
                    enemy.animation.hit_timer = enemy.animation.max_hit_timer

                    bullet.lifetime.current = 0
                    break

    def enemy_vs_enemy(self) -> None:
        for i, enemy1 in enumerate(self.enemy_manager.enemies):
            for j in range(i + 1, len(self.enemy_manager.enemies)):
                enemy2: Enemy = self.enemy_manager.enemies[j]

                aabb(
                    CollisionType.TWO_WAY,
                    enemy1.position,
                    enemy1.rect.width / 2.0,
                    enemy1.rect.height / 2.0,
                    enemy2.position,
                    enemy2.rect.width / 2.0,
                    enemy2.rect.height / 2.0,
                )

    def update(self) -> None:
        self.player_vs_enemy()
        self.player_vs_drop()
        self.bullet_vs_enemy()
        self.enemy_vs_enemy()
