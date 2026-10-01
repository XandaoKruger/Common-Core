
FLAGS =  --warn-return-any \
		--warn-unused-ignores \
		--ignore-missing-imports \
		--disallow-untyped-defs \
		--check-untyped-defs

FLAKE8_EXCLUDE = .venv,.git,__pycache__,.mypy_cache,build,dist,testes,maze_analizer.py


install:
	@echo "\033[0;36mSynchronizing dependencies\033[0m"
	@uv sync

run:
	@echo "\033[0;32mInitializing maze processes\033[0m"
	@uv run a_maze_ing.py config.txt

debug:
	uv run python3 -m pdb a_maze_ing.py config.txt

clean:
	@rm -rf __pycache__
	@rm -rf .mypy_cache
	@rm -rf view/__pycache__
	@rm -rf mazegen/__pycache__
	@rm -rf view/.mypy_cache
	@rm -rf mazegen/.mypy_cache
	@echo "\033[0;31m All .mypy_cache & __pycache__ removed.\033[0m"
 
lint:
	@echo "\033[0;35mRunning mypy .\033[0m"
	@uv run mypy . ${FLAGS}

	@echo " "

	@echo "\033[0;35mRunning flake8 .\033[0m"
	@uv run flake8 --exclude=${FLAKE8_EXCLUDE} .

	@rm -rf .mypy_cache
	@rm -rf view/.mypy_cache
	@rm -rf mazegen/.mypy_cache

lint-strict:
	@echo "\033[0;35mRunning mypy --strict .\033[0m"
	@uv run mypy --strict .

	@rm -rf .mypy_cache
	@rm -rf view/.mypy_cache
	@rm -rf mazegen/.mypy_cache

.PHONY: install run debug clean lint lint-strict
