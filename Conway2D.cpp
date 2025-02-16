#include "Conway2D.h"


//counts cells around the local to determine it's values
int countAliveNeighbours(int arrayCurState[MAX_X_CELLS][MAX_Y_CELLS], int x, int y){
    
    int liveNeighbours = 0;
    
    int i_low = -1;
    int j_low = -1;
    int i_high = 1;
    int j_high = 1;

    //addjusts bounds of for loops to ensure we don't ping outside the array.
    if (x == 0) {
        i_low = 0;
    }
    if (y == 0) {
        j_low = 0;
    }
    if (x == MAX_X_CELLS-1) {
        i_high = 0;
    }
    if (y == MAX_Y_CELLS-1) {
        j_high = 0;
    }

    // loop throuugh valid neighbours to count how many are alive
    for (int i = i_low; i <= i_high; i++){
        for (int j = i_low; j <= j_high; j++){
            if (arrayCurState[x+i][y+j] == 1){
                liveNeighbours++;
            }
        }
    }
    return liveNeighbours;
}

// rules for 2D ConwayGame
int rule2DConway(int arrayCurState[MAX_X_CELLS][MAX_Y_CELLS], int i, int j){
    int localNextState = 0; //return val for Dead/Alive
    int localAlive = arrayCurState[i][j]; //local val before update
    
    //count # of live neighbours for each cells as it needs
    int liveNeighbours = countAliveNeighbours(arrayCurState, i, j) - localAlive;

    //rules    
    if (liveNeighbours == 3){
        localNextState = 1;
    }
    else if(localAlive ==1 && liveNeighbours == 2){
        localNextState = 1;
    }
    else{
        //do nothing, next state already 0;
    }
    return localNextState;
}

//main function which gets the array updated into it's next state.
//it loops through all (2) dimensions and calls the rule2DConway to determine the value the cell should be.
void gameLoop2D(int arrayCurState[MAX_X_CELLS][MAX_Y_CELLS], int arrayNextState[MAX_X_CELLS][MAX_Y_CELLS]){ 

    //outerloop to iterate through Chunks
    for (int c_x = 0; c_x < CHUNKSDIMX; c_x++) {
        for (int c_y = 0; c_y < CHUNKSDIMY; c_y++) {
            
            //inner loop to iterate inside Chunk
            //c_x*chunkLen+i is calculating offset based on which chunk
            for (int i = 0; i < chunkLenX; i++) {
                for (int j= 0; j < chunkLenX; j++) {
                    arrayNextState[c_x*chunkLenX+i][c_y*chunkLenY+j] = rule2DConway(arrayCurState, c_x*chunkLenX+i, c_y*chunkLenY+j);
                }
            }
        }
    }
}