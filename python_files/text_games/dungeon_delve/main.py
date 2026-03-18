import sys
from enum import Enum
from os import system

from game_data import characters


class GameState(Enum):
    MAIN_MENU = 0
    CHARACTER_SELECTION = 1
    TOWN = 2
    COMBAT = 3
    EXIT = 4


def draw_main_menu() -> None:
    print()
    print("DUNGEON DELVE")
    print()
    print("1) New Game")
    print("2) Exit")
    print()


def clear_last_lines(n: int = 3) -> None:
    for _ in range(n):
        sys.stdout.write("\033[F")
        sys.stdout.write("\033[K")


def print_error_msg() -> None:
    print("Invalid choice, try again")
    input("press enter to continue...")
    clear_last_lines(3)


def get_user_input(available_inputs: list[int]) -> int:
    while True:
        try:
            user_input: int = int(input("> "))

            if user_input in available_inputs:
                return user_input
            else:
                print_error_msg()

        except ValueError:
            print_error_msg()


def print_character_info(character_type: str) -> None:

    c_dict: dict = characters[character_type]

    print()
    print(f"Level: {c_dict['level']}")
    print(f"HP: {c_dict['hp']}")
    print(f"Mana: {c_dict['mana']}")
    print(f"Attack: {c_dict['attack']}")
    print(f"Defense: {c_dict['defense']}")
    print(f"Weapon: {c_dict['weapon']}")
    print(f"Armor: {c_dict['armor']}")
    print("Inventory: ")
    for item in c_dict["inventory"]:
        print(" - " + item)
    print()


def print_character_selection_menu() -> None:
    count: int = 1

    for key in characters.keys():
        print(f"{count}: {key.upper()}")

        print_character_info(key)

        count += 1


class Player:
    def __init__(self, type: str) -> None:
        self.type: str = type
        self.level: int = characters[self.type]["level"]
        self.hp: int = characters[self.type]["hp"]
        self.mana: int = characters[self.type]["mana"]
        self.attack: int = characters[self.type]["attack"]
        self.defense: int = characters[self.type]["defense"]
        self.weapon: str = characters[self.type]["weapon"]
        self.armor: str = characters[self.type]["armor"]
        self.inventory: list["str"] = characters[self.type]["inventory"]

    def print_player_info(self) -> None:
        print_character_info(self.type)


class GameManager:
    def __init__(self) -> None:
        self.state: GameState = GameState.MAIN_MENU

    def update(self) -> bool:
        user_input: int = -1
        available_inputs: list[int] = []  # imp: empty every time before using

        match self.state:
            case GameState.MAIN_MENU:
                draw_main_menu()

                available_inputs = [1, 2]
                user_input = get_user_input(available_inputs)

                match user_input:
                    case 1:
                        self.state = GameState.CHARACTER_SELECTION
                    case 2:
                        self.state = GameState.EXIT

            case GameState.CHARACTER_SELECTION:
                print_character_selection_menu()

                available_inputs = []
                for i in range(len(characters.keys())):
                    available_inputs.append(i + 1)

                # because user choices starts from 1
                user_input = get_user_input(available_inputs) - 1

                self.player: Player = Player(list(characters.keys())[user_input])

                self.state = GameState.TOWN

            case GameState.TOWN:
                print(self.player.type)
                input()

            case GameState.COMBAT:
                pass

            case GameState.EXIT:
                print()
                print("Exiting...")
                print("Thank you for playing")
                print()
                return False

        return True


def main() -> None:
    game_manager: GameManager = GameManager()
    running: bool = True

    while running:
        system("clear")
        running = game_manager.update()


if __name__ == "__main__":
    main()
