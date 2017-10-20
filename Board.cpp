// Board.cpp

#pragma once
#include "Board.h"
#include "Pieces.h"
#include "Types.h"

class PieceClass;

Tile::Tile()
{
	this->piece_p = nullptr;
	this->hasPiece = false;
}

PieceClass* Tile::getPieceType()
{
	if ( hasPiece )
	{
		return this->piece_p->getType();
	}
	else
	{
		return nullptr;
	}
}

int Tile::getPlayer()
{
	if ( this->hasPiece )
	{
		return piece_p->getPlayer();
	}
	else
	{
		return -1;
	}
}

void Tile::changePiece( Piece* newPiece_p )
{
	this->piece_p = newPiece_p;
	this->hasPiece = true;
}

Piece* Tile::getPiece()
{
	return piece_p;
}

bool Tile::isOccupied()
{
	return hasPiece;
}

void Tile::removePiece()
{
	this->hasPiece = false;
	this->piece_p = nullptr;
}
