import random

import pyray as p

from drop import Drop, DropType


class DropManager:
    def __init__(self) -> None:
        self.drops: list[Drop] = []

    def get_random_drop_type(self) -> DropType:
        random_num: float = random.uniform(0, 100)

        if random_num >= 90.0:
            return DropType.HP
        elif random_num >= 75.0:
            return DropType.XP
        else:
            return DropType.XP

    def spawn(self, drop_type: DropType, start_pos: p.Vector2) -> None:
        self.drops.append(Drop(drop_type, start_pos))

    def despawn(self, index: int) -> None:
        if index < 0 or index >= len(self.drops):
            return

        self.drops[index] = self.drops[len(self.drops) - 1]
        self.drops.pop()

    def update(self) -> None:
        drop_removal_list: list[int] = []
        for index, drop in enumerate(self.drops):
            if not drop.state.active:
                drop_removal_list.append(index)

        for index in drop_removal_list:
            self.despawn(index)

    def draw(self) -> None:
        for drop in self.drops:
            if not drop.state.active:
                continue

            drop.draw()
