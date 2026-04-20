import random
from enum import IntEnum
from typing import TypedDict

import pyray as p

import systems
import utils
from player import Player

MAX_CHOICES: int = 3


class UpgradeType(IntEnum):
    player_hp = 0
    player_speed = 1
    bullet_damage = 2
    bullet_speed = 3
    bullet_lifetime = 4


class Upgrade(TypedDict):
    name: str
    desc: str
    amount: int | float


upgrade_db: dict[UpgradeType, Upgrade] = {
    UpgradeType.player_hp: {"name": "PLAYER HP", "desc": "Increase xp", "amount": 10},
    UpgradeType.player_speed: {
        "name": "PLAYER SPEED",
        "desc": "Increase speed",
        "amount": 10,
    },
    UpgradeType.bullet_damage: {
        "name": "BULLET DAMAGE",
        "desc": "Increase bullet damage",
        "amount": 1,
    },
    UpgradeType.bullet_speed: {
        "name": "BULLET SPEED",
        "desc": "Increase bullet speed",
        "amount": 10,
    },
    UpgradeType.bullet_lifetime: {
        "name": "BULLET LIFETIME",
        "desc": "Increase bullet range",
        "amount": 0.5,
    },
}


class UpgradeManager:
    def __init__(self, player: Player) -> None:
        self.player: Player = player
        self.current_upgrade: UpgradeType | None = None
        self.choices: list[UpgradeType] = []

    def draw(self) -> None:
        if self.current_upgrade or len(self.choices) <= 0:
            return

        # choice box
        margin: float = 50.0
        gap: float = 30.0
        cb_width: float = (
            p.get_screen_width() - (gap * (MAX_CHOICES - 1)) - (margin * 2)
        ) / MAX_CHOICES
        cb_height: float = 150.0
        cb_outline_thickness: float = 5.0
        cb_y: float = (p.get_screen_height() - cb_height) / 2.0

        for i, upgrade_type in enumerate(self.choices):
            cb_x: float = margin + (i * (cb_width + gap))

            cb_rect: p.Rectangle = p.Rectangle(cb_x, cb_y, cb_width, cb_height)

            is_hovered: bool = p.check_collision_point_rec(
                p.get_mouse_position(), cb_rect
            )

            if is_hovered and p.is_mouse_button_pressed(
                p.MouseButton.MOUSE_BUTTON_LEFT
            ):
                self.current_upgrade = upgrade_type
                break

            cb_outline_color: p.Color = p.RED if is_hovered else p.BLACK

            # draw choice boxes
            p.draw_rectangle_lines_ex(
                cb_rect,
                cb_outline_thickness,
                cb_outline_color,
            )

            # draw choices
            utils.center_and_draw_text(
                origin_type=utils.OriginType.top_left,
                text=upgrade_db[upgrade_type]["name"],
                bounds_rect=cb_rect,
                font_size=20.0,
                spacing=2.0,
                tint=cb_outline_color,
            )

            utils.center_and_draw_text(
                origin_type=utils.OriginType.top_left,
                text=upgrade_db[upgrade_type]["desc"],
                bounds_rect=p.Rectangle(cb_x, cb_y, cb_width, cb_height + 50),
                font_size=15.0,
                spacing=2.0,
                tint=cb_outline_color,
            )

    def fill_choices_array(self) -> None:
        available_upgrades: list[UpgradeType] = list(UpgradeType)

        for _ in range(MAX_CHOICES):
            random_choice: UpgradeType = random.choice(available_upgrades)
            available_upgrades.remove(random_choice)
            self.choices.append(random_choice)

    def apply_upgrade(self) -> None:
        match self.current_upgrade:
            case UpgradeType.player_hp:
                self.player.health.hp += int(
                    upgrade_db[UpgradeType.player_hp]["amount"]
                )
            case UpgradeType.player_speed:
                self.player.move.speed += float(
                    upgrade_db[UpgradeType.player_speed]["amount"]
                )
            case UpgradeType.bullet_damage:
                self.player.bullet_config.damage += int(
                    upgrade_db[UpgradeType.bullet_damage]["amount"]
                )
            case UpgradeType.bullet_speed:
                self.player.bullet_config.speed += float(
                    upgrade_db[UpgradeType.bullet_speed]["amount"]
                )
            case UpgradeType.bullet_lifetime:
                self.player.bullet_config.lifetime += float(
                    upgrade_db[UpgradeType.bullet_lifetime]["amount"]
                )

    def update(self) -> None:
        if not self.current_upgrade and len(self.choices) <= 0:
            self.fill_choices_array()

        if self.current_upgrade:
            self.apply_upgrade()
            systems.consume_levelup(self.player.level)

            # reset
            self.current_upgrade = None
            self.choices = []
