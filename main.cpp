#include <math.h>
#include <iostream>
#include <string>
#include <sstream>

#include "Constants.h"
#include "Pieces.h"
#include "Board.h"
#include "Types.h"
#pragma warning(disable:4996)

void printBoard( Tile** boardArray, int playerTurn );
void printMoveBoard( Tile** boardArray, int playerTurn, int xFrom, int yFrom, int movePossibilites[BOARD_SIZE][BOARD_SIZE] );
void generateBoardImage( std::string boardImage[BOARD_IMAGE_HEIGHT] );
void checkPossibleMoves( Tile** board, int playerTurn, int xFrom, int yFrom, int validMoves[BOARD_SIZE][BOARD_SIZE] );
void printArray( int inArray[BOARD_SIZE][BOARD_SIZE], int xSize, int ySize );
void printCharArray( std::string inArray[], int ySize, bool reverseY );
void printBoolArray( bool inArray[BOARD_SIZE][BOARD_SIZE] );
int getDistance( int x1, int y1, int x2, int y2 );

void printBoard_old( Tile** boardArray, int playerTurn );
void printMoveBoard_old( Tile** boardArray, int playerTurn, int xFrom, int yFrom, int movePossibilites[BOARD_SIZE][BOARD_SIZE] );

class Piece;
class Tile;

const int MAX_REPROMPTS = 2;
const bool DEBUG = false;

int main()
{
	Piece* pieces = nullptr;
	pieces = new Piece[32];

	Tile** board;
	board = new Tile*[BOARD_SIZE];
	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		board[i] = new Tile[BOARD_SIZE];
	}

	PieceClass* piece_p[10] = { nullptr };
	PieceClass Queen( "Queen", "pieces\\queen.txt" );
	piece_p[4]			= &Queen;

	PieceClass King( "King", "pieces\\king.txt" );
	piece_p[5]			= &King;

	PieceClass Pawn_white( "Pawn", "pieces\\pawn_white.txt", piece_p[4], BOARD_SIZE-1, BOARD_SIZE-1 );
	piece_p[8]			= &Pawn_white;

	PieceClass Pawn_white_start( "Pawn", "pieces\\pawn_white_start.txt", piece_p[8] );
	piece_p[6]			= &Pawn_white_start;

	PieceClass Pawn_black( "Pawn", "pieces\\pawn_black.txt", piece_p[4], 0, 0 );
	piece_p[9]		= &Pawn_black;

	PieceClass Pawn_black_start( "Pawn", "pieces\\pawn_black_start.txt", piece_p[9] );
	piece_p[7]  = &Pawn_black_start;

	PieceClass Rook( "Rook", "pieces\\rook.txt" );
	piece_p[1]				= &Rook;

	PieceClass Knight( "Knight", "pieces\\knight.txt" );
	piece_p[2]			= &Knight;

	PieceClass Bishop( "Bishop", "pieces\\bishop.txt" );
	piece_p[3]			= &Bishop;
	

	// initialize pieces
	int counter = 0;
	for ( int column = 0; column < BOARD_SIZE; column++ )
	{
		for ( int row = 0; row < BOARD_SIZE; row++ )
		{
			if ( PIECE_START[row][column] )
			{
				int player = 0;
				if ( PIECE_START[row][column] < 0 )
				{
					player = 1;
				}
				pieces[counter] = Piece( piece_p[abs(PIECE_START[row][column])], column, row, player, board );
				pieces[counter].updateBoard( board );
				counter++;
				/*
				std::cerr << board[0][0].getPiece()->getType()->getName() << "\n";
				std::cerr << board[0][0].getPiece() << "\n";
				std::cerr << board[0][0].getPiece()->getPlayer() << "\n";
				std::cerr << pieces[0].getType()->getName() << "\n";
				std::cerr << pieces << "\n";
				std::cerr << pieces[0].getPlayer() << "\n\n";
				*/
			}
		}
	}

	/*
	pieces[0]  = Piece( piece_p[1], 0, 0, 0, board );
	pieces[1]  = Piece( piece_p[2], 1, 0, 0, board );
	pieces[2]  = Piece( piece_p[3], 2, 0, 0, board );
	pieces[3]  = Piece( piece_p[4], 3, 0, 0, board );
	pieces[4]  = Piece( piece_p[5], 4, 0, 0, board );
	pieces[5]  = Piece( piece_p[3], 5, 0, 0, board );
	pieces[6]  = Piece( piece_p[2], 6, 0, 0, board );
	pieces[7]  = Piece( piece_p[1], 7, 0, 0, board );
	pieces[8]  = Piece( piece_p[6], 0, 1, 0, board );
	pieces[9]  = Piece( piece_p[6], 1, 1, 0, board );
	pieces[10] = Piece( piece_p[6], 2, 1, 0, board );
	pieces[11] = Piece( piece_p[6], 3, 1, 0, board );
	pieces[12] = Piece( piece_p[6], 4, 1, 0, board );
	pieces[13] = Piece( piece_p[6], 5, 1, 0, board );
	pieces[14] = Piece( piece_p[6], 6, 1, 0, board );
	pieces[15] = Piece( piece_p[6], 7, 1, 0, board );
	pieces[16] = Piece( piece_p[7], 0, 6, 1, board );
	pieces[17] = Piece( piece_p[7], 1, 6, 1, board );
	pieces[18] = Piece( piece_p[7], 2, 6, 1, board );
	pieces[19] = Piece( piece_p[7], 3, 6, 1, board );
	pieces[20] = Piece( piece_p[7], 4, 6, 1, board );
	pieces[21] = Piece( piece_p[7], 5, 6, 1, board );
	pieces[22] = Piece( piece_p[7], 6, 6, 1, board );
	pieces[23] = Piece( piece_p[7], 7, 6, 1, board );
	pieces[24] = Piece( piece_p[1], 0, 7, 1, board );
	pieces[25] = Piece( piece_p[2], 1, 7, 1, board );
	pieces[26] = Piece( piece_p[3], 2, 7, 1, board );
	pieces[27] = Piece( piece_p[5], 3, 7, 1, board );
	pieces[28] = Piece( piece_p[4], 4, 7, 1, board );
	pieces[29] = Piece( piece_p[3], 5, 7, 1, board );
	pieces[30] = Piece( piece_p[2], 6, 7, 1, board );
	pieces[31] = Piece( piece_p[1], 7, 7, 1, board );
	*/


	int playerTurn = 0;
	bool gameOver = false;
	bool inputFinished = false;
	bool exiting = false;
	bool goingBack = false;
	std::string input = "";
	int xFrom = -1;
	int yFrom = -1;
	int xTo = -1;
	int yTo = -1;

	// main game loop
	while ( !gameOver )
	{		
		// get player move input
		inputFinished = false;
		while ( !inputFinished )
		{
			fflush( stdin );
			xFrom = -1;
			yFrom = -1;
			xTo = -1;
			yTo = -1;
			goingBack = false;

			printBoard( board, playerTurn );
			if ( playerTurn == 0 )
			{
				fprintf( stdout, "White's move. What are the coordinates of the piece you would like to move?\n" );
			}
			else if ( playerTurn == 1 )
			{
				fprintf( stdout, "Black's move. What are the coordinates of the piece you would like to move?\n" );
			}

			// From coordinates
			while ( true )
			{
				std::getline( std::cin, input );
				if ( input == "exit" )
				{
					fprintf( stdout, "Exiting game.\n" );
					inputFinished = true;
					fflush(stdin);
					exiting = true;
					break;
				}
				std::stringstream ss(input);
				if (!( ss >> xFrom >> yFrom ))
				{
					fprintf( stdout, "Invalid input, enter again.\n" );
					fflush( stdin );
					continue;
				}
				break;
			}
			if ( exiting )
			{	break;	}

			if ( xFrom <= 0 || xFrom > BOARD_SIZE )
			{
				fprintf( stdout, "Invalid x coordinate, enter again.\n" );
				fflush( stdin );
				continue;
			}
			if ( yFrom <= 0 || yFrom > BOARD_SIZE )
			{
				fprintf( stdout, "Invalid y coordinate, enter again.\n" );
				fflush( stdin );
				continue;
			}
			xFrom--;
			yFrom--;
			if ( board[xFrom][yFrom].getPlayer() != playerTurn )
			{
				fprintf( stdout, "Player does not control piece on that tile, enter again.\n" );
				fflush( stdin );
				continue;
			}

			// Check possible destination coordinates
			int validMoves[BOARD_SIZE][BOARD_SIZE] = {0};
			checkPossibleMoves( board, playerTurn, xFrom, yFrom, validMoves );

			// Get destination coordinates
			while ( true )
			{
				fflush( stdin );

				// print board with destination options highlighted
				printMoveBoard( board, playerTurn, xFrom, yFrom, validMoves );
				if ( playerTurn == 0 )
				{
					fprintf( stdout, "White's move. Where would you like to move? (type 'back' to go back).\n" );
				}
				else if ( playerTurn == 1 )
				{
					fprintf( stdout, "Black's move. Where would you like to move? (type 'back' to go back).\n" );
				}

				std::getline( std::cin, input );
				if ( input == "exit" )
				{
					fprintf( stdout, "Exiting game.\n" );
					inputFinished = true;
					fflush(stdin);
					exiting = true;
					break;
				}
				else if ( input == "back" )
				{
					fprintf( stdout, "Going back.\n" );
					fflush(stdin);
					goingBack = true;
					break;
				}

				// process input
				std::stringstream ss(input);
				if (!( ss >> xTo >> yTo ))
				{
					fprintf( stdout, "Invalid input, enter again.\n" );
					fflush( stdin );
					continue;
				}
				if ( xTo <= 0 || xTo > BOARD_SIZE )
				{
					fprintf( stdout, "Invalid x coordinate, enter again.\n" );
					fflush( stdin );
					continue;
				}
				if ( yTo <= 0 || yTo > BOARD_SIZE )
				{
					fprintf( stdout, "Invalid y coordinate, enter again.\n" );
					fflush( stdin );
					continue;
				}
				xTo--;
				yTo--;
				if ( !validMoves[xTo][yTo] )
				{
					fprintf( stdout, "Piece can't move there, enter again.\n" );
					fflush( stdin );
					continue;
				}
				break;
			}
			if ( exiting )
			{	break;	}
			if ( goingBack )
			{	continue;	}

			inputFinished = true;
		}

		if ( exiting )
		{	break;	}

		// move piece
		board[xFrom][yFrom].getPiece()->move( xTo, yTo );

		// check for gameover
		for ( int i = 0; i < 32; i++ )
		{
			if ( pieces[i].getType() == piece_p[5] && !( pieces[i].isAlive() ) )
			{
				gameOver = true;
				continue;
			}
		}

		playerTurn = ( playerTurn + 1 ) % 2;	// toggle player turn
	}

	fprintf( stdout, "Game over. " );
	if ( playerTurn == 0 )
	{
		fprintf( stdout, "White wins!\n" );
	}
	else
	{
		fprintf( stdout, "Black wins!\n" );
	}

	// clear memory
	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		delete[] board[i];
	}
	delete[] board;
	board = nullptr;

	delete[] pieces;
	pieces = nullptr;

	return 0;
}


void printBoard( Tile** boardArray, int playerTurn )
{
	// draw the board to the buffer
	std::string image[BOARD_IMAGE_HEIGHT] = { "" };
	generateBoardImage( image );

	// print numbers to the border
	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		int x = BOARD_IMAGE_PADDING_X + BOARD_IMAGE_TOP_LABEL_OFFSET + i * ( BOARD_TILE_WIDTH + 1 );
		int y = 2*BOARD_IMAGE_PADDING_Y +  i * ( BOARD_TILE_HEIGHT + 1 );
		
		char xCharacter = 97 + i;
		char yCharacter = 49 + i;
		image[0][x] = xCharacter;
		image[BOARD_IMAGE_HEIGHT - BOARD_IMAGE_PADDING_Y][x] = xCharacter;
		image[y][BOARD_IMAGE_PADDING_X-1] = yCharacter;
		image[y][BOARD_IMAGE_PADDING_X + BOARD_SIZE * ( BOARD_TILE_WIDTH + 1 ) + 1] = yCharacter;
	}

	// print piece owners to buffer
	for ( int y = 0; y < BOARD_SIZE; y++ )
	{
		for ( int x = 0; x < BOARD_SIZE; x++ )
		{
			if ( boardArray[x][y].getPlayer() == -1 )
			{
				continue;
			}
			
			int stringRow = BOARD_IMAGE_PADDING_Y + 1 + y * ( BOARD_TILE_HEIGHT + 1);
			int stringColumn = BOARD_IMAGE_PADDING_X + 1 + x * ( BOARD_TILE_WIDTH + 1 ) + 1;
			if ( boardArray[x][y].getPlayer() == 0 )
			{
				image[stringRow].replace( stringColumn, 5, "White" );
			}
			else if ( boardArray[x][y].getPlayer() == 1 )
			{
				image[stringRow].replace( stringColumn, 5, "Black" );
			}
		}
	}


	// print piece types to buffer
	for ( int y = 0; y < BOARD_SIZE; y++ )
	{
		for ( int x = 0; x < BOARD_SIZE; x++ )
		{
			if ( boardArray[x][y].getPlayer() == -1 )
			{
				continue;
			}
			
			std::string typeName = boardArray[x][y].getPieceType()->getName();
			int stringRow = BOARD_IMAGE_PADDING_Y + 1 + y * ( BOARD_TILE_HEIGHT + 1) + 1;
			int stringColumn = BOARD_IMAGE_PADDING_X + 1 + x * ( BOARD_TILE_WIDTH + 1 ) + BOARD_TILE_WIDTH - typeName.length();
			image[stringRow].replace( stringColumn, typeName.length(), typeName );
		}
	}

	// print buffer to screen
	printCharArray( image, BOARD_IMAGE_HEIGHT, ( playerTurn == 0 ) );
}

void printMoveBoard( Tile** boardArray, int playerTurn, int xFrom, int yFrom, int movePossibilities[BOARD_SIZE][BOARD_SIZE] )
{
	// draw the board to the buffer
	std::string image[BOARD_IMAGE_HEIGHT] = { "" };
	generateBoardImage( image );

	// print numbers to the border
	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		int x = BOARD_IMAGE_PADDING_X + BOARD_IMAGE_TOP_LABEL_OFFSET + i * ( BOARD_TILE_WIDTH + 1 );
		int y = 2*BOARD_IMAGE_PADDING_Y +  i * ( BOARD_TILE_HEIGHT + 1 );
		
		char xCharacter = 97 + i;
		char yCharacter = 49 + i;
		image[0][x] = xCharacter;
		image[BOARD_IMAGE_HEIGHT - BOARD_IMAGE_PADDING_Y][x] = xCharacter;
		image[y][BOARD_IMAGE_PADDING_X-1] = yCharacter;
		image[y][BOARD_IMAGE_PADDING_X + BOARD_SIZE * ( BOARD_TILE_WIDTH + 1 ) + 1] = yCharacter;
	}

	// print highlighted tiles to buffer
	for ( int y = 0; y < BOARD_SIZE; y++ )
	{
		for ( int x = 0; x < BOARD_SIZE; x++ )
		{
			if ( movePossibilities[x][y] == 1 )
			{
				for ( int i = 0; i < BOARD_TILE_HEIGHT + 2; i++ )
				{
					int stringRow = BOARD_IMAGE_PADDING_Y + y * ( BOARD_TILE_HEIGHT + 1 ) + i;
					int stringColumn = BOARD_IMAGE_PADDING_X + x * ( BOARD_TILE_WIDTH + 1 );
					image[stringRow].replace( stringColumn, BOARD_TILE_WIDTH + 2, TILE_HIGHLIGHT_IMAGE[i] );
				}
			}
		}
	}

	// print selected tile highlight to buffer
	for ( int i = 0; i < BOARD_TILE_HEIGHT + 2; i++ )
	{
		int stringRow = BOARD_IMAGE_PADDING_Y + yFrom * ( BOARD_TILE_HEIGHT + 1 ) + i;
		int stringColumn = BOARD_IMAGE_PADDING_X + xFrom * ( BOARD_TILE_WIDTH + 1 );
		image[stringRow].replace( stringColumn, BOARD_TILE_WIDTH + 2, TILE_SELECT_IMAGE[i] );
	}

	// print piece owners to buffer
	for ( int y = 0; y < BOARD_SIZE; y++ )
	{
		for ( int x = 0; x < BOARD_SIZE; x++ )
		{
			if ( boardArray[x][y].getPlayer() == -1 )
			{
				continue;
			}
			
			int stringRow = BOARD_IMAGE_PADDING_Y + 1 + y * ( BOARD_TILE_HEIGHT + 1);
			int stringColumn = BOARD_IMAGE_PADDING_X + 1 + x * ( BOARD_TILE_WIDTH + 1 ) + 1;
			if ( boardArray[x][y].getPlayer() == 0 )
			{
				image[stringRow].replace( stringColumn, 5, "White" );
			}
			else if ( boardArray[x][y].getPlayer() == 1 )
			{
				image[stringRow].replace( stringColumn, 5, "Black" );
			}
		}
	}


	// print piece types to buffer
	for ( int y = 0; y < BOARD_SIZE; y++ )
	{
		for ( int x = 0; x < BOARD_SIZE; x++ )
		{
			if ( boardArray[x][y].getPlayer() == -1 )
			{
				continue;
			}
			
			std::string typeName = boardArray[x][y].getPieceType()->getName();
			int stringRow = BOARD_IMAGE_PADDING_Y + 1 + y * ( BOARD_TILE_HEIGHT + 1) + 1;
			int stringColumn = BOARD_IMAGE_PADDING_X + 1 + x * ( BOARD_TILE_WIDTH + 1 ) + BOARD_TILE_WIDTH - typeName.length();
			image[stringRow].replace( stringColumn, typeName.length(), typeName );
		}
	}

	// print buffer to screen
	printCharArray( image, BOARD_IMAGE_HEIGHT, ( playerTurn == 0 ) );
}

void generateBoardImage( std::string boardImage[BOARD_IMAGE_HEIGHT] )
{
	for ( int i = 0; i < BOARD_IMAGE_HEIGHT; i++ )
	{
		boardImage[i] = "";
	}

	for ( int row = 0; row < BOARD_IMAGE_HEIGHT; row++ )
	{
		while ( boardImage[row].length() < BOARD_IMAGE_WIDTH )
		{
			boardImage[row] = boardImage[row] + " ";
		}

		std::string topBorder = "+";
		for ( int tile = 0; tile < BOARD_SIZE; tile++ )
		{
			for ( int space = 0; space < BOARD_TILE_WIDTH; space++ )
			{
				topBorder = topBorder + "-";
			}
			topBorder = topBorder + "+";
		}

		if ( row == BOARD_IMAGE_PADDING_Y || row == BOARD_IMAGE_HEIGHT - BOARD_IMAGE_PADDING_Y - 1 )
		{
			boardImage[row].replace( BOARD_IMAGE_PADDING_X, topBorder.length(), topBorder );
			continue;
		}
		
		if ( row > BOARD_IMAGE_PADDING_Y && row < BOARD_IMAGE_HEIGHT - BOARD_IMAGE_PADDING_Y - 1 )
		{
			boardImage[row].replace( BOARD_IMAGE_PADDING_X, 1, "|" );
			boardImage[row].replace( BOARD_IMAGE_WIDTH - BOARD_IMAGE_PADDING_X - 1, 1, "|" );
		}

		if ( ( row - BOARD_IMAGE_PADDING_Y ) % ( BOARD_TILE_HEIGHT + 1 ) == 0 )
		{
			for ( int column = BOARD_IMAGE_PADDING_X; column < BOARD_IMAGE_WIDTH - BOARD_IMAGE_PADDING_X - 1; column += BOARD_TILE_WIDTH + 1 )
			{
				boardImage[row].replace( column, 1, "+" );
			}
		}
	}
}

void checkPossibleMoves( Tile** board, int playerTurn, int xFrom, int yFrom, int outputMoveset[BOARD_SIZE][BOARD_SIZE] )
{
	int possibleMoves[BOARD_SIZE][BOARD_SIZE] = {0};
	board[xFrom][yFrom].getPiece()->getPossibleMoves( possibleMoves );

	bool canMovePast[BOARD_SIZE][BOARD_SIZE] = { false };
	canMovePast[xFrom][yFrom] = true;

	bool checked[BOARD_SIZE][BOARD_SIZE] = { false };

	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		for ( int j = 0; j < BOARD_SIZE; j++ )
		{
			outputMoveset[i][j] = 0;
		}
	}


	if ( board[xFrom][yFrom].getPieceType()->checkJump() )
	{
		// check possible moves
		for ( int i = 0; i < BOARD_SIZE; i++ )
		{
			for ( int j = 0; j < BOARD_SIZE; j++ )
			{
				// check ownership of destination
				if ( possibleMoves[j][i] == 1 && ( board[j][i].getPlayer() != playerTurn || board[j][i].getPlayer() == -1 ) )
				{
					outputMoveset[j][i] = 1;
				}
			}
		}
		return;
	}
	else // can't jump
	{
		// check possible destination tiles
		for ( int i = 0; i < BOARD_SIZE; i++ )
		{
			for ( int j = 0; j < BOARD_SIZE; j++ )
			{
				// check ownership of destination
				if ( possibleMoves[j][i] == 1 && board[j][i].getPlayer() == playerTurn )
				{
					possibleMoves[j][i] = 0;
				}
			}
		}
		
		// check whether destination tiles are reachable
		for ( int rad = 1; rad < BOARD_SIZE-1; rad++)
		{
			for ( int y = yFrom - rad; y <= yFrom + rad; y++ )
			{
				for ( int x = xFrom - rad; x <= xFrom + rad; x++ )
				{
					// check for out of bounds
					if ( x < 0 || x >= BOARD_SIZE )
					{
						continue;
					}
					if ( y < 0 || y >= BOARD_SIZE )
					{
						continue;
					}

					if ( checked[x][y] )
					{
						continue;
					}
					checked[x][y] = true;

					if ( possibleMoves[x][y] == 0 )
					{
						continue;
					}

					// compile list of tiles that could provide a path to x, y
					int checkList[3][2] = {0};
					int checkListLength = 0;
					bool canReach = false;

					for ( int dy = -1; dy < 2; dy++ )
					{
						for ( int dx = -1; dx < 2; dx++ )
						{
							if ( getDistance( x+dx, y+dy, xFrom, yFrom ) < getDistance( x, y, xFrom, yFrom ) )
							{
								checkList[checkListLength][0] = x + dx;
								checkList[checkListLength][1] = y + dy;
								checkListLength++;
							}
						}
					}

					if ( DEBUG )
					{
						fprintf( stdout, "radius: %d\n", rad );
						fprintf( stdout, "checking goto tile x: %d, y: %d\n", x, y );
						fprintf( stdout, "checklist:\n" );
						for ( int a = 0; a < checkListLength; a++ )
						{
							fprintf( stdout, "%d, %d\n", checkList[a][0], checkList[a][1] );
						}
					}

					for ( int j = 0; j < checkListLength; j++ )
					{
						if ( canMovePast[checkList[j][0]][checkList[j][1]] )
						{
							canReach = true;
							if ( DEBUG)
							{	fprintf( stdout, "success!\n\n" );	}
							break;
						}
					}

					if ( canReach && board[x][y].getPlayer() != playerTurn )
					{
						if ( possibleMoves[x][y] == 1 ) // if piece can move or attack target tile
						{
							outputMoveset[x][y] = 1;
						}
						else if ( possibleMoves[x][y] == 2 && board[x][y].getPlayer() == -1 ) // if piece can move but not attack target tile
						{
							outputMoveset[x][y] = 1;
						}
						else if ( possibleMoves[x][y] == 3 && board[x][y].getPlayer() != -1 ) // if piece can only attack target tile
						{
							outputMoveset[x][y] = 1;
						}
					}


					if ( canReach && !(board[x][y].isOccupied()) )
					{
						canMovePast[x][y] = true;
					}
				}
			}
		}
	}
	
	if ( DEBUG )
	{
		fprintf( stdout, "within movement range:\n" );
		printArray( possibleMoves, BOARD_SIZE, BOARD_SIZE );
		fprintf( stdout, "valid destinations:\n" );
		printArray( outputMoveset, BOARD_SIZE, BOARD_SIZE );
		fprintf( stdout, "passable tiles:\n" );
		printBoolArray( canMovePast );
	}
}

int getDistance( int x1, int y1, int x2, int y2 )
{
	return abs( x1 - x2 ) + abs( y1 - y2 );
}

void printArray( int inArray[BOARD_SIZE][BOARD_SIZE], int xSize, int ySize )
{
	for ( int i = 0; i < ySize; i++ )
	{
		for ( int j = 0; j < xSize; j++ )
		{
			fprintf( stdout, "%d ", inArray[j][i] );
		}
		fprintf( stdout, "\n" );
	}
	fprintf( stdout, "\n" );
}

void printCharArray( std::string inArray[], int ySize, bool reverseY )
{
	if ( reverseY )
	{
		for ( int i = ySize-1; i >= 0; i-- )
		{
			std::cout << inArray[i] << "\n";
		}
	}
	else
	{
		for ( int i = 0; i < ySize; i++ )
		{
			std::cout << inArray[i] << "\n";
		}
	}
}

void printBoolArray( bool inArray[BOARD_SIZE][BOARD_SIZE] )
{
	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		for ( int j = 0; j < BOARD_SIZE; j++ )
		{
			if ( inArray[j][i] )
			{
				fprintf( stdout, "X " );
			}
			else
			{
				fprintf( stdout, ". " );
			}
		}
		fprintf( stdout, "\n" );
	}
	fprintf( stdout, "\n" );
}

void printBoard_old( Tile** boardArray, int playerTurn )
{
	PieceClass* type = nullptr;
	int owner = -1;
	std::string ownerName = "";
	std::string typeName = "";
	int rowStart = 0;
	int rowIncrement = 1;

	if ( playerTurn == 0 )
	{
		rowStart = BOARD_SIZE-1;
		rowIncrement = -1;
	}

	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		fprintf( stdout, " %5d ", i );
	}
	fprintf( stdout, "\n" );
	fprintf( stdout, "%3s+------+------+------+------+------+------+------+------+\n", " " );

	for ( int i = rowStart; i < BOARD_SIZE && i >= 0; i += rowIncrement )
	{
		// printing player owner
		fprintf( stdout, "%3d|", i );
		for (int j = 0; j < BOARD_SIZE; j++ )
		{
			owner = boardArray[j][i].getPlayer();
			if ( owner == 0 )
			{
				ownerName = "White";
			} 
			else if ( owner == 1 )
			{
				ownerName = "Black";
			}
			else if ( owner == -1 )
			{
				ownerName = "";
			}

			// fprintf( stdout, "%6s", ownerName );
			std::cout.width(6);
			std::cout << ownerName;
			if ( j < 7 )
			{	fprintf( stdout, " " );	}
			else
			{	fprintf( stdout, "|%d\n", i );	}

		}

		// printing piece type
		fprintf( stdout, "%3s|", " " );
		for (int j = 0; j < BOARD_SIZE; j++ )
		{
			type = boardArray[j][i].getPieceType();
			if ( type == NULL )
			{
				typeName = "";
			}
			else
			{
				typeName = type->getName();
			}
			
			// fprintf( stdout, "%6s", typeName);
			std::cout.width(6);
			std::cout << typeName;

			if ( j < 7 )
			{	fprintf( stdout, " " );	}
			else
			{	fprintf( stdout, "|\n" );	}
			type = nullptr;
		}

		if ( i + rowIncrement < BOARD_SIZE && i + rowIncrement >= 0 )
		{	
			fprintf( stdout, "%3s+", " " );
			for ( int j = 0; j < 8; j++ )
			{
				fprintf( stdout, "      +" );
			}
		}
		else
		{	
			fprintf( stdout, "%3s+", " " );
			for ( int j = 0; j < 8; j++ )
			{
				fprintf( stdout, "------+" );
			}
			fprintf( stdout, "\n" );

			for ( int j = 0; j < 8; j++ )
			{
				fprintf( stdout, " %5d ", j );
			}
		}
		fprintf( stdout, "\n" );
	}
}

void printMoveBoard_old( Tile** boardArray, int playerTurn, int xFrom, int yFrom, int movePossibilities[BOARD_SIZE][BOARD_SIZE] )
{
	PieceClass* type = nullptr;
	int owner = -1;
	std::string ownerName = "";
	std::string typeName = "";
	int rowStart = 0;
	int rowIncrement = 1;
	int moveSet[BOARD_SIZE][BOARD_SIZE] = {0};
	
	if ( playerTurn == 0 )
	{
		rowStart = BOARD_SIZE-1;
		rowIncrement = -1;
	}

	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		fprintf( stdout, " %5d ", i );
	}
	fprintf( stdout, "\n" );

	// print top horizontal
	fprintf( stdout, "%3s+", " " );
	for ( int j = 0; j < BOARD_SIZE; j++ )
	{
		if ( yFrom == rowStart && j == rowStart )
		{
			fprintf( stdout, "~~~~~~+" );
		}
		else
		{
			fprintf( stdout, "------+" );
		}
	}
	fprintf( stdout, "\n" );

	for ( int i = rowStart; i < BOARD_SIZE && i >= 0; i += rowIncrement )
	{
		// printing player owner
		fprintf( stdout, "%3d|", i );
		for (int j = 0; j < BOARD_SIZE; j++ )
		{
			owner = boardArray[j][i].getPlayer();
			if ( owner == 0 )
			{
				ownerName = "White";
			} 
			else if ( owner == 1 )
			{
				ownerName = "Black";
			}
			else if ( owner == -1 )
			{
				ownerName = "";
			}

			std::cout.width(6);
			std::cout << ownerName;

			// print vertical lines
			if ( i == yFrom && ( j == xFrom || j == xFrom - 1 ) )
			{	
				fprintf( stdout, "/" );
				if ( j >= 7 )
				{	fprintf( stdout, "%d\n", i );	}
			}
			else if	( j >= 7 )
			{	fprintf( stdout, "|%d\n", i );	}
			else if ( movePossibilities[j][i] == 1 || movePossibilities[j+1][i] == 1 )
			{	fprintf( stdout, "|" );	}
			else
			{	fprintf( stdout, " " );	}

		}

		// printing piece type
		fprintf( stdout, "%3s|", " " );
		for (int j = 0; j < BOARD_SIZE; j++ )
		{
			type = boardArray[j][i].getPieceType();
			if ( type == NULL )
			{
				typeName = "";
			}
			else
			{
				typeName = type->getName();
			}
			
			// fprintf( stdout, "%6s", typeName);
			std::cout.width(6);
			std::cout << typeName;

			// print vertical lines
			if ( i == yFrom && ( j == xFrom || j == xFrom - 1 ) )
			{	
				fprintf( stdout, "/" );
				if ( j >= 7 )
				{	fprintf( stdout, "\n" );	}
			}
			else if	( j >= 7 )
			{	fprintf( stdout, "|\n" );	}
			else if ( movePossibilities[j][i] == 1 || movePossibilities[j+1][i] == 1 )
			{	fprintf( stdout, "|" );	}
			else
			{	fprintf( stdout, " " );	}
			type = nullptr;
		}

		// print horizontal lines
		fprintf( stdout, "%3s+", " " );
		for ( int j = 0; j < 8; j++ )
		{
			if ( j == xFrom && ( i == yFrom || i + rowIncrement == yFrom ) )
			{
				fprintf( stdout, "~~~~~~+");
			}
			else if ( !( i + rowIncrement < BOARD_SIZE && i + rowIncrement >= 0 ) ) // if on the edge of the board
			{
				fprintf( stdout, "------+");
			}
			else if ( movePossibilities[j][i] == 1 || movePossibilities[j][i+rowIncrement] == 1 )
			{
				fprintf( stdout, "------+");
			}
			else
			{
				fprintf( stdout, "      +" );
			}
		}
		fprintf( stdout, "\n" );

		if ( i + rowIncrement >= BOARD_SIZE || i + rowIncrement < 0 )
		{
			for ( int j = 0; j < 8; j++ )
			{
				fprintf( stdout, " %5d ", j );
			}
			fprintf( stdout, "\n" );
		}
	}
}
