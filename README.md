# ai-sliding-puzzle
Compile:
```
make
```
Compile with debug flag:
```
make EXTRA="-DDEBUG"
```
Output format:
```
$expansions $moves ${steps}
```

# puzzles
In the source, `puzzle.txt` has a very simple puzzle whereas `puzzle_question.txt` was adapted from a question to provide a more real work example of a sliding puzzle.

# output
Depth-first search using `./main.bin puzzle.txt DFS` required 6 expansions and 6 moves.
```
6 6  Up; Up; Up; Up; Left; Left;
```
Breadth-first search using `/main.bin puzzle.txt BFS` required 11 expansions and 6 moves.
```
11 6  Up; Up; Up; Up; Left; Left;
```
Greedy Best-First Search using `./main.bin puzzle_question.txt GBS` required 17423 expansions and 90 moves.
```
17423 90  Down; Left; Up; Right; Up; Up; Left; Down; Right; Down; Down; Left; Up; Up; Right; Down; Left; Up; Right; Down; Left; Down; Right; Up; Left; Down; Right; Up; Up; Left; Down; Right; Left; Down; Right; Right; Down; Left; Up; Left; Left; Up; Up; Right; Down; Right; Up; Left; Down; Right; Right; Up; Up; Up; Left; Down; Down; Right; Up; Left; Up; Right; Down; Down; Left; Left; Up; Right; Down; Right; Up; Left; Up; Right; Down; Left; Left; Up; Right; Right; Down; Down; Left; Up; Up; Left; Down; Right; Down; Right;
```
A Star search using `./main.bin puzzle_question.txt AS` required 33 expansions and 14 moves.
```
33 14  Up; Up; Left; Down; Down; Down; Right; Up; Up; Left; Down; Down; Right; Right;
```

# results
* DFS and BFS, while able to complete the best-case scenario `puzzle.txt`, they fail on the larger `puzzle_question.txt` as they are non optimal search algorithms.
* GBS is able to complete both puzzles, but `puzzle_question.txt` non-optimally as expected.
* A Star revealed the most promising results, both with the lowest cost.
