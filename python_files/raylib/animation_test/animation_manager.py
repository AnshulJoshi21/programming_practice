from dataclasses import dataclass
from enum import Enum

from pyray import Texture

from asset_manager import AssetManager


class AnimationType(Enum):
    air_attack1 = "air_attack1"
    air_attack2 = "air_attack2"
    air_attack3_end = "air_attack3_end"
    air_attack3_loop = "air_attack3_loop"
    air_attack3_ready = "air_attack3_ready"
    attack1 = "attack1"
    attack2 = "attack2"
    attack3 = "attack3"
    bow = "bow"
    bow_jump = "bow_jump"
    cast = "cast"
    cast_loop = "cast_loop"
    corner_climb = "corner_climb"
    corner_grab = "corner_grab"
    corner_jump = "corner_jump"
    crouch = "crouch"
    crouch_walk = "crouch_walk"
    die = "die"
    drop_kick = "drop_kick"
    fall = "fall"
    get_up = "get_up"
    hurt = "hurt"
    idle = "idle"
    idle2 = "idle2"
    items = "items"
    jump = "jump"
    kick = "kick"
    knock_down = "knock_down"
    ladder_climb = "ladder_climb"
    punch = "punch"
    run = "run"
    run2 = "run2"
    run_punch = "run_punch"
    slide = "slide"
    somersault = "somersault"
    stand = "stand"
    sword_draw = "sword_draw"
    sword_sheathe = "sword_sheathe"
    walk = "walk"
    wall_run = "wall_run"
    wall_slide = "wall_slide"


@dataclass(slots=True, frozen=True)
class AnimationConfig:
    duration: float
    loops: bool


def _animation_get_config() -> dict[str, AnimationConfig]:
    config: dict[str, AnimationConfig] = {
        "air_attack1": AnimationConfig(0.045, False),
        "air_attack2": AnimationConfig(0.050, False),
        "air_attack3_end": AnimationConfig(0.035, False),
        "air_attack3_loop": AnimationConfig(0.025, True),
        "air_attack3_ready": AnimationConfig(0.030, False),
        "attack1": AnimationConfig(0.040, False),
        "attack2": AnimationConfig(0.045, False),
        "attack3": AnimationConfig(0.060, False),
        "bow": AnimationConfig(0.070, False),
        "bow_jump": AnimationConfig(0.075, False),
        "cast": AnimationConfig(0.080, False),
        "cast_loop": AnimationConfig(0.035, True),
        "corner_climb": AnimationConfig(0.090, False),
        "corner_grab": AnimationConfig(0.020, False),
        "corner_jump": AnimationConfig(0.050, False),
        "crouch": AnimationConfig(0.015, False),
        "crouch_walk": AnimationConfig(0.060, True),
        "die": AnimationConfig(0.120, False),
        "drop_kick": AnimationConfig(0.055, False),
        "fall": AnimationConfig(0.020, True),
        "get_up": AnimationConfig(0.085, False),
        "hurt": AnimationConfig(0.035, False),
        "idle": AnimationConfig(0.180, True),
        "idle2": AnimationConfig(0.150, True),
        "items": AnimationConfig(0.050, False),
        "jump": AnimationConfig(0.045, False),
        "kick": AnimationConfig(0.040, False),
        "knock_down": AnimationConfig(0.070, False),
        "ladder_climb": AnimationConfig(0.050, True),
        "punch": AnimationConfig(0.030, False),
        "run": AnimationConfig(0.055, True),
        "run2": AnimationConfig(0.045, True),
        "run_punch": AnimationConfig(0.050, False),
        "slide": AnimationConfig(0.040, False),
        "somersault": AnimationConfig(0.080, False),
        "stand": AnimationConfig(0.010, False),
        "sword_draw": AnimationConfig(0.045, False),
        "sword_sheathe": AnimationConfig(0.045, False),
        "walk": AnimationConfig(0.080, True),
        "wall_run": AnimationConfig(0.050, True),
        "wall_slide": AnimationConfig(0.040, True),
    }

    return config


class AnimationManager:
    def __init__(self, asset_manager: AssetManager) -> None:
        self.asset_manager: AssetManager = asset_manager
        self.animation_configs: dict[str, AnimationConfig] = _animation_get_config()

        self.current_type: AnimationType = AnimationType.idle
        self.current_frame: int = 0
        self.frame_timer: float = 0.0
        self.is_finished: bool = False

    def _get_frames(self, anim_type: AnimationType) -> list[Texture]:
        return self.asset_manager.animations[anim_type.value]

    def _get_config(self, anim_type: AnimationType) -> AnimationConfig:
        return self.animation_configs[anim_type.value]

    def set(self, new_type: AnimationType) -> None:
        if self.current_type == new_type:
            return

        self.current_type = new_type
        self.current_frame = 0
        self.frame_timer = 0.0
        self.is_finished = False

    def update(self, dt: float) -> None:
        if self.is_finished:
            return

        config: AnimationConfig = self._get_config(self.current_type)
        frames: list[Texture] = self._get_frames(self.current_type)

        self.frame_timer += dt
        if self.frame_timer >= config.duration:
            self.frame_timer = 0.0
            self.current_frame += 1

            if self.current_frame >= len(frames):
                if config.loops:
                    self.current_frame = 0
                else:
                    self.current_frame = len(frames) - 1
                    self.is_finished = True
