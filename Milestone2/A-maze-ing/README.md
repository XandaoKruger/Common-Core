*This project has been created as part of the 42 curriculum by jode-mel, acano-kr.*

# A-Maze-ing

## Description

A-Maze-ing is a terminal-based maze generator and solver written in Python 3.10+.

The project generates mazes using either the Depth-First Search (DFS) Recursive Backtracker algorithm or Prim's algorithm, embeds a customizable alphanumeric pattern within the maze (default: `"42"`), computes the shortest path between the entry and exit using Breadth-First Search (BFS), and renders the result directly in the terminal using ANSI colors and Unicode block characters.

The application includes:

* Procedural maze generation
* Pattern embedding system
* BFS pathfinding
* Interactive terminal renderer
* Animated maze generation and path visualization
* Configurable maze dimensions, seed, and generation mode
* Reusable Python package (`mazegen`)

### Project Goal

The goal of the project is to explore procedural content generation through maze algorithms while developing a reusable, modular, and configurable maze-generation library.

---

## Features

* DFS (Recursive Backtracker) maze generation
* Prim's maze generation
* Perfect and imperfect maze modes
* Embedded text patterns (default `"42"`)
* Reproducible generation using seeds
* BFS shortest-path solving
* Interactive terminal interface
* Animated maze generation
* Animated solution visualization
* Reusable Python package

---

## Instructions

### Requirements

* Python 3.10+
* pip
* make

### Build and Run

```bash
# Build the package
make build

# Install dependencies in a virtual environment
make install

# Run the project
make run
```

### Development Commands

```bash
make debug
make lint
make lint-strict
make clean
make clean-venv
```

### Manual Execution

```bash
python3 a_maze_ing.py config.txt
```

---

## Configuration File

The program expects a configuration file as its only argument.

### Format

```ini
WIDTH=20
HEIGHT=15
ENTRY=0,0
EXIT=19,14
OUTPUT_FILE=maze.txt
PERFECT=True
SEED=12345
PATTERN=42
```

### Supported Keys

| Key         | Type    | Required | Description                    |
| ----------- | ------- | -------- | ------------------------------ |
| WIDTH       | Integer | Yes      | Maze width                     |
| HEIGHT      | Integer | Yes      | Maze height                    |
| ENTRY       | x,y     | Yes      | Entry coordinates              |
| EXIT        | x,y     | Yes      | Exit coordinates               |
| OUTPUT_FILE | String  | Yes      | Output file path               |
| PERFECT     | Boolean | Yes      | Perfect maze (no loops)        |
| SEED        | Integer | No       | Reproducible random seed       |
| PATTERN     | String  | No       | Embedded pattern (default: 42) |

### Notes

* Keys are case-insensitive.
* Lines beginning with `#` are treated as comments.
* Entry and exit coordinates must be within maze boundaries.
* Entry and exit cannot be the same cell.

---

## Maze Generation Algorithm

### Primary Algorithm: DFS Recursive Backtracker

The default maze-generation algorithm is the iterative Depth-First Search Recursive Backtracker.

Algorithm steps:

1. Select a random starting cell.
2. Mark the cell as visited.
3. Randomly select an unvisited neighbor.
4. Remove the wall between the current cell and the selected neighbor.
5. Continue until no unvisited neighbors remain.
6. Backtrack using a stack.
7. Repeat until all reachable cells have been visited.

### Why DFS?

DFS was chosen because:

* It produces long and visually interesting corridors.
* It creates challenging mazes with a strong sense of exploration.
* It is simple to implement efficiently using an explicit stack.
* It integrates naturally with the pattern-mask system used by this project.
* It guarantees a perfect maze when no additional walls are removed.

### Alternative Algorithm: Prim's Algorithm

Prim's algorithm is available through the interactive menu.

Compared to DFS:

* Produces more branching paths.
* Generates shorter dead ends.
* Creates a different maze aesthetic.

---

## Pathfinding

After generation, the maze is solved using Breadth-First Search (BFS).

BFS guarantees the shortest path between the entry and exit cells.

The resulting solution path is stored as a sequence of directions:

```python
['E', 'E', 'S', 'S', 'W']
```

and can be visualized directly in the terminal.

---

## Reusable Components

The project contains a reusable Python package called `mazegen`.

### Reusable Module

```python
from mazegen.maze_generator import MazeGenerator
```

The `MazeGenerator` class can be imported into any Python project and used independently of the terminal renderer.

### Example

```python
from mazegen.maze_generator import MazeGenerator

maze = MazeGenerator(
    width=20,
    height=15,
    entry={'x': 0, 'y': 0},
    exit={'x': 19, 'y': 14},
    perfect=True,
    pattern='42',
    seed=12345
)

maze.generate(
    algorithm='dfs',
    output_file='maze.txt'
)
```

### Exposed Data

```python
maze.grid
maze.solution_path
maze.seed
```

This separation between generation and rendering allows the maze engine to be reused in other projects without modification.

---

## Team and Project Management

### Team Members and Roles

| Member   | Responsibilities                                                                                                                                              |
| -------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| jode-mel | Maze generation engine, DFS implementation, Prim implementation, BFS pathfinding, pattern masking system, hollow-cell handling, reusable package architecture |
| acano-kr | Terminal renderer, animation system, configuration parser, interactive menu, package integration, project documentation                                       |

### Project Planning

#### Initial Plan

Week 1:

* Configuration parser
* DFS generation
* BFS solver
* Terminal renderer
* Prim's algorithm
* Pattern embedding
* Animations
* Packaging
* Documentation

#### Challenges Encountered

The pattern embedding system required additional work due to:

* Mask management
* Hollow character support
* Integration with generation algorithms

The animation system also required multiple iterations to synchronize rendering and maze state updates correctly.

### What Worked Well

* Bitmask wall representation
* Callback-based animation system
* Deterministic generation through seeds
* Separation between generator and renderer

### Potential Improvements

* Additional generation algorithms (Kruskal, Wilson)
* More customizable pattern fonts
* Additional export formats
* Enhanced renderer themes

---

## Resources

### Documentation and References

* Mazes for Programmers — Jamis Buck
* Recursive Backtracker (DFS) — Jamis Buck
* Prim's Maze Generation Algorithm — Jamis Buck
* Maze Generation Algorithms — Wikipedia
* Breadth-First Search — Wikipedia
* ANSI Escape Codes — Wikipedia

### AI Usage

AI tools were used throughout development as learning and development assistants.

Used for:

* Understanding maze-generation algorithms
* Reviewing implementation approaches
* Discussing architectural decisions
* Explaining Python concepts
* Improving documentation structure

AI was not used to generate the final project automatically. All implementation, integration, debugging, testing, and final design decisions were completed by the project authors.
