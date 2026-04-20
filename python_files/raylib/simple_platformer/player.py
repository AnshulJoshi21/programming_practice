import pyray as p

from settings import MAP_SIZE


class Player:
    def __init__(self) -> None:
        size: float = 40.0
        x: float = 10.0
        y: float = 10.0

        self.rect: p.Rectangle = p.Rectangle(x, y, size, size)
        self.color: p.Color = p.BLUE
        self.speed: float = 300.0

        self.change_y: float = 0.0
        self.jump_force: float = -600
        self.gravity: float = 1200
        self.can_jump: bool = True

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self, dt: float) -> None:
        # initiate jump
        if p.is_key_pressed(p.KeyboardKey.KEY_W) and self.can_jump:
            self.can_jump = False
            self.change_y = self.jump_force

        # move horizontally
        if p.is_key_down(p.KeyboardKey.KEY_A):
            self.rect.x -= self.speed * dt
        if p.is_key_down(p.KeyboardKey.KEY_D):
            self.rect.x += self.speed * dt

        # jumping
        if not self.can_jump:
            self.rect.y += self.change_y * dt

        # apply gravity
        self.change_y += self.gravity * dt

        # hit ground
        if self.rect.y + self.rect.height == MAP_SIZE:
            self.can_jump = True

        # bounds
        self.rect.x = max(0, min(self.rect.x, MAP_SIZE - self.rect.width))
        self.rect.y = max(
            0,
            min(self.rect.y, MAP_SIZE - self.rect.height),
        )
