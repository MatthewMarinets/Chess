#pragma once
#include "Pieces.h"
#include "Types.h"
// Board.h
#pragma warning(disable:4996)

class PieceClass;
class Piece;

class Tile
{
	private:
		Piece* piece_p;
		bool hasPiece;

	public:
		Tile();

		void changePiece( Piece* newPiece_p );

		void removePiece();

		PieceClass* getPieceType();

		Piece* getPiece();

		int getPlayer();

		bool isOccupied();

};

#include "Board.cpp"
