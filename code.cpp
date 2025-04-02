#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

char tetromino[7][4][5] = {
    {"....",".XX.",".XX.","...."},
    {".X..",".X..",".X..",".X.."},
    {".X..",".XX","..X.","...."},
    {"..X.",".XX.",".X..","...."},
    {".X..",".XX.",".X..","...."},
    {".X..",".X..",".XX.","...."},
    {"..X.","..X.",".XX.","...."}
};

char rotatedTetromino[4][4];
char grid[HEIGHT][WIDTH] = {};
int currentX = WIDTH / 2 - 2;
int currentY = 0;
int currentPiece = 0;
int currentRotation = 0;
int score = 0;
int highscore=0;
int level=1;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ClearConsole() {
    system("cls");
}

void RotatePiece(int rotation) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            switch (rotation % 4) {
                case 0: rotatedTetromino[i][j] = tetromino[currentPiece][i][j]; break;
                case 1: rotatedTetromino[i][j] = tetromino[currentPiece][3 - j][i]; break;
                case 2: rotatedTetromino[i][j] = tetromino[currentPiece][3 - i][3 - j]; break;
                case 3: rotatedTetromino[i][j] = tetromino[currentPiece][j][3 - i]; break;
            }
        }
    }
}

void ClearScreen() {
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

bool IsValidMove(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rotatedTetromino[i][j] == 'X') {
                int nx = x + j;
                int ny = y + i;
                if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT || grid[ny][nx] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void HardDrop() {
    while (IsValidMove(currentX, currentY + 1)) {
        currentY++;
    }
}

void ClearLines() {
    for (int y = 0; y < HEIGHT; y++) {
        bool fullLine = true;
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] == 0) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int ny = y; ny > 0; ny--) {
                for (int nx = 0; nx < WIDTH; nx++) {
                    grid[ny][nx] = grid[ny - 1][nx];
                }
            }
            for (int nx = 0; nx < WIDTH; nx++) {
                grid[0][nx] = 0;
            }
            score += 100;
            if (score >= highscore) {
                highscore = score;
            }
            level=score/200+1;
        }
    }
}

void DrawGrid() {
    ClearScreen();
    cout << BLUE << "+----------+" << RESET << endl;
    for (int y = 0; y < HEIGHT; y++) {
        cout << BLUE << "|" << RESET;
        for (int x = 0; x < WIDTH; x++) {
            bool isPiece = false;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (rotatedTetromino[i][j] == 'X' && currentY + i == y && currentX + j == x) {
                        isPiece = true;
                    }
                }
            }
            if (isPiece) {
                cout << RED << "X" << RESET;
            } else if (grid[y][x]) {
                cout << GREEN << "#" << RESET;
            } else {
                cout << " ";
            }
        }
        cout << BLUE << "|" << RESET << endl;
    }
    cout << BLUE << "+----------+" << RESET << endl;
    cout << "Score: " << YELLOW << score << RESET << "  High Score: " << CYAN << highscore << RESET << endl;
}

void PlacePiece() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rotatedTetromino[i][j] == 'X') {
                int nx = currentX + j;
                int ny = currentY + i;
                if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                    grid[ny][nx] = '#';
                }
            }
        }
    }
    score+=10;
    if (score >= highscore) {
        highscore = score;
    }
    level=score/100+1;
    ClearLines();
}

void HandleInput() {
    while (_kbhit()) {
        char key = _getch();
        if (key == 'q') {
            cout << "Game Exited! Final Score: " << score << endl;
            exit(0);
        }
        switch (key) {
            case 'a': case 75: if (IsValidMove(currentX - 1, currentY)) currentX--; break;
            case 'd': case 77: if (IsValidMove(currentX + 1, currentY)) currentX++; break;
            case 's': case 80: if (IsValidMove(currentX, currentY + 1)) currentY++; break;
            case 'w': case 72: 
                currentRotation = (currentRotation + 1) % 4;
                RotatePiece(currentRotation);
                break;
            case ' ': HardDrop(); break;
        }
    }
}

void GameLoop() {
    ClearConsole();
    
    while (true) {
        int normalSpeed = max(50,250-(level-1)*50);
        int softDropSpeed =normalSpeed/2;
        ClearScreen();
        DrawGrid();
        RotatePiece(currentRotation);
        HandleInput();
        int fallSpeed = (GetAsyncKeyState(VK_DOWN) & 0x8000) ? softDropSpeed : normalSpeed;
        if (!IsValidMove(currentX, currentY + 1)) {
            if (score >= highscore) {
                highscore = score;
            }
            PlacePiece();
            currentX = WIDTH / 2 - 2;
            currentY = 0;
            currentPiece = rand() % 7;
            currentRotation = 0;
            RotatePiece(currentRotation);
            if (!IsValidMove(currentX, currentY)) {
                
                cout << "Game Over! Final Score: " << score << " High Score: " << highscore << endl;
                break;
            }
        } else {
            currentY++;
        }
        Sleep(fallSpeed);
    }
}
void ResetGame() {
    memset(grid, 0, sizeof(grid));
    currentX = WIDTH / 2 - 2;
    currentY = 0;
    currentPiece = rand() % 7;
    currentRotation = 0;
    score = 0;
    level=1;
    RotatePiece(currentRotation); 
}
void ShowInstructions() {
    ClearConsole();
    cout << BLUE << "+---------------------------+" << RESET << endl;
    cout << GREEN << "        TETRIS GAME        " << RESET << endl;
    cout << BLUE << "+---------------------------+" << RESET << endl;
    cout << YELLOW << "Controls:" << RESET << endl;
    cout << "  " << GREEN << "[A] or Left Arrow  " << RESET << " - Move Left" << endl;
    cout << "  " << GREEN << "[D] or Right Arrow " << RESET << " - Move Right" << endl;
    cout << "  " << GREEN << "[S] or Down Arrow  " << RESET << " - Soft Drop" << endl;
    cout << "  " << GREEN << "[W] or Up Arrow    " << RESET << " - Rotate" << endl;
    cout << "  " << GREEN << "[Space]            " << RESET << " - Hard Drop" << endl;
    cout << "  " << GREEN << "[Q]                " << RESET << " - Quit" << endl;

    cout << BLUE << "+---------------------------+" << RESET << endl;
    cout << "Goal: " << endl;
    cout << "  - Stack and clear lines to score points!" << endl;
    cout << "  - The game speeds up as you level up." << endl;
    cout << "  - The game ends if blocks reach the top." << endl;
    cout << BLUE << "+---------------------------+" << RESET << endl;

    cout << CYAN << "Press any key to start..." << RESET << endl;
    _getch(); // Wait for user input before starting
}
int main() {
    srand((unsigned)time(0));
    HideCursor();
    ShowInstructions();
    while (true) {
        ResetGame(); // Reset the game state
        GameLoop();
        
        char choice;
        cout << "Do you want to play again (y/n)? ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }
    return 0;
}
