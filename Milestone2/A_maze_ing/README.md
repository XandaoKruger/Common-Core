*This project has been created as part of the 42 curriculum by acano-kr, dserra-d.*

# A-Maze-ing

<p align="center">
  <a href="https://github.com/XandaoKruger"><img src="https://img.shields.io/badge/GitHub-acano--kr-181717?style=for-the-badge&logo=github" alt="acano-kr"/></a>
  <a href="https://github.com/Davidtexas-94"><img src="https://img.shields.io/badge/GitHub-dserra--d-181717?style=for-the-badge&logo=github" alt="dserra-d"/></a>
</p>

## Description

A-Maze-ing generates a random maze from a configuration file, writes it to a
file in a hexadecimal wall format, and displays it in the terminal with an
interactive menu. Goal: practise algorithms (maze generation, shortest path),
clean Python (typing, docstrings, `flake8`, `mypy`) and building a reusable
package.

Overview:

- Reads a `KEY=VALUE` config file and validates it (clear errors, no crash).
- Generates a perfect maze (one path between any two cells) or a non-perfect
  one (loops, almost no dead ends) with a reproducible seed.
- Draws a "42" pattern of closed cells in the centre of the maze.
- Computes the shortest path entry -> exit and writes it to the output file.
- Renders the maze with `rich`, with colours, wall styles and animations.
- Ships the generator as a standalone pip-installable package (`mazegen`).

## Instructions

Requirements: Python 3.10+ and [`uv`](https://docs.astral.sh/uv/).

```
make install     # create the virtualenv and install dependencies
make run         # run with config.txt  (uv run a_maze_ing.py config.txt)
```

Without `make`: `python3 a_maze_ing.py <config_file>` (needs `rich` installed).

| Target             | What it does                                           |
|--------------------|--------------------------------------------------------|
| `make install`     | `uv sync`                                              |
| `make run`         | run the program with `config.txt`                      |
| `make debug`       | run under `pdb`                                        |
| `make lint`        | `flake8 .` and `mypy` with the required flags          |
| `make lint-strict` | `flake8 .` and `mypy --strict`                         |
| `make build`       | build `mazegen-*.whl` at the root of the repository    |
| `make clean`       | remove `__pycache__` and `.mypy_cache`                 |

### Interactive menu

| Key | Action                                      |
|-----|---------------------------------------------|
| `1` | new maze (new random seed)                  |
| `2` | new random colours                          |
| `3` | next wall style                             |
| `4` | everything random (seed, colours, style)    |
| `5` | show / hide the shortest path               |
| `6` | toggle perfect / non-perfect                |
| `7` | animate the shortest path                   |
| `8` | animation on / off                          |
| `q` | quit                                        |

## Config file

One `KEY=VALUE` per line. Blank lines and lines starting with `#` are
ignored. Keys are case-insensitive, spaces around keys and values are
ignored, unknown keys are ignored, a repeated key is an error.

| Key           | Required | Format / meaning                                          |
|---------------|----------|-----------------------------------------------------------|
| `WIDTH`       | yes      | integer > 0, cells per row                                |
| `HEIGHT`      | yes      | integer > 0, number of rows                               |
| `ENTRY`       | yes      | `x,y` inside the grid, not in the "42" pattern            |
| `EXIT`        | yes      | `x,y` inside the grid, different from `ENTRY`, not in "42"|
| `OUTPUT_FILE` | yes      | path of the file where the maze is written                |
| `PERFECT`     | yes      | `True` or `False` (anything else is an error)             |
| `SEED`        | no       | integer; same seed and config give the same maze          |
|               |          | (random if absent, and printed at start)                  |

Example (`config.txt`):

```
# A-Maze-ing default config - 20x15 grid, perfect mode, seed 42
WIDTH=20
HEIGHT=15
ENTRY=0,0
EXIT=19,14
OUTPUT_FILE=maze.txt
PERFECT=True
SEED=42
```

Invalid files (missing file, missing key, bad value, entry equal to exit,
entry or exit inside the "42", ...) print `Config error: <reason>` and exit
with code 1, without a traceback.

The "42" pattern is drawn only if the grid is at least 9x7; in a smaller grid
it is skipped with a message.

## Output file

```
<H rows of W hexadecimal digits>
<empty line>
<entry x,y>
<exit x,y>
<shortest path as letters N, E, S, W>
```

Each digit encodes the walls of one cell as 4 bits, `1` = closed:
`N = 1`, `E = 2`, `S = 4`, `W = 8` (e.g. `F` = fully closed, `0` = fully
open). Neighbouring cells always agree about the wall they share. The file is
rewritten every time a new maze is shown, so it always matches the screen.

## Algorithm

**Generation: randomized depth-first search (recursive backtracker),
iterative version.** From the entry cell, walk to a random unvisited
neighbour and open the wall between them; when a cell has no unvisited
neighbour, backtrack through an explicit stack. The "42" cells are marked as
visited from the start, so they stay closed. The result is a spanning tree:
a perfect maze.

**Non-perfect mode (`PERFECT=False`).** After the DFS, one extra wall is opened
at every dead end (braiding), which creates loops. A wall is opened only if
it does not create a 3x3 open area and does not lead into the "42". Then the
four corners and the centre are guaranteed to have at least one opening, so
the maze is playable. A dead end that sits against the "42" and has no safe
wall may remain.

**Solving: breadth-first search (BFS).** BFS expands the maze in layers, so
the first time it reaches the exit it has found a shortest path, also when
the maze has loops. A DFS would only give *a* path.

### Why these choices

- The backtracker is simple, needs no recursion (no recursion-limit problem
  on big grids), is O(W x H) and produces long winding corridors.
- Starting from "all walls closed + visited '42' cells" makes the pattern
  trivial to respect.
- BFS gives the shortest path required by the output format, in O(W x H).

## Reusable code

The generator is a standalone package, `mazegen`, with no dependencies
(only the viewer in `view/` needs `rich`). Build and install it:

```
make build
pip install mazegen-1.0.0-py3-none-any.whl
```

```python
from mazegen import MazeGenerator

maze = MazeGenerator(
    width=20,
    height=15,
    entry=(0, 0),
    exit_pos=(19, 14),
    perfect=True,
    seed=42,
)
maze.generate()

print(maze.solve())
```

| Parameter  | Meaning                                              |
|------------|------------------------------------------------------|
| `width`    | cells per row                                        |
| `height`   | number of rows                                       |
| `entry`    | `(x, y)` of the entry cell                           |
| `exit_pos` | `(x, y)` of the exit cell                            |
| `perfect`  | `True`: one path only. `False`: loops, few dead ends |
| `seed`     | same seed and parameters always give the same maze   |

Accessing the maze and a solution:

- `maze.get_cell_walls(x, y)`: walls of one cell as bits (N=1, E=2, S=4, W=8).
- `maze.to_hex_rows()`: the whole grid, one hex digit per cell.
- `maze.solve()`: shortest path as letters, e.g. `['E', 'E', 'S']`.
- `maze.find_path()`: the same path as a list of `(x, y)` cells.
- `maze.get_pattern_cells()`: cells of the "42" pattern.
- `generate(on_step=callback)`: optional callback called after each wall is
  opened (used by the viewer to animate the generation).

`generate()` raises `ValueError` if entry or exit fall inside the "42".

## Advanced features

- 17 wall styles (thin, rounded, thick, double, dashed, ASCII, blocks, ...),
  rounded is the default; random colour themes; path arrows in 3 sets.
- Animation of the maze being carved, and of the shortest path.
- Reproducible mazes through `SEED`.

## Project structure

```
a_maze_ing.py      entry point
config.py          config parsing and validation
config.txt         default configuration
mazegen/           reusable package (generator, '42' glyphs)
view/              terminal view (render, menu) built on rich
pyproject.toml     package and dev tooling
Makefile
mazegen-1.0.0-py3-none-any.whl
```

## Team and project management

**Roles**

We split the project as follows, but both of us worked on every part of it:

- Alexandre (acano-kr): maze generator (`mazegen`), config parsing,
  shortest-path solver, linting and typing, packaging.

- David (dserra-d): terminal view (`view/`: render and interactive menu),
  integration in `a_maze_ing.py`, validation of the generator output.

**Planning and how it evolved.** We started by splitting the work in
generator, config and view, agreeing on a small public API
(`get_cell_walls`, `solve`, `width`, `height`, `entry`, `exit_pos`) so that
the view never touches generator internals. When the subject was updated
(non-perfect mazes must be playable: open corners and centre, at least two
independent routes, few dead ends) we added the corner/centre rule and a
margin of one cell around the "42" (minimum grid 9x7). Late in the project
we added the packaging and finished the animations (maze generation and
shortest path), including their performance optimisation.

**What worked well.** The clean split between `mazegen` and `view`; both of us
knowing the whole code base, so we could review and fix each other's parts;
keeping helper functions small (solve, config parsing); checking mazes with
scripts over many seeds and sizes (consistent walls, borders, connectivity,
no 3x3 area, valid path).

**What could be improved.** Possible extensions: more generation algorithms
(for example Prim or Kruskal) selectable from the config file.

**Tools.** Git and GitHub, `uv`, `make`, `rich`, `flake8`, `mypy`,
`setuptools` to build the wheel, and an AI assistant (see below).

## Resources

- Maze generation algorithms:
  <https://en.wikipedia.org/wiki/Maze_generation_algorithm>
- Depth-first search: <https://en.wikipedia.org/wiki/Depth-first_search>
- Breadth-first search: <https://en.wikipedia.org/wiki/Breadth-first_search>
- Jamis Buck, *Mazes for Programmers* (Pragmatic Bookshelf, 2015) and his
  blog series on maze algorithms.
- Python: `collections.deque`, `dataclasses`, `typing`
  (<https://docs.python.org/3/>), PEP 8, PEP 257
  (<https://peps.python.org/pep-0257/>).
- `rich`: <https://rich.readthedocs.io/>
- Python Packaging User Guide: <https://packaging.python.org/>
- `mypy`: <https://mypy.readthedocs.io/>, `flake8`:
  <https://flake8.pycqa.org/>

**Use of AI.** We used an AI assistant (Claude, by Anthropic) for:
reviewing the code against the subject; explaining concepts (BFS/DFS, typing,
packaging, text encodings). We tested the results ourselves (many seeds and
sizes, lint, a clean-virtualenv install of the wheel) and we can explain every
part of the code.

## License

MIT, see [LICENSE.md](LICENSE.md).