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
int speed = 200, nextBlock = -1, b;
char board[H][W] = {};
int score = 0;

class Block {
protected:
    int rotation;
    int x, y;
public:
    Block() : rotation(0), x(4), y(0) {}
    virtual ~Block() {}

    void setPos(int nx, int ny) { x = nx; y = ny; }
    int getX() { return x; }
    int getY() { return y; }

    virtual char getBlock(int r, int c) = 0;

    void updateOnBoard(bool erase = false) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (getBlock(i, j) != ' ') {
                    int ty = y + i;
                    int tx = x + j;
                    if (ty >= 0 && ty < H && tx >= 1 && tx < W - 1) {
                        board[ty][tx] = erase ? ' ' : BLOCK;
                    }
                }
            }
        }
    }

    int getMaxCol() {
        int maxCol = -1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (this->getBlock(i, j) != ' ') {
                    if (j > maxCol) maxCol = j;
                }
            }
        }
        return maxCol + 1;
    }

    bool canMove(int dx, int dy) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (getBlock(i, j) != ' ') {
                    int tx = x + j + dx;
                    int ty = y + i + dy;
                    if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                    if (ty >= 0 && board[ty][tx] == BLOCK) return false;
                }
            }
        }
        return true;
    }
};

Block* currentPiece = nullptr;

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

Block* spawnBlock(int type) {
    switch (type) {
        case 0: return new BlockI();
        case 1: return new BlockO();
        case 2: return new BlockT();
        case 3: return new BlockS();
        case 4: return new BlockZ();
        case 5: return new BlockJ();
        case 6: return new BlockL();
        default: return new BlockI();
    }
}

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
    gotoxy(0, 0); 
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (board[i][j] == BLOCK) {
                cout << board[i][j] << board[i][j];
            } else {
                cout << board[i][j] << board[i][j];
            }
        }
        cout << "\n";
    }
    cout << "Score: " << score << "        Next: ";
    char nextBlockName[] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
    if (nextBlock >= 0 && nextBlock < 7) {
        cout << nextBlockName[nextBlock];
    }
    cout << "\n";
    cout << "Controls: A/D=Move  S=Down  W=Rotate  Q=Quit\n";
    cout.flush();
}

void removeLine(){
    for (int i = H - 2; i >= 1; i--){
        bool full = true;
        for (int j = 1; j < W - 1; j++){
            if (board[i][j] != BLOCK) {
                full = false;
                break;
            }
        }
        if (full) {
            for (int k = i; k > 0; k--){
                for (int j = 1; j < W - 1; j++){
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 1; j < W - 1; j++){
                board[0][j] = ' ';
            }
            score += 100;
            i++;  
        }
    }
}


int getRandomX(Block*p) {
    if (!p) return 0;
    int blockMaxCol = p->getMaxCol();
    int maxX = W - 1 - blockMaxCol;
    if (maxX < 1) maxX = 1;
    return 1 + (rand() % maxX);
}

bool isGameOver() {
    for (int j = 1; j < W - 1; j++) {
        if (board[0][j] == BLOCK) {
            return true;
        }
    }
    return false;
}

int main(){
    system("chcp 437 >nul");
    
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    srand((unsigned)time(0));
    initBoard();
    nextBlock = rand() % 7;
    b = nextBlock;
    currentPiece = spawnBlock(b);
    currentPiece->setPos(getRandomX(currentPiece), 0);
    nextBlock = rand() % 7;
    int fallCounter = 0;
    bool gameOver = false;
    while (!gameOver){
        currentPiece->updateOnBoard(true);
        if (_kbhit()){
            unsigned char ch = _getch();
            char c = tolower(ch);
            if (c == 'a') {
                if (currentPiece->canMove(-1, 0)) {
                    currentPiece->setPos(currentPiece->getX() - 1, currentPiece->getY());
                }
            }
            else if (c == 'd') {
                if (currentPiece->canMove(1, 0)) {
                    currentPiece->setPos(currentPiece->getX() + 1, currentPiece->getY());
                }
            }
            else if (c == 's') {
                if (currentPiece->canMove(0, 1)) {
                    currentPiece->setPos(currentPiece->getX(), currentPiece->getY() + 1);
                }
            }
            else if (c == 'q') {
                gameOver = true;
                break;
            }
        }
        fallCounter++;
        if (fallCounter >= speed / 30) {
            if (currentPiece->canMove(0, 1)) {
                currentPiece->setPos(currentPiece->getX(), currentPiece->getY() + 1);
            }
            else {
                currentPiece->updateOnBoard();
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
                currentPiece = spawnBlock(b);
                currentPiece->setPos(getRandomX(currentPiece), 0);
                if (!currentPiece->canMove(0, 0)) {
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
        currentPiece->updateOnBoard();
        draw();
        Sleep(30);  
    }
    return 0;
}
