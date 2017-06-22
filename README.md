## Description

- Visualize simple 2D cellular automata
- Core functionality is provided by `life.hpp`/`life.cpp`
- `life_example.cpp` is a simple program illustrating the game. It randomly creates a starting grid of user-specified dimensions, then users cycle through generations by pressing **Enter**.
- `life_example.cpp` includes the rule sets provided below

#### [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
1. Each living cell with four or more neighbors that are alive dies, due to overpopulation.
2. Each living cell with only one neighbor or with no neighbor alive dies, due to isolation.
3. Each living cell with two or three neighboring cells that are alive survives for the next generation.
4. Each cell that is currently dead and that has exactly three neighbors that are alive is in just the right nurturing environment to be a “birth cell,” and becomes alive in the next period.

#### Traffic
1. To be announced

#### Custom Rules
- Users can define their own rules by defining a function like `int rulefunction(Life& game)`, then passing its pointer to `run`

## Example Usage (*nix systems)
1. `make`
2. `./life_example 5 4 0.6`
3. Press **Enter** a bunch (if you don't want to have to do this, pipe in `yes`)

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

## TODO

- [x] use `std::vector` instead of C-style arrays
- [x] support different game rules
- [x] let user define their own rules (without modifying `life.h`)
- [ ] implement traffic rules
- [ ] read/write gamestate files
- [ ] add at least 1 or 2 simple tests