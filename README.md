# Chess Game in C++


## Overview
This is a fully functional chess game implemented in C++ using advanced design patterns and object-oriented programming principles. The game supports all standard chess rules, including special moves like en passant, castling, and pawn promotion. It also features AI opponents with 4 varying difficulty levels and allows for customization of the board setup.


## Features
- **Standard Chess Rules**: Includes all chess rules, such as check, checkmate, stalemate, en passant, castling, and pawn promotion.
- **AI Opponents**: Play against AI with different difficulty levels, where the AI can move randomly (level 1) or strategically based on piece values (levels 2-4).
- **Customizable Gameplay**: Set up your own board configurations, play against another human, or watch two AI players compete.
- **Undo Feature**: Players can undo their last move, with full move history tracking.
- **X11 UI**: To visualize the chess board.


## Design Patterns
- **Model-View-Controller (MVC)**: Separates game logic from UI rendering.
- **Observer Pattern**: Ensures UI updates whenever the game state changes.
- **Continuously Recurring Template Pattern (CRTP)**: Enhances scalability by allowing new chess pieces to be added without modifying existing code.
- **Template Method Pattern**: Used to streamline the move-making process, reducing code duplication across piece types.
- **Polymorphic Cloning** (extension of CRTP): Safely clones chess pieces using smart pointers to ensure no shared state between copies.


## Gallery
#### Regular move:
<img width="1046" alt="move" src="https://github.com/user-attachments/assets/32bca5a0-9233-4670-ae19-bdd765d94d7a">

#### Setup mode: 
<img width="1046" alt="move" src="https://github.com/user-attachments/assets/3d2a49be-803d-42ae-823e-104c6e9c5634">

#### Checkmate:
<img width="1046" alt="move" src="https://github.com/user-attachments/assets/0239a993-72d7-4608-9cf6-cb9da14f0a2e">


## Commands
- `game white-player black-player` starts a new game. The parameters white-player and black-player can be either `human` or `computer[1-4]` (e.g. `computer2`).
- `resign` concedes the game to your opponent.
- `move e2 e4` moves the piece on e2 to e4. Pawn promotion should additionally specify which piece to promote to, like `move e7 e8 Q` to promote white's e pawn to a queen.
- `undo` undos the previous move,
- `setup` enters setup mode
    - `+ K e1` places the piece K (i.e., the white king in this case) on the square e1,
    - `- e1` removes the piece from the square e1,
    - `= colour` makes it colour’s turn to go next.
    - `done` leaves setup mode. You can not leave setup mode until the following conditions are fulfilled:
         - There must be exactly one white king and exactly one black king.
         - There must be no pawns on the back ranks (first and last rows of the board).
         - Neither player can be in check.


## Build Instructions
### Prerequisites
- C++14 or higher
- GCC that supports the above C++ version
- [Make](https://www.gnu.org/software/make/)

### Steps
1. Clone the repository:
    ```bash
    git clone https://github.com/Tidyrice/chess
    cd chess-game
    ```
2. Compile the project using `make`:
    ```bash
    make
    ```

### Running the Game
After compiling, you can run the game by executing:
```bash
./chess
```
