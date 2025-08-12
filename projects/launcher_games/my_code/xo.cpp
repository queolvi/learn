#include <iostream>
#include <vector>


void printBoard(const std::vector<std::vector<char>>& board);
bool checkWin(const std::vector<std::vector<char>>& board, char player);
bool checkDraw(const std::vector<std::vector<char>>& board);
void game();

int main() {
    game();
    return 0;
}

void game() {
  std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));
    char players[] = {'X', 'O'};
    int currentPlayer = 0, moves = 0;
    const int maxMoves = 9;

    while (true) {
        printBoard(board);
        
        int row, col;
        std::cout << "Player " << (currentPlayer + 1) << " (" << players[currentPlayer] << "), enter row (1-3) and column (1-3): ";
        std::cin >> row >> col;
        if (row < 1 || row > 3 || col < 1 || col > 3) { std::cout << "Invalid input! Try again.\n"; continue; }
        if (board[row-1][col-1] != ' ') { std::cout << "This cell is already occupied! Try again.\n";  continue; }
        
        board[row-1][col-1] = players[currentPlayer];
        moves++;
        
        if (checkWin(board, players[currentPlayer])) {  printBoard(board);  std::cout << "Player " << (currentPlayer + 1) << " (" << players[currentPlayer] << ") wins!\n"; break;  }
        if (moves == maxMoves) {  printBoard(board);  std::cout << "It's a draw!\n"; break;  }

        currentPlayer = 1 - currentPlayer;
    }
}

void printBoard(const std::vector<std::vector<char>>& board) {
  std::cout << "\nCurrent board:\n"; std::cout << "  1 2 3\n";
    for (int i = 0; i < 3; ++i) {
      std::cout << i+1 << " ";
        for (int j = 0; j < 3; ++j) {
          std::cout << board[i][j];
            if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "  -+-+-\n";
    }
    std::cout << "\n";
}

bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    
    return false;
}

bool checkDraw(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}
