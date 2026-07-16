from enum import Enum, auto

import pyray as p

import components
import systems


class DropType(Enum):
    NONE = auto()
    XP = auto()
    HP = auto()


DROP_RADIUS: float = 20.0


class Drop:
    def __init__(self, drop_type: DropType, start_pos: p.Vector2) -> None:
        self.state: components.State = components.State(active=True)

        self.position: components.Position = components.Position(
            start_pos.x, start_pos.y
        )

        self.circle: components.Circle = components.Circle(radius=DROP_RADIUS)

        self.color: components.Color = components.Color(tint=p.ORANGE)

        self.text: components.Text = components.Text(
            text="", font_size=20.0, spacing=2.0, tint=p.WHITE
        )

        self.amount: int = 0
        self.type: DropType = drop_type

        if self.type == DropType.XP:
            self.text.text = "XP"
            self.amount = 20
        elif self.type == DropType.HP:
            self.text.text = "HP"
            self.amount = 10
        elif self.type == DropType.NONE:
            self.state.active = False
        else:
            raise ValueError("unknown drop type")

    def draw(self) -> None:
        systems.draw_circle(self.position, self.circle, self.color)

        systems.draw_centered_text(
            self.position, self.circle.radius * 2, self.circle.radius * 2, self.text
        )
