from dataclasses import dataclass
from enum import Enum, auto


class Jobs(Enum):
    Idle = auto()
    GatherFood = auto()
    GatherWood = auto()


class Resources(Enum):
    Food = auto()
    Wood = auto()


class Settler:
    def __init__(self, name: str) -> None:
        self.name: str = name
        self.job: Jobs = Jobs.Idle
        self.hunger: int = 100  # 0-100, 100 is dead
        self.alive: bool = True

    def update(self) -> None:
        pass


class World:
    def __init__(self) -> None:
        self.current_day: int = 0
        self.food_stored: int = 10
