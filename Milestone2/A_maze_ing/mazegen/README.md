# mazegen

Reusable maze generator: randomized DFS (backtracker) with a BFS solver.
Pure Python 3.10+, no dependencies.

## Install

    pip install mazegen-1.0.0-py3-none-any.whl

## Basic usage

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

## Custom parameters

| Parameter  | Meaning                                                    |
|------------|------------------------------------------------------------|
| `width`    | cells per row                                              |
| `height`   | number of rows                                             |
| `entry`    | `(x, y)` of the entry cell                                 |
| `exit_pos` | `(x, y)` of the exit cell                                  |
| `perfect`  | `True`: one path only. `False`: loops, few dead ends       |
| `seed`     | same seed and parameters always give the same maze         |

`generate()` raises `ValueError` if entry or exit fall inside the
centred "42" pattern (drawn only when the grid is at least 9x7).

## Accessing the maze and a solution

- `maze.get_cell_walls(x, y)`: walls of one cell as bits
  (N=1, E=2, S=4, W=8; a set bit means the wall is closed).
- `maze.to_hex_rows()`: the whole grid, one hex digit per cell.
- `maze.solve()`: shortest path as letters, e.g. `['E', 'E', 'S']`.
- `maze.find_path()`: the same path as a list of `(x, y)` cells.
- `maze.get_pattern_cells()`: cells of the "42" pattern.