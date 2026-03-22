import pyray as p

import utils as u
from bullet_manager import BulletManager
from settings import MAP_SIZE


class Player:
    def __init__(self) -> None:
        size: float = 40.0
        x: float = MAP_SIZE / 2.0 - size / 2.0
        y: float = MAP_SIZE / 2.0 - size / 2.0

        self.rect: p.Rectangle = p.Rectangle(x, y, size, size)
        self.color: p.Color = p.GRAY

        self.speed: float = 150.0
        self.direction: p.Vector2 = p.Vector2(0, 0)

        self.max_hp: int = 100
        self.hp: int = self.max_hp

        self.bullet_manager: BulletManager = BulletManager()

    def draw(self) -> None:
        self.bullet_manager.draw()
        p.draw_rectangle_rec(self.rect, self.color)

        u.utils_center_and_draw_text("P", self.rect)

    def handle_input(self) -> None:
        self.direction.x = int(p.is_key_down(p.KeyboardKey.KEY_D)) - int(
            p.is_key_down(p.KeyboardKey.KEY_A)
        )
        self.direction.y = int(p.is_key_down(p.KeyboardKey.KEY_S)) - int(
            p.is_key_down(p.KeyboardKey.KEY_W)
        )

        self.direction = p.vector2_normalize(self.direction)

    def move(self, dt: float) -> None:
        self.rect.x += self.direction.x * self.speed * dt
        self.rect.y += self.direction.y * self.speed * dt

    def bounds(self) -> None:
        self.rect.x = max(0.0, min(self.rect.x, MAP_SIZE - self.rect.width))
        self.rect.y = max(0.0, min(self.rect.y, MAP_SIZE - self.rect.height))

    def update(self, dt: float, target_pos: p.Vector2) -> None:
        self.handle_input()
        self.move(dt)
        self.bounds()

        origin: p.Vector2 = u.utils_get_rect_origin(self.rect)
        self.bullet_manager.update(
            dt, start_pos=p.Vector2(origin.x, origin.y), target_pos=target_pos
        )
