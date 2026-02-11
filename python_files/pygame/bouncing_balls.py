import random
import sys

import pygame as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "Bouncing Balls"
SCREEN_BACKGROUND: str = "white"
FPS: int = 60


class Ball:
    def __init__(self) -> None:
        self.radius: float = random.uniform(5, 30)
        self.center: p.math.Vector2 = p.math.Vector2(
            random.uniform(self.radius, SCREEN_WIDTH - self.radius),
            random.uniform(self.radius, SCREEN_HEIGHT - self.radius),
        )
        self.speed: float = random.uniform(100, 300)
        self.direction: p.math.Vector2 = p.math.Vector2(
            -1 if random.randint(0, 1) == 0 else 1,
            -1 if random.randint(0, 1) == 0 else 1,
        )
        self.color: p.Color = p.Color(
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255),
        )

    def draw(self, surface: p.Surface) -> None:
        p.draw.circle(surface, self.color, self.center, self.radius)

    def update(self, dt: float) -> None:
        # move
        self.center.x += self.direction.x  * self.speed * dt
        self.center.y += self.direction.y  * self.speed * dt

        # bounds
        if self.center.x < self.radius || self.center.x > SCREEN_WIDTH - self.radius:
            self.direction.x *= -1
        if self.center.y < self.radius || self.center.y > SCREEN_HEIGHT - self.radius:
            self.direction.y *= -1


class Game:
    def __init__(self) -> None:
        p.init()

        self.screen: p.Surface = p.display.set_mode(
            (SCREEN_WIDTH, SCREEN_HEIGHT)
        )
        p.display.set_caption(SCREEN_TITLE)

        self.clock: p.time.Clock = p.time.Clock()
        self.running: bool = False

    def handle_events(self) -> None:
        for event in p.event.get():
            if event.type == p.QUIT:
                self.running = False

    def draw(self) -> None:
        self.screen.fill(SCREEN_BACKGROUND)

        p.display.flip()

    def update(self, dt: float) -> None:
        pass

    def run(self) -> None:
        while self.running:
            # delta time
            dt: float = self.clock.tick(FPS) / 1000.0

            self.handle_events()
            self.update(dt)
            self.draw()

        p.quit()
        sys.exit()
