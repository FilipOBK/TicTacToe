#include <iostream>
enum STATE{BLANK, O, X};

std::string getChar(STATE state) {
    
    switch(state){

            case O:
            return " O ";
            break;
            case X:
            return " X ";
            break;
            case BLANK:
            return "   ";
            break;
            default:
            return " ! ";

        }
}

void printGrid(STATE grid[9]){

    // print cell
    for(int i = 0; i < 9; i++){

        if(i % 3 == 0){
            std::cout << std::endl;
            
            if(i > 0){
                std::cout << "-----------" << std::endl;
            }
        }

        std::cout << getChar(grid[i]);

        if(i % 3 == 0 || i % 3 == 1) { std::cout << "|"; }
    }
    std::cout << std::endl;
}

class GameController{
    private:

    STATE* gridPtr;

    public:

    GameController(STATE* _grid) : gridPtr(_grid) {}
    ~GameController() {}

    void startRound(STATE &turn){
        char player = (turn == O ? "O"[0] : "X"[0]);
        std::cout << "It is " << player << "'s turn";
        printGrid(gridPtr);
        
        int cell = 50;
        std::cout << "Enter a cell index: ";
        std::cin >> cell;
        while(cell < 0 || cell > 8 || gridPtr[cell] != BLANK){
            std::cout << "INVALID\n";
            std::cout << "Enter a cell index: ";
            std::cin >> cell;
        }
        
        gridPtr[cell] = turn;

        turn = turn == O ? X : O;
    }
    
    STATE checkWin(STATE grid[9]){ 
        //check the rows 
        for (int i = 0; i < 3; i++) 
        { 
            if (grid[i * 3] == grid[(i * 3) + 1] && 
                grid[(i * 3) + 1] == grid[(i * 3) + 2] && 
                grid[i * 3] != BLANK) { return (grid[i * 3]); } 
        } 
        
        //check the columns 
        for (int i = 0; i < 3; i++)
        { 
            if (grid[i] == grid[i + 3] && 
                grid[i + 3] == grid[i + 6] && 
                grid[i] != BLANK) { return grid[i]; }
        } 
        
        //check the diagonals 
        if (grid[0] == grid[4] && 
            grid[4] == grid[8] && 
            grid[0] != BLANK) { return grid[0]; } 
        
        if (grid[2] == grid[4] && 
            grid[4] == grid[6] && 
            grid[2] != BLANK) { return grid[2]; } 
        
        //none of the above conditions were met 
        return BLANK; 
    } 

    bool checkDraw(){
        bool hasBlank = false;
        for(int i = 0; i < 9; i++){
            
            if(gridPtr[i] == BLANK) hasBlank = true;

        }
        return !hasBlank;
    }

};

int main(){
    STATE grid[9];
    GameController controller(&grid[0]);
    STATE turn = X;
    for(int i = 0; i < 9; i++){ grid[i] = BLANK; }
    while(controller.checkWin(grid) == BLANK && !controller.checkDraw()){

        controller.startRound(turn);

    }
    STATE winner = controller.checkWin(grid); 
    printGrid(grid);
    std::cout << (winner == BLANK ? "Nobody" : getChar(winner)) << " won!\n";

}