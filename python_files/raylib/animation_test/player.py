from enum import Enum, auto

import pyray as p

from animation_manager import AnimationConfig, AnimationManager, AnimationType
from asset_manager import AssetManager
from settings import MAP_HEIGHT, MAP_WIDTH, SPRITE_HEIGHT, SPRITE_WIDTH


class PlayerState(Enum):
    attack = auto()
    cast = auto()
    climb = auto()
    grab = auto()
    jump = auto()
    crouch = auto()
    die = auto()
    fall = auto()
    get_up = auto()
    hurt = auto()
    idle = auto()
    items = auto()
    knock_down = auto()
    punch = auto()
    run = auto()
    slide = auto()
    somersault = auto()
    stand = auto()
    walk = auto()


class Intent(Enum):
    none = auto()
    attack = auto()
    cast = auto()
    climb = auto()
    jump = auto()
    crouch = auto()
    items = auto()
    run = auto()
    slide = auto()
    somersault = auto()
    stand = auto()
    walk = auto()


class Player:
    def __init__(self, asset_manager: AssetManager) -> None:
        self.animation_manager: AnimationManager = AnimationManager(asset_manager)

        self.current_state: PlayerState = PlayerState.idle
        self.prev_state: PlayerState
        self.state_locked: bool = False

        self.scale: float = 3.0
        self.source: p.Rectangle = p.Rectangle(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT)
        self.dest: p.Rectangle = p.Rectangle(
            self.source.width,
            MAP_HEIGHT - self.source.height / 2.0,
            self.source.width * self.scale,
            self.source.height * self.scale,
        )
        self.origin: p.Vector2 = p.Vector2(
            self.dest.width / 2.0, self.dest.height / 2.0
        )
        self.rotation: float = 0.0
        self.tint: p.Color = p.WHITE

        self.speed: p.Vector2 = p.Vector2(300, 0)
        self.direction_x: float = 0.0

        self.jump_force: float = 600.0
        self.gravity: float = 1200.0
        self.on_ground: float = True

        self.input_intent: Intent = Intent.none

    def _get_animation_type(self, state: PlayerState) -> AnimationType:
        match state:
            case PlayerState.attack:
                return AnimationType.attack1
            case PlayerState.cast:
                return AnimationType.cast
            case PlayerState.climb:
                return AnimationType.corner_climb
            case PlayerState.grab:
                return AnimationType.corner_grab
            case PlayerState.jump:
                return AnimationType.jump
            case PlayerState.crouch:
                return AnimationType.crouch
            case PlayerState.die:
                return AnimationType.die
            case PlayerState.fall:
                return AnimationType.fall
            case PlayerState.get_up:
                return AnimationType.get_up
            case PlayerState.hurt:
                return AnimationType.hurt
            case PlayerState.idle:
                return AnimationType.idle
            case PlayerState.items:
                return AnimationType.items
            case PlayerState.knock_down:
                return AnimationType.knock_down
            case PlayerState.punch:
                return AnimationType.punch
            case PlayerState.run:
                return AnimationType.run
            case PlayerState.slide:
                return AnimationType.slide
            case PlayerState.somersault:
                return AnimationType.somersault
            case PlayerState.stand:
                return AnimationType.stand
            case PlayerState.walk:
                return AnimationType.walk

    def _get_input(self) -> None:
        left: bool = p.is_key_down(p.KeyboardKey.KEY_A)
        right: bool = p.is_key_down(p.KeyboardKey.KEY_D)

        # flip sprite
        if left:
            self.source.width = -SPRITE_WIDTH
        if right:
            self.source.width = SPRITE_WIDTH

        # set direction
        self.direction_x = float(right) - float(left)

        # is_pressed before is_down
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.input_intent = Intent.jump
        elif p.is_key_pressed(p.KeyboardKey.KEY_E):
            self.input_intent = Intent.attack
        # is_down
        elif p.is_key_down(p.KeyboardKey.KEY_C):
            self.input_intent = Intent.crouch
        elif left or right:
            if p.is_key_down(p.KeyboardKey.KEY_LEFT_SHIFT):
                self.input_intent = Intent.run
            else:
                self.input_intent = Intent.walk
        else:
            self.input_intent = Intent.none

    def _set_state(self, new_state: PlayerState) -> None:
        if self.current_state == new_state:
            return

        if self.state_locked:
            return

        self.prev_state = self.current_state
        self.current_state = new_state

        self.animation_manager.set(self._get_animation_type(self.current_state))

    def update(self, dt: float) -> None:
        self._get_input()
        run_speed_multiplier: float = 1.0

        match self.current_state:
            case PlayerState.attack:
                if self.input_intent == Intent.none:
                    self._set_state(PlayerState.idle)

                if self.input_intent == Intent.walk:
                    self._set_state(PlayerState.walk)

                if self.input_intent == Intent.run:
                    self._set_state(PlayerState.run)

            case PlayerState.cast:
                pass
            case PlayerState.climb:
                pass
            case PlayerState.grab:
                pass

            case PlayerState.jump:
                if self.speed.y > 0:
                    self._set_state(PlayerState.fall)

            case PlayerState.crouch:
                if self.input_intent == Intent.none:
                    self._set_state(PlayerState.stand)

            case PlayerState.die:
                pass

            case PlayerState.fall:
                # hit ground
                if self.dest.y + self.origin.y >= MAP_HEIGHT:
                    self.speed.y = 0.0
                    self.on_ground = True
                    self._set_state(PlayerState.idle)

                if self.on_ground:
                    if self.input_intent == Intent.walk:
                        self._set_state(PlayerState.walk)

                    if self.input_intent == Intent.run:
                        self._set_state(PlayerState.run)

            case PlayerState.get_up:
                pass
            case PlayerState.hurt:
                pass

            case PlayerState.idle:
                if self.input_intent == Intent.walk:
                    self._set_state(PlayerState.walk)

                if self.input_intent == Intent.jump:
                    self._set_state(PlayerState.jump)
                    self.on_ground = False
                    self.speed.y = -self.jump_force

                if self.input_intent == Intent.crouch:
                    self._set_state(PlayerState.crouch)

                if self.input_intent == Intent.attack:
                    self._set_state(PlayerState.attack)

            case PlayerState.items:
                pass
            case PlayerState.knock_down:
                pass
            case PlayerState.punch:
                pass
            case PlayerState.run:
                run_speed_multiplier = 2.0

                if self.input_intent == Intent.none:
                    self._set_state(PlayerState.idle)

                if self.input_intent == Intent.walk:
                    self._set_state(PlayerState.walk)

                if self.input_intent == Intent.jump:
                    self._set_state(PlayerState.jump)
                    self.on_ground = False
                    self.speed.y = -self.jump_force

                if self.input_intent == Intent.attack:
                    self._set_state(PlayerState.attack)

            case PlayerState.slide:
                pass
            case PlayerState.somersault:
                pass
            case PlayerState.stand:
                if self.input_intent == Intent.none:
                    self._set_state(PlayerState.idle)

            case PlayerState.walk:
                if self.input_intent == Intent.none:
                    self._set_state(PlayerState.idle)

                if self.input_intent == Intent.run:
                    self._set_state(PlayerState.run)

                if self.input_intent == Intent.jump:
                    self._set_state(PlayerState.jump)
                    self.on_ground = False
                    self.speed.y = -self.jump_force

                if self.input_intent == Intent.attack:
                    self._set_state(PlayerState.attack)

        # flip sprite
        self.dest.width = self.source.width * self.scale

        # movement
        ## horizontal
        if (
            self.current_state == PlayerState.walk
            or self.current_state == PlayerState.run
            or self.current_state == PlayerState.jump
            or self.current_state == PlayerState.fall
        ):
            self.dest.x += self.speed.x * self.direction_x * run_speed_multiplier * dt

        ## vertical
        self.speed.y += self.gravity * dt
        self.dest.y += self.speed.y * dt

        # set bounds
        self.dest.x = max(self.origin.x, min(self.dest.x, MAP_WIDTH - self.origin.x))
        self.dest.y = max(self.origin.y, min(self.dest.y, MAP_HEIGHT - self.origin.y))

        # set state lock
        config: AnimationConfig = self.animation_manager._get_config(
            self._get_animation_type(self.current_state)
        )
        if not config.loops:
            self.state_locked = True

        self.animation_manager.update(dt)

        # reset lock state
        if self.animation_manager.is_finished:
            self.state_locked = False

    def draw(self) -> None:
        frames: list[p.Texture] = self.animation_manager._get_frames(
            self.animation_manager.current_type
        )
        frame: p.Texture = frames[self.animation_manager.current_frame]

        p.draw_texture_pro(
            frame, self.source, self.dest, self.origin, self.rotation, self.tint
        )
