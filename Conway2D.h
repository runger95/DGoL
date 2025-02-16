#pragma once
static const int CHUNKSDIMX = 2;
static const int CHUNKSDIMY = 2;
static const int MAX_X_CELLS = 10;
static const int MAX_Y_CELLS = 10;
static const int chunkLenX = MAX_X_CELLS/CHUNKSDIMX;
static const int chunkLenY = MAX_Y_CELLS/CHUNKSDIMY;



void gameLoop2D(int arrayCurState[MAX_X_CELLS][MAX_Y_CELLS], int arrayNextState[MAX_X_CELLS][MAX_Y_CELLS]);