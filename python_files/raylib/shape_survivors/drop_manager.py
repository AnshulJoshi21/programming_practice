import pyray as p

import components
from drop import Drop
from drop_type import DropType


class DropManager:
    def __init__(self) -> None:
        self.drops: list[Drop] = []

        self.spawner: components.Spawner = components.Spawner(max=200)

    def draw(self) -> None:
        for drop in self.drops:
            drop.draw()

    def spawn(self, type: DropType, start_pos: p.Vector2) -> None:
        if len(self.drops) >= self.spawner.max:
            return

        self.drops.append(Drop(type, start_pos))

    def despawn(self, index: int) -> None:
        self.drops[index] = self.drops[len(self.drops) - 1]
        self.drops.pop()

    def update(self) -> None:
        for i, drop in enumerate(self.drops):
            if not drop.state.active:
                self.despawn(index=i)
