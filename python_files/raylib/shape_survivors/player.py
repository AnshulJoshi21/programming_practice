import pyray as p

import components as c
import systems
from bullet import BulletConfig
from settings import MAP_SIZE


class Player:
    def __init__(self) -> None:
        self.level: c.LevelComponent = c.LevelComponent(current=1, pending=0)
        self.xp: c.XpComponent = c.XpComponent(xp=0, xp_next=0)
        self.xp.xp_next = systems.get_xp_next(self.level)
        self.position: c.PositionComponent = c.PositionComponent(
            x=MAP_SIZE / 2.0, y=MAP_SIZE / 2.0
        )
        self.rect: c.RectComponent = c.RectComponent(width=40.0, height=40.0)
        self.rotation: c.RotationComponent = c.RotationComponent(angle=0.0)
        self.color: c.ColorComponent = c.ColorComponent(tint=p.BLUE)
        self.text: c.TextComponent = c.TextComponent(string="P")
        self.move: c.MoveComponent = c.MoveComponent(
            speed=120.0, direction=p.Vector2(0, 0)
        )
        self.health: c.HealthComponent = c.HealthComponent(max_hp=100, hp=100)
        self.animation: c.AnimationComponent = c.AnimationComponent(hit_timer=0.0)
        self.bullet_timer: c.TimerComponent = c.TimerComponent(
            elapsed=p.get_time(), interval=1.0
        )
        self.bullet_config: BulletConfig = BulletConfig(
            speed=300.0, damage=1, lifetime=1.0
        )

    def draw(self) -> None:
        systems.draw_rect(
            self.position, self.rect, self.rotation, self.color, self.animation
        )
        systems.draw_centered_text(
            text=self.text,
            bounds_rect=p.Rectangle(
                self.position.x, self.position.y, self.rect.width, self.rect.height
            ),
            font_size=20,
            spacing=0.0,
            tint=p.WHITE,
        )

    def handle_input(self) -> None:
        self.move.direction.x = int(p.is_key_down(p.KeyboardKey.KEY_D)) - int(
            p.is_key_down(p.KeyboardKey.KEY_A)
        )
        self.move.direction.y = int(p.is_key_down(p.KeyboardKey.KEY_S)) - int(
            p.is_key_down(p.KeyboardKey.KEY_W)
        )

        self.move.direction = p.vector2_normalize(self.move.direction)

    def update(self, dt: float) -> None:
        self.handle_input()
        systems.move_entity(self.position, self.move, dt)
        systems.set_bounds(
            self.position,
            self.rect.width / 2.0,
            self.rect.height / 2.0,
            p.Rectangle(0, 0, MAP_SIZE, MAP_SIZE),
        )
        systems.update_hit_timer(self.animation, dt)
