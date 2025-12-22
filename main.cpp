#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <string>

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

class Block {
protected:
    int rotation;
public:
    Block() : rotation(0) {}
    virtual ~Block() {}
    virtual char getBlock(int r, int c) = 0;
};

// --- KHỐI I ---
class BlockI : public Block {
private:
    static char data[4][4][4]; 
public:
    BlockI() : Block() {}
    char getBlock(int r, int c) override { return data[rotation][r][c]; }
};

char BlockI::data[4][4][4] = {
    {{' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}},
    {{' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,BLOCK}, {' ',' ',' ',' '}, {' ',' ',' ',' '}},
    {{' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}},
    {{' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,BLOCK}, {' ',' ',' ',' '}, {' ',' ',' ',' '}}
};

// --- KHỐI O ---
class BlockO : public Block {
private:
    static char data[4][4][4]; 
public:
    BlockO() : Block() {}
    char getBlock(int r, int c) override { return data[rotation][r][c]; }
};

char BlockO::data[4][4][4] = {
    {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}}
};

// --- KHỐI T ---
class BlockT : public Block {
private:
    static char data[4][4][4]; 
public:
    BlockT() : Block() {}
    char getBlock(int r, int c) override { return data[rotation][r][c]; }
};

char BlockT::data[4][4][4] = {
    {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}},
    {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,' ',' '}}
};

// --- KHỐI S ---
class BlockS : public Block {
private:
    static char data[4][4][4]; 
public:
    BlockS() : Block() {}
    char getBlock(int r, int c) override { return data[rotation][r][c]; }
};

char BlockS::data[4][4][4] = {
    {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {BLOCK,BLOCK,' ',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',BLOCK,' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {BLOCK,BLOCK,' ',' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',BLOCK,' '}}
};

// --- KHỐI Z ---
class BlockZ : public Block {
private:
    static char data[4][4][4]; 
public:
    BlockZ() : Block() {}
    char getBlock(int r, int c) override { return data[rotation][r][c]; }
};

char BlockZ::data[4][4][4] = {
    {{' ',' ',' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',' ',BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}},
    {{' ',' ',' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',' ',BLOCK,' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}}
};

// --- KHỐI J ---
class BlockJ : public Block {
private:
    static char data[4][4][4]; 
public:
    BlockJ() : Block() {}
    char getBlock(int r, int c) override { return data[rotation][r][c]; }
};

char BlockJ::data[4][4][4] = {
    {{' ',' ',' ',' '}, {BLOCK,' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,BLOCK,' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}},
    {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',BLOCK,' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {BLOCK,BLOCK,' ',' '}}
};

// --- KHỐI L ---
class BlockL : public Block {
private:
    static char data[4][4][4]; 
public:
    BlockL() : Block() {}
    char getBlock(int r, int c) override { return data[rotation][r][c]; }
};

char BlockL::data[4][4][4] = {
    {{' ',' ',' ',' '}, {' ',' ',BLOCK,' '}, {BLOCK,BLOCK,BLOCK,' '}, {' ',' ',' ',' '}},
    {{' ',' ',' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,BLOCK,' '}},
    {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {BLOCK,BLOCK,BLOCK,' '}, {BLOCK,' ',' ',' '}},
    {{' ',' ',' ',' '}, {BLOCK,BLOCK,' ',' '}, {' ',BLOCK,' ',' '}, {' ',BLOCK,' ',' '}}
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
    int fallCounter = 0;
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
        fallCounter++;
        if (fallCounter >= speed / 30) {
            if (canMove(0, 1)) {
                y++;
            }
            else {
                block2Board();
                removeLine();
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
                fallCounter = 0;
            }
            fallCounter = 0;
        }
        block2Board();
        draw();
        Sleep(30);  
    }
    return 0;
}
