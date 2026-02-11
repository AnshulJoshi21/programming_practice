import pygame
import random
from pygame.math import Vector2


SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Bouncing Balls"
SCREEN_BACKGROUND: str = "white"


class Ball:
    def __init__(self) -> None:
        self.radius: float = random.uniform(5, 30)
        self.center: Vector2 = Vector2(
            random.uniform(self.radius, SCREEN_WIDTH - self.radius),
            random.uniform(self.radius, SCREEN_HEIGHT - self.radius),
        )
        self.speed: float = random.uniform(100, 300)
        self.direction: Vector2 = Vector2(
            -1 if random.randint(0, 1) == 0 else 1,
            -1 if random.randint(0, 1) == 0 else 1,
        )
        self.color: pygame.Color = pygame.Color(
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255),
        )

    def draw(self, surface: pygame.Surface) -> None:
        pygame.draw.circle(surface, self.color, self.center, self.radius)

    def update(self, dt: float) -> None:
        self.center += self.direction * self.speed * dt


def main() -> None:
    pass


if __name__ == "__main__":
    main()
