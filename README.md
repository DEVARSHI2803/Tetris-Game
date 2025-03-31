

# Block Blitz

Tetris was one of the very first puzzle games that captivated players worldwide. Here we Binary Bandits have created a simpler version of it using our knowledge on data structures and some libraries.

## Authors

Team: Binary Bandits

Names: | Student Id:

Vatsal Mori | 202401436  

Devarshi Patel | 202401445  

Shrey Patel | 202401449  

Vedant Shah | 202401475  


## How to Start

Requirements:  
- Windows OS  
- C++ Compiler  

Steps to Compile & Run:
1) Open a terminal (or Command Prompt in Windows).  
2) Navigate to the folder containing `tetris_q.cpp`.  
3) Compile using G++: `g++ tetris_q.cpp -o tetris_game`  
4) Run the executable: `./tetris_game`  

## WORKING

Simple keyboard keys are taken into account to operate through the game.  

- 'A' or '<': Move tetromino left  
- 'D' or '>': Move tetromino right  
- 'W' or '^': Rotate tetromino  
-  'v': Drop tetromino faster  
- 'Space': Hard drop tetromino  
- 'Q': Quit game  

Rules are as simple as it gets: arrange falling tetrominoes to form complete horizontal lines. Clear as many lines as you can before the stack reaches the top. The more lines you clear, the higher your score. Compete with your friends showing off your highest score.

## Code Structure

1) ResetGame()
   Working:
   - Clears the game grid.  
   - Resets all variables (position, score, level) when the game starts.  
   - Spawns a new tetromino at the top center of the screen.  

2) DrawGrid()
   Working:
   - Clears the screen.  
   - Prints boundaries in blue.  
   - Draws the current tetromino in red and locked pieces in green.  

3) HandleInput()  
   Working: 
   - Checks if a key is pressed.  
   - Supports WASD, spacebar, and 'Q' for quitting.  

4) PlacePiece() 
   Working: 
   - Locks the current tetromino into the grid when it can’t move down.  
   - Adds points to the score and updates the high score.  
   - Calls `ClearLines()` to remove completed lines.  

5) ClearLines() 
   Working:  
   - Checks for full horizontal lines.  
   - Shifts lines down when a line is cleared.  
   - Increases score by 100 per line and updates level.  

6) GameLoop()  
   Working: 
   - Runs the main game loop.  
   - Handles tetromino falling speed based on level and input.
 7) IsValidMove()

    Working:
   - Checks for game over when a new piece can’t spawn.  

7) Main()  
   It initializes the game, calls `ResetGame()` and `GameLoop()`, and offers a replay option.

## Data Structure Analysis

1) Array:  
   A 2D array in C++ is used to represent the game grid, storing the positions of locked tetrominoes.  
   Syntax: `char grid[HEIGHT][WIDTH]`  
   - ARRAY IS THE MOST PREFERABLE DATA STRUCTURE BECAUSE IT PROVIDES FAST ACCESS TO ANY POSITION IN THE GRID USING INDICES.  
   ✔ This matches the grid-based nature of Tetris.  
   ✔ Linked lists or queues would be less efficient for random access.  



2) Variables:  
   - `int currentX, currentY`: Stores the current tetromino’s position.  
   - `int score`: Keeps track of the player’s score.  
   - `int highscore`: Tracks the highest score achieved.  
   - `int level`: Increases with score to adjust game speed.



  
   

## Major Highlights

- The user can influence the falling speed with soft drops (‘^’) and hard drops (‘Space’).  
- Game can be restarted infinitely many times based on user’s choice.  
- This code is Windows-specific.  

## Future Improvements

- Implementing a high-score tracking system that persists across sessions.  
- Having a better UI and graphics to make the game look realistic.  
- Adding custom gameplay options for users’ favorite variety of Tetris modes.  
- Multiplayer can be introduced for a fascinating experience.  






