import pyray as p

import components as c
from drop import Drop
from drop_type import DropType


class DropManager:
    def __init__(self) -> None:
        self.drops: list[Drop] = []

        self.spawner: c.SpawnerComponent = c.SpawnerComponent(max=100)

    def draw(self) -> None:
        for drop in self.drops:
            drop.draw()

    def spawn(self, drop_type: DropType, start_pos: p.Vector2) -> None:
        if len(self.drops) < self.spawner.max:
            self.drops.append(Drop(drop_type, start_pos))

    def despawn(self, index: int) -> None:
        self.drops[index] = self.drops[-1]
        self.drops.pop()

    def update(self) -> None:
        for i in range(len(self.drops) - 1, -1, -1):
            drop: Drop = self.drops[i]

            if not drop.state.active:
                self.despawn(index=i)
