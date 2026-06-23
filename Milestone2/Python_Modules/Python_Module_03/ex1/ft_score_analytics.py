#!/usr/bin/env python3
import sys


def main() -> None:

    scores = sys.argv[1:]
    if len(sys.argv) == 1:
        print(
            f"No scores provided: Usage: python3 {sys.argv[0]}"
            f" <score1> <score2> ..."
        )
        return

    convert = []

    for args in scores:
        try:
            convert += [int(args)]
        except ValueError:
            print(f"Invalid parameter: '{args}'")
    if not convert:
        print(
            f"No scores provided: Usage: python3 {sys.argv[0]}"
            f" <score1> <score2> ..."
        )
        return

    maior = max(convert)
    menor = min(convert)
    print(f"Scores processed: {convert}")
    print(f"Total players: {len(convert)}")
    print(f"Total score: {sum(convert)}")
    print(f"Average score: {sum(convert) / len(convert):.1f}")
    print(f"High score: {maior}")
    print(f"Low score: {menor}")
    print(f"Score range: {maior - menor}")


if __name__ == "__main__":
    print("=== Player Score Analytics ===")
    main()
