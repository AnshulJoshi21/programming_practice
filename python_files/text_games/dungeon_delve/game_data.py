characters = {
    "warrior": {
        "level": 1,
        "hp": 120,
        "mana": 20,
        "attack": 12,
        "defense": 8,
        "weapon": "rusty_sword",
        "armor": "cloth_tunic",
        "inventory": ["small_health_potion"],
    },
    "mage": {
        "level": 1,
        "hp": 70,
        "mana": 120,
        "attack": 15,
        "defense": 3,
        "weapon": "wooden_staff",
        "armor": "cloth_robe",
        "inventory": ["small_mana_potion"],
    },
    "rogue": {
        "level": 1,
        "hp": 90,
        "mana": 40,
        "attack": 14,
        "defense": 5,
        "weapon": "rusty_dagger",
        "armor": "leather_vest",
        "inventory": ["small_health_potion"],
    },
}

enemies = {
    "rat": {
        "level": 1,
        "hp": 20,
        "attack": 4,
        "defense": 1,
        "xp_drop": 5,
        "loot_table": ["rat_tail"],
    },
    "goblin": {
        "level": 1,
        "hp": 35,
        "attack": 6,
        "defense": 2,
        "xp_drop": 10,
        "loot_table": ["goblin_ear", "small_health_potion"],
    },
    "slime": {
        "level": 1,
        "hp": 30,
        "attack": 5,
        "defense": 0,
        "xp_drop": 8,
        "loot_table": ["slime_gel"],
    },
}

weapons = {
    "rusty_sword": {"attack_bonus": 3, "value": 5},
    "wooden_staff": {"attack_bonus": 2, "mana_bonus": 10, "value": 6},
    "rusty_dagger": {"attack_bonus": 3, "crit_bonus": 0.05, "value": 5},
}

armors = {
    "cloth_tunic": {"defense_bonus": 2, "value": 4},
    "cloth_robe": {"defense_bonus": 1, "mana_bonus": 10, "value": 5},
    "leather_vest": {"defense_bonus": 3, "value": 6},
}

consumables = {
    "small_health_potion": {"effect": "heal", "amount": 30, "value": 5},
    "small_mana_potion": {"effect": "restore_mana", "amount": 30, "value": 5},
    "antidote": {"effect": "cure_poison", "value": 4},
}

towns = {}

locations = {}

npcs = {}
