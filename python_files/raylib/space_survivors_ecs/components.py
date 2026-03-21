from dataclasses import dataclass
from enum import IntFlag, auto

import pyray as p


class ComponentMask(IntFlag):
    NONE = 0
    PLAYER = auto()
    TRANSFORM = auto()
    ANIMATION = auto()
    COLOR = auto()
    MOVE = auto()
    HEALTH = auto()
    DAMAGE = auto()
    TARGET = auto()
    LIFETIME = auto()


@dataclass(slots=True)
class TransformComponent:
    pos: p.Vector2 = p.Vector2(0, 0)
    scale: p.Vector2 = p.Vector2(0, 0)
    rotation: float = 0.0


@dataclass(slots=True)
class AnimationComponent:
    current_sprite: str = ""


@dataclass(slots=True)
class ColorComponent:
    tint: p.Color = p.WHITE


@dataclass(slots=True)
class MoveComponent:
    speed: float = 0.0
    direction: p.Vector2 = p.Vector2(0, 0)


@dataclass(slots=True)
class HealthComponent:
    max_hp: int = 0
    hp: int = 0


@dataclass(slots=True)
class DamageComponent:
    damage: int = 0


@dataclass(slots=True)
class TargetComponent:
    pos: p.Vector2 = p.Vector2(0, 0)
    track_once: bool = False


@dataclass(slots=True)
class LifetimeComponent:
    lifetime: float = 0.0
