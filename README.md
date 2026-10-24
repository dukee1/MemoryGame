# MemoryGame

A memory-matching game written in C++17. Find all matching pairs of cards on a 4×4 board by flipping two cards per turn.

## How to Play

1. In the main menu, choose `1` to start a new game.
2. Enter the row and column of the first card, e.g. `1 2`.
3. Enter the row and column of the second card.
4. If the symbols match, the pair stays revealed. Otherwise, both cards are hidden again.
5. The game ends when all pairs are found. Your score is the number of turns taken.

## Build and Run

Requirements: CMake 3.14+ and a compiler with C++17 support.

```
mkdir build
cd build
cmake ..
cmake --build .
./MemoryGame
```

On Windows, the executable is `MemoryGame.exe` (inside `build` or `build/Debug`).

## Project Structure

```
MemoryGame/
├── include/
│   ├── Board.h
│   ├── Card.h
│   └── Game.h
├── src/
│   ├── Board.cpp
│   ├── Card.cpp
│   └── Game.cpp
├── CMakeLists.txt
└── main.cpp
```