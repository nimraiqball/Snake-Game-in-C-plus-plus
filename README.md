# Snake-Game-in-C-plus-plus
Introduction:
This Snake game is implemented in C++ using the SFML library and Windows API for console manipulation. The game follows the classic Snake concept, where the player controls a snake and attempts to eat food while avoiding collision with the walls or the snake's own body. The game utilizes linked lists to represent the snake and includes functions for drawing the game border, handling user input, updating the snake's position, and managing game logic.

Game Overview:
The Snake game allows the player to control a snake on a bordered grid. The objective is to eat food and grow the snake's length. As the snake eats food, its length increases, making it more challenging to avoid collisions with the walls or the snake's own body. The game continues until the snake collides with a wall or itself. The player's score increases with each food item eaten, and the game ends when a certain score threshold is reached.

Functions Overview:

1. `void border(int** a, int size, bool& gameOver)`
   - This function is responsible for drawing the game border and managing the game logic.
   - It takes the game grid `a`, grid size `size`, and a boolean `gameOver` as parameters.
   - The function utilizes the SFML library and Windows API to draw the game elements on the console.
   - It manages the snake's movement, collision detection, food generation, and score tracking.
   - The game loop is controlled by the `gameOver` flag.

2. `class Node` and `class List`
   - These classes implement a linked list data structure to represent the snake.
   - The `Node` class represents a node in the linked list, with row and column coordinates.
   - The `List` class manages the snake by providing operations such as inserting and deleting nodes.
   - Functions like `insert_begin`, `insert_end`, `delete_begin`, and `delete_end` are used to manipulate the snake's body.

3. `void setCursorPosition(int x, int y)` and `void hideCursor()`
   - These functions utilize the Windows API to manipulate the console's cursor position and visibility.
   - `setCursorPosition` sets the cursor position to the specified coordinates (x, y) on the console.
   - `hideCursor` hides the console cursor to improve the game's visual appearance.

4. `int main()`
   - This function serves as the entry point of the program and contains the main game loop.
   - It utilizes the SFML library to create a window for displaying graphics.
   - The function sets up the game environment, including loading textures, defining sprites, and configuring fonts.
   - It also handles user input events and displays game instructions and information.
   - The game grid is dynamically allocated, and the `border` function is called to start the game.

Conclusion:
The Snake game implemented in C++ using the SFML library and Windows API provides an entertaining gaming experience. The code effectively utilizes linked lists, console manipulation, and graphics to try to create a functional game environment. The provided functions and classes provide key concepts such as linked list manipulation, console control, and game logic. 

