import pyray as p

import components as c
import systems
from drop_type import DropType


class Drop:
    def __init__(self, drop_type: DropType, start_pos: p.Vector2) -> None:

        self.state: c.StateComponent = c.StateComponent(active=True)

        self.position: c.PositionComponent = c.PositionComponent(
            x=start_pos.x, y=start_pos.y
        )
        self.circle: c.CircleComponent = c.CircleComponent(radius=20.0)
        self.color: c.ColorComponent = c.ColorComponent(tint=p.GRAY)

        self.text: c.TextComponent
        self.drop: c.DropComponent = c.DropComponent(type=drop_type, amount=0)

        match drop_type:
            case DropType.XP:
                self.text = c.TextComponent(string="XP")
                self.drop.amount = 20
            case DropType.HP:
                self.text = c.TextComponent(string="HP")
                self.drop.amount = 10

    def draw(self) -> None:
        if self.state.active:
            systems.draw_circle(self.position, self.circle, self.color)
            systems.draw_centered_text(
                text=self.text,
                bounds_rect=p.Rectangle(
                    self.position.x,
                    self.position.y,
                    self.circle.radius * 2,
                    self.circle.radius * 2,
                ),
                font_size=20,
                spacing=2.0,
                tint=p.WHITE,
            )
