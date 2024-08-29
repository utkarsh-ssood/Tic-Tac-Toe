import sys

COMPUTER = 1
HUMAN = 2

SIDE = 3

COMPUTERMOVE = 'O'
HUMANMOVE = 'X'

def show_board(board):
    for i in range(SIDE):
        print("\t\t\t", end="")
        for j in range(SIDE):
            if j == SIDE - 1:
                print(board[i][j], end="")
            else:
                print(board[i][j], end=" | ")
        print()
        if i != SIDE - 1:
            print("\t\t\t--| --| --")
    print()

def show_instructions():
    print("\nChoose a number from 1 to 9 as below and play\n")
    count = 1
    for i in range(SIDE):
        print("\t\t\t", end="")
        for j in range(SIDE):
            if j == SIDE - 1:
                print(count, end="")
                count += 1
            else:
                print(count, end=" | ")
                count += 1
        print()
        if i != SIDE - 1:
            print("\t\t\t--| --| --")
    print()

def declare_winner(whose_turn, player_name):
    if whose_turn == COMPUTER:
        print("Computer has won the game.")
    else:
        print(f"{player_name} has won")

def row_fulfilled(board):
    for i in range(SIDE):
        if board[i][0] == board[i][1] == board[i][2] != '*':
            return True
    return False

def column_fulfilled(board):
    for i in range(SIDE):
        if board[0][i] == board[1][i] == board[2][i] != '*':
            return True
    return False

def diagonal_fulfilled(board):
    if board[0][0] == board[1][1] == board[2][2] != '*':
        return True
    if board[0][2] == board[1][1] == board[2][0] != '*':
        return True
    return False

def game_over(board):
    return row_fulfilled(board) or column_fulfilled(board) or diagonal_fulfilled(board)

def minimax(board, depth, is_human):
    if game_over(board):
        return -10 if is_human else 10

    if depth < 9:
        best_score = -sys.maxsize if is_human else sys.maxsize
        for i in range(SIDE):
            for j in range(SIDE):
                if board[i][j] == '*':
                    board[i][j] = COMPUTERMOVE if is_human else HUMANMOVE
                    score = minimax(board, depth + 1, not is_human)
                    board[i][j] = '*'
                    if is_human:
                        best_score = max(best_score, score)
                    else:
                        best_score = min(best_score, score)
        return best_score
    return 0

def best_move(board, move_index):
    best_score = -sys.maxsize
    best_move = -1
    for i in range(SIDE):
        for j in range(SIDE):
            if board[i][j] == '*':
                board[i][j] = COMPUTERMOVE
                score = minimax(board, move_index + 1, False)
                board[i][j] = '*'
                if score > best_score:
                    best_score = score
                    best_move = i * 3 + j
    return best_move

def play_tic_tac_toe(whose_turn, person_name):
    board = [['*' for _ in range(SIDE)] for _ in range(SIDE)]
    move_index = 0

    show_instructions()

    while not game_over(board) and move_index != SIDE * SIDE:
        if whose_turn == COMPUTER:
            n = best_move(board, move_index)
            x, y = divmod(n, SIDE)
            board[x][y] = COMPUTERMOVE
            print(f"COMPUTER has put {COMPUTERMOVE} in cell {n + 1}\n")
            show_board(board)
            move_index += 1
            whose_turn = HUMAN

        elif whose_turn == HUMAN:
            print("You can insert in the following positions:", end=" ")
            for i in range(SIDE):
                for j in range(SIDE):
                    if board[i][j] == '*':
                        print(i * 3 + j + 1, end=" ")
            print("\n\nEnter the position: ", end="")
            n = int(input()) - 1
            x, y = divmod(n, SIDE)

            if board[x][y] == '*' and 0 <= n < 9:
                board[x][y] = HUMANMOVE
                print(f"{person_name} has put a {HUMANMOVE} in cell {n + 1}\n")
                show_board(board)
                move_index += 1
                whose_turn = COMPUTER
            else:
                print("\nPosition is pre-occupied or invalid. Select another position.")

    if not game_over(board) and move_index == SIDE * SIDE:
        print("It's a draw")
    else:
        whose_turn = HUMAN if whose_turn == COMPUTER else COMPUTER
        declare_winner(whose_turn, person_name)

def main():
    print("\n----------------------------------------------------")
    print("\t\t\tTic-Tac-Toe")
    print("----------------------------------------------------\n")

    while True:
        player_name = input("Enter name of the player: ")
        choice = input("Do you want to start first? (y/n): ")
        if choice.lower() == 'n':
            play_tic_tac_toe(COMPUTER, player_name)
        elif choice.lower() == 'y':
            play_tic_tac_toe(HUMAN, player_name)
        else:
            print("Invalid choice")

        cont = input("Do you want to quit? (y/n): ")
        if cont.lower() == 'y':
            break

if __name__ == "__main__":
    main()
