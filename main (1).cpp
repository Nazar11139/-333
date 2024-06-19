#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;


const int MIN_BOARD_SIZE = 3;
const int MAX_BOARD_SIZE = 10;
const int MIN_TURN_TIME = 5;
const int MAX_TURN_TIME = 20;
const int DEFAULT_TURN_TIME = 7;


class Board {
private:
    int size; 
    vector<vector<char>> grid; 

public:
    Board(int s) : size(s) {
        grid.resize(size, vector<char>(size, ' '));
    }

    void display() {
        cout << "  ";
        for (int i = 0; i < size; ++i)
            cout << i << " ";
        cout << endl;

        for (int i = 0; i < size; ++i) {
            cout << i << " ";
            for (int j = 0; j < size; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isValidMove(int x, int y) {
        return (x >= 0 && x < size && y >= 0 && y < size && grid[x][y] == ' ');
    }

    void makeMove(int x, int y, char symbol) {
        grid[x][y] = symbol;
    }

    bool isFull() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }
};


bool waitForMove(int maxWaitTime) {
    cout << "Waiting for player move..." << endl;
    auto start = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds;

    while (true) {
        auto current = chrono::steady_clock::now();
        elapsed_seconds = current - start;
        if (elapsed_seconds.count() >= maxWaitTime)
            break;

        
        this_thread::sleep_for(chrono::milliseconds(500)); // Перевірка кожні 0.5 секунди
    }

    if (elapsed_seconds.count() >= maxWaitTime) {
        cout << "Time's up! Automatically passing the turn." << endl;
        return false; 
    } else {
        return true; 
    }
}

int main() {
    int boardSize, turnTime;
    

    cout << "Enter board size (between " << MIN_BOARD_SIZE << " and " << MAX_BOARD_SIZE << "): ";
    cin >> boardSize;
    if (boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE) {
        cerr << "Invalid board size!" << endl;
        return 1;
    }
    

    cout << "Enter turn time (between " << MIN_TURN_TIME << " and " << MAX_TURN_TIME << " seconds): ";
    cin >> turnTime;
    if (turnTime < MIN_TURN_TIME || turnTime > MAX_TURN_TIME) {
        cerr << "Invalid turn time!" << endl;
        return 1;
    }

    Board game(boardSize);
    bool isPlayer1Turn = true;
    
    while (!game.isFull()) {
        game.display();
        
        if (isPlayer1Turn)
            cout << "Player 1's turn:" << endl;
        else
            cout << "Player 2's turn:" << endl;
        
   
        bool moveMade = waitForMove(turnTime);

        if (!moveMade) {
           
            isPlayer1Turn = !isPlayer1Turn;
            continue;
        }

        
        int x, y;
        cout << "Enter coordinates (x y): ";
        cin >> x >> y;

        if (game.isValidMove(x, y)) {
            if (isPlayer1Turn)
                game.makeMove(x, y, 'X');
            else
                game.makeMove(x, y, 'O');
        } else {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        isPlayer1Turn = !isPlayer1Turn;
    }

    cout << "Game Over!" << endl;
    game.display();

    return 0;
}



