from random import Random
from mazegen.glyphs import GLYPHS
from collections import deque
from typing import Callable


class MazeGenerator:
    """Generate, store and solve a rectangular maze.

    The maze is carved with a randomized DFS (backtracker). With
    perfect=False, extra walls are opened to create loops and remove
    dead ends. A '42' pattern of closed cells is drawn in the centre
    when the grid is big enough.

    Args:
        width: Number of cells per row.
        height: Number of rows.
        entry: (x, y) of the entry cell.
        exit_pos: (x, y) of the exit cell.
        perfect: True for a single path between entry and exit.
        seed: Seed for the random generator (same seed, same maze).
    """

    def __init__(
        self,
        width: int,
        height: int,
        entry: tuple[int, int],
        exit_pos: tuple[int, int],
        perfect: bool,
        seed: int,
        algorithm: str = "backtracker",
    ) -> None:
        """Create a maze with every wall closed; call generate to carve it."""

        self.width = width
        self.height = height
        self.entry = entry
        self.exit_pos = exit_pos
        self.perfect = perfect
        self.seed = seed
        self.algorithm = algorithm
        self._rng = Random(seed)

        # Todas as paredes começam fechadas -> Bloco fechado com 4 paredes
        self._horizontal_walls = [

            # [True] * width = Verdadeiro width vezes, resumindo, num width=3
            # seria [True, True, True]
            [True] * width for _ in range(height + 1)
        ]
        self._vertical_walls = [
            [True] * (width + 1) for _ in range(height)
        ]
        self._generated = False
        self.pattern_cells: set[tuple[int, int]] = set()

    def get_cell_walls(self, x: int, y: int) -> int:
        """Return the walls of cell (x, y) as a 4-bit integer.

        Bits: 1 = north, 2 = east, 4 = south, 8 = west. A set bit means
        the wall is closed, so 0 is a fully open cell and 15 a fully
        closed one.
        """

        walls = 0

        if self._horizontal_walls[y][x]:
            walls += 1

        if self._vertical_walls[y][x + 1]:
            walls += 2

        if self._horizontal_walls[y + 1][x]:
            walls += 4

        if self._vertical_walls[y][x]:
            walls += 8

        return walls

    def _get_unvisited_neighbors(
            self, x: int, y: int, visited: set[tuple[int, int]]
    ) -> list[tuple[int, int]]:
        """Return in-bounds neighboring cells of (x, y) not yet visited.

        Args:
            x: Column of the current cell.
            y: Row of the current cell.
            visited: Set of already-visited (x, y) coordinates.

        Returns:
            List of (x, y) tuples for valid, unvisited neighbors.
        """

        candidates = [(x, y - 1), (x, y + 1), (x + 1, y), (x - 1, y)]

        return [
            (nx, ny) for nx, ny in candidates
            if 0 <= nx < self.width
            and 0 <= ny < self.height
            and (nx, ny) not in visited
        ]

    def _remove_wall(
            self, x1: int, y1: int, x2: int, y2: int
    ) -> None:
        """Open the wall between two adjacent cells.

        Args:
            x1: Column of the first cell.
            y1: Row of the first cell.
            x2: Column of the second cell, adjacent to the first.
            y2: Row of the second cell.
        """

        if x2 > x1:
            self._vertical_walls[y1][x1 + 1] = False
        elif x2 < x1:
            self._vertical_walls[y1][x1] = False
        elif y2 > y1:
            self._horizontal_walls[y1 + 1][x1] = False
        elif y2 < y1:
            self._horizontal_walls[y1][x1] = False

    def generate(
        self,
        on_step: Callable[["MazeGenerator"], None] | None = None,
    ) -> None:
        """Carve the maze using an iterative randomized DFS (backtracker).

        Builds a spanning tree over the grid by walking to random
        unvisited neighbors and removing walls between visited cells,
        backtracking via an explicit stack when a cell has no unvisited
        neighbors left.

        Args:
            on_step: Optional callback called after each wall is opened.
        """

        self.pattern_cells = self._build_pattern_cells()

        if (
            self.entry in self.pattern_cells
                or self.exit_pos in self.pattern_cells):
            raise ValueError(
                "entry/exit cannot be inside the '42' pattern"
            )

        visited: set[tuple[int, int]] = set(self.pattern_cells)
        stack: list[tuple[int, int]] = []

        start = self.entry
        visited.add(start)
        stack.append(start)

        while stack:
            x, y = stack[-1]
            neighbors = self._get_unvisited_neighbors(x, y, visited)

            if neighbors:
                nx, ny = self._rng.choice(neighbors)
                self._remove_wall(x, y, nx, ny)
                if on_step:
                    on_step(self)
                visited.add((nx, ny))
                stack.append((nx, ny))
            else:
                stack.pop()

        self._generated = True
        if not self.perfect:
            self._braid(on_step)
            self._enforce_corners_and_center(on_step)

    def _build_pattern_cells(self, text: str = "42") -> set[tuple[int, int]]:
        """Compute the set of (x, y) cells forming the given pattern text.

        Centers the pattern in the grid. Returns an empty set (and prints
        a warning) if the grid is too small to fit it.
        """

        glyph_w, glyph_h = 3, 5
        gap = 1
        total_w = len(text) * glyph_w + (len(text) - 1) * gap
        margin = 1

        if (total_w + 2 * margin > self.width
                or glyph_h + 2 * margin > self.height):
            print(f"Grid too small for '{text}' pattern - skipping.")
            return set()

        start_x = self.width // 2 - 3
        start_y = (self.height - glyph_h) // 2

        cells: set[tuple[int, int]] = set()
        for i, char in enumerate(text):
            glyph = GLYPHS[char]
            char_x = start_x + i * (glyph_w + gap)
            for row, line in enumerate(glyph):
                for col, pixel in enumerate(line):
                    if pixel == "#":
                        cells.add((char_x + col, start_y + row))

        center = (self.width // 2, self.height // 2)
        cells.discard(center)

        return cells

    def _get_reachable_neighbors(
            self, x: int, y: int, visited: set[tuple[int, int]]
    ) -> list[tuple[int, int]]:
        """Return in-bounds neighboring cells reachable (no wall)
        and unvisited.

        Args:
            x: Column of the current cell.
            y: Row of the current cell.
            visited: Set of already-visited (x, y) coordinates.

        Returns:
            List of (x, y) tuples for neighbors open (no wall) and not visited.
        """

        walls = self.get_cell_walls(x, y)

        candidates = [
            (x, y - 1, 1),   # North, bit 1
            (x + 1, y, 2),   # East,  bit 2
            (x, y + 1, 4),   # South, bit 4
            (x - 1, y, 8),   # West,  bit 8
        ]

        return [
            (nx, ny) for nx, ny, bit in candidates
            if 0 <= nx < self.width
            and 0 <= ny < self.height
            and not (walls & bit)
            and (nx, ny) not in visited
        ]

    def _bfs_parents(self) -> dict[tuple[int, int], tuple[int, int]]:
        """Run BFS from entry and map each reached cell to its parent."""
        queue: deque[tuple[int, int]] = deque([self.entry])
        visited: set[tuple[int, int]] = {self.entry}
        came_from: dict[tuple[int, int], tuple[int, int]] = {}

        while queue:
            x, y = queue.popleft()
            if (x, y) == self.exit_pos:
                break
            for nx, ny in self._get_reachable_neighbors(x, y, visited):
                visited.add((nx, ny))
                came_from[(nx, ny)] = (x, y)
                queue.append((nx, ny))
        return came_from

    def find_path(self) -> list[tuple[int, int]]:
        """Return the shortest path as cells, from entry to exit.

        Raises:
            ValueError: if the exit cannot be reached from the entry.
        """
        came_from = self._bfs_parents()
        if self.exit_pos not in came_from:
            raise ValueError("no path between entry and exit")

        path = [self.exit_pos]
        while path[-1] != self.entry:
            path.append(came_from[path[-1]])
        path.reverse()
        return path

    @staticmethod
    def path_to_directions(path: list[tuple[int, int]]) -> list[str]:
        """Convert a list of adjacent cells into N/E/S/W letters."""
        moves = {(0, -1): "N", (1, 0): "E", (0, 1): "S", (-1, 0): "W"}
        return [
            moves[(x2 - x1, y2 - y1)]
            for (x1, y1), (x2, y2) in zip(path, path[1:])
        ]

    def solve(self) -> list[str]:
        """Return the shortest path from entry to exit as N/E/S/W letters."""
        return self.path_to_directions(self.find_path())

    def to_hex_rows(self) -> list[str]:
        """Encode the maze as rows of hexadecimal wall digits.

        Returns:
            One string per row; each character is get_cell_walls(x, y)
            for that cell, formatted as a single hex digit.
        """
        rows = []
        for y in range(self.height):
            row = ""
            for x in range(self.width):
                row += format(self.get_cell_walls(x, y), "x")
            rows.append(row)
        return rows

    def _count_open_walls(self, x: int, y: int) -> int:
        """Return how many of the 4 sides of cell (x, y) are open."""

        walls = self.get_cell_walls(x, y)

        # bin é função do py, que devolve o inteiro em representação binária.
        # (com "0b" na frente) exemplo: bin(13)  ->  "0b1101".
        # count("1") é para contar quantos 1 tem no binário, no 13 -> 3
        closed = bin(walls).count("1")

        # 4 - closed, o que sobra é quantas estão abertas
        return 4 - closed

    def _get_closed_neighbors(self, x: int, y: int) -> list[tuple[int, int]]:
        """Return in-bounds neighboring cells with a closed wall in between.

        Args:
            x: Column of the current cell.
            y: Row of the current cell.

        Returns:
            List of (x, y) tuples for neighbors separated by a closed wall.
        """

        walls = self.get_cell_walls(x, y)

        candidates = [
            (x, y-1, 1),  # North
            (x+1, y, 2),  # East
            (x, y+1, 4),  # South
            (x-1, y, 8),  # West
        ]

        return [
            (nx, ny) for nx, ny, bit in candidates
            if 0 <= nx < self.width
            and 0 <= ny < self.height
            and (walls & bit)
        ]

    def _braid(
        self,
        on_step: Callable[["MazeGenerator"], None] | None = None,
    ) -> None:
        """Open one extra wall at every dead end, when it is safe.

        A wall is only opened if it does not create a 3x3 open area and
        does not lead into a '42' cell. A dead end with no safe wall is
        left as it is (the subject tolerates a few).

        Args:
            on_step: Optional callback called after each wall is opened.
        """

        for y in range(self.height):
            for x in range(self.width):
                if self._count_open_walls(x, y) == 1:
                    self._open_safe_wall(x, y, on_step)

    def _open_safe_wall(
        self,
        x: int,
        y: int,
        on_step: Callable[["MazeGenerator"], None] | None = None,
    ) -> None:
        """Open one closed wall of (x, y) without creating a 3x3 area.

        Tries the candidate walls in random order and stops at the first
        safe one. If none is safe, the cell is left untouched.

        Args:
            x: Column of the dead-end cell.
            y: Row of the dead-end cell.
            on_step: Optional callback called once a wall is opened.
        """

        candidates = [
            c for c in self._get_closed_neighbors(x, y)
            if c not in self.pattern_cells
        ]
        self._rng.shuffle(candidates)

        for nx, ny in candidates:
            self._remove_wall(x, y, nx, ny)
            if not self._3x3_open_area():
                if on_step:
                    on_step(self)
                return
            self._add_wall(x, y, nx, ny)

    def _is_block_fully_open(self, x: int, y: int) -> bool:
        """
        Check whether the 3x3 block with top-left cell (x, y) is fully open.
        """

        for row in range(y, y + 3):
            for col in range(x, x + 2):
                if self._vertical_walls[row][col + 1]:
                    return False

        for row in range(y, y + 2):
            for col in range(x, x + 3):
                if self._horizontal_walls[row + 1][col]:
                    return False

        return True

    def _3x3_open_area(self) -> bool:
        """
        Check if any 3x3 block in the grid is fully open
        (all internal walls removed).
        """

        for y in range(self.height - 2):
            for x in range(self.width - 2):
                if self._is_block_fully_open(x, y):
                    return True
        return False

    def _add_wall(self, x1: int, y1: int, x2: int, y2: int) -> None:
        """
        Close the wall between two adjacent cells
        (inverse of _remove_wall).
        """

        if x2 > x1:
            self._vertical_walls[y1][x1 + 1] = True
        elif x2 < x1:
            self._vertical_walls[y1][x1] = True
        elif y2 > y1:
            self._horizontal_walls[y1 + 1][x1] = True
        elif y2 < y1:
            self._horizontal_walls[y1][x1] = True

    def _enforce_corners_and_center(
        self,
        on_step: Callable[["MazeGenerator"], None] | None = None,
    ) -> None:
        """Guarantee the four corners and the centre have at least one
        open wall (Pac-Man board rule), never opening into a pattern cell.
        """
        corners = [
            (0, 0),
            (self.width - 1, 0),
            (0, self.height - 1),
            (self.width - 1, self.height - 1),
        ]
        center = (self.width // 2, self.height // 2)

        for x, y in corners + [center]:
            if (x, y) in self.pattern_cells:
                continue
            if self._count_open_walls(x, y) == 0:
                candidates = [
                    c for c in self._get_closed_neighbors(x, y)
                    if c not in self.pattern_cells
                ]
                if candidates:
                    nx, ny = candidates[0]
                    self._remove_wall(x, y, nx, ny)
                    if on_step:
                        on_step(self)

    def get_pattern_cells(self) -> set[tuple[int, int]]:
        """Return the (x, y) cells that form the '42' pattern."""
        return set(self.pattern_cells)
