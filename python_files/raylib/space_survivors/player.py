import pyray as p

from entity import Entity, EntityType
from laser_manager import LaserManager
from settings import MAP_SIZE, PLAYER_SCALE


class Player:
    def __init__(self, sprite_dict: dict[str, p.Rectangle]) -> None:
        self.entity: Entity = Entity(
            entity_type=EntityType.PLAYER,
            sprite_dict=sprite_dict,
            current_sprite="playerShip1_blue.png",
            start_pos=p.Vector2(MAP_SIZE / 2.0, MAP_SIZE / 2.0),
            scale=PLAYER_SCALE,
            speed=200.0,
        )

        self.laser_manager: LaserManager = LaserManager()

    def draw(self, spritesheet: p.Texture) -> None:
        self.laser_manager.draw(spritesheet)

        self.entity.draw(spritesheet)

    def update(
        self,
        sprite_dict: dict[str, p.Rectangle],
        delta_time: float,
        mouse_pos_world: p.Vector2,
    ) -> None:
        self.entity.handle_input()
        self.entity.rotate(mouse_pos_world)
        self.entity.move(delta_time)
        self.entity.set_bounds()

        player_pos: p.Vector2 = p.Vector2(self.entity.dest.x, self.entity.dest.y)
        self.laser_manager.update(
            sprite_dict, delta_time, start_pos=player_pos, target_pos=mouse_pos_world
        )
