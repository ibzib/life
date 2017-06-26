## Description

- Visualize simple 2D, binary-state cellular automata
- Core functionality is provided by `life.hpp`/`life.cpp`
- `life_example.cpp` is a simple program illustrating the game. It randomly creates a starting grid of user-specified dimensions, then users cycle through generations by pressing **Enter**.

## Rules

#### `conway.cpp` [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
1. Each living cell with four or more neighbors that are alive dies, due to overpopulation.
2. Each living cell with only one neighbor or with no neighbor alive dies, due to isolation.
3. Each living cell with two or three neighboring cells that are alive survives for the next generation.
4. Each cell that is currently dead and that has exactly three neighbors that are alive is in just the right nurturing environment to be a “birth cell,” and becomes alive in the next period.

#### Custom Rules
- Users can define their own rules by defining a function like `int rulefunction(Life& game)`, then passing its pointer to `Life::run`

## Example Usage
1. `make`
2. `./life_example 5 5 0.6`
3. Press **Enter** a bunch to iterate through generations
4. Press `q` to quit

## TODO

- [x] let user define their own rules (without modifying `life.h`)
- [x] make console printing less "flickery" somehow
- [ ] read/write gamestate files
- [ ] add at least 1 or 2 simple tests
