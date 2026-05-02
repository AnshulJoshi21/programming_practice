import random
from enum import IntEnum

from player import Player

MAX_CHOICES: int = 3


class UpgradeType(IntEnum):
    PLAYER_SPEED = 0
    PLAYER_HEALTH = 1
    BULLET_SPEED = 2
    BULLET_DAMAGE = 3
    BULLET_RANGE = 4


class UpgradeManager:
    def __init__(self, player: Player) -> None:
        self.player: Player = player
        self.choices_arr: list[UpgradeType] = []

    def get_random_choices(self) -> None:
        self.choices_arr = []
        upgrade_list: list[UpgradeType] = list(UpgradeType)

        for _ in range(MAX_CHOICES):
            random_choice: UpgradeType = random.choice(upgrade_list)
            upgrade_list.remove(random_choice)
            self.choices_arr.append(random_choice)

    def draw_upgrades(self) -> None:
        pass

    def apply_upgrade(self) -> None:
        pass
