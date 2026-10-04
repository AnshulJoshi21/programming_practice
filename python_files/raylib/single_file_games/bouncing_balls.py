import random

import pyray as p

SCREEN_WIDTH: int = 1280
SCREEN_HEIGHT: int = 720
MAX_BALLS: int = 400


class Ball:
    def __init__(self) -> None:
        self.radius: float = random.uniform(5, 40)
        self.center: p.Vector2 = p.Vector2(
            random.uniform(self.radius, SCREEN_WIDTH - self.radius),
            random.uniform(self.radius, SCREEN_HEIGHT - self.radius),
        )
        self.speed: float = random.uniform(100, 300)
        self.direction: p.Vector2 = p.Vector2(
            random.choice([-1, 1]), random.choice([-1, 1])
        )
        self.color: p.Color = p.Color(
            random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 255
        )

    def update(self, dt: float) -> None:
        self.direction = p.vector2_normalize(self.direction)

        # move
        self.center.x += self.direction.x * self.speed * dt
        self.center.y += self.direction.y * self.speed * dt

        # set bounds
        if self.center.x < self.radius:
            self.center.x = self.radius
            self.direction.x *= -1

        if self.center.x > SCREEN_WIDTH - self.radius:
            self.center.x = SCREEN_WIDTH - self.radius
            self.direction.x *= -1

        if self.center.y < self.radius:
            self.center.y = self.radius
            self.direction.y *= -1

        if self.center.y > SCREEN_HEIGHT - self.radius:
            self.center.y = SCREEN_HEIGHT - self.radius
            self.direction.y *= -1

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)


def main() -> None:
    p.set_config_flags(p.ConfigFlags.FLAG_WINDOW_RESIZABLE)
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncing Balls")
    p.set_target_fps(60)

    canvas: p.RenderTexture = p.load_render_texture(SCREEN_WIDTH, SCREEN_HEIGHT)
    assert p.is_render_texture_valid(canvas)

    world_mouse: p.Vector2

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
            p.get_screen_width() / SCREEN_WIDTH, p.get_screen_height() / SCREEN_HEIGHT
        )
        offset: p.Vector2 = p.Vector2(
            (p.get_screen_width() - (SCREEN_WIDTH * scale)) / 2.0,
            (p.get_screen_height() - (SCREEN_HEIGHT * scale)) / 2.0,
        )

        source: p.Rectangle = p.Rectangle(0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT)
        dest: p.Rectangle = p.Rectangle(
            offset.x, offset.y, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale
        )

        world_mouse = p.Vector2(
            (p.get_mouse_x() - offset.x) / scale, (p.get_mouse_y() - offset.y) / scale
        )

        p.begin_drawing()
        p.clear_background(p.BLACK)

        p.draw_texture_pro(canvas.texture, source, dest, p.Vector2(0, 0), 0.0, p.WHITE)

        p.end_drawing()

    p.unload_render_texture(canvas)

    p.close_window()


if __name__ == "__main__":
    main()
