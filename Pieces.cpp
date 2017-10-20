// Pieces.cpp

#pragma once
#include "Pieces.h"
#include "Board.h"

class Tile;

Piece::Piece( const Piece &obj )
	: type( obj.type ), xPosition( obj.xPosition ), yPosition( obj.yPosition ), board_p( obj.board_p ), player( obj.player )
{
	this->alive = true;
}

Piece::Piece( PieceClass* pieceType, int position_x, int position_y, int player, Tile** board ) 
	: type( pieceType ), xPosition( position_x ), yPosition( position_y ), board_p( board ), player(player)
{
	// board[xPosition][yPosition].changePiece( this );
	this->alive = true;
}

void Piece::updateBoard( Tile** board )
{
	board[this->xPosition][this->yPosition].changePiece( this );
}

void Piece::move( int x, int y )
{
	board_p[xPosition][yPosition].removePiece();

	if ( board_p[x][y].getPiece() )
	{
		board_p[x][y].getPiece()->capture();
	}
	this->xPosition = x;
	this->yPosition = y;
	board_p[x][y].changePiece( this );
	this->updatePieceType();
}

int Piece::getPlayer()
{	
	return player;
}

Piece::Piece()
{
	this->type = nullptr;
	this->player = -1;
	this->xPosition = 0;
	this->yPosition = 0;
	this->board_p = nullptr;
	this->alive = true;
}


void Piece::getPossibleMoves( int boardMoves[BOARD_SIZE][BOARD_SIZE] )
{
	int x = this->xPosition;
	int y = this->yPosition;
	int moveArray[15][15] = { 0 };
	this->type->getMoveSet( moveArray );

	for ( int i = 0; i < BOARD_SIZE; i++ )
	{
		for ( int j = 0; j < BOARD_SIZE; j++ )
		{
			boardMoves[j][i] = moveArray[7-x+j][7-y+i];
		}
	}
}

void Piece::updatePieceType()
{
	if ( this->yPosition >= this->type->getUpgradeMin() && this->yPosition <= this->type->getUpgradeMax() )
	{
		if ( type->getUpgradeType() != nullptr )
		{
			this->type = type->getUpgradeType();
		}
	}
}

bool Piece::isAlive()
{
	return this->alive;
}

void Piece::capture()
{
	this->alive = false;
}