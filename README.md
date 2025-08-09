This is a command-line Cricket Game Simulation written in C. The game simulates a 5-over cricket match between the user and a computer-controlled team. It includes toss logic, difficulty levels, gameplay, and a final match summary with a scorecard.

## Features

- Toss to decide who bats first
- Four difficulty levels: Easy, Medium, Hard, Impossible
- 5-over limited-overs format (30 balls per team)
- Player statistics: runs, balls faced, and out status
- Realistic cricket rules with extras (wides, no balls)
- Final scorecard and match result display

## How to Compile and Run

### 1. Compile the Program

Using GCC:

```bash
gcc -o cricket_game cricket_game.c

2. Run the Program
bash

./cricket_game
Controls
Toss: Choose Heads or Tails

Select difficulty: Enter 1 (Easy) to 4 (Impossible)

Batting: Input number of runs (0, 1, 2, 3, 4, or 6)

Invalid inputs or risky plays may get your batsman out

Bowling is automatic for the computer

Requirements
A C compiler (e.g., GCC)

Works on Linux, macOS, and Windows (using MinGW or compatible)

License
This project is licensed under the MIT License. See the LICENSE file for details.

Credits
Created for educational and entertainment purposes

Player names are used for simulation only and not affiliated with real individuals