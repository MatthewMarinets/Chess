// Constants.h

#ifndef CHESS_CONSTANTS
#define CHESS_CONSTANTS

const int BOARD_SIZE = 8;

const int BOARD_TILE_WIDTH = 6;
const int BOARD_TILE_HEIGHT = 2;
const int BOARD_IMAGE_PADDING_X = 3;
const int BOARD_IMAGE_PADDING_Y = 1;
const int BOARD_IMAGE_TOP_LABEL_OFFSET = 2;
const int BOARD_IMAGE_WIDTH = BOARD_SIZE * ( BOARD_TILE_WIDTH + 1 ) + 2*BOARD_IMAGE_PADDING_X + 1;
const int BOARD_IMAGE_HEIGHT = BOARD_SIZE * ( BOARD_TILE_HEIGHT + 1 ) + 2*BOARD_IMAGE_PADDING_Y + 1;
const char TILE_HIGHLIGHT_IMAGE[BOARD_TILE_HEIGHT+2][BOARD_TILE_WIDTH+3] =
{
	{ "+------+" },
	{ "|      |" },
	{ "|      |" },
	{ "+------+" },
};
const char TILE_SELECT_IMAGE[BOARD_TILE_HEIGHT+2][BOARD_TILE_WIDTH+3] =
{
	{ "+~~~~~~+" },
	{ "\\      /" },
	{ "/      \\" },
	{ "+~~~~~~+" },
};
const int PIECE_START[BOARD_SIZE][BOARD_SIZE] =
{
	{  1,  2,  3,  4,  5,  3,  2,  1 },
	{  6,  6,  6,  6,  6,  6,  6,  6 },
	{  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0 },
	{ -7, -7, -7, -7, -7, -7, -7, -7 },
	{ -1, -2, -3, -4, -5, -3, -2, -1 }
};



#endif // CHESS_CONSTANTS