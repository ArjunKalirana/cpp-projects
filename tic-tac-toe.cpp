#include <bits/stdc++.h>
using namespace std;

class GameBoard {
    private:
        char board[3][3];
    public:
        GameBoard(){
            for(int i=0;i<3;++i)
                for(int j=0;j<3;++j)
                    board[i][j]=' ';
        }
        void displayBoard(){
            cout << "\n     1   2   3\n";
            char rowLabels[3]={'A','B','C'};
            for(int i=0;i<3;++i){
                cout<< " "<< rowLabels[i] << "   ";
                for(int j=0;j<3;++j){
                    cout << board[i][j];
                    if(j<2) cout << " | ";
                }
                cout << "\n";
                if(i<2) cout<< "    ---+---+---+\n";
            }
        };

        bool isMoveValid(int row,int col){
            return row>=0 && row<3 &&
                col>=0 && col < 3 &&
                board[row][col] == ' ';
        };
        void makeMove(int row,int col,char symbol){
            board[row][col]=symbol;
        };
        char checkWin(){
            for(int i=0;i<3;++i){
                    if( board[i][0]!=' '&&
                        board[i][0]==board[i][1]&&
                        board[i][1]==board[i][2])
                        return board[i][0];
                }

                for(int j=0;j<3;++j){
                    if( board[0][j]!= ' '&&
                        board[0][j]==board[1][j] &&
                        board[1][j]==board[2][j])
                        return board[0][j];
                }
                if (board[0][0] != ' ' &&
                    board[0][0] == board[1][1] &&
                    board[1][1] == board[2][2])
                    return board[0][0];
                if (board[0][2] != ' ' &&
                    board[0][2] == board[1][1] &&
                    board[1][1] == board[2][0])
                    return board[0][2];


                if(isFull())
                    return 'D';
                return ' ';
            
        };
        bool isFull(){
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (board[i][j] == ' ')
                        return false;
            return true;
        };
        void resetBoard(){
            for(int i=0;i<3;++i)
                for(int j = 0; j<3; ++j)
                    board[i][j]= ' ';
        };

};

class Player {
    protected:
        char symbol;

    public:
    Player(char sym){
        symbol=sym;
    };
    virtual void makeMove(GameBoard &board) = 0;
    char getSymbol(){
        return symbol;
    };
};

class HumanPlayer :public Player{
    public:
    HumanPlayer(char sym): Player(sym){};
    void makeMove(GameBoard &board) {
        string input;
            int row,col;
            while(true){
                cout<<"\nYour Move:(eg., A1,B3):";
                cin>> input;
                if(input.length()==2 && toupper(input[0])>='A' && toupper(input[0])<='C' 
                && input[1]>='1' && input[1]<='3'){
                    row=toupper(input[0])-'A';
                    col=input[1]-'1';
                    
                    if(board.isMoveValid(row,col)){
                        board.makeMove(row,col,symbol);
                        break;
                    }
                    else{
                        cout << "Cell already taken! try some other value.\n";
                    }
                }
                else{

                    cout<< "Invalid input format! Use something like A1,B2...\n";
                }
            }
    };
};

class AIPlayer :public Player{
    public:
        AIPlayer(char sym):Player(sym){};
        char getOpponentSymbol(){
            return (symbol=='X')? 'O':'X';
        }
        void makeMove(GameBoard &board){
            int bestScore=-1000;
            int bestRow=-1,bestCol=-1;

            for(int i=0;i<3;++i){
                for(int j=0;j<3;++j){
                    if(board.isMoveValid(i,j)){
                        board.makeMove(i,j,symbol);
                        int score=minimax(board,false);
                        board.makeMove(i,j,' ');

                        if(score>bestScore){
                            bestScore=score;
                            bestCol=j;
                            bestRow=i;
                        }
                    }
                }
            }
            board.makeMove(bestRow,bestCol,symbol);
            cout << "\nAI plays at "<< char('A'+ bestRow) << (bestCol+1)<<"\n";
        };

    private:
        int minimax(GameBoard &board,bool isMax){
            char result= board.checkWin();
            if(result==symbol)return 1;
            else if(result == getOpponentSymbol())return -1;
            else if (board.isFull())return 0;

            int bestScore = isMax ? -1000:1000;
            for(int i=0;i<3;++i){
                for(int j=0;j<3;++j){
                    if(board.isMoveValid(i,j)){
                        board.makeMove(i,j,isMax ? symbol : getOpponentSymbol());
                        int score =minimax(board,!isMax);
                        board.makeMove(i,j,' ');
                        bestScore = isMax? max(score,bestScore): min(score,bestScore);
                    }
                }
            }
            return bestScore;
        };
};

class Game {
    GameBoard board;
    HumanPlayer player;
    AIPlayer ai;
    char currentPlayer;

public:
    Game(): player('X'), ai('O'), currentPlayer('X') {}

    void playGame() {
        while (true) {
            board.displayBoard();

            if (currentPlayer == player.getSymbol()) {
                player.makeMove(board);
            } else {
                ai.makeMove(board);
            }

            char result = board.checkWin();
            if (result == 'X' || result == 'O') {
                board.displayBoard();
                cout << "\nPlayer " << result << " wins!\n";
                break;
            } else if (result == 'D') {
                board.displayBoard();
                cout << "\nIt's a draw!\n";
                break;
            }

            // Toggle turn
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
};


int main() {
    Game game;
    game.playGame();
    return 0;
}

