from dataclasses import dataclass

import pyray as p

from drop_type import DropType


@dataclass(slots=True)
class LevelComponent:
    current: int
    pending: int


@dataclass(slots=True)
class XpComponent:
    xp: int
    xp_next: int


@dataclass(slots=True)
class StateComponent:
    active: bool


@dataclass(slots=True)
class PositionComponent:
    x: float
    y: float


@dataclass(slots=True)
class RectComponent:
    width: float
    height: float


@dataclass(slots=True)
class CircleComponent:
    radius: float


@dataclass(slots=True)
class RotationComponent:
    angle: float


@dataclass(slots=True)
class ColorComponent:
    tint: p.Color


@dataclass(slots=True)
class TextComponent:
    string: str


@dataclass(slots=True)
class MoveComponent:
    speed: float
    direction: p.Vector2


@dataclass(slots=True)
class HealthComponent:
    max_hp: int
    hp: int


@dataclass(slots=True)
class DamageComponent:
    amount: int


@dataclass(slots=True)
class LifetimeComponent:
    max: float
    remaining: float


@dataclass(slots=True)
class AnimationComponent:
    hit_timer: float


@dataclass(slots=True)
class SpawnerComponent:
    max: int


@dataclass(slots=True)
class TimerComponent:
    elapsed: float
    interval: float

    def tick(self) -> bool:
        current: float = p.get_time()
        if current - self.elapsed >= self.interval:
            self.elapsed = current

            return True

        return False


@dataclass(slots=True)
class DropComponent:
    type: DropType
    amount: int
