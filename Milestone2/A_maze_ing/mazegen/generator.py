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
            self, x: int, y: int, visited: set[tuple[int,int]]
    ) -> list[tuple[int,int]]:
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
    
    def _get_reachable_neighbors(
            self, x: int, y: int, visited: set[tuple[int, int]]
    ) -> list[tuple[int, int]]:
        """Return in-bounds neighboring cells reachable (no wall) and unvisited.

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

    def solve(self) -> :