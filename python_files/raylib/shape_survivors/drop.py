import pyray as p

import components
import systems
from drop_type import DropType


class Drop:
    def __init__(self, type: DropType, start_pos: p.Vector2) -> None:
        self.state: components.State = components.State(active=True)
        self.position: components.Position = components.Position(
            start_pos.x, start_pos.y
        )
        self.circle: components.Circle = components.Circle(radius=10.0)
        self.color: components.Color = components.Color(tint=p.BLACK)

        self.drop: components.Drop = components.Drop(type=type, amount=0)

        match type:
            case DropType.XP:
                self.drop.amount += 10
                self.color.tint = p.SKYBLUE
            case DropType.HP:
                self.drop.amount += 20
                self.color.tint = p.RED
            case DropType.GOLD:
                self.drop.amount += 100
                self.color.tint = p.GOLD

    def draw(self) -> None:
        if self.state.active:
            systems.draw_circle(self.position, self.circle, self.color)
