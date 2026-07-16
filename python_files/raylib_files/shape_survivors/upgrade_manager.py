import random
from dataclasses import dataclass
from enum import Enum, auto
from typing import Callable

import pyray as p

import utils
from player import Player
from settings import BASE_HEIGHT, BASE_WIDTH

MAX_CHOICES: int = 3


class UpgradeType(Enum):
    NONE = auto()

    PLAYER_SPEED = auto()
    PLAYER_MAX_HEALTH = auto()
    PLAYER_RECOVER = auto()

    BULLET_SPEED = auto()
    BULLET_DAMAGE = auto()
    BULLET_RANGE = auto()


@dataclass(slots=True)
class Upgrade:
    type: UpgradeType
    name: str
    description: str
    amount: float
    apply: Callable[[Player, float], None]


upgrade_db: dict[UpgradeType, Upgrade] = {
    UpgradeType.PLAYER_SPEED: Upgrade(
        UpgradeType.PLAYER_SPEED,
        "Player Speed",
        "Increase Speed",
        10,
        lambda player, amount: setattr(
            player.movement,
            "speed",
            player.movement.speed + amount,
        ),
    ),
    UpgradeType.PLAYER_MAX_HEALTH: Upgrade(
        UpgradeType.PLAYER_MAX_HEALTH,
        "Player Health",
        "Increase Max Health",
        20,
        lambda player, amount: setattr(
            player.health,
            "max",
            player.health.max + int(amount),
        ),
    ),
    UpgradeType.PLAYER_RECOVER: Upgrade(
        UpgradeType.PLAYER_RECOVER,
        "Player Recover",
        "Recover Player Health",
        20,
        lambda player, amount: setattr(
            player.health,
            "current",
            player.health.current + int(amount),
        ),
    ),
    UpgradeType.BULLET_SPEED: Upgrade(
        UpgradeType.BULLET_SPEED,
        "Bullet Speed",
        "Increase Bullet Speed",
        10,
        lambda player, amount: setattr(
            player.bullet_config,
            "speed",
            player.bullet_config.speed + amount,
        ),
    ),
    UpgradeType.BULLET_DAMAGE: Upgrade(
        UpgradeType.BULLET_DAMAGE,
        "Bullet Damage",
        "Increase Bullet Damage",
        1,
        lambda player, amount: setattr(
            player.bullet_config,
            "damage",
            player.bullet_config.damage + int(amount),
        ),
    ),
    UpgradeType.BULLET_RANGE: Upgrade(
        UpgradeType.BULLET_RANGE,
        "Bullet Range",
        "Increase Bullet Range",
        1,
        lambda player, amount: setattr(
            player.bullet_config,
            "lifetime",
            player.bullet_config.lifetime + amount,
        ),
    ),
}


class UpgradeManager:
    def __init__(self, player: Player) -> None:
        self.player: Player = player

        self.choices: list[UpgradeType] = []
        self.selected_upgrade: UpgradeType = UpgradeType.NONE

    def gen_choices(self) -> None:
        upgrade_list: list[UpgradeType] = list(upgrade_db)

        for _ in range(MAX_CHOICES):
            random_choice: UpgradeType = random.choice(upgrade_list)
            upgrade_list.remove(random_choice)
            self.choices.append(random_choice)

    def update(self) -> None:
        if self.selected_upgrade == UpgradeType.NONE:
            return

        upgrade: Upgrade = upgrade_db[self.selected_upgrade]
        upgrade.apply(self.player, upgrade.amount)

        self.selected_upgrade = UpgradeType.NONE
        self.choices.clear()

    def draw(self, world_mouse: p.Vector2) -> None:
        if not self.choices:
            return

        margin: float = 100.0
        gap: float = 30.0
        usable_width: float = BASE_WIDTH - (margin * 2)
        rect_width: float = (usable_width - (gap * 2)) / MAX_CHOICES
        rect_height: float = 150.0
        rect_y: float = BASE_HEIGHT / 2.0 - rect_height / 2.0

        line_thickness: float = 5.0
        hovered: bool = False

        for i, choice in enumerate(self.choices):
            rect: p.Rectangle = p.Rectangle(
                (rect_width + gap) * i + margin, rect_y, rect_width, rect_height
            )

            hovered = p.check_collision_point_rec(world_mouse, rect)
            line_color: p.Color = p.RED if hovered else p.BLACK

            if hovered and p.is_mouse_button_pressed(p.MouseButton.MOUSE_BUTTON_LEFT):
                self.selected_upgrade = choice
                return

            p.draw_rectangle_lines_ex(rect, line_thickness, line_color)

            upgrade: Upgrade = upgrade_db[choice]

            # name
            utils.center_and_draw_text(
                utils.OriginType.TOP_LEFT,
                upgrade.name,
                rect,
                20.0,
                2.0,
                p.BLACK,
            )

            # description
            utils.center_and_draw_text(
                utils.OriginType.TOP_LEFT,
                upgrade.description,
                p.Rectangle(rect.x, rect.y, rect.width, rect.height + 100),
                10.0,
                2.0,
                p.BLACK,
            )
