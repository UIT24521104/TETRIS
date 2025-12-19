#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <algorithm> 

#define H 20
#define W 15
#define VIEWPORT_HEIGHT 20 

using namespace std;

const char BLOCK = char(219);
int speed = 200;
char board[H][W] = {};
int score = 0;

void enableRawMode() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hIn, &mode);
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hIn, mode);
}

char blocks[7][4][4][4] = {
    
    {
        {{' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}},
        {{' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,BLOCK}, {' ',' ',' ',' '}, {' ',' ',' ',' '}},
        {{' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}},
        {{' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,BLOCK}, {' ',' ',' ',' '}, {' ',' ',' ',' '}}
    },

    {
        {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}}
    },
    {
        {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}},
        {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,' ',' '}}
    },
    {
        {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {BLOCK,BLOCK,' ',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',BLOCK,' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {BLOCK,BLOCK,' ',' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',BLOCK,' '}}
    },
    {
        {{' ',' ',' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',' ',BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}},
        {{' ',' ',' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',' ',BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}}

    },
     {
        {{' ',' ',' ',' '}, {BLOCK,' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}},
        {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',BLOCK,' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {BLOCK,BLOCK,' ',' '}}
    },
    {
        {{' ',' ',' ',' '}, {' ',' ',BLOCK,' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
        {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}},
        {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {BLOCK,' ',' ',' '}},
        {{' ',' ',' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}}

    }


};

int x = 4, y = 0, b = 1;
int rotation = 0;
int nextBlock = -1;

void gotoxy(int x, int y) {
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void initBoard(){
    for (int i = 0 ; i < H ; i++){
        for (int j = 0 ; j < W ; j++){
            if(i == H-1) {
                if(j==0) board[i][j] = char(200);
                else if(j==W-1) board[i][j] = char(188);
                else board[i][j] = char(205);
            }
            else if ((j == 0) || (j == W-1))
                board[i][j] = char(186);
            else
                board[i][j] = ' ';
        }
    }
}



void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (blocks[b][rotation][i][j] != ' '){
                int ty = y + i;
                int tx = x + j;
                if (ty >= 0 && ty < H && tx >= 1 && tx < W-1){
                    board[ty][tx] = ' ';
                }
            }
        }
    }
}

void block2Board(){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (blocks[b][rotation][i][j] != ' '){
                int ty = y + i;
                int tx = x + j;
                if (ty >= 0 && ty < H && tx >= 1 && tx < W-1){
                    board[ty][tx] = BLOCK;
                }
            }
        }
    }
}

void draw(){
    system("cls");
    for (int i = 0; i < VIEWPORT_HEIGHT && i < H; i++){
        for (int j = 0; j < W; j++){
            cout << board[i][j] << board[i][j];
        }
        cout << "\n";
    } 
    cout << "\n";
    cout << "Score: " << score << "        Next: ";
    char nextBlockName[] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
    if (nextBlock >= 0 && nextBlock < 7) {
        cout << nextBlockName[nextBlock];
    }
    cout << "\n";
    cout << "Controls: A/D=Move  S=Down  W=Rotate  Q=Quit\n";
    cout.flush();
}

bool canMove(int dx, int dy){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (blocks[b][rotation][i][j] != ' '){
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W-1 || ty >= H-1) return false;
                if (ty >= 0 && (board[ty][tx] == char(35) || board[ty][tx] == BLOCK)) return false;
            }
        }
    }
    return true;
}

bool canRotate(int newRotation) {
for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (blocks[b][newRotation][i][j] != ' '){
                int tx = x + j;
                int ty = y + i;
                if (tx < 1 || tx >= W-1 || ty >= H-1) return false;
                if (ty >= 0 && (board[ty][tx] == '#' || board[ty][tx] == BLOCK))
                    return false;
            }
        }
    }
    return true;
}

void rotateBlock() {
    int newRotation = (rotation + 1) % 4;
    if (canRotate(newRotation)) {
        rotation = newRotation;
    }
}

int getBlockMaxCol(int blockIndex) {
    int maxCol = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[blockIndex][0][i][j] != ' ') {
                maxCol = max(maxCol, j);
            }
        }
    }
    return maxCol + 1;
}

int getRandomX(int blockIndex) {
    int blockMaxCol = getBlockMaxCol(blockIndex);
    int maxX = W - 1 - blockMaxCol;
    if (maxX < 1) maxX = 1;
    return 1 + rand() % maxX;
}

bool isGameOver() {
    for (int j = 1; j < W - 1; j++) {
        if (board[0][j] == BLOCK) {
            return true;
        }
    }
    return false;
}
void removeLine() {
    for (int i = H - 2; i >= 1; i--) {
        bool full = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] != BLOCK) {
                full = false;
                break;
            }
        }
        if (full) {
            for (int k = i; k > 0; k--) {
                for (int j = 1; j < W - 1; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 1; j < W - 1; j++) {
                board[0][j] = ' ';
            }
            score += 100;
            i++;
        }
    }

}


int main(){
    enableRawMode();
    system("chcp 437 >nul");
    SetConsoleOutputCP(437);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    system("cls");
    srand((unsigned)time(0));
    initBoard();
    b = rand() % 7;
    nextBlock = rand() % 7;
    rotation = 0;
    x = getRandomX(b);
    y = 0;
    int fallcounter = 0;
    bool gameOver = false;
    while (!gameOver){
        boardDelBlock();
        if (_kbhit()){
            unsigned char ch = _getch();
            char c = tolower(ch);
            if (c == 'a') {
                if (canMove(-1, 0)) x--;
            }
            else if (c == 'd') {
                if (canMove(1, 0)) x++;
            }
            else if (c == 's') {
                if (canMove(0, 1)) y++;
            }
            else if (c == 'w') {
                rotateBlock();
            }
            else if (c == 'q') {
                gameOver = true;
                break;
            }
        }
        if (canMove(0, 1)) {
            y++;
        }
        else {
            block2Board();
                
                if (isGameOver()) {
                    draw();
                    cout << "\n========== GAME OVER ==========" << endl;
                    cout << "Final Score: " << score << endl;
                    cout << "================================" << endl;
                    cout << "Press any key to exit..." << endl;
                    _getch();
                    gameOver = true;
                    break;
                }
                b = nextBlock;
                nextBlock = rand() % 7;
                rotation = 0;
                x = getRandomX(b);
                y = 0;
                if (!canMove(0, 0)) {
                    draw();
                    cout << "\n========== GAME OVER ==========" << endl;
                    cout << "Final Score: " << score << endl;
                    cout << "================================" << endl;
                    cout << "Press any key to exit..." << endl;
                    _getch();
                    gameOver = true;
                    break;
                }
        }
        block2Board();
        draw();
        Sleep(speed);  
    }
    return 0;
}
