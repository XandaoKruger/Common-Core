import sys

from config import MazeConfig, ConfigError
from mazegen import MazeGenerator


def write_output(path: str, maze: MazeGenerator) -> None:
    """Write the maze to disk in the format required by the subject."""
    with open(path, "w") as f:
        for row in maze.to_hex_rows():
            f.write(row + "\n")

        f.write("\n")
        f.write(f"{maze.entry[0]},{maze.entry[1]}\n")
        f.write(f"{maze.exit_pos[0]},{maze.exit_pos[1]}\n")
        f.write("".join(maze.solve()) + "\n")


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: python3 a_maze_ing.py <config_file>")
        sys.exit(1)

    try:
        config = MazeConfig.from_file(sys.argv[1])
    except ConfigError as error:
        print(f"Config error: {error}")
        sys.exit(1)

    maze = MazeGenerator(
        width=config.width,
        height=config.height,
        entry=config.entry,
        exit_pos=config.exit_block,
        perfect=config.perfect,
        seed=config.seed,
    )
    maze.generate()
    write_output(config.output_file, maze)
    print(f"Maze written to {config.output_file}")


if __name__ == "__main__":
    main()