from collections import deque
from random import uniform

import pyray as p
from center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Flappy Bird"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

PLACEMENT_OFFSET: float = 10.0


class Player:
    def __init__(self) -> None:
        size: float = 40.0
        x = y = 250.0

        self.rect: p.Rectangle = p.Rectangle(x, y, size, size)
        self.color: p.Color = p.BLUE
        self.change_y: float = 0.0
        self.jump_force: float = -600.0
        self.gravity: float = 1500.0

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self, dt: float) -> None:
        # initiate jump
        if p.is_key_pressed(p.KeyboardKey.KEY_W):
            self.change_y = self.jump_force

        # jumping
        self.change_y += self.gravity * dt
        self.rect.y += self.change_y * dt

        # bounds
        self.rect.y = max(
            0.0, min(self.rect.y, SCREEN_HEIGHT - self.rect.height)
        )


class Pillar:
    def __init__(self, vertical_gap: float) -> None:
        width: float = 100.0
        height: float = uniform(0, SCREEN_HEIGHT - vertical_gap)
        x: float = SCREEN_WIDTH + PLACEMENT_OFFSET
        y: float = 0.0

        self.vertical_gap: float = vertical_gap
        self.rect: p.Rectangle = p.Rectangle(x, y, width, height)
        self.color: p.Color = p.DARKGREEN
        self.is_scored: bool = False

    def get_bottom_pillar(self) -> p.Rectangle:
        bottom_y: float = self.rect.y + self.rect.height + self.vertical_gap
        bottom_height: float = SCREEN_HEIGHT - bottom_y
        bottom_rect: p.Rectangle = p.Rectangle(
            self.rect.x, bottom_y, self.rect.width, bottom_height
        )

        return bottom_rect

    def draw(self) -> None:
        # top pillar
        p.draw_rectangle_rec(self.rect, self.color)

        # bottom pillar
        bottom_rect: p.Rectangle = self.get_bottom_pillar()

        p.draw_rectangle_rec(bottom_rect, self.color)

    def update(self, dt: float, speed: float) -> None:
        self.rect.x -= speed * dt


class PillarManager:
    def __init__(self) -> None:
        self.pillars: deque[Pillar] = deque()

        self.speed: float = 200.0
        self.speed_increment: float = 10.0
        self.vertical_gap: float = 200.0
        self.horizontal_gap: float = 400.0

    def draw(self) -> None:
        for pillar in self.pillars:
            pillar.draw()

    def update(self, dt: float) -> None:
        self.speed += self.speed_increment * dt

        # add pillar to list
        if (
            len(self.pillars) <= 0
            or self.pillars[-1].rect.x
            + self.pillars[-1].rect.width
            + self.horizontal_gap
            <= SCREEN_WIDTH
        ):
            self.pillars.append(Pillar(self.vertical_gap))

        # move
        for pillar in self.pillars:
            pillar.update(dt, self.speed)

        # remove offscreen pillar
        if (
            self.pillars[0].rect.x
            + self.pillars[0].rect.width
            + PLACEMENT_OFFSET
            <= 0
        ):
            self.pillars.popleft()


class GameManager:
    def reset(self) -> None:
        self.score: int = 0
        self.game_over: bool = False

        self.player: Player = Player()
        self.pillar_manager: PillarManager = PillarManager()

    def __init__(self) -> None:
        self.reset()

    def draw_game_status(self) -> None:
        text: str = "GAME OVER"

        # outline rect
        width: float = 300.0
        height: float = 150.0
        x: float = SCREEN_WIDTH / 2.0 - width / 2.0
        y: float = SCREEN_HEIGHT / 2.0 - height / 2.0
        rect: p.Rectangle = p.Rectangle(x, y, width, height)
        thickness: float = 5.0
        color: p.Color = p.BLACK

        p.draw_rectangle_lines_ex(rect, thickness, color)

        center_and_draw_text(text, rect, color=p.BLACK)

    def draw(self) -> None:
        self.player.draw()
        self.pillar_manager.draw()

        # draw score
        p.draw_text(str(self.score), 50, 50, 30, p.BLACK)

        if self.game_over:
            self.draw_game_status()

    def update(self, dt: float) -> None:
        if not self.game_over:
            dt: float = p.get_frame_time()

            self.player.update(dt)
            self.pillar_manager.update(dt)

            for pillar in self.pillar_manager.pillars:
                # update score
                if (
                    not pillar.is_scored
                    and self.player.rect.x > pillar.rect.x + pillar.rect.width
                ):
                    pillar.is_scored = True
                    self.score += 1

                # player collision pillars

                # top pillar
                if p.check_collision_recs(self.player.rect, pillar.rect):
                    self.game_over = True

                # bottom pillar
                bottom_pillar: p.Rectangle = pillar.get_bottom_pillar()

                if p.check_collision_recs(self.player.rect, bottom_pillar):
                    self.game_over = True

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                self.reset()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        game_manager.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
