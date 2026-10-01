import time
import sys
import termios
from random import choice as pick, randint
from typing import Any, Callable

from rich.align import Align
from rich.console import Console
from rich.control import Control
from rich.screen import Screen

from mazegen import MazeGenerator
from view.renderer import (
    ARROW_SETS,
    JUNCTION_STYLES,
    path_cells,
    rand_color,
    render_maze,
)


def run_menu(
    make_maze: Callable[..., MazeGenerator],
    seed: int,
    perfect: bool,
    on_new_maze: Callable[[MazeGenerator], None] | None = None,
) -> None:
    """Show the maze and handle user commands until the user quits.

    Args:
        make_maze: Builds a maze from (seed, perfect, optional on_step).
        seed: Seed used for the first maze.
        perfect: Whether the first maze is perfect.
        on_new_maze: Optional callback called with every maze shown.
    """
    console = Console()
    screen = console.screen(hide_cursor=True)
    show_path = False
    animate = True
    theme: dict[str, str] = {}
    style_index = 0
    style_names = list(JUNCTION_STYLES)

    def look() -> dict[str, Any]:
        """Return the current render options (theme + wall style)."""
        return {**theme, "style": style_names[style_index]}

    def draw(renderable: Any) -> None:
        """Draw one full frame from the top-left corner, no flicker."""
        console.print(
            Control.home(),
            Screen(Align.center(renderable, vertical="middle")),
            end="",
        )

    def flush_input() -> None:
        """Discard keys typed while an animation was running."""
        try:
            termios.tcflush(sys.stdin, termios.TCIFLUSH)
        except (termios.error, ValueError, OSError):
            pass

    def random_theme() -> dict[str, str]:
        """Build a random colour theme."""
        return {
            "wall_style": f"bold {rand_color()}",
            "pattern_style": f"bold {rand_color()}",
            "entry_style": f"bold {rand_color()}",
            "exit_style": f"bold {rand_color()}",
            "path_style": f"bold {rand_color()}",
            "arrows": pick(ARROW_SETS),
        }

    def new_animated_maze() -> MazeGenerator:
        """Generate a maze, drawing every step if animation is on."""

        def on_step(m: MazeGenerator) -> None:
            """Redraw the maze after each generation step."""
            draw(render_maze(m, **look()))
            time.sleep(min(0.05, 3 / (m.width * m.height)))

        if animate:
            new_maze = make_maze(seed, perfect, on_step)
        else:
            new_maze = make_maze(seed, perfect)
        if on_new_maze:
            on_new_maze(new_maze)
        return new_maze

    def animate_path(current: MazeGenerator) -> None:
        """Draw the shortest path one cell at a time, centred."""
        if not animate:
            return
        steps = list(path_cells(current).items())
        if not steps:
            return
        delay = min(0.1, 3 / len(steps))
        for i in range(1, len(steps) + 1):
            draw(render_maze(current, path=dict(steps[:i]), **look()))
            time.sleep(delay)

    with screen:
        maze = new_animated_maze()
        animate_path(maze)
        #  show_path = True

        while True:
            console.clear()
            console.print(
                render_maze(
                    maze,
                    path=path_cells(maze) if show_path else None,
                    **look(),
                ),
                justify="center",
            )
            console.print(
                f"Seed: {seed}    "
                f"Path: [repr.number]{'ON' if show_path else 'OFF'}[/]    "
                f"Perfect: [repr.number]{'ON' if perfect else 'OFF'}[/]    "
                f"Animation: [repr.number]{'ON' if animate else 'OFF'}[/]",
                justify="center",
            )
            console.print(
                "\n\\[1]new maze    "
                "\\[2]new colours    "
                "\\[3]new walls    "
                "\\[4]random\n"
                "\\[5]show/hide path    "
                "\\[6]perfect on/off    "
                "\\[7]animate path    "
                "\\[8]animation on/off    "
                "\\[q]quit",
                justify="center",
            )

            flush_input()
            try:
                key = input("CHOOSE ACTION: ").strip().lower()
            except (EOFError, KeyboardInterrupt):
                break

            if key == "1":
                seed = randint(0, 999999)
                maze = new_animated_maze()
                animate_path(maze)
                show_path = False
            elif key == "2":
                theme = random_theme()
            elif key == "3":
                style_index = (style_index + 1) % len(style_names)
            elif key == "4":
                seed = randint(0, 999999)
                theme = random_theme()
                style_index = randint(0, len(style_names) - 1)
                maze = new_animated_maze()
                animate_path(maze)
                show_path = False
            elif key == "5":
                show_path = not show_path
            elif key == "6":
                perfect = not perfect
                maze = make_maze(seed, perfect)
                if on_new_maze:
                    on_new_maze(maze)
            elif key == "7":
                animate_path(maze)
                show_path = True
            elif key == "8":
                animate = not animate
            elif key == "q":
                break
