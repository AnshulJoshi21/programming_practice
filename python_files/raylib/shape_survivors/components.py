from dataclasses import dataclass

import pyray as p

from drop_type import DropType


@dataclass(slots=True)
class Level:
    level: int


@dataclass(slots=True)
class Xp:
    xp: int
    xp_next: int
    pending_levelups: int


@dataclass(slots=True)
class State:
    active: bool


@dataclass(slots=True)
class Position:
    x: float
    y: float


@dataclass(slots=True)
class Rect:
    width: float
    height: float


@dataclass(slots=True)
class Circle:
    radius: float


@dataclass(slots=True)
class Rotation:
    angle: float


@dataclass(slots=True)
class Color:
    tint: p.Color


@dataclass(slots=True)
class Text:
    text: str
    font_size: float
    spacing: float
    tint: p.Color


@dataclass(slots=True)
class Move:
    speed: float
    direction: p.Vector2


@dataclass(slots=True)
class Health:
    max: int
    current: int


@dataclass(slots=True)
class Damage:
    amount: int


@dataclass(slots=True)
class Lifetime:
    max: float
    remaining: float


@dataclass(slots=True)
class Animation:
    max_hit_timer: float
    hit_timer: float


@dataclass(slots=True)
class Spawner:
    max: int


@dataclass(slots=True)
class Timer:
    elapsed: float
    interval: float

    def tick(self) -> bool:
        current: float = p.get_time()
        if current - self.elapsed >= self.interval:
            self.elapsed = current

            return True

        return False


@dataclass(slots=True)
class Drop:
    type: DropType
    amount: int
