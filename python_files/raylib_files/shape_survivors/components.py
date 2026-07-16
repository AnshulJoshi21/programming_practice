from dataclasses import dataclass

import pyray as p


@dataclass(slots=True)
class Level:
    current: int
    pending: int = 0


@dataclass(slots=True)
class Xp:
    current: int
    next: int


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
class Movement:
    speed: float
    direction: p.Vector2


@dataclass(slots=True)
class Health:
    max: int
    current: int


@dataclass(slots=True)
class Damage:
    current: int


@dataclass(slots=True)
class Lifetime:
    max: float
    current: float


@dataclass(slots=True)
class Animation:
    max_hit_timer: float
    hit_timer: float


@dataclass(slots=True)
class Timer:
    elapsed: float
    interval: float

    def tick(self) -> bool:
        current_time: float = p.get_time()
        if current_time - self.elapsed >= self.interval:
            self.elapsed = current_time
            return True

        return False
