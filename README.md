Chess AI with Minimax + Alpha-Beta Pruning (Python)

Problem Statement
This project implements a **Chess AI** using the **Minimax algorithm with Alpha-Beta Pruning.  
- The AI evaluates chess positions using a material-based evaluation function.  
- Alpha-Beta pruning significantly reduces the number of explored moves, making the AI faster and stronger compared to plain Minimax.  
- The user can play as **White** or **Black**, while the AI plays the opposite side.  

 Approach
1. Board Representation  
   - Uses the [`python-chess`](https://pypi.org/project/chess/) library for move legality, board representation, and rules.

2. Evaluation Function 
   - Assigns material values to pieces:  
     - Pawn = 1  
     - Knight = 3  
     - Bishop = 3  
     - Rook = 5  
     - Queen = 9  
     - King = 0 (not scored).  
   - Additional cases:  
     - Checkmate → ±9999  
     - Stalemate or insufficient material → 0  

3. Minimax with Alpha-Beta Pruning 
   - Standard Minimax recursively explores moves.  
   - **Alpha (best guaranteed for maximizer)** and **Beta (best guaranteed for minimizer)** prune branches that cannot influence the final decision.  
   - This reduces computation without affecting correctness.

4. Best Move Selection  
   - Evaluates all legal moves at the current position.  
   - Chooses the move with the highest evaluation.  

5. Game Loop  
   - Player enters moves in **UCI format** (e.g., `e2e4`).  
   - AI responds with its calculated move.  
   - Continues until checkmate, stalemate, or draw.  

Implementation Details
- evaluate_board(board)`** → Evaluates the board based on material count and endgame states.  
- minimax(board, depth, alpha, beta, maximizing)`** → Recursive Minimax search with Alpha-Beta pruning.  
- find_best_move(board, depth)`** → Selects the AI’s best move at given depth.  
- play_game() → Runs the interactive loop between human and AI.  


Time Complexity
- Plain Minimax: O(b^d)  
- With Alpha-Beta Pruning: O(b^(d/2)) (best case)  
  - b = branching factor (~35 legal moves in chess).  
  - d = search depth (set to 6).  

Space Complexity
- O(d) recursion depth (stack space).  

 Use Cases
- Learn adversarial search algorithms in AI.  
- Understand benefits of Alpha-Beta pruning.  
- Educational tool for **game-playing AI**.  
- Can serve as the foundation for more advanced chess engines.  

 Limitations
- Shallow search depth (6)** → Cannot plan long strategies.  
- Simple evaluation function** → Ignores positional play, king safety, pawn structure, etc.  
- No move ordering or transposition table** → Further optimizations possible.  
- Not competitive with real chess engines** like Stockfish.


# Tic-Tac-Toe AI with Minimax + Alpha-Beta Pruning (C++)

## Problem Statement
This project implements a **Tic-Tac-Toe AI** using the **Minimax algorithm with Alpha-Beta Pruning**.  
- The game allows a human to play against the computer.  
- The AI uses optimal decision-making and will never lose.  
- Alpha-Beta pruning ensures faster computation compared to plain Minimax.  

---

## Approach
1. **Board Representation**  
   - The board is stored as a `vector<char>` of size 9.  
   - Indices 0–8 represent the 3×3 grid.  

2. **Evaluation Function**  
   - Returns **+10** if AI wins.  
   - Returns **-10** if human wins.  
   - Returns **0** for draw or no winner yet.  

3. **Minimax Algorithm with Alpha-Beta Pruning**  
   - AI (maximizer) tries to maximize score.  
   - Human (minimizer) tries to minimize score.  
   - **Alpha** = best score AI can guarantee.  
   - **Beta** = best score human can guarantee.  
   - Branches that cannot affect final outcome are pruned.  

4. **Game Loop**  
   - Human can choose to play first or second.  
   - Player inputs moves as numbers (1–9).  
   - AI chooses optimal moves using Minimax + pruning.  
   - The game continues until **win/draw**.  

---

## Implementation Details
- **`checkWinner(board)`** → Checks for a winning line.  
- **`isFull(board)`** → Checks if the board is full (draw).  
- **`minimax(board, maximizing, ai, human, alpha, beta)`** → Recursive Minimax with pruning.  
- **`bestMove(board, ai, human)`** → Finds the optimal move for AI.  
- **`printBoard(board)`** → Displays board in a human-readable format.  
- **`main()`** → Handles user interaction, AI moves, and game loop.  

---


## Time Complexity
- **Without pruning**: O(b^d)  
- **With Alpha-Beta pruning**: O(b^(d/2)) in best case.  
  - b = branching factor (~9 at start).  
  - d = depth of search (≤ 9 moves in Tic-Tac-Toe).  
- In practice, AI always evaluates quickly because Tic-Tac-Toe is small.  

## Space Complexity
- **O(d)** recursion depth.  
- Max depth = 9 (full board).  

---

## Use Cases
- Educational tool to demonstrate Minimax and Alpha-Beta pruning.  
- Understand game-tree search in AI.  
- Show why Tic-Tac-Toe is a **solved game**.  
- Extendable to larger games (e.g., Connect-4, Chess).  

---

 Limitations
- Works only for 3×3 Tic-Tac-Toe.  
- Not scalable to large games without further optimizations.  
- Evaluation is simple (win/lose/draw only).  


