import chess

def evaluate_board(board: chess.Board) -> int:
    if board.is_checkmate():
        return 9999 if board.turn == chess.BLACK else -9999
    if board.is_stalemate() or board.is_insufficient_material():
        return 0

    piece_values = {
        chess.PAWN: 1,
        chess.KNIGHT: 3,
        chess.BISHOP: 3,
        chess.ROOK: 5,
        chess.QUEEN: 9,
        chess.KING: 0
    }

    score = 0
    for piece_type in piece_values:
        score += len(board.pieces(piece_type, chess.WHITE)) * piece_values[piece_type]
        score -= len(board.pieces(piece_type, chess.BLACK)) * piece_values[piece_type]

    return score


def minimax(board: chess.Board, depth: int, alpha: int, beta: int, maximizing: bool) -> int:
    if depth == 0 or board.is_game_over():
        return evaluate_board(board)

    if maximizing:
        max_eval = -99999
        for move in board.legal_moves:
            board.push(move)
            eval = minimax(board, depth - 1, alpha, beta, False)
            board.pop()
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:  
                break
        return max_eval
    else:
        min_eval = 99999
        for move in board.legal_moves:
            board.push(move)
            eval = minimax(board, depth - 1, alpha, beta, True)
            board.pop()
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:  
                break
        return min_eval


def find_best_move(board: chess.Board, depth: int) -> chess.Move:
    best_move = None
    best_value = -99999

    for move in board.legal_moves:
        board.push(move)
        board_value = minimax(board, depth - 1, -100000, 100000, False)
        board.pop()
        if board_value > best_value:
            best_value = board_value
            best_move = move

    return best_move


def play_game():
    board = chess.Board()
    depth = 6  
    print("Welcome to Chess AI (Minimax + Alpha-Beta Pruning)")
    print(f"Search depth fixed at {depth} moves.\n")
    print(board)

    choice = input("Do you want to play as White and move first? (y/n): ").strip().lower()
    user_is_white = (choice == "y")

    while not board.is_game_over():
        if (board.turn == chess.WHITE and user_is_white) or (board.turn == chess.BLACK and not user_is_white):
            move = None
            while move not in board.legal_moves:
                user_input = input("Your move (UCI format, e.g. e2e4): ")
                try:
                    move = chess.Move.from_uci(user_input)
                except:
                    print("Invalid format. Try again.")
                    continue
                if move not in board.legal_moves:
                    print("Illegal move. Try again.")
            board.push(move)
            print("\nBoard after your move:")
            print(board)
        else:
            ai_move = find_best_move(board, depth)
            board.push(ai_move)
            print(f"\nAI plays: {ai_move}")
            print(board)

    print("\nGame Over:", board.result())


if __name__ == "__main__":
    play_game()