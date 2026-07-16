import pyray as p

import components
import systems
from bullet import BulletConfig
from settings import MAP_SIZE

PLAYER_SIZE: float = 40.0
PLAYER_MAX_HEALTH: int = 100
PLAYER_MAX_HIT_TIMER: float = 0.2

PLAYER_BULLET_SPAWN_INTERVAL: float = 1.0


class Player:
    def __init__(self) -> None:
        self.level: components.Level = components.Level(
            current=1,
            pending=0,
        )

        self.xp: components.Xp = components.Xp(
            current=0,
            next=systems.get_xp_next(self.level),
        )

        self.position: components.Position = components.Position(
            x=MAP_SIZE / 2.0,
            y=MAP_SIZE / 2.0,
        )

        self.rect: components.Rect = components.Rect(
            width=PLAYER_SIZE, height=PLAYER_SIZE
        )

        self.rotation: components.Rotation = components.Rotation(angle=0.0)

        self.color: components.Color = components.Color(tint=p.BLUE)

        self.text: components.Text = components.Text(
            text="P",
            font_size=20.0,
            spacing=0.0,
            tint=p.WHITE,
        )

        self.movement: components.Movement = components.Movement(
            speed=120.0,
            direction=p.Vector2(0, 0),
        )

        self.health: components.Health = components.Health(
            max=PLAYER_MAX_HEALTH,
            current=PLAYER_MAX_HEALTH,
        )

        self.animation: components.Animation = components.Animation(
            max_hit_timer=PLAYER_MAX_HIT_TIMER,
            hit_timer=0.0,
        )

        self.bullet_timer: components.Timer = components.Timer(
            elapsed=p.get_time(),
            interval=PLAYER_BULLET_SPAWN_INTERVAL,
        )

        self.bullet_config: BulletConfig = BulletConfig(
            damage=1,
            speed=300.0,
            lifetime=1.0,
        )

    def handle_input(self) -> None:
        self.movement.direction.x = float(p.is_key_down(p.KeyboardKey.KEY_D)) - float(
            p.is_key_down(p.KeyboardKey.KEY_A)
        )
        self.movement.direction.y = float(p.is_key_down(p.KeyboardKey.KEY_S)) - float(
            p.is_key_down(p.KeyboardKey.KEY_W)
        )

        self.movement.direction = p.vector2_normalize(self.movement.direction)

    def update(self, dt: float) -> None:
        systems.update_xp(self.level, self.xp)

        self.handle_input()
        systems.move(self.position, self.movement, dt)
        systems.set_bounds(
            self.position,
            self.rect.width / 2.0,
            self.rect.height / 2.0,
            p.Rectangle(0, 0, MAP_SIZE, MAP_SIZE),
        )
        systems.update_hit_timer(self.animation, dt)
        systems.update_health(self.health)

    def draw(self) -> None:
        systems.draw_rect(
            self.position, self.rotation, self.rect, self.color, self.animation
        )

        systems.draw_centered_text(
            self.position, self.rect.width, self.rect.height, self.text
        )
