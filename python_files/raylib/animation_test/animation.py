from dataclasses import dataclass
from enum import Enum
from pathlib import Path

import pyray as p


class AnimationType(Enum):
    AIR_ATTACK1 = "air_attack1"
    AIR_ATTACK2 = "air_attack2"
    AIR_ATTACK3_END = "air_attack3_end"
    AIR_ATTACK3_LOOP = "air_attack3_loop"
    AIR_ATTACK3_READY = "air_attack3_ready"
    ATTACK1 = "attack1"
    ATTACK2 = "attack2"
    ATTACK3 = "attack3"
    BOW = "bow"
    BOW_JUMP = "bow_jump"
    CAST = "cast"
    CAST_LOOP = "cast_loop"
    CORNER_CLIMB = "corner_climb"
    CORNER_GRAB = "corner_grab"
    CORNER_JUMP = "corner_jump"
    CROUCH = "crouch"
    CROUCH_WALK = "crouch_walk"
    DIE = "die"
    DROP_KICK = "drop_kick"
    FALL = "fall"
    GET_UP = "get_up"
    HURT = "hurt"
    IDLE = "idle"
    IDLE2 = "idle2"
    ITEMS = "items"
    JUMP = "jump"
    KICK = "kick"
    KNOCK_DOWN = "knock_down"
    LADDER_CLIMB = "ladder_climb"
    PUNCH = "punch"
    RUN = "run"
    RUN2 = "run2"
    RUN_PUNCH = "run_punch"
    SLIDE = "slide"
    SOMERSAULT = "somersault"
    STAND = "stand"
    SWORD_DRAW = "sword_draw"
    SWORD_SHEATHE = "sword_sheathe"
    WALK = "walk"
    WALL_RUN = "wall_run"
    WALL_SLIDE = "wall_slide"


@dataclass(slots=True)
class AnimationConfig:
    frames: list[p.Texture]
    duration: float
    loops: bool


def load_assets() -> dict[AnimationType, AnimationConfig]:
    animation_db: dict[AnimationType, AnimationConfig] = {}
    assets_dir: Path = Path("./assets")

    for folder in assets_dir.iterdir():
        if folder.is_dir():
            files = sorted(folder.glob("*.png"))
            anim_type: AnimationType = AnimationType(folder.name)

            animation_db[anim_type] = AnimationConfig(
                frames=[p.load_texture(str(png_path)) for png_path in files],
                duration=0.0,
                loops=False,
            )

    return animation_db


def unload_assets(animation_db: dict[AnimationType, AnimationConfig]) -> None:
    for config in animation_db.values():
        for frame in config.frames:
            p.unload_texture(frame)
