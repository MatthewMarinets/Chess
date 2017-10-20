// Pieces.h
#pragma once
#include "Constants.h"
#include "Board.h"
#include "Types.h"
#pragma warning(disable:4996)

class Tile;

class Piece
{
	private:
		PieceClass* type;
		int player;
		int xPosition;
		int yPosition;
		Tile** board_p;
		bool alive;

	public:
		Piece();

		Piece( const Piece &obj );

		void updateBoard( Tile** board );

		Piece( PieceClass* pieceType, int position_x, int position_y, int player, Tile** board );

		int getYPosition()
		{
			return this->yPosition;
		}

		int getXPosition()
		{
			return this->xPosition;
		}

		PieceClass* getType()
		{
			return this->type;
		}

		int getPlayer();

		void move( int x, int y );

		void getPossibleMoves( int boardMoves[BOARD_SIZE][BOARD_SIZE] );

		void updatePieceType();

		bool isAlive();

		void capture();
};

#include "Pieces.cpp"
