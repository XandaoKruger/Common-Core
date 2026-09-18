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
