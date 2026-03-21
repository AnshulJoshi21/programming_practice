import components as C
from settings import MAX_ENTITIES


class World:
    def __init__(self) -> None:
        self.entity_count: int = 0

        self.mask_list: list[int] = [0] * MAX_ENTITIES
        self.transform_list: list[C.TransformComponent] = [
            C.TransformComponent()
        ] * MAX_ENTITIES
        self.animation_list: list[C.AnimationComponent] = [
            C.AnimationComponent()
        ] * MAX_ENTITIES
        self.color_list: list[C.ColorComponent] = [C.ColorComponent()] * MAX_ENTITIES
        self.move_list: list[C.MoveComponent] = [C.MoveComponent()] * MAX_ENTITIES
        self.health_list: list[C.HealthComponent] = [C.HealthComponent()] * MAX_ENTITIES
        self.damage_list: list[C.DamageComponent] = [C.DamageComponent()] * MAX_ENTITIES
        self.target_list: list[C.TargetComponent] = [C.TargetComponent()] * MAX_ENTITIES
        self.lifetime_list: list[C.LifetimeComponent] = [
            C.LifetimeComponent()
        ] * MAX_ENTITIES

    def create_entity(self) -> int:
        if self.entity_count < MAX_ENTITIES:
            id: int = self.entity_count
            self.entity_count += 1
            return id
        return -1

    def delete_entity(self, id: int) -> None:
        if not 0 <= id < self.entity_count:
            return

        last_id: int = self.entity_count - 1

        # spawn id with last
        if id < last_id:
            self.mask_list[id] = self.mask_list[last_id]
            self.transform_list[id] = self.transform_list[last_id]
            self.animation_list[id] = self.animation_list[last_id]
            self.color_list[id] = self.color_list[last_id]
            self.move_list[id] = self.move_list[last_id]
            self.health_list[id] = self.health_list[last_id]
            self.damage_list[id] = self.damage_list[last_id]
            self.target_list[id] = self.target_list[last_id]
            self.lifetime_list[id] = self.lifetime_list[last_id]

        # resize
        self.entity_count -= 1

        # reset last
        self.mask_list[last_id] = 0
        self.transform_list[last_id] = C.TransformComponent()
        self.animation_list[last_id] = C.AnimationComponent()
        self.color_list[last_id] = C.ColorComponent()
        self.move_list[last_id] = C.MoveComponent()
        self.health_list[last_id] = C.HealthComponent()
        self.damage_list[last_id] = C.DamageComponent()
        self.target_list[last_id] = C.TargetComponent()
        self.lifetime_list[last_id] = C.LifetimeComponent()
