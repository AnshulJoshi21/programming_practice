from pathlib import Path

import pyray as p


class AssetManager:
    def __init__(self) -> None:
        self.animations: dict[str, list[p.Texture]] = {}

        self.load()
        self.check_validity()

    def load(self) -> None:
        base_path: Path = Path("./animations")

        for anim_dir in base_path.iterdir():
            if anim_dir.is_dir():
                frames: list[Path] = sorted(
                    anim_dir.glob("*.png"), key=lambda p: int(p.stem)
                )

                self.animations[anim_dir.name] = [
                    p.load_texture(str(frame)) for frame in frames
                ]

    def check_validity(self) -> None:
        for frames in self.animations.values():
            for frame in frames:
                assert p.is_texture_valid(frame)

    def unload(self) -> None:
        for frames in self.animations.values():
            for frame in frames:
                p.unload_texture(frame)
