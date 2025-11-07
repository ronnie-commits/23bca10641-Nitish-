#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Cell {
    bool mine = false;
    bool revealed = false;
    int nearby = 0;
};

class Minesweeper {
private:
    int rows, cols, mines;
    vector<vector<Cell>> board;

public:
    Minesweeper(int r, int c, int m) : rows(r), cols(c), mines(m) {
        board.resize(rows, vector<Cell>(cols));
        placeMines();
        calculateNumbers();
    }

    void placeMines() {
        srand(time(0));
        int placed = 0;
        while (placed < mines) {
            int r = rand() % rows;
            int c = rand() % cols;
            if (!board[r][c].mine) {
                board[r][c].mine = true;
                placed++;
            }
        }
    }

    void calculateNumbers() {
        int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {

                if (board[r][c].mine) continue;

                int count = 0;
                for (int i = 0; i < 8; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        if (board[nr][nc].mine) count++;
                    }
                }

                board[r][c].nearby = count;
            }
        }
    }

    void printBoard() {
        cout << "\n   ";
        for (int c = 0; c < cols; c++) cout << c << " ";
        cout << "\n";

        for (int r = 0; r < rows; r++) {
            cout << r << " | ";
            for (int c = 0; c < cols; c++) {
                if (!board[r][c].revealed)
                    cout << "# ";
                else if (board[r][c].mine)
                    cout << "* ";
                else
                    cout << board[r][c].nearby << " ";
            }
            cout << "\n";
        }
    }

    bool reveal(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
        if (board[r][c].revealed) return true;

        board[r][c].revealed = true;

        if (board[r][c].mine)
            return false;

        if (board[r][c].nearby == 0) {
            int dr[8] = {-1,-1,-1,0,0,1,1,1};
            int dc[8] = {-1,0,1,-1,1,-1,0,1};
            for (int i = 0; i < 8; i++) {
                reveal(r + dr[i], c + dc[i]);
            }
        }
        return true;
    }

    void start() {
        while (true) {
            printBoard();
            int r, c;
            cout << "\nEnter row and column to reveal (r c): ";
            cin >> r >> c;

            if (!reveal(r, c)) {
                printBoard();
                cout << "\n💥 Game Over! You hit a mine.\n";
                break;
            }
        }
    }
};

int main() {
    int r = 8, c = 8, m = 10;
    Minesweeper game(r, c, m);
    game.start();
    return 0;
}