## Description

- Simple implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
- Core functionality is provided by `life.hpp`/`life.cpp`
- `life_example.cpp` is a simple program illustrating the game. It randomly creates a starting grid of user-specified dimensions, then users cycle through generations by pressing **Enter**.
- **NOTE**: this implementation uses row-major indexing

#### Rules
1. Each living cell with four or more neighbors that are alive dies, due to overpopulation.
2. Each living cell with only one neighbor or with no neighbor alive dies, due to isolation.
3. Each living cell with two or three neighboring cells that are alive survives for the next generation.
4. Each cell that is currently dead and that has exactly three neighbors that are alive is in just the right nurturing environment to be a “birth cell,” and becomes alive in the next period.

## Example Usage
1. `make`
2. `./life_example 5 4 0.6`
3. Press **Enter** a bunch

Output:
```
. # # #
# . # .
# . # #
. # # .
# # . .

. # # #
# . . .
# . . #
. . . #
# # # .

. # # .
# . . #
. . . .
# . . #
. # # .

. # # .
. # # .
. . . .
. # # .
. # # .
Equilibrium reached.
Simulation ended after 4 generations.
```

## To do

- [x] use std::vector instead of C-style arrays
- [x] support different game rules
- [ ] implement traffic rules
- [ ] read/write gamestate files
- [ ] add at least 1 or 2 simple tests