# =========================
# BASE WEAPONS
# =========================
base_weapons = {
    "short_sword": {
        "type": "melee",
        "slot": "one_hand",
        "damage": (3, 7),
        "attack_speed": 1.2,
        "stat_requirements": {"strength": 5},
        "value": 25,
    },
    "axe": {
        "type": "melee",
        "slot": "one_hand",
        "damage": (5, 10),
        "attack_speed": 1.0,
        "stat_requirements": {"strength": 8},
        "value": 40,
    },
    "bow": {
        "type": "ranged",
        "slot": "two_hand",
        "damage": (4, 9),
        "attack_speed": 1.3,
        "stat_requirements": {"dexterity": 7},
        "value": 45,
    },
    "staff": {
        "type": "magic",
        "slot": "two_hand",
        "damage": (2, 6),
        "attack_speed": 1.1,
        "stat_requirements": {"intelligence": 8},
        "value": 35,
        "mana_bonus": 5,
    },
}

# =========================
# BASE ARMORS
# =========================
base_armors = {
    "cloth_armor": {
        "slot": "chest",
        "armor": 3,
        "stat_requirements": {},
        "value": 20,
        "resistances": {},
    },
    "leather_armor": {
        "slot": "chest",
        "armor": 8,
        "stat_requirements": {"dexterity": 6},
        "value": 50,
        "resistances": {"poison": 5},
    },
    "chain_mail": {
        "slot": "chest",
        "armor": 15,
        "stat_requirements": {"strength": 10},
        "value": 90,
        "resistances": {"physical": 5},
    },
    "plate_armor": {
        "slot": "chest",
        "armor": 25,
        "stat_requirements": {"strength": 15},
        "value": 160,
        "resistances": {"physical": 10},
    },
}

# =========================
# BASE POTIONS
# =========================
base_potions = {
    "minor_healing_potion": {
        "effect": "heal",
        "amount": 25,
        "cooldown": 5,
        "value": 10,
    },
    "healing_potion": {
        "effect": "heal",
        "amount": 75,
        "cooldown": 5,
        "value": 30,
    },
    "mana_potion": {
        "effect": "restore_mana",
        "amount": 50,
        "cooldown": 5,
        "value": 25,
    },
    "strength_potion": {
        "effect": "buff",
        "stat": "strength",
        "amount": 5,
        "duration": 30,
        "value": 40,
    },
}

# =========================
# BASE ENEMIES
# =========================
base_enemies = {
    "fallen": {
        "level": 1,
        "health": 20,
        "damage": (2, 4),
        "attack_speed": 1.2,
        "experience": 10,
        "loot_table": ["gold", "minor_healing_potion"],
    },
    "skeleton": {
        "level": 2,
        "health": 35,
        "damage": (3, 6),
        "attack_speed": 1.0,
        "experience": 18,
        "resistances": {"poison": 100},
        "loot_table": ["gold", "short_sword"],
    },
    "zombie": {
        "level": 3,
        "health": 60,
        "damage": (4, 8),
        "attack_speed": 0.7,
        "experience": 30,
        "loot_table": ["gold", "healing_potion"],
    },
    "demon_brute": {
        "level": 5,
        "health": 120,
        "damage": (8, 15),
        "attack_speed": 0.9,
        "experience": 75,
        "loot_table": ["gold", "axe", "plate_armor"],
    },
}

# =========================
# BASE CHARACTERS (CLASSES)
# =========================
base_characters = {
    "warrior": {
        "base_stats": {
            "strength": 10,
            "dexterity": 5,
            "intelligence": 2,
            "vitality": 8,
        },
        "health_per_level": 10,
        "mana_per_level": 2,
        "starting_equipment": ["short_sword", "cloth_armor"],
    },
    "rogue": {
        "base_stats": {
            "strength": 5,
            "dexterity": 10,
            "intelligence": 3,
            "vitality": 6,
        },
        "health_per_level": 7,
        "mana_per_level": 3,
        "starting_equipment": ["bow", "leather_armor"],
    },
    "mage": {
        "base_stats": {
            "strength": 2,
            "dexterity": 4,
            "intelligence": 12,
            "vitality": 5,
        },
        "health_per_level": 5,
        "mana_per_level": 10,
        "starting_equipment": ["staff", "cloth_armor"],
    },
}
