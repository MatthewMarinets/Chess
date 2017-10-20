// Types.cpp

#pragma once
#include <string>
#include "Types.h"
#include "Pieces.h"

PieceClass::PieceClass( std::string typeName, std::string fileName, PieceClass* upgradeClass, int upgradeMin, int upgradeMax )
	: upgradeClass( upgradeClass ),
	upgradeRequirementMin( upgradeMin ),
	upgradeRequirementMax( upgradeMax )
{
	this->canJump = false;

	name = typeName;
	std::stringstream buffer;
	std::ifstream inputFile( fileName );

	if ( !inputFile.is_open() )
	{
		std::cerr << "Failed to open file for " << typeName << "\n";
	}
	else
	{
		buffer << inputFile.rdbuf();

		for ( int i = 0; i < 15; i++ )
		{
			for ( int j = 0; j < 15; j++ )
			{
				if ( !( buffer >> moveArray[j][i] ) )
				{
					std::cerr << "Failed to read moveset for " << name << " on line "<< i << "\n";
				}
				if ( moveArray[j][i] > 3 || moveArray[j][i] < 0 )
				{
					std::cerr << "Invalid character in moveset for " << name << " on line " << i << "\n";
				}
			}
		}
		std::string tag = "";
		buffer >> tag;
		if ( tag == "canJump" )
		{
			this->canJump = true;
		}

		inputFile.close();
	}
}

void PieceClass::getMoveSet( int moveArray[15][15] )
{
	for ( int i = 0; i < 15; i++ )
	{
		for ( int j = 0; j < 15; j++ )
		{
			moveArray[j][i] = this->moveArray[j][i];
		}
	}
}

