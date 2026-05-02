import pyray as p

import components
import systems
from bullet import BulletConfig
from settings import MAP_SIZE


class Player:
    def __init__(self) -> None:
        self.level: components.Level = components.Level(level=1)
        self.xp: components.Xp = components.Xp(
            xp=0, xp_next=systems.get_xp_next(self.level), pending_levelups=0
        )
        self.position: components.Position = components.Position(
            x=MAP_SIZE / 2.0, y=MAP_SIZE / 2.0
        )
        size: float = 40.0
        self.rect: components.Rect = components.Rect(width=size, height=size)
        self.rotation: components.Rotation = components.Rotation(angle=0.0)
        self.color: components.Color = components.Color(tint=p.BLUE)
        self.text: components.Text = components.Text(
            text="P", font_size=20.0, spacing=0.0, tint=p.WHITE
        )
        self.move: components.Move = components.Move(
            speed=120.0, direction=p.Vector2(0, 0)
        )
        max_hp: int = 100
        self.health: components.Health = components.Health(max=max_hp, current=max_hp)
        self.animation: components.Animation = components.Animation(
            max_hit_timer=0.2, hit_timer=0.0
        )

        self.bullet_timer: components.Timer = components.Timer(
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
            self.text, systems.get_dest_rect(self.position, self.rect)
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
        systems.move(self.position, self.move, dt)
        systems.set_bounds(
            self.position,
            self.rect.width / 2.0,
            self.rect.height / 2.0,
            bounds_rect=p.Rectangle(0, 0, MAP_SIZE, MAP_SIZE),
        )
        systems.update_animation(self.animation, dt)
