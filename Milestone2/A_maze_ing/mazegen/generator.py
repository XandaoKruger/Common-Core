from random import Random


class MazeGenerator:
    '''
    Docstring for MazeGenerator
    '''

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

    def get_cell_walls(self, x: int, y: int) -> int:
        '''

        '''
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

        neighbors = []
        candidates = [(x, y - 1), (x, y + 1), (x + 1, y), (x - 1, y)]

        for nx, ny in candidates:
            if (
                0 <= nx < self.width
                and 0 <= ny < self.height
                and (nx, ny) not in visited
            ):
                neighbors.append((nx, ny))
        return neighbors

    def _remove_wall(
            self, x1: int, y1: int, x2: int, y2: int
    ) -> None:
        """Open the wall between two adjacent cells.

        Args:
        x1, y1: Coordinates of the first cell.
        x2, y2: Coordinates of the second cell, adjacent to the first.
        """

        if x2 > x1:
            self._vertical_walls[y1][x1 + 1] = False
        elif x2 < x1:
            self._vertical_walls[y1][x1] = False
        elif y2 > y1:
            self._horizontal_walls[y1 + 1][x1] = False
        elif y2 < y1:
            self._horizontal_walls[y1][x1] = False

    def generate(self) -> None:
        """Carve the maze using an iterative randomized DFS (backtracker).

        Builds a spanning tree over the grid by walking to random
        unvisited neighbors and removing walls between visited cells,
        backtracking via an explicit stack when a cell has no unvisited
        neighbors left.
        """

        visited: set[tuple[int, int]] = set()
        stack: list[tuple[int, int]] = []

        start = (0, 0)
        visited.add(start)
        stack.append(start)

        while stack:
            x, y = stack[-1]
            neighbors = self._get_unvisited_neighbors(x, y, visited)

            if neighbors:
                nx, ny = self._rng.choice(neighbors)
                self._remove_wall(x, y, nx, ny)
                visited.add((nx, ny))
                stack.append((nx, ny))
            else:
                stack.pop()

        self._generated = True
        if not self.perfect:
            self._braid()

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
        neighbors = []

        candidates = [
            (x, y - 1, 1),   # North, bit 1
            (x + 1, y, 2),   # East,  bit 2
            (x, y + 1, 4),   # South, bit 4
            (x - 1, y, 8),   # West,  bit 8
        ]

        for nx, ny, bit in candidates:
            if not (0 <= nx < self.width and 0 <= ny < self.height):
                continue
            if walls & bit:
                continue
            if (nx, ny) in visited:
                continue
            neighbors.append((nx, ny))

        return neighbors

    def solve(self) -> list[str]:
        """Find the shortest path from entry to exit using BFS.

        Returns:
            Ordered list of direction letters ('N', 'E', 'S', 'W')
            describing the shortest path from entry to exit.
        """
        queue: list[tuple[int, int]] = [self.entry]
        visited: set[tuple[int, int]] = {self.entry}
        came_from: dict[tuple[int, int], tuple[int, int]] = {}

        while queue:
            x, y = queue.pop(0)

            if (x, y) == self.exit_pos:
                break

            for nx, ny in self._get_reachable_neighbors(x, y, visited):
                visited.add((nx, ny))
                came_from[(nx, ny)] = (x, y)
                queue.append((nx, ny))

        path_cells = [self.exit_pos]
        while path_cells[-1] != self.entry:
            path_cells.append(came_from[path_cells[-1]])
        path_cells.reverse()

        directions = []
        for (x1, y1), (x2, y2) in zip(path_cells, path_cells[1:]):
            if x2 > x1:
                directions.append("E")
            elif x2 < x1:
                directions.append("W")
            elif y2 > y1:
                directions.append("S")
            elif y2 < y1:
                directions.append("N")

        return directions

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
        walls = self.get_cell_walls(x, y)

        # bin é função do py, que devolve o inteiro em representação binária.
        # (com "0b" na frente) exemplo: bin(13)  ->  "0b1101".
        # count("1") é para contar quantos 1 tem no binário, no 13 -> 3
        closed = bin(walls).count("1")

        # 4 - closed, o que sobra é quantas estão abertas
        return 4 - closed

    def _get_closed_neighbors(self, x: int, y: int) -> list[tuple[int, int]]:

        walls = self.get_cell_walls(x, y)

        candidates = [
            (x, y-1, 1),  # North
            (x+1, y, 2),  # East
            (x, y+1, 4),  # South
            (x-1, y, 8),  # West
        ]

        neighbors = []

        for nx, ny, bit in candidates:
            if not (0 <= nx < self.width and 0 <= ny < self.height):
                continue
            if walls & bit:
                neighbors.append((nx, ny))
        return neighbors

    def _braid(self) -> None:
        """Remove all dead ends by opening one extra wall per dead-end cell.

        Skips candidate walls whose removal would create a 3x3 fully-open
        area, trying alternatives first; falls back to the first candidate
        only if every option would violate the corridor-width rule.
        """

        for y in range(self.height):
            for x in range(self.width):
                if self._count_open_walls(x, y) == 1:
                    candidates = self._get_closed_neighbors(x, y)
                    self._rng.shuffle(candidates)

                    opened = False
                    for nx, ny in candidates:
                        self._remove_wall(x, y, nx, ny)
                        if self._3x3_open_area():
                            self._add_wall(x, y, nx, ny)
                        else:
                            opened = True
                            break

                    if not opened and candidates:
                        nx, ny = candidates[0]
                        self._remove_wall(x, y, nx, ny)

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
