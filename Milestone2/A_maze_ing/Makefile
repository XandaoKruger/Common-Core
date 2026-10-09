
FLAGS =  --warn-return-any \
		--warn-unused-ignores \
		--ignore-missing-imports \
		--disallow-untyped-defs \
		--check-untyped-defs

FLAKE8_EXCLUDE = .venv,.git,__pycache__,.mypy_cache,build,dist,testes,maze_analizer.py,mazegen.egg-info

LIMIT ?= on

install:
	@echo "\033[0;36mSynchronizing dependencies\033[0m"
	@uv sync

run:
	@echo "\033[0;32mInitializing maze processes\033[0m"
	@uv run a_maze_ing.py config.txt --limit=${LIMIT}

debug:
	uv run python3 -m pdb a_maze_ing.py config.txt --limit=${LIMIT}

clean:
	@rm -rf .mypy_cache
	@rm -rf __pycache__
	@rm -rf view/__pycache__
	@rm -rf mazegen/__pycache__
	@rm -rf view/.mypy_cache
	@rm -rf mazegen/.mypy_cache
	@echo "\033[0;31m All .mypy_cache & __pycache__ removed.\033[0m"

build:
	uv build --wheel --out-dir .
	@rm -rf build *.egg-info
 
lint:
	@echo "\033[0;35mRunning mypy with flags\033[0m"
	@uv run mypy . ${FLAGS}

	@echo " "

	@echo "\033[0;35mRunning flake8 .\033[0m"
	@uv run flake8 --exclude=${FLAKE8_EXCLUDE} .

	@rm -rf .mypy_cache
	@rm -rf view/.mypy_cache
	@rm -rf mazegen/.mypy_cache
	@rm -rf __pycache__
	@rm -rf view/__pycache__
	@rm -rf mazegen/__pycache__

lint-strict:
	@echo "\033[0;35mRunning mypy --strict .\033[0m"
	@uv run mypy --strict .

	@echo " "

	@echo "\033[0;35mRunning flake8 .\033[0m"
	@uv run flake8 --exclude=${FLAKE8_EXCLUDE} .

	@rm -rf .mypy_cache
	@rm -rf view/.mypy_cache
	@rm -rf mazegen/.mypy_cache
	@rm -rf __pycache__
	@rm -rf view/__pycache__
	@rm -rf mazegen/__pycache__

.PHONY: install run debug clean build lint lint-strict
