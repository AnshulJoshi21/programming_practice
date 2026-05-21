from enum import Enum, auto

import pyray as p

from animation import AnimationConfig, AnimationType
from animation_manager import AnimationManager
from settings import MAP_HEIGHT, MAP_WIDTH, SPRITE_HEIGHT, SPRITE_WIDTH


class PlayerState(Enum):
    IDLE = auto()
    WALK = auto()
    RUN = auto()
    CROUCH = auto()

    JUMP = auto()
    FALL = auto()

    ATTACK = auto()
    AIR_ATTACK = auto()

    HURT = auto()
    DIE = auto()

    SLIDE = auto()
    WALL_RUN = auto()

    LADDER_CLIMB = auto()

    CORNER_GRAB = auto()
    CORNER_CLIMB = auto()

    CAST = auto()
    BOW = auto()

    KNOCK_DOWN = auto()
    GET_UP = auto()


class Player:
    def __init__(self, animation_db: dict[AnimationType, AnimationConfig]) -> None:

        self.animation_db: dict[AnimationType, AnimationConfig] = animation_db

        self.current_state: PlayerState = PlayerState.IDLE
        self.prev_state: PlayerState = self.current_state
        self.is_locked: bool = False

        self.source: p.Rectangle = p.Rectangle(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT)
        self.dest: p.Rectangle = p.Rectangle(
            SPRITE_WIDTH,
            MAP_HEIGHT - SPRITE_HEIGHT,
            SPRITE_WIDTH,
            SPRITE_HEIGHT,
        )
        self.origin: p.Vector2 = p.Vector2(
            self.dest.width / 2.0, self.dest.height / 2.0
        )
        self.rotation: float = 0.0
        self.tint: p.Color = p.WHITE

        self.flip_horizontally: bool = False

        self.speed_h: float = 300.0
        self.speed_v: float = 0.0

        self.jump_force: float = -600.0
        self.gravity: float = 1200.0
        self.can_jump: bool = False

        self.animation_manager: AnimationManager = AnimationManager(animation_db)

    def get_animation_type(self) -> AnimationType:
        match self.current_state:
            case PlayerState.IDLE:
                return AnimationType.IDLE
            case PlayerState.WALK:
                return AnimationType.WALK
            case PlayerState.RUN:
                return AnimationType.RUN
            case PlayerState.CROUCH:
                return AnimationType.CROUCH

            case PlayerState.JUMP:
                return AnimationType.JUMP
            case PlayerState.FALL:
                return AnimationType.FALL

            case PlayerState.ATTACK:
                return AnimationType.ATTACK1
            case PlayerState.AIR_ATTACK:
                return AnimationType.AIR_ATTACK1

            case PlayerState.HURT:
                return AnimationType.HURT
            case PlayerState.DIE:
                return AnimationType.DIE

            case PlayerState.SLIDE:
                return AnimationType.SLIDE
            case PlayerState.WALL_RUN:
                return AnimationType.WALL_RUN

            case PlayerState.LADDER_CLIMB:
                return AnimationType.LADDER_CLIMB

            case PlayerState.CORNER_GRAB:
                return AnimationType.CORNER_GRAB
            case PlayerState.CORNER_CLIMB:
                return AnimationType.CORNER_CLIMB

            case PlayerState.CAST:
                return AnimationType.CAST
            case PlayerState.BOW:
                return AnimationType.BOW

            case PlayerState.KNOCK_DOWN:
                return AnimationType.KNOCK_DOWN
            case PlayerState.GET_UP:
                return AnimationType.GET_UP

    def update(self, dt: float) -> None:

        # set bounds
        self.dest.x = max(self.origin.x, min(self.dest.x, MAP_WIDTH - self.origin.x))
        self.dest.y = max(self.origin.y, min(self.dest.y, MAP_HEIGHT - self.origin.y))

        self.animation_manager.update(dt)

    def draw(self) -> None:

        anim_type: AnimationType = self.get_animation_type()
        frame: p.Texture = self.animation_db[anim_type].frames[
            self.animation_manager.current_frame
        ]

        p.draw_texture_pro(
            frame, self.source, self.dest, self.origin, self.rotation, self.tint
        )
