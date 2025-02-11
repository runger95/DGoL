#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>


/* For when I build Chunks to Parse //use universe array which holds 
#define MAX_X_CHUNKS 1 #define MAX_Y_CHUNKS 1
*/
#define CHUNKSPERDIM 2
#define MAX_X_CELLS 10
#define MAX_Y_CELLS 10

//This will change eventually.
int arrayOdd[MAX_X_CELLS][MAX_Y_CELLS] = {
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}
}; 

int arrayEven[MAX_X_CELLS][MAX_Y_CELLS] = {
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,1,0,0,0,0},
{0,0,0,0,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}
}; 

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
    for (int i = 0; i < MAX_X_CELLS; i++) {
        for (int j= 0; j < MAX_Y_CELLS; j++) {

            arrayNextState[i][j] = rule2DConway(arrayCurState, i, j);
        }
    }
}

//function that prints the 2D Board in ASCII
void print2DASCII(int arrayToPrint[MAX_X_CELLS][MAX_Y_CELLS]){
   for (int i = 0; i < 10; i++){
        for (int j = 0; j< 10; j++){
            printf("%i ", arrayToPrint[i][j]);
        }
        printf("\n");
    }
    printf("\n");
} 

int main() {
    //function call for game gameLoop()     
    int looper = 1; //tmp until event handling starts - basically While(TRUE)
    int cycle = 1; //current cycle, set so we switch between old/new array
    
    printf("gametime: Initial Array\n");
    print2DASCII(arrayEven);
    printf("\n");

    while (looper <= 10){
        if (cycle % 2 == 0) {
            gameLoop2D(arrayOdd, arrayEven);
            print2DASCII(arrayEven);
        }
        else {
            gameLoop2D(arrayEven, arrayOdd);
            print2DASCII(arrayOdd);
        }
        cycle++;
        Sleep(1000); // wait 2 seconds, need to find way to link stdlib.h
        looper++;  // setting bounds for now in order to quick analuze
    }
    return 0;
}
