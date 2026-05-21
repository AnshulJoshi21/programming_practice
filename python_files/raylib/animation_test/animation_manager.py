from animation import AnimationConfig, AnimationType


class AnimationManager:
    def set(self, new_type: AnimationType) -> None:
        if self.current_type == new_type:
            return

        self.current_type = AnimationType.IDLE
        self.current_frame = 0
        self.frame_timer = 0.0
        self.is_finished = False

    def __init__(self, animation_db: dict[AnimationType, AnimationConfig]) -> None:
        self.animation_db: dict[AnimationType, AnimationConfig] = animation_db

        self.current_type: AnimationType
        self.current_frame: int
        self.frame_timer: float
        self.is_finished: bool

        self.set(AnimationType.IDLE)

    def update(self, dt: float) -> None:
        if self.is_finished:
            return

        config: AnimationConfig = self.animation_db[self.current_type]

        self.frame_timer += dt
        if self.frame_timer >= config.duration:
            self.frame_timer = 0.0
            self.current_frame += 1

            if self.current_frame >= len(config.frames):
                if config.loops:
                    self.current_frame = 0
                else:
                    self.current_frame = len(config.frames) - 1
                    self.is_finished = True
