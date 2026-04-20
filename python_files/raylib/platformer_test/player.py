from enum import IntEnum

import pyray as p

from settings import MAP_SIZE


class PlayerAnimationState(IntEnum):
    idle = 0
    run = 1
    attack = 2
    death = 3
    hurt = 4
    jump = 5
    upto_fall = 6
    fall = 7
    edge_grab = 8
    edge_idle = 9
    wall_slide = 10
    crouch = 11
    dash = 12
    dash_attack = 13
    slide = 14
    ladder_grab = 15


class Player:
    def __init__(self, sprite_dict: dict[str, p.Rectangle]) -> None:
        self.current_sprite: str = "idle_1"
        self.current_anim_state: PlayerAnimationState = PlayerAnimationState.idle
        self.frame_index: int = 0
        self.frame_timer: float = 0.0
        self.frame_speed: float = 0.1

        self.animations: dict[PlayerAnimationState, list[p.Rectangle]] = {
            PlayerAnimationState.idle: [
                sprite_dict["idle_1"],
                sprite_dict["idle_2"],
                sprite_dict["idle_3"],
                sprite_dict["idle_4"],
                sprite_dict["idle_5"],
                sprite_dict["idle_6"],
            ],
            PlayerAnimationState.run: [
                sprite_dict["run_1"],
                sprite_dict["run_2"],
                sprite_dict["run_3"],
                sprite_dict["run_4"],
                sprite_dict["run_5"],
                sprite_dict["run_6"],
                sprite_dict["run_7"],
                sprite_dict["run_8"],
            ],
            PlayerAnimationState.attack: [
                sprite_dict["attack_1"],
                sprite_dict["attack_2"],
                sprite_dict["attack_3"],
                sprite_dict["attack_4"],
                sprite_dict["attack_5"],
                sprite_dict["attack_6"],
                sprite_dict["attack_7"],
                sprite_dict["attack_8"],
                sprite_dict["attack_9"],
                sprite_dict["attack_10"],
                sprite_dict["attack_11"],
                sprite_dict["attack_12"],
            ],
            PlayerAnimationState.death: [
                sprite_dict["death_1"],
                sprite_dict["death_2"],
                sprite_dict["death_3"],
                sprite_dict["death_4"],
                sprite_dict["death_5"],
                sprite_dict["death_6"],
                sprite_dict["death_7"],
                sprite_dict["death_8"],
                sprite_dict["death_9"],
                sprite_dict["death_10"],
                sprite_dict["death_11"],
            ],
            PlayerAnimationState.hurt: [
                sprite_dict["hurt_1"],
                sprite_dict["hurt_2"],
                sprite_dict["hurt_3"],
                sprite_dict["hurt_4"],
            ],
            PlayerAnimationState.jump: [
                sprite_dict["jump_1"],
                sprite_dict["jump_2"],
                sprite_dict["jump_3"],
            ],
            PlayerAnimationState.upto_fall: [
                sprite_dict["upto_fall_1"],
                sprite_dict["upto_fall_2"],
            ],
            PlayerAnimationState.fall: [
                sprite_dict["fall_1"],
                sprite_dict["fall_2"],
                sprite_dict["fall_3"],
            ],
            PlayerAnimationState.edge_grab: [
                sprite_dict["edge_grab_1"],
                sprite_dict["edge_grab_2"],
                sprite_dict["edge_grab_3"],
                sprite_dict["edge_grab_4"],
                sprite_dict["edge_grab_5"],
            ],
            PlayerAnimationState.edge_idle: [
                sprite_dict["edge_idle_1"],
                sprite_dict["edge_idle_2"],
                sprite_dict["edge_idle_3"],
                sprite_dict["edge_idle_4"],
                sprite_dict["edge_idle_5"],
                sprite_dict["edge_idle_6"],
            ],
            PlayerAnimationState.wall_slide: [
                sprite_dict["wall_slide_1"],
                sprite_dict["wall_slide_2"],
                sprite_dict["wall_slide_3"],
            ],
            PlayerAnimationState.crouch: [
                sprite_dict["crouch_1"],
                sprite_dict["crouch_2"],
                sprite_dict["crouch_3"],
                sprite_dict["crouch_4"],
                sprite_dict["crouch_5"],
                sprite_dict["crouch_6"],
            ],
            PlayerAnimationState.dash: [
                sprite_dict["dash_1"],
                sprite_dict["dash_2"],
                sprite_dict["dash_3"],
                sprite_dict["dash_4"],
                sprite_dict["dash_5"],
                sprite_dict["dash_6"],
                sprite_dict["dash_7"],
            ],
            PlayerAnimationState.dash_attack: [
                sprite_dict["dash_attack_1"],
                sprite_dict["dash_attack_2"],
                sprite_dict["dash_attack_3"],
                sprite_dict["dash_attack_4"],
                sprite_dict["dash_attack_5"],
                sprite_dict["dash_attack_6"],
                sprite_dict["dash_attack_7"],
                sprite_dict["dash_attack_8"],
                sprite_dict["dash_attack_9"],
                sprite_dict["dash_attack_10"],
            ],
            PlayerAnimationState.slide: [
                sprite_dict["slide_1"],
                sprite_dict["slide_2"],
                sprite_dict["slide_3"],
                sprite_dict["slide_4"],
                sprite_dict["slide_5"],
            ],
            PlayerAnimationState.ladder_grab: [
                sprite_dict["ladder_grab_1"],
                sprite_dict["ladder_grab_2"],
                sprite_dict["ladder_grab_3"],
                sprite_dict["ladder_grab_4"],
                sprite_dict["ladder_grab_5"],
                sprite_dict["ladder_grab_6"],
                sprite_dict["ladder_grab_7"],
                sprite_dict["ladder_grab_8"],
            ],
        }

        self.source: p.Rectangle = sprite_dict[self.current_sprite]
        self.scale: float = 3.0

        width: float = self.source.width * self.scale
        height: float = self.source.height * self.scale
        x: float = 100.0
        y: float = MAP_SIZE - height
        self.dest: p.Rectangle = p.Rectangle(x, y, width, height)
        self.origin: p.Vector2 = p.Vector2(width / 2.0, height / 2.0)
        self.rotation: float = 0.0
        self.tint: p.Color = p.WHITE

        self.speed: float = 300.0
        self.change_y: float = 0.0
        self.jump_force: float = -500.0
        self.gravity: float = 900.0
        self.can_jump: bool = False

    def draw(self, sheet: p.Texture) -> None:

        p.draw_texture_pro(
            sheet, self.source, self.dest, self.origin, self.rotation, self.tint
        )

        p.draw_rectangle_lines_ex(
            p.Rectangle(
                self.dest.x - self.origin.x,
                self.dest.y - self.origin.y,
                self.dest.width,
                self.dest.height,
            ),
            2.0,
            p.GRAY,
        )

    def update(self, dt: float) -> None:

        # set animation state
        if not self.can_jump:
            self.current_anim_state = PlayerAnimationState.jump
        elif p.is_key_down(p.KeyboardKey.KEY_D) or p.is_key_down(p.KeyboardKey.KEY_A):
            self.current_anim_state = PlayerAnimationState.run
        else:
            self.current_anim_state = PlayerAnimationState.idle

        # reset animation
        if self.current_anim_state != getattr(self, "prev_state", None):
            self.frame_index = 0
            self.frame_timer = 0.0
            self.prev_state: PlayerAnimationState = self.current_anim_state

        # animation
        frames: list[p.Rectangle] = self.animations[self.current_anim_state]
        self.frame_timer += dt
        if self.frame_timer >= self.frame_speed:
            self.frame_timer = 0.0
            self.frame_index = (self.frame_index + 1) % len(frames)

        self.source = frames[self.frame_index]

        # horizontal movement
        if p.is_key_down(p.KeyboardKey.KEY_D):
            self.dest.x += self.speed * dt
            self.source.width = abs(self.source.width)
        if p.is_key_down(p.KeyboardKey.KEY_A):
            self.dest.x -= self.speed * dt
            self.source.width = -abs(self.source.width)

        # initiate jump
        if p.is_key_pressed(p.KeyboardKey.KEY_W) and self.can_jump:
            self.can_jump = False
            self.change_y = self.jump_force

        # jumping
        if not self.can_jump:
            self.change_y += self.gravity * dt
            self.dest.y += self.change_y * dt

        # hit ground
        if self.dest.y + self.origin.y >= MAP_SIZE:
            self.can_jump = True

        # bounds
        self.dest.x = max(self.origin.x, min(self.dest.x, MAP_SIZE - self.origin.x))
        self.dest.y = max(self.origin.y, min(self.dest.y, MAP_SIZE - self.origin.y))
