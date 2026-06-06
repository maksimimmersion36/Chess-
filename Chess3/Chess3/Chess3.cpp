#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;
char tempBoard[8][8]{};
bool isCheck(char targetPieceKing, char board[8][8]);
//отрисовка начальной доски
void copyBoard(char mainBoard[8][8], char boardForCopy[8][8]) {
    for (int i = 0; i < 8;i++) {
        for (int y = 0; y < 8;y++) {
            boardForCopy[i][y] = mainBoard[i][y];
        }
    }
}



void drawingBoard(char board[8][8]) {
    // отрисовка всех клеток
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = '.';
        }
    }

    //белые пешки
    for (int whiteCol = 0; whiteCol < 8; whiteCol++) {
        board[6][whiteCol] = 'p';
    }

    //черные пешки
    for (int blackCol = 0; blackCol < 8; blackCol++) {
        board[1][blackCol] = 'P';
    }

    //черные
    board[0][0] = 'R'; //ладья
    board[0][1] = 'N'; //конь
    board[0][2] = 'B'; //слон
    board[0][3] = 'Q'; //ферзь
    board[0][4] = 'K'; //king
    board[0][5] = 'B'; //слон
    board[0][6] = 'N'; //конь
    board[0][7] = 'R'; //ладья

    //белые
    board[7][0] = 'r';
    board[7][1] = 'n';
    board[7][2] = 'b';
    board[7][3] = 'q';
    board[7][4] = 'k';
    board[7][5] = 'b';
    board[7][6] = 'n';
    board[7][7] = 'r';
}
// прорисовка доски
void printBoard(char board[8][8]) {
    cout << "\n\t\t       a   b   c   d   e   f   g   h\n";
    for (int row = 0; row < 8; row++) {
        cout << "\t\t   " << 8 - row << " ";
        for (int col = 0; col < 8; col++) {
            cout << "| " << board[row][col] << " ";
        }
        cout << "|\n";
        if (row < 7) {
            cout << "\t\t     " << "|---+---+---+---+---+---+---+---|\n";
        }
    }
    cout << "\n";
}

//проверка возможности хода ладьи
//bool canRookMove(int fromRow, int fromCol, int toRow, int toCol) {
//    if (fromRow == toRow && fromCol != toCol) {
//        return 1;
//    }
//    if (fromRow != toRow && fromCol == toCol) {
//        return 1;
//    }
//    return 0;
//}

bool canRookGo(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    if (!(fromRow == toRow && fromCol != toCol) && !(fromRow != toRow && fromCol == toCol)) return 0;

    if (fromRow < toRow) {
        for (int startY = fromRow + 1; startY < toRow;startY++) {
            if (board[startY][fromCol] != '.') return 0;
        }
        return 1;
    }
    else if (fromRow > toRow) {
        for (int startY = fromRow - 1; startY > toRow;startY--) {
            if (board[startY][fromCol] != '.') return 0;
        }
        return 1;
    }

    if (fromCol < toCol) {
        for (int startX = fromCol + 1;startX < toCol;startX++) {
            if (board[fromRow][startX] != '.') return 0;
        }
        return 1;
    }
    else if (fromCol > toCol) {
        for (int startX = fromCol - 1;startX > toCol;startX--) {
            if (board[fromRow][startX] != '.') return 0;
        }
        return 1; 
    }
    return 0;
}
bool canBishopGo(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) { 
    // !!!!!
    if (!(abs(toRow - fromRow) == abs(toCol - fromCol))) return 0;
    
    //вверх влево
        if (fromRow > toRow && fromCol > toCol) {
            for (int startRow = fromRow-1, startCol = fromCol-1; startRow> toRow;startRow--, startCol--) {
                if (board[startRow][startCol] != '.') return 0;
            }
            return 1;
        }
    //вниз влево 
    else if(fromRow < toRow && fromCol > toCol){
        for (int startRow = fromRow +1, startCol = fromCol-1;startRow<toRow;startCol--, startRow++) {
            if (board[startRow][startCol] != '.') return 0;
        }
        return 1;
    }
    //вверх вправо
    else if(fromRow > toRow && fromCol < toCol){
        for (int startRow = fromRow - 1, startCol = fromCol + 1;startRow > toRow;startRow--, startCol++) {
            if (board[startRow][startCol] != '.') return 0;
        }
        return 1;
    }
    //вниз вправо
    else if(fromRow < toRow && fromCol < toCol){
        for (int startRow = fromRow + 1, startCol = fromCol + 1;toRow > startRow;startRow++, startCol++) {
            if (board[startRow][startCol] != '.') return 0;
        }
        return 1;
    }

    
    return 0;

};

bool canKnightGo(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) { 
    
    int deltaRow = abs(fromRow - toRow); 
    int deltaCol = abs(fromCol - toCol); 

    if ((deltaRow == 1 && deltaCol == 2) || (deltaRow == 2 && deltaCol == 1)) return 1;
    return 0;
};


bool canQueenGo(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    return canRookGo(board, fromRow, fromCol, toRow, toCol) || canBishopGo(board, fromRow, fromCol, toRow, toCol); 
};


bool canKingGo(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) { 

    if (fromRow == toRow && fromCol == toCol) return 0;

    if ((abs(fromRow-toRow) == 1 || abs(fromRow - toRow) == 0) && (abs(fromCol - toCol) == 1 || abs(fromCol - toCol) == 0)) return 1;

    return 0;

};


bool canCastle(char chessBoard[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhite, int kingMoved, int rookMoved) {

    if (chessBoard[fromRow][toCol] != '.') return 0;

    // проверка на первый ход. Ту ров излишняя переменная функции, но раз работает нету смысла ее удалять))))
    if (kingMoved >= 1 || rookMoved >= 1)return 0;

    if (fromRow == 0) {
        if (fromCol > toCol) {
            if (chessBoard[0][0] == 'R');
            else return 0;
        }
        if (fromCol < toCol) {
            if (chessBoard[0][7] == 'R');
            else return 0;
        }
    }
    else if (fromRow == 7) {
        if (fromCol > toCol) {
            if (chessBoard[7][0] == 'r');
            else return 0;
        }
        if (fromCol < toCol) {
            if (chessBoard[7][7] == 'r');
            else return 0;
        }
    }
    // проверка на длинную рокировку, берется вся часть доски между королем и ладьей
    if (fromCol > toCol) {
        for (int col = fromCol - 1; col > 0; col--) {
            if (chessBoard[fromRow][col] != '.')return 0;
       
        }
    }
    // проверка на короткую рокировку, берется вся часть доски между королем и ладьей
    if (fromCol < toCol) {
        for (int col = fromCol +1 ; col < 7; col++) {
            if (chessBoard[fromRow][col] != '.')return 0;
        }
    }



    return 1;
}



bool canPawnGo(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) { 

    //фигура, которой совершается ход
    char targetPiece = board[fromRow][fromCol];
    int step;
    if (targetPiece == 'P') {
        step = 1; // проверка обычного хода через цвет фигуры+доступный шаг
        if (fromRow > toRow) return 0; // проверка хода назад
    }
    else {
        step = -1; // проверка обычного хода через цвет фигуры+доступный шаг
        if (fromRow < toRow) return 0; // проверка хода назад
    }

    

    // проверка на двойной первый ход
    if (((fromRow == 1 && toRow == 3) && fromCol == toCol) || ((fromRow == 6 && toRow == 4)) && fromCol == toCol) {
        if (fromRow == 1 && toRow == 3) {
            for (int startRow = fromRow + 1;startRow <= toRow; startRow++) {
                if (board[startRow][fromCol] != '.')return 0;
            }
            return 1;
        }

        if (fromRow == 6 && toRow == 4) {
            for (int startRow = fromRow -1;startRow >= toRow; startRow--) {
                if (board[startRow][fromCol] != '.')return 0;
            }
            return 1;
        }


    }
    //проверка на взятие со стороны черных
    if (targetPiece == 'P' && fromRow - toRow == -1 && (fromCol - toCol == 1 || fromCol - toCol == -1) && board[toRow][toCol] != '.') return 1;

    //проверка на взятие со стороны белых
    if (targetPiece == 'p' && fromRow - toRow == 1 && (fromCol - toCol == 1 || fromCol - toCol == -1) && board[toRow][toCol] != '.') return 1;

    // проверка хода на ту же позицию или на сдвиг в сторону
    if (fromRow == toRow || fromCol != toCol) return 0;

    //ход фигуры
    if (toRow == fromRow + step) {
        if (board[toRow][toCol] != '.') return 0;
        return 1;
    }

    return 0;
}

bool isCheck(char targetPieceKing, char board[8][8]) {

    int kingRow, kingCol;
    bool colorKing;

    //фалс - черный, тру - белый
    if (targetPieceKing == 'K') colorKing = false;
    else colorKing = true;

    for (int i = 0; i < 8;i++) {
        for (int y = 0; y < 8;y++) {
            if (board[i][y] == targetPieceKing) {
                kingRow = i;
                kingCol = y;
            }
        }
    }

    for (int i = 0;i < 8;i++) {
        for (int y = 0; y < 8;y++) {
            if (colorKing == true) {
                if (board[i][y] == '.') continue; // под вопросом
                else if (board[i][y] == 'P' && canPawnGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'B' && canBishopGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'N' && canKnightGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'R' && canRookGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'Q' && canQueenGo(board, i, y, kingRow, kingCol)) return 1;
            }
            else if (colorKing == false) {
                if (board[i][y] == '.') continue;
                else if (board[i][y] == 'p' && canPawnGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'b' && canBishopGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'n' && canKnightGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'r' && canRookGo(board, i, y, kingRow, kingCol)) return 1;
                else if (board[i][y] == 'q' && canQueenGo(board, i, y, kingRow, kingCol)) return 1;
            }
            }
        }
    return 0;
    
    }

bool isCastleSafe(char board[8][8], int fromCol, int toCol, int fromRow, bool isKingWhite) {

    if (isKingWhite == true && toCol == 6) {
        for (int i = 0; i < 8;i++) {
            for (int y = 0; y < 8; y++) {
                if (board[i][y] == '.') continue; // под вопросом
                else if (board[i][y] == 'P' && canPawnGo(board, i, y, 7, 5)) return 0;
                else if (board[i][y] == 'B' && canBishopGo(board, i, y, 7, 5)) return 0;
                else if (board[i][y] == 'N' && canKnightGo(board, i, y, 7, 5)) return 0;
                else if (board[i][y] == 'R' && canRookGo(board, i, y, 7, 5)) return 0;
                else if (board[i][y] == 'Q' && canQueenGo(board, i, y, 7, 5)) return 0;

                else if (board[i][y] == 'P' && canPawnGo(board, i, y, 7, 6)) return 0;
                else if (board[i][y] == 'B' && canBishopGo(board, i, y, 7, 6)) return 0;
                else if (board[i][y] == 'N' && canKnightGo(board, i, y, 7, 6)) return 0;
                else if (board[i][y] == 'R' && canRookGo(board, i, y, 7, 6)) return 0;
                else if (board[i][y] == 'Q' && canQueenGo(board, i, y, 7, 6)) return 0;
            }
        }
    }

    if (isKingWhite == true && toCol == 2) {
        for (int i = 0; i < 8;i++) {
            for (int y = 0; y < 8; y++) {
                if (board[i][y] == '.') continue; // под вопросом
                else if (board[i][y] == 'P' && canPawnGo(board, i, y, 7, 2)) return 0;
                else if (board[i][y] == 'B' && canBishopGo(board, i, y, 7, 2)) return 0;
                else if (board[i][y] == 'N' && canKnightGo(board, i, y, 7, 2)) return 0;
                else if (board[i][y] == 'R' && canRookGo(board, i, y, 7, 2)) return 0;
                else if (board[i][y] == 'Q' && canQueenGo(board, i, y, 7, 2)) return 0;

                else if (board[i][y] == 'P' && canPawnGo(board, i, y, 7, 3)) return 0;
                else if (board[i][y] == 'B' && canBishopGo(board, i, y, 7, 3)) return 0;
                else if (board[i][y] == 'N' && canKnightGo(board, i, y, 7, 3)) return 0;
                else if (board[i][y] == 'R' && canRookGo(board, i, y, 7, 3)) return 0;
                else if (board[i][y] == 'Q' && canQueenGo(board, i, y, 7, 3)) return 0;
            }
        }
    }
    if (isKingWhite == false && toCol == 6) {
        for (int i = 0; i < 8;i++) {
            for (int y = 0; y < 8; y++) {
                if (board[i][y] == '.') continue; // под вопросом
                else if (board[i][y] == 'p' && canPawnGo(board, i, y, 0, 5)) return 0;
                else if (board[i][y] == 'b' && canBishopGo(board, i, y, 0, 5)) return 0;
                else if (board[i][y] == 'n' && canKnightGo(board, i, y, 0, 5)) return 0;
                else if (board[i][y] == 'r' && canRookGo(board, i, y, 0, 5)) return 0;
                else if (board[i][y] == 'q' && canQueenGo(board, i, y, 0, 5)) return 0;

                else if (board[i][y] == 'p' && canPawnGo(board, i, y, 0, 6)) return 0;
                else if (board[i][y] == 'b' && canBishopGo(board, i, y, 0, 6)) return 0;
                else if (board[i][y] == 'n' && canKnightGo(board, i, y, 0, 6)) return 0;
                else if (board[i][y] == 'r' && canRookGo(board, i, y, 0, 6)) return 0;
                else if (board[i][y] == 'q' && canQueenGo(board, i, y, 0, 6)) return 0;
            }
        }
    }

    if (isKingWhite == false && toCol == 2) {
        for (int i = 0; i < 8;i++) {
            for (int y = 0; y < 8; y++) {
                if (board[i][y] == '.') continue; // под вопросом
                else if (board[i][y] == 'p' && canPawnGo(board, i, y, 0, 2)) return 0;
                else if (board[i][y] == 'b' && canBishopGo(board, i, y, 0, 2)) return 0;
                else if (board[i][y] == 'n' && canKnightGo(board, i, y, 0, 2)) return 0;
                else if (board[i][y] == 'r' && canRookGo(board, i, y, 0, 2)) return 0;
                else if (board[i][y] == 'q' && canQueenGo(board, i, y, 0, 2)) return 0;

                else if (board[i][y] == 'p' && canPawnGo(board, i, y, 0, 3)) return 0;
                else if (board[i][y] == 'b' && canBishopGo(board, i, y, 0, 3)) return 0;
                else if (board[i][y] == 'n' && canKnightGo(board, i, y, 0, 3)) return 0;
                else if (board[i][y] == 'r' && canRookGo(board, i, y, 0, 3)) return 0;
                else if (board[i][y] == 'q' && canQueenGo(board, i, y, 0, 3)) return 0;
            }
        }
    }
    return 1;
}
int translateMove(char boardChar) {
    switch (boardChar) {
    case 'a': return 0;
    case 'b': return 1;
    case 'c': return 2;
    case 'd': return 3;
    case 'e': return 4;
    case 'f': return 5;
    case 'g': return 6;
    case 'h': return 7;
    default: return -1; // неверная буква
    }
}

bool isCheckmate(char targetKing, char board[8][8]) {
    if (!isCheck(targetKing, board)) return false; 

    char temp[8][8];
    copyBoard(board, temp);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char piece = temp[i][j];
            if (piece == '.') continue;
            bool isWhitePiece = (piece >= 'a' && piece <= 'z');
            bool isWhiteKing = (targetKing == 'k');
            if (isWhitePiece != isWhiteKing) continue;

            for (int ti = 0; ti < 8; ti++) {
                for (int tj = 0; tj < 8; tj++) {
                    if (i == ti && j == tj) continue;

                    bool canMove = false;
                    switch (piece) {
                    case 'R': case 'r': canMove = canRookGo(temp, i, j, ti, tj); break;
                    case 'B': case 'b': canMove = canBishopGo(temp, i, j, ti, tj); break;
                    case 'Q': case 'q': canMove = canQueenGo(temp, i, j, ti, tj); break;
                    case 'N': case 'n': canMove = canKnightGo(temp, i, j, ti, tj); break;
                    case 'K': case 'k': canMove = canKingGo(temp, i, j, ti, tj); break;
                    case 'P': case 'p': canMove = canPawnGo(temp, i, j, ti, tj); break;
                    }
                    if (!canMove) continue;

                    char tempBoardCopy[8][8];
                    copyBoard(temp, tempBoardCopy);
                    tempBoardCopy[ti][tj] = tempBoardCopy[i][j];
                    tempBoardCopy[i][j] = '.';
                    if (!isCheck(targetKing, tempBoardCopy)) return false;
                }
            }
        }
    }
    return 1;
}


    

void runTests() {

    // Проверка копирования доски
    char board1[8][8];
    drawingBoard(board1);
    char copy[8][8];
    copyBoard(board1, copy);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            assert(copy[i][j] == board1[i][j]);
        }
    }

    // Проверка начальной расстановки
    char board2[8][8];
    drawingBoard(board2);
    assert(board2[7][7] == 'r');
    assert(board2[7][0] == 'r');
    assert(board2[0][0] == 'R');
    assert(board2[0][7] == 'R');
    assert(board2[7][4] == 'k');
    assert(board2[0][4] == 'K');
    assert(board2[6][0] == 'p');
    assert(board2[1][0] == 'P');
    assert(board2[3][4] == '.');

    // Проверка ладьи (горизонталь, вертикаль, препятствия)
    char rookBoard[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            rookBoard[i][j] = '.';
    rookBoard[4][4] = 'r';
    assert(canRookGo(rookBoard, 4, 4, 4, 7) == 1);
    assert(canRookGo(rookBoard, 4, 4, 4, 0) == 1);
    assert(canRookGo(rookBoard, 4, 4, 7, 4) == 1);
    assert(canRookGo(rookBoard, 4, 4, 0, 4) == 1);
    assert(canRookGo(rookBoard, 4, 4, 5, 5) == 0);
    rookBoard[4][6] = 'P';
    assert(canRookGo(rookBoard, 4, 4, 4, 7) == 0);
    rookBoard[4][6] = '.';
    rookBoard[6][4] = 'p';
    assert(canRookGo(rookBoard, 4, 4, 7, 4) == 0);

    // Проверка слона (диагонали, препятствия)
    char bishopBoard[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            bishopBoard[i][j] = '.';
    bishopBoard[4][4] = 'b';
    assert(canBishopGo(bishopBoard, 4, 4, 6, 6) == 1);
    assert(canBishopGo(bishopBoard, 4, 4, 2, 2) == 1);
    assert(canBishopGo(bishopBoard, 4, 4, 6, 2) == 1);
    assert(canBishopGo(bishopBoard, 4, 4, 2, 6) == 1);
    assert(canBishopGo(bishopBoard, 4, 4, 4, 6) == 0);
    bishopBoard[5][5] = 'p';
    assert(canBishopGo(bishopBoard, 4, 4, 6, 6) == 0);
    bishopBoard[5][5] = '.';
    bishopBoard[3][3] = 'P';
    assert(canBishopGo(bishopBoard, 4, 4, 2, 2) == 0);

    // Проверка ферзя (комбинация ладьи и слона)
    char queenBoard[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            queenBoard[i][j] = '.';
    queenBoard[4][4] = 'q';
    assert(canQueenGo(queenBoard, 4, 4, 4, 7) == 1);
    assert(canQueenGo(queenBoard, 4, 4, 7, 4) == 1);
    assert(canQueenGo(queenBoard, 4, 4, 6, 6) == 1);
    assert(canQueenGo(queenBoard, 4, 4, 5, 3) == 1);
    assert(canQueenGo(queenBoard, 4, 4, 3, 5) == 1);

    // Проверка коня (буквой Г, без проверки пути)
    char knightBoard[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            knightBoard[i][j] = '.';
    knightBoard[4][4] = 'n';
    assert(canKnightGo(knightBoard, 4, 4, 6, 5) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 6, 3) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 5, 6) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 5, 2) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 2, 5) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 2, 3) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 3, 6) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 3, 2) == 1);
    assert(canKnightGo(knightBoard, 4, 4, 4, 6) == 0);
    assert(canKnightGo(knightBoard, 4, 4, 5, 5) == 0);

    // Проверка короля (1 клетка в любую сторону)
    char kingBoard[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            kingBoard[i][j] = '.';
    kingBoard[4][4] = 'k';
    assert(canKingGo(kingBoard, 4, 4, 5, 5) == 1);
    assert(canKingGo(kingBoard, 4, 4, 5, 4) == 1);
    assert(canKingGo(kingBoard, 4, 4, 4, 5) == 1);
    assert(canKingGo(kingBoard, 4, 4, 3, 3) == 1);
    assert(canKingGo(kingBoard, 4, 4, 3, 4) == 1);
    assert(canKingGo(kingBoard, 4, 4, 4, 3) == 1);
    assert(canKingGo(kingBoard, 4, 4, 4, 4) == 0);
    assert(canKingGo(kingBoard, 4, 4, 6, 6) == 0);

    // Проверка пешки (ход вперёд, двойной, взятие)
    char pawnBoard[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            pawnBoard[i][j] = '.';
    pawnBoard[6][4] = 'p'; // белая пешка
    assert(canPawnGo(pawnBoard, 6, 4, 5, 4) == 1);
    assert(canPawnGo(pawnBoard, 6, 4, 4, 4) == 1); // двойной
    assert(canPawnGo(pawnBoard, 6, 4, 3, 4) == 0);
    pawnBoard[5][5] = 'P';
    assert(canPawnGo(pawnBoard, 6, 4, 5, 5) == 1); // взятие
    pawnBoard[5][3] = 'P';
    assert(canPawnGo(pawnBoard, 6, 4, 5, 3) == 1);
    pawnBoard[6][4] = 'P'; // чёрная пешка
    pawnBoard[1][4] = 'P';
    assert(canPawnGo(pawnBoard, 1, 4, 2, 4) == 1);
    assert(canPawnGo(pawnBoard, 1, 4, 3, 4) == 1);
    pawnBoard[2][5] = 'p';
    assert(canPawnGo(pawnBoard, 1, 4, 2, 5) == 1);
    assert(canPawnGo(pawnBoard, 1, 4, 1, 4) == 0);

    // Проверка рокировки (короткая и длинная, без препятствий, без учёта шаха)
    char castleBoard[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            castleBoard[i][j] = '.';
    castleBoard[7][4] = 'k';
    castleBoard[7][7] = 'r';
    for (int j = 5; j <= 6; j++) castleBoard[7][j] = '.';
    assert(canCastle(castleBoard, 7, 4, 7, 6, true, 0, 0) == 1);
    assert(canCastle(castleBoard, 7, 4, 7, 2, true, 0, 0) == 0);
    castleBoard[7][0] = 'r';
    for (int j = 1; j <= 3; j++) castleBoard[7][j] = '.';
    assert(canCastle(castleBoard, 7, 4, 7, 2, true, 0, 0) == 1);
    assert(canCastle(castleBoard, 7, 4, 7, 6, true, 1, 0) == 0); // король ходил
    assert(canCastle(castleBoard, 7, 4, 7, 2, true, 0, 1) == 0); // ладья ходила

    // Проверка isCheck (шах)
    char checkBoard[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            checkBoard[i][j] = '.';
        }
    }
    checkBoard[0][0] = 'K'; // чёрный король
    checkBoard[2][0] = 'r'; // белая ладья
    assert(isCheck('K', checkBoard) == 1);
    checkBoard[2][0] = '.';
    checkBoard[3][1] = 'n'; // белый конь
    assert(isCheck('K', checkBoard) == 0);
    checkBoard[1][1] = 'n';
    checkBoard[1][1] = '.';
    checkBoard[3][4] = 'b'; // белый слон
    assert(isCheck('K', checkBoard) == 0);
    checkBoard[4][4] = 'b';
    assert(isCheck('K', checkBoard) == 1);
    // шах пешкой
    char pawnCheck[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            pawnCheck[i][j] = '.';
        }
    }
    pawnCheck[4][4] = 'k'; // белый король
    pawnCheck[3][5] = 'P'; // чёрная пешка бьёт
    assert(isCheck('k', pawnCheck) == 1);
    pawnCheck[3][5] = '.';
    pawnCheck[3][3] = 'P';
    assert(isCheck('k', pawnCheck) == 1);
    pawnCheck[3][3] = '.';
    pawnCheck[3][4] = 'P';
    assert(isCheck('k', pawnCheck) == 0); // прямо не бьёт

    std::cout << "Все юнит-тесты пройдены успешно!\n";
}

int main() {
    runTests();
    setlocale(LC_ALL, "rus");

    const int xCHESS = 8, yCHESS = 8;
    char chessBoard[yCHESS][xCHESS];
    drawingBoard(chessBoard);
    printBoard(chessBoard); //первая отрисовка

    // проверка на очередность хода
    int move = 1;


    int firstMoveKingWhite = 0, firstMoveKingBlack = 0,
        firstMoveRookA1 = 0, firstMoveRookH1 = 0,
        firstMoveRookA8 = 0, firstMoveRookH8 = 0;


    while (true) {

        // проверка хода по счетчику(первый = 1, соответсвенно move%2 != 0 белые, иначе черные
        if (move % 2 == 0) cout << "Хiд чoрних";
        else cout << "Хiд бiлих";
        cout << endl;
        // проверка на шах
        char targetKing;
        if (move % 2 == 0) targetKing = 'K';
        else if (move % 2 != 0)targetKing = 'k';

        if (isCheck(targetKing, chessBoard)) {
            cout << "Шах!\n";
            if (isCheckmate(targetKing, chessBoard)) {
                cout << "Мат! Гру закiнчено.\n";
                return 0;
            }
        }

        int fromRow, fromCol, toRow, toCol;


        

        cout << "Введiть хiд в форматi звiдки/куди: ";
        string from, to;
        cin >> from >> to;
        if (from.length() != 2 || to.length() != 2) {
            cout << "Неправильний формат! Використовуйте букву a-h та цифру 1-8.\n";
            continue;
        }
        fromCol = translateMove(from[0]);
        fromRow = 8 - (from[1] - '0');
        toCol = translateMove(to[0]);
        toRow = 8 - (to[1] - '0');

        if (fromCol == -1 || toCol == -1) {
            cout << "Неправильна буква! Використовуйте a-h.\n";
            continue;
        }
        if (fromRow < 0 || fromRow > 7 || toRow < 0 || toRow > 7) {
            cout << "Неправильна цифра! Використовуйте 1-8.\n";
            continue;
        }


        if (fromRow < 0 || fromRow>7 || fromCol < 0 || fromCol>7 || toRow < 0 || toRow>7 || toCol < 0 || toCol>7) {
            cout << "Вихiд за межі";
            continue;
        }

        // получение цвета фигуры
        char piece = chessBoard[fromRow][fromCol];


        // проверка хода цвета фигуры
        if (move % 2 != 0 && piece >= 'A' && piece <= 'Z') {
            cout << "Зараз хiд бiлих! Ви обрали чорну фiгуру.\n" << endl;
            continue;
        }
        if (move % 2 == 0 && piece >= 'a' && piece <= 'z') {
            cout << "Зараз хiд чорних! Ви обрали бiлу фiгуру.\n" << endl;
            continue;
        }

        // проверка хода на свою фигуру
        char targetPiece = chessBoard[toRow][toCol];

        if (move % 2 != 0 && targetPiece >= 'a' && targetPiece <= 'z') {
            cout << "Хід на свою фігуру!\n";
            continue;
        }
        if (move % 2 == 0 && targetPiece >= 'A' && targetPiece <= 'Z') {
            cout << "Хід на свою фігуру\n";
            continue;
        }

        

        //ход фигуры
        if (piece == '.') {
            cout << "На цiй клiтинi вiдсутнi фiгури!\n";
            continue;
        }
        else if (piece == 'R' || piece == 'r') {
            if (canRookGo(chessBoard, fromRow, fromCol, toRow, toCol)) {
                copyBoard(chessBoard, tempBoard);
                tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
                tempBoard[fromRow][fromCol] = '.';
                char colorOfKing;
                if (move % 2 != 0) colorOfKing = 'k';
                else colorOfKing = 'K';
                if (!isCheck(colorOfKing, tempBoard)) {
                    if (fromRow == 7 && fromCol == 7) firstMoveRookH1++;
                    if (fromRow == 7 && fromCol == 0) firstMoveRookA1++;
                    if (fromRow == 0 && fromCol == 0) firstMoveRookA8++;
                    if (fromRow == 0 && fromCol == 7) firstMoveRookH8++;
                    chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                    chessBoard[fromRow][fromCol] = '.';
                    printBoard(chessBoard);
                    move++;
                }
                else {
                    cout << "Хід неможливий!,король під шахом!\n";
                    continue;
                }
            }
            else {
                cout << "Хiд неможливий!\n";
            }
        }

        
        else if (piece == 'K' || piece == 'k') {
            if (fromCol - toCol == 2 || fromCol - toCol == -2) {
                if (piece == 'k' && toCol == 6 && !isCheck('k', chessBoard)) {
                    if (canCastle(chessBoard, fromRow, fromCol, toRow, toCol, 1, firstMoveKingWhite, firstMoveRookH1)) {
                        if (isCastleSafe(chessBoard, fromCol, toCol, fromRow, true)) {
                            chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                            chessBoard[7][5] = 'r';
                            chessBoard[7][7] = '.';
                            chessBoard[fromRow][fromCol] = '.';
                            printBoard(chessBoard);
                            firstMoveKingWhite++;
                            move++;
                        }
                        else {
                            cout << "Рокiрування через бите поле!\n";
                            continue;
                        }
                    }
                }
                if (piece == 'k' && toCol == 2 && !isCheck('k', chessBoard)) {
                    if (canCastle(chessBoard, fromRow, fromCol, toRow, toCol, 1, firstMoveKingWhite, firstMoveRookA1)) {
                        if (isCastleSafe(chessBoard, fromCol, toCol, fromRow, true)) {
                            chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                            chessBoard[fromRow][fromCol] = '.';
                            chessBoard[7][3] = 'r';
                            chessBoard[7][0] = '.';
                            printBoard(chessBoard);
                            firstMoveKingWhite++;
                            move++;
                        }
                        else {
                            cout << "Рокiрування через бите поле!\n";
                            continue;
                        }
                    }
                }
                if (piece == 'K' && toCol == 2 && !isCheck('K',chessBoard)) {
                    if (canCastle(chessBoard, fromRow, fromCol, toRow, toCol, 0, firstMoveKingBlack, firstMoveRookA8)) {
                        if (isCastleSafe(chessBoard, fromCol, toCol, fromRow, false)) {
                            chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                            chessBoard[0][3] = 'R';
                            chessBoard[0][0] = '.';
                            chessBoard[fromRow][fromCol] = '.';
                            printBoard(chessBoard);
                            firstMoveKingBlack++;
                            move++;
                        }
                        else {
                            cout << "Рокiрування через бите поле!\n";
                            continue;
                        }
                    }
                }
                if (piece == 'K' && toCol == 6 && !isCheck('K', chessBoard)) {
                    if (canCastle(chessBoard, fromRow, fromCol, toRow, toCol, 0, firstMoveKingBlack, firstMoveRookH8)) {
                        if (isCastleSafe(chessBoard, fromCol, toCol, fromRow, false)) {
                            chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                            chessBoard[0][5] = 'R';
                            chessBoard[0][7] = '.';
                            chessBoard[fromRow][fromCol] = '.';
                            printBoard(chessBoard);
                            firstMoveKingBlack++;
                            move++;
                        }
                        else {
                            cout << "Рокiрування через бите поле!\n";
                            continue;
                        }
                    }
                }
            }
                
                // обычный ход короля
            else if (canKingGo(chessBoard, fromRow, fromCol, toRow, toCol)) {

                
                copyBoard(chessBoard, tempBoard);
                tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
                tempBoard[fromRow][fromCol] = '.';
                if (!isCheck(piece, tempBoard)) {

                    if (piece == 'k') firstMoveKingWhite++;
                    if (piece == 'K')  firstMoveKingBlack++;
                    chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                    chessBoard[fromRow][fromCol] = '.';
                    printBoard(chessBoard);
                    move++;
                }
            }

                else {
                    cout << "Хiд неможливий!\n";
                    continue;
                }
        }


        /////
       
         ////////
        else if (piece == 'N' || piece == 'n') {


            if (canKnightGo(chessBoard, fromRow, fromCol, toRow, toCol)) {
                copyBoard(chessBoard, tempBoard);
                tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
                tempBoard[fromRow][fromCol] = '.';
                char colorOfKing;


                if (move % 2 != 0) colorOfKing = 'k';
                else colorOfKing = 'K';

                // проверка хода + отсутсвие шаха
                if (!isCheck(colorOfKing, tempBoard)) {
                    chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                    chessBoard[fromRow][fromCol] = '.';
                    printBoard(chessBoard);
                    move++;
                }
                else{
                    cout << "Хід неможливий!,король під шахом!\n";
                    continue;
                }
            }
            else {
                cout << "Хiд неможливий!\n";
                continue;
            }
        }
        else if (piece == 'Q' || piece == 'q') {
            if (canQueenGo(chessBoard, fromRow, fromCol, toRow, toCol)) {
                copyBoard(chessBoard, tempBoard);
                tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
                tempBoard[fromRow][fromCol] = '.';
                char colorOfKing;
                if (move % 2 != 0) colorOfKing = 'k';
                else colorOfKing = 'K';

                if (!isCheck(colorOfKing, tempBoard)) {
                    chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                    chessBoard[fromRow][fromCol] = '.';
                    printBoard(chessBoard);
                    move++;
                }
                else {
                    cout << "Хід неможливий!,король під шахом!\n";
                    continue;
                }
            }
            else {
                cout << "Хiд неможливий!\n";
                continue;
            }
        }
        else if (piece == 'P' || piece == 'p') {
            if (canPawnGo(chessBoard, fromRow, fromCol, toRow, toCol)) {
                copyBoard(chessBoard, tempBoard);
                tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
                tempBoard[fromRow][fromCol] = '.';
                char colorOfKing;
                if (move % 2 != 0) colorOfKing = 'k';
                else colorOfKing = 'K';

                if (!isCheck(colorOfKing, tempBoard)) {
                    chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                    chessBoard[fromRow][fromCol] = '.';

                link: // goto ссылка для структуры ниже дабы игрок выбрал правильный цвет фигуры
                    //выбор новой фигуры при достижении противоположной части доски
                    if (piece == 'p' && toRow == 0) {
                        char changePiece;
                        cout << "Ви можете обрати нову фiгуру!\n" << "q - королева\n" << "r - тура\n" << "n - кiнь\n" << "b - слон";
                        cin >> changePiece;
                        if (changePiece < 'a' || changePiece > 'z') {
                            cout << "Ви обрали неправильний колiр фiгури! Введiть фiгуру з маленької лiтери!" << endl;
                            goto link;
                        }
                        chessBoard[fromRow][fromCol] = '.';
                        chessBoard[toRow][toCol] = changePiece;
                    }
                    if (piece == 'P' && toRow == 7) {
                        char changePiece;
                        cout << "Ви можете обрати нову фiгуру!\n" << "Q - королева\n" << "R - тура\n" << "N - кiнь\n" << "B - слон";
                        cin >> changePiece;
                        if (changePiece < 'A' || changePiece > 'Z') {
                            cout << "Ви обрали неправильний колiр фiгури! Введiть фiгуру з великоi лiтери!" << endl;
                            goto link;
                        }
                        chessBoard[fromRow][fromCol] = '.';
                        chessBoard[toRow][toCol] = changePiece;
                    }
                    printBoard(chessBoard);
                    move++;

                }
                else {
                    cout << "Хід неможливий!,король під шахом!\n";
                    continue;
                }
            }
            else {
                cout << "Хiд неможливий!\n";
                continue;
            }
        }
        else if (piece == 'B' || piece == 'b') {
            if (canBishopGo(chessBoard, fromRow, fromCol, toRow, toCol)) {
                copyBoard(chessBoard, tempBoard);
                tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
                tempBoard[fromRow][fromCol] = '.';
                char colorOfKing;

                if (move % 2 != 0) colorOfKing = 'k';
                else colorOfKing = 'K';

                if (!isCheck(colorOfKing, tempBoard)) {
                    chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
                    chessBoard[fromRow][fromCol] = '.';
                    printBoard(chessBoard);
                    move++;
                }
                else {
                    cout << "Хід неможливий!,король під шахом!\n";
                    continue;
                }
            }
            else {
                cout << "Хiд неможливий!\n";
                continue;
            }
        }
    }

    cout << "End";
}

