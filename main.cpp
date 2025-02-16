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

#include "Conway2D.h"


/* For when I build Chunks to Parse //use universe array which holds 
#define MAX_X_CHUNKS 1 #define MAX_Y_CHUNKS 1
*/

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
{0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}
}; 




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
        printf("\n");
        printf("%d ", looper);
        printf("\n");

        Sleep(1000); // wait 2 seconds, need to find way to link stdlib.h
        looper++;  // setting bounds for now in order to quick analuze
    }
    printf("Done");

    return 0;
}
