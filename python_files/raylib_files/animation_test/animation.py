from dataclasses import dataclass
from enum import IntEnum

import pyray as p


class AnimationType(IntEnum):
    IDLE = 6
    RUN = 8
    TWO_COMBO_ATTACK = 12
    DEATH = 11
    HURT = 4
    JUMP = 3
    UP_TO_FALL = 2
    FALL = 3
    EDGE_GRAB = 5
    EDGE_IDLE = 6
    WALL_SLIDE = 3
    CROUCH = 6
    DASH = 7
    DASH_ATTACK = 10
    SLIDE = 5
    LADDER_GRAB = 8


@dataclass(slots=True)
class AnimationConfig:
    frames: list[p.Rectangle]
    size: int
    duration: float
    loops: bool


animation_configs: dict[AnimationType, AnimationConfig] = {
    AnimationType.IDLE: AnimationConfig(frames=),
}
