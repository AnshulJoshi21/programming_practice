from pyray import get_time


class IntervalTimer:
    def __init__(self, duration: float) -> None:
        self.duration: float = duration
        self.last_time: float = get_time()

    def update(self) -> bool:
        current_time: float = get_time()
        if current_time - self.last_time >= self.duration:
            self.last_time = current_time

            return True

        return False
