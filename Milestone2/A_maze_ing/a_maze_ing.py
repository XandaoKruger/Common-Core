import sys
from config import MazeConfig, ConfigError
from mazegen import MazeGenerator
from view import run_menu
from typing import Callable


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
    """Run the maze program."""
    if len(sys.argv) != 2:
        print("Usage: python3 a_maze_ing.py <config_file>")
        sys.exit(1)

    try:
        config = MazeConfig.from_file(sys.argv[1])
    except ConfigError as error:
        print(f"Config error: {error}")
        sys.exit(1)

    def build(
        seed: int,
        perfect: bool,
        on_step: Callable[[MazeGenerator], None] | None = None,
    ) -> MazeGenerator:
        """Create and generate a maze for the given seed."""
        maze = MazeGenerator(
            width=config.width,
            height=config.height,
            entry=config.entry,
            exit_pos=config.exit_block,
            perfect=perfect,
            seed=seed,
        )
        maze.generate(on_step=on_step)
        return maze

    def save(maze: MazeGenerator) -> None:
        """Write the displayed maze to the configured output file."""
        try:
            write_output(config.output_file, maze)
        except OSError as error:
            print(f"Could not write '{config.output_file}': {error}")

    try:
        build(config.seed, config.perfect)
    except ValueError as error:
        print(f"Config error: {error}")
        sys.exit(1)

    run_menu(build, config.seed, config.perfect, on_new_maze=save)


if __name__ == "__main__":
    main()
