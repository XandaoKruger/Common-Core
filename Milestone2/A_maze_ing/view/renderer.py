"""Unicode maze renderer built on top of rich."""
from rich.console import Console
from rich.text import Text
from mazegen import MazeGenerator
from random import randint


# nome: (16 cantos, horizontal, vertical)
# posição do canto = up*8 + down*4 + left*2 + right
JUNCTION_STYLES: dict[str, tuple[str, str, str]] = {
    # --- linhas ---
    "arredondado": (" ╶╴─╷╭╮┬╵╰╯┴│├┤┼", "───", "│"),
    "fino":        (" ╶╴─╷┌┐┬╵└┘┴│├┤┼", "───", "│"),
    "grosso":      (" ╺╸━╻┏┓┳╹┗┛┻┃┣┫╋", "━━━", "┃"),
    "duplo":       (" ═══║╔╗╦║╚╝╩║╠╣╬", "═══", "║"),
    "ascii":       (" ++-++++++++|+++", "---", "|"),
    # --- tracejados ---
    "tracejado":   (" ╶╴─╷┌┐┬╵└┘┴│├┤┼", "┄┄┄", "┆"),
    "tracejado2":  (" ╶╴─╷╭╮┬╵╰╯┴│├┤┼", "╌╌╌", "╎"),
    "grosso-traç": (" ╺╸━╻┏┓┳╹┗┛┻┃┣┫╋", "┅┅┅", "┇"),
    # --- misturas ---
    "mais":        (" " + "+" * 15, "───", "│"),
    # --- um só símbolo em tudo ---
    "blocos":      (" " + "█" * 15, "███", "█"),
    "sombra":      (" " + "▒" * 15, "▒▒▒", "▒"),
    "pontos":      (" " + "•" * 15, "•••", "•"),
    "diamantes":   (" " + "◆" * 15, "◆◆◆", "◆"),
    "cruzes":      (" " + "╳" * 15, "╳╳╳", "╳"),
    "cardinal":    (" " + "#" * 15, "###", "#"),
    "estrelas":    (" " + "*" * 15, "***", "*"),
    "braille":     (" " + "⣿" * 15, "⣿⣿⣿", "⣿"),
}

NORTH, EAST, SOUTH, WEST = 1, 2, 4, 8

_STEPS: dict[str, tuple[int, int]] = {
    "N": (0, -1),
    "E": (1, 0),
    "S": (0, 1),
    "W": (-1, 0),
}

# Cada conjunto tem 4 símbolos, pela ordem N, E, S, W
ARROW_SETS: list[str] = ["↑→↓←", "▲▶▼◀", "⇑⇒⇓⇐"]


def _corner(maze: MazeGenerator, cx: int, cy: int, joints: str) -> str:
    """Return the box-drawing char for the corner at grid point (cx, cy)."""
    w, h = maze.width, maze.height

    up = down = left = right = False

    if cy > 0:  # parede vertical por cima do canto
        up = bool(
            maze.get_cell_walls(cx, cy - 1) & WEST if cx < w
            else maze.get_cell_walls(cx - 1, cy - 1) & EAST
        )

    if cy < h:  # parede vertical por baixo do canto
        down = bool(
            maze.get_cell_walls(cx, cy) & WEST if cx < w
            else maze.get_cell_walls(cx - 1, cy) & EAST
        )

    if cx > 0:  # parede horizantal do lado esquerdo
        left = bool(
            maze.get_cell_walls(cx - 1, cy) & NORTH if cy < h
            else maze.get_cell_walls(cx - 1, cy - 1) & SOUTH
        )

    if cx < w:  # parede horizantal do lado direito
        right = bool(
            maze.get_cell_walls(cx, cy) & NORTH if cy < h
            else maze.get_cell_walls(cx, cy - 1) & SOUTH
        )

    return joints[up * 8 + down * 4 + left * 2 + right]


def path_cells(maze: MazeGenerator) -> dict[tuple[int, int], str]:
    """Map each path cell to the direction of the step leaving it."""
    x, y = maze.entry
    cells: dict[tuple[int, int], str] = {}
    for step in maze.solve():
        cells[(x, y)] = step
        dx, dy = _STEPS[step]
        x, y = x + dx, y + dy
    return cells


def rand_color() -> str:
    """Return a random colour like 'rgb(12,200,90)'."""
    return f"rgb({randint(100, 255)},{randint(100, 255)},{randint(100, 255)})"


def render_maze(
    maze: MazeGenerator,
    wall_style: str = "bold green",
    pattern_style: str = "bold red",
    entry_style: str = "bold green",
    exit_style: str = "bold red",
    path: dict[tuple[int, int], str] | None = None,
    path_style: str = "bold white",
    bg: str = "#000000",
    arrows: str = "↑→↓←",
    style: str = "fino",
) -> Text:
    """build a rich text with the full maze (wall, entry, exit, '42')."""
    joints, horizontal, vertical = JUNCTION_STYLES[style]
    wall_style = f"{wall_style} on {bg}"
    pattern_style = f"{pattern_style} on {bg}"
    entry_style = f"{entry_style} on {bg}"
    exit_style = f"{exit_style} on {bg}"
    path_style = f"{path_style} on {bg}"
    arrow_map = dict(zip("NESW", arrows))

    text = Text()
    # order = {cell: i for i, cell in enumerate(path or {})}
    # total = max(len(order), 1)
    for y in range(maze.height + 1):
        # linha das parede horizontais + cantos
        for x in range(maze.width + 1):
            text.append(_corner(maze, x, y, joints), style=wall_style)
            if x < maze.width:
                if y < maze.height:
                    closed = maze.get_cell_walls(x, y) & NORTH
                else:
                    closed = maze.get_cell_walls(x, y - 1) & SOUTH
                text.append(horizontal if closed else "   ", style=wall_style)
        text.append("\n")

        if y == maze.height:
            break

        # linha do interior das celulas + paredes verticais
        for x in range(maze.width + 1):
            if x < maze.width:
                west_closed = maze.get_cell_walls(x, y) & WEST
            else:
                west_closed = maze.get_cell_walls(x - 1, y) & EAST
            text.append(vertical if west_closed else " ", style=wall_style)

            if x < maze.width:
                if (x, y) == maze.entry:
                    text.append(" ● ", style=entry_style)
                elif (x, y) == maze.exit_pos:
                    text.append(" ● ", style=exit_style)
                elif (x, y) in maze.pattern_cells:
                    text.append("⣿⣿⣿", style=pattern_style)
                elif path and (x, y) in path:
                    arrow = arrow_map[path[(x, y)]]
                    text.append(f" {arrow} ", style=path_style)
                else:
                    text.append("   ", style=f"on {bg}")
        text.append("\n")

    return text


if __name__ == "__main__":
    demo = MazeGenerator(20, 15, (5, 10), (19, 10), True, seed=42)
    demo.generate()
    Console().print(render_maze(demo))
