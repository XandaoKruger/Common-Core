"""Quick, throwaway Unicode maze viewer for local debugging.

Not part of the graded deliverable — never imported by mazegen/,
a_maze_ing.py, or the packaged module. Safe to keep in .gitignore.

Usage:
    uv run python debug_view.py
"""
from mazegen.generator import MazeGenerator
from rich import print


def print_maze(maze: MazeGenerator) -> None:
    """Print a Box-Drawing double-line rendering of the maze."""

    STYLE = "bold cyan"

    for y in range(maze.height):
        top_line = ""
        side_line = ""
        for x in range(maze.width):
            walls = maze.get_cell_walls(x, y)

            # Canto superior esquerdo + Parede Norte (Bitmask 1)
            # Determina se precisa de canto interseção ou linha contínua
            top_line += "╔" if x == 0 and y == 0 else ("╦" if y == 0 else ("╠" if x == 0 else "╬"))
            top_line += "═" * 3 if walls & 1 else "   "

            # Parede Oeste (Bitmask 8) + Espaço interno
            side_line += "║" if walls & 8 else " "
            side_line += "   "

        # Parede Leste da última coluna (Bitmask 2)
        last_walls = maze.get_cell_walls(maze.width - 1, y)
        top_line += "╗" if y == 0 else "╣"
        side_line += "║" if last_walls & 2 else " "

        print(f"[{STYLE}]{top_line}[/]")
        print(f"[{STYLE}]{side_line}[/]")

    # Linha inferior do labirinto (Parede Sul / Bitmask 4)
    bottom_line = ""
    for x in range(maze.width):
        walls = maze.get_cell_walls(x, maze.height - 1)
        bottom_line += "╚" if x == 0 else "╩"
        bottom_line += "═" * 3 if walls & 4 else "   "
    bottom_line += "╝"

    print(f"[{STYLE}]{bottom_line}[/]")


if __name__ == "__main__":
    maze = MazeGenerator(10, 5, (1, -1), (19, 14), True, seed=1)
    maze.generate()
    print_maze(maze)
