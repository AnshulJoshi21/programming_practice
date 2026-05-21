from enum import IntEnum, auto

import pyray as p


class Action(IntEnum):
    WALK = auto()
    RUN = auto()
    CROUCH = auto()
    JUMP = auto()
    ATTACK = auto()
    SLIDE = auto()
    CLIMB = auto()
    GRAB = auto()
    CAST = auto()


class Input:
    def __init__(self, action: Action, keys: list[p.KeyboardKey]) -> None:
        self.bindings: list[p.KeyboardKey] = keys

    def is_key_down(self, action: Action) -> bool:
        for key in self.bindings:
            if p.is_key_down(key):
                return True

        return False
