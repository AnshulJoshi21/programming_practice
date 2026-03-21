from math import cos, pi, sin
from random import choice, randint, uniform

import pyray as p

import settings as S
from entity import Entity, EntityType
from utils import IntervalTimer

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


class Enemy:
    def __init__(
        self, sprite_dict: dict[str, p.Rectangle], start_pos: p.Vector2
    ) -> None:
        random_sprite: str = choice(enemy_spritename_list)

        self.entity: Entity = Entity(
            entity_type=EntityType.ENEMY,
            sprite_dict=sprite_dict,
            current_sprite=random_sprite,
            start_pos=start_pos,
            scale=S.ENEMY_SCALE,
            speed=100.0,
        )

        self.max_hp: int = 100
        self.hp: int = self.max_hp
        self.damage: int = randint(1, 3)

    def draw(self, spritesheet: p.Texture) -> None:
        self.entity.draw(spritesheet)

    def update(self, delta_time: float, target_pos: p.Vector2) -> None:
        self.entity.set_direction(target_pos)
        self.entity.rotate(target_pos)
        self.entity.move(delta_time)
        self.entity.set_bounds()


class EnemyManager:
    def __init__(self) -> None:
        self.enemies: list[Enemy] = []

        self.spawn_rate: float = S.ENEMY_SPAWN_RATE

        self.interval_timer: IntervalTimer = IntervalTimer(self.spawn_rate)

    def draw(self, spritesheet: p.Texture) -> None:
        for enemy in self.enemies:
            enemy.draw(spritesheet)

    def update(
        self,
        sprite_dict: dict[str, p.Rectangle],
        delta_time: float,
        target_pos: p.Vector2,
    ) -> None:
        # spawn enemy
        if len(self.enemies) < S.MAX_ENEMIES:
            if len(self.enemies) <= 0 or self.interval_timer.update():
                random_angle: float = uniform(0, 2 * pi)
                random_distance: float = uniform(
                    S.ENEMY_MIN_SPAWN_DISTANCE, S.ENEMY_MAX_SPAWN_DISTANCE
                )
                start_pos: p.Vector2 = p.Vector2(
                    cos(random_angle) * random_distance + target_pos.x,
                    sin(random_angle) * random_distance + target_pos.x,
                )
                self.enemies.append(Enemy(sprite_dict, start_pos))

        remove_enemies_index: list[int] = []
        for i, enemy in enumerate(self.enemies):
            enemy.update(delta_time, target_pos)

            # remove dead enemy
            if enemy.hp <= 0:
                remove_enemies_index.append(i)

        for i in remove_enemies_index:
            self.enemies[i] = self.enemies[len(self.enemies) - 1]
