import sys

import pygame as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = ""
SCREEN_BACKGROUND: str = "white"
FPS: int = 60


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

    def update(self) -> None:
        pass

    def run(self) -> None:
        while self.running:
            # delta time
            # dt: float = self.clock.tick(FPS) / 1000.0

            self.handle_events()
            self.update()
            self.draw()

            # set target fps
            self.clock.tick(FPS)

        p.quit()
        sys.exit()
