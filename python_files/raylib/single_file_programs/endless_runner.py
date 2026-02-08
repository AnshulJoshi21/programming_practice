from collections import deque
from random import uniform

import pyray as p
from center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 200
SCREEN_TITLE: str = "Endless Runner"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

ENTITY_WIDTH: float = 20.0
PLACEMENT_OFFSET: float = 10.0


class Player:
    def __init__(self) -> None:
        height: float = 50.0
        x: float = 150.0
        y: float = SCREEN_HEIGHT - height

        self.rect: p.Rectangle = p.Rectangle(x, y, ENTITY_WIDTH, height)
        self.color: p.Color = p.BLUE
        self.change_y: float = 0.0
        self.jump_force: float = -550.0
        self.gravity: float = 1500.0
        self.can_jump: float = True

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self, dt: float) -> None:
        # initiate jump
        if p.is_key_pressed(p.KeyboardKey.KEY_W) and self.can_jump:
            self.can_jump = False
            self.change_y = self.jump_force

        # jumping
        self.change_y += self.gravity * dt
        self.rect.y += self.change_y * dt

        # hit ground
        if self.rect.y + self.rect.height > SCREEN_HEIGHT:
            self.can_jump = True

        # bounds
        self.rect.y = max(
            0.0, min(self.rect.y, SCREEN_HEIGHT - self.rect.height)
        )


class Enemy:
    def __init__(self) -> None:
        height: float = uniform(50, 80)
        x: float = SCREEN_WIDTH + PLACEMENT_OFFSET
        y: float = SCREEN_HEIGHT - height

        self.rect: p.Rectangle = p.Rectangle(x, y, ENTITY_WIDTH, height)
        self.color: p.Color = p.DARKGREEN
        self.is_scored: bool = False

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self, dt: float, speed: float) -> None:
        self.rect.x -= speed * dt


class EnemyManager:
    def __init__(self) -> None:
        self.enemies: deque[Enemy] = deque()
        self.speed: float = 200.0
        self.speed_increment: float = 10.0
        self.horizontal_gap: float = 400.0

    def draw(self) -> None:
        for enemy in self.enemies:
            enemy.draw()

    def update(self, dt: float) -> None:
        self.speed += self.speed_increment * dt

        # add enemies to list/deque
        if (
            len(self.enemies) <= 0
            or self.enemies[-1].rect.x
            + self.enemies[-1].rect.width
            + self.horizontal_gap
            <= SCREEN_WIDTH
        ):
            self.enemies.append(Enemy())

        # move
        for enemy in self.enemies:
            enemy.update(dt, self.speed)

        # remove offscreen enemy
        if (
            self.enemies[0].rect.x
            + self.enemies[0].rect.width
            + PLACEMENT_OFFSET
            <= 0
        ):
            self.enemies.popleft()


class GameManager:
    def reset(self) -> None:
        self.score: int = 0
        self.game_over: bool = False

        self.player: Player = Player()
        self.enemy_manager: EnemyManager = EnemyManager()

    def __init__(self) -> None:
        self.reset()

    def draw(self) -> None:
        p.draw_text(str(self.score), 20, 20, 30, p.BLACK)

        self.player.draw()
        self.enemy_manager.draw()

        if self.game_over:
            center_and_draw_text(
                "GAME OVER", p.Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
            )

    def update(self, dt: float) -> None:
        if not self.game_over:
            self.player.update(dt)
            self.enemy_manager.update(dt)

            # player collision enemy
            for enemy in self.enemy_manager.enemies:
                # game over condition
                if p.check_collision_recs(self.player.rect, enemy.rect):
                    self.game_over = True

                # update score
                if (
                    not enemy.is_scored
                    and self.player.rect.x > enemy.rect.x + enemy.rect.width
                ):
                    self.score += 1
                    enemy.is_scored = True

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
