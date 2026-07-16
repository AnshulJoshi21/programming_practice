def linear_search(arr: list[int], num: int) -> int:
    for i, arr_num in enumerate(arr):
        if arr_num == num:
            return i

    raise ValueError("Number not in list")


def main() -> None:
    arr: list[int] = [5, 3, 12, 34234, 25]

    print(f"Index: {linear_search(arr, 25)}")


if __name__ == "__main__":
    main()
