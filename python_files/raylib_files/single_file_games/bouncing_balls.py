import random

import pyray as p

BASE_WIDTH: int = 800
BASE_HEIGHT: int = 600
MAX_BALLS: int = 200


class Ball:
    def __init__(self) -> None:
        self.radius: float = random.uniform(5, 30)
        self.center: p.Vector2 = p.Vector2(
            random.uniform(self.radius, BASE_WIDTH - self.radius),
            random.uniform(self.radius, BASE_HEIGHT - self.radius),
        )
        self.speed: float = random.uniform(100, 300)
        self.direction: p.Vector2 = p.Vector2(
            random.choice([-1, 1]),
            random.choice([-1, 1]),
        )
        self.color: p.Color = p.Color(
            random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 255
        )

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float) -> None:
        self.direction = p.vector2_normalize(self.direction)

        # move
        self.center.x += self.direction.x * self.speed * dt
        self.center.y += self.direction.y * self.speed * dt

        # bounds
        if self.center.x < self.radius:
            self.center.x = self.radius
            self.direction.x *= -1

        if self.center.x > BASE_WIDTH - self.radius:
            self.center.x = BASE_WIDTH - self.radius
            self.direction.x *= -1

        if self.center.y < self.radius:
            self.center.y = self.radius
            self.direction.y *= -1

        if self.center.y > BASE_HEIGHT - self.radius:
            self.center.y = BASE_HEIGHT - self.radius
            self.direction.y *= -1


def main() -> None:
    p.set_config_flags(p.ConfigFlags.FLAG_WINDOW_RESIZABLE)

    p.init_window(BASE_WIDTH, BASE_HEIGHT, "Bouncing Balls")
    p.set_target_fps(60)

    canvas: p.RenderTexture = p.load_render_texture(BASE_WIDTH, BASE_HEIGHT)
    assert p.is_render_texture_valid(canvas)

    balls: list[Ball] = [Ball() for _ in range(MAX_BALLS)]

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        for ball in balls:
            ball.update(dt)

        p.begin_texture_mode(canvas)
        p.clear_background(p.RAYWHITE)

        for ball in balls:
            ball.draw()

        p.end_texture_mode()

        scale: float = min(
            p.get_screen_width() / BASE_WIDTH, p.get_screen_height() / BASE_HEIGHT
        )
        offset: p.Vector2 = p.Vector2(
            (p.get_screen_width() - (BASE_WIDTH * scale)) / 2,
            (p.get_screen_height() - (BASE_HEIGHT * scale)) / 2,
        )

        source: p.Rectangle = p.Rectangle(0, 0, BASE_WIDTH, -BASE_HEIGHT)
        dest: p.Rectangle = p.Rectangle(
            offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale
        )

        p.begin_drawing()
        p.clear_background(p.BLACK)

        p.draw_texture_pro(canvas.texture, source, dest, p.Vector2(0, 0), 0.0, p.WHITE)

        p.end_drawing()

    p.unload_render_texture(canvas)

    p.close_window()


if __name__ == "__main__":
    main()
