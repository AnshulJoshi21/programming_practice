from math import atan2, degrees, sqrt

import pyray as p

import settings as S
from entity import Entity, EntityType
from utils import IntervalTimer


class Laser:
    def __init__(
        self,
        sprite_dict: dict[str, p.Rectangle],
        start_pos: p.Vector2,
        target_pos: p.Vector2,
    ) -> None:

        self.entity: Entity = Entity(
            entity_type=EntityType.LASER,
            sprite_dict=sprite_dict,
            current_sprite="laserBlue01.png",
            start_pos=start_pos,
            scale=S.LASER_SCALE,
            speed=300.0,
        )

        # set direction
        dx: float = target_pos.x - self.entity.dest.x
        dy: float = target_pos.y - self.entity.dest.y
        distance: float = sqrt(dx**2 + dy**2)
        if distance > 0:
            self.entity.direction = p.Vector2(dx / distance, dy / distance)

        # sel rotation
        self.entity.rotation = degrees(atan2(dy, dx)) + S.ROTATION_OFFSET

        self.lifetime: float = S.LASER_MAX_LIFETIME

    def draw(self, spritesheet: p.Texture) -> None:
        self.entity.draw(spritesheet)

    def update(self, delta_time: float) -> None:
        self.entity.move(delta_time)

        # update lifetime
        self.lifetime -= delta_time


class LaserManager:
    def __init__(self) -> None:
        self.lasers: list[Laser] = []
        self.spawn_rate: float = S.LASER_SPAWN_RATE
        self.inteval_timer: IntervalTimer = IntervalTimer(S.LASER_SPAWN_RATE)

    def draw(self, spritesheet: p.Texture) -> None:
        for laser in self.lasers:
            laser.draw(spritesheet)

    def update(
        self,
        sprite_dict: dict[str, p.Rectangle],
        delta_time: float,
        start_pos: p.Vector2,
        target_pos: p.Vector2,
    ) -> None:
        # spawn laser
        if len(self.lasers) < S.MAX_LASERS:
            if self.inteval_timer.update():
                self.lasers.append(Laser(sprite_dict, start_pos, target_pos))

        remove_lasers_index: list[int] = []
        for i, laser in enumerate(self.lasers):
            laser.update(delta_time)

            if laser.lifetime <= 0:
                remove_lasers_index.append(i)

        for i in remove_lasers_index:
            self.lasers[i] = self.lasers[len(self.lasers) - 1]
