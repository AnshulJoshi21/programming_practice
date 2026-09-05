from collections import deque

import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 200


class Player:
    def __init__(self) -> None:
        width: float = 20.0
        height: float = 50.0
        self.rect: p.Rectangle = p.Rectangle(
            200, p.get_screen_height() - height, width, height
        )
        self.color: p.Color = p.BLUE
        self.change_y: float = 0.0
        self.jump_force: float = 500.0
        self.gravity: float = 1200.0
        self.can_jump: bool = True

    def update(self, dt: float) -> None:
        # initiate jump
        if p.is_key_pressed(p.KeyboardKey.KEY_W) and self.can_jump:
            self.can_jump = False
            self.change_y = -self.jump_force

        self.change_y += self.gravity * dt
        self.rect.y += self.change_y * dt

        if self.rect.y + self.rect.height >= p.get_screen_height():
            self.can_jump = True
            self.change_y = 0.0

        # set bounds
        self.rect.y = max(0, min(self.rect.y, p.get_screen_height() - self.rect.height))

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


class Enemy:
    def __init__(self) -> None:
        self.rect: p.Rectangle = p.Rectangle()
        self.color: p.Color = p.DARKGREEN

    def update(self, dt: float, speed: float) -> None:
        self.rect.x -= speed * dt

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


class EnemyManager:
    def __init__(self) -> None:
        self.enemies: deque[Enemy] = deque()

        self.speed: float = 300.0
        self.speed_increment: float = 10.0

    def update(self, dt: float) -> None:
        # update speed
        self.speed += self.speed_increment * dt

        for enemy in self.enemies:
            enemy.update(dt, self.speed)

    def draw(self) -> None:
        for enemy in self.enemies:
            enemy.draw()


class GameManager:
    def __init__(self) -> None:
        self.score: int = 0
        self.game_over: bool = False

        self.player: Player = Player()
        self.enemy_manager: EnemyManager = EnemyManager()

    def update(self, dt) -> None:
        self.player.update(dt)
        self.enemy_manager.update(dt)

    def draw(self) -> None:
        # draw score
        p.draw_text(str(self.score), 20, 10, 30, p.BLACK)

        self.player.draw()
        self.enemy_manager.draw()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless Runner")

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_drawing()
        p.clear_background(p.LIGHTGRAY)

        game_manager.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
