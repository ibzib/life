## Description

- Visualize simple 2D, binary-state cellular automata
- Core functionality is provided by `life.hpp`/`life.cpp`
- `life_example.cpp` is a simple program illustrating the game. It randomly creates a starting grid of user-specified dimensions, then users cycle through generations by pressing **Enter**.
- `life_example.cpp` includes the rule sets provided below

## Rule Sets

#### [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
1. Each living cell with four or more neighbors that are alive dies, due to overpopulation.
2. Each living cell with only one neighbor or with no neighbor alive dies, due to isolation.
3. Each living cell with two or three neighboring cells that are alive survives for the next generation.
4. Each cell that is currently dead and that has exactly three neighbors that are alive is in just the right nurturing environment to be a “birth cell,” and becomes alive in the next period.

#### Traffic
- This one is a lot more boring, mostly just to demonstrate that other rules are possible.
- Each row can be viewed as a lane of traffic flowing from left to right.
1. If the space ahead of a car in its own lane is unoccupied, it advances to that space.
2. If the space ahead of a car in its own lane is occupied, and a space adjacent to that car in its neighboring lanes is unoccupied, it will switch lanes (with the left (upper) lane getting preference).
3. If two cars try to move into the same space at once, they will "crash" and will both be removed from the game.

#### Custom Rules
- Users can define their own rules by defining a function like `int rulefunction(Life& game)`, then passing its pointer to `Life::run`

## Example Usage (*nix systems)
1. `make`
2. `./life_example 5 4 0.6`
3. Press **Enter** a bunch (or pipe in `yes`)

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
- [x] implement traffic rules
- [ ] make console printing less "flickery" somehow
- [ ] read/write gamestate files
- [ ] add at least 1 or 2 simple tests