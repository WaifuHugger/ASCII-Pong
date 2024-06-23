#include <iostream>
#include <conio.h>   // key system
#include <windows.h> // windows console clear

using namespace std;

// constants for the game dimensions
const int width = 40;
const int height = 20;

// game state variables
int ballX, ballY;        // ball position
int player1X, player1Y;  // player 1 paddle
int player2X, player2Y;  // player 2 paddle
int score1, score2;      // player scores
int ballDirX, ballDirY;  // ball direction hit
bool gameOver;           // game over

// intial game state
void Setup() {
    gameOver = false;
    ballX = width / 2;
    ballY = height / 2;
    player1X = 1;
    player1Y = height / 2 - 2;
    player2X = width - 2;
    player2Y = height / 2 - 2;
    score1 = 0;
    score2 = 0;
    ballDirX = -1;
    ballDirY = -1;
}

// Function to draw the game state on the console
void Draw() {
    system("cls"); // clear windows console

    
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // play area
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";

            // Ball position
            if (i == ballY && j == ballX)
                cout << "O";
            // player paddles
            else if (i >= player1Y && i < player1Y + 4 && j == player1X)
                cout << "|";
            
            else if (i >= player2Y && i < player2Y + 4 && j == player2X)
                cout << "|";
            // empty space
            else
                cout << " ";

            if (j == width - 1) cout << "#"; 
        }
        cout << endl;
    }

    
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // player scores
    cout << "Score1: " << score1 << " Score2: " << score2 << endl;
}

// user inputs
void Input() {
    if (_kbhit()) { // check key press
        switch (_getch()) {
            // player 1 controls
        case 'w':
            if (player1Y > 0) player1Y--;
            break;
        case 's':
            if (player1Y < height - 4) player1Y++;
            break;
            // player 2 controls
        case 'i':
            if (player2Y > 0) player2Y--;
            break;
        case 'k':
            if (player2Y < height - 4) player2Y++;
            break;
            // quit game
        case 'q':
            gameOver = true;
            break;
        }
    }
}

// update game logic
void Logic() {
    // update ball position
    ballX += ballDirX;
    ballY += ballDirY;

    // ball collision with walls
    if (ballY <= 0 || ballY >= height - 1) ballDirY = -ballDirY;

    // ball collision with player
    if (ballX == player1X + 1 && ballY >= player1Y && ballY < player1Y + 4) ballDirX = -ballDirX;
    if (ballX == player2X - 1 && ballY >= player2Y && ballY < player2Y + 4) ballDirX = -ballDirX;

    // ball goes out of bounds to the left
    if (ballX <= 0) {
        score2++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -ballDirX;
    }

    // ball goes out of bounds to the right
    if (ballX >= width - 1) {
        score1++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -ballDirX;
    }
}

// main function
int main() {
    Setup(); // initializion
    while (!gameOver) {
        Draw();  
        Input(); 
        Logic(); 
    }
}
