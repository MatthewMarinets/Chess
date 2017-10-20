// Types.h
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Constants.h"
#include "Pieces.h"
#pragma warning(disable:4996)


class PieceClass
{
	private:
		PieceClass* upgradeClass;
		int upgradeRequirementMin;
		int upgradeRequirementMax;
		int moveArray[15][15];
		bool canJump;
		std::string name;

		////// MOVE ARRAY FORMAT //////
		// 0: cannot move to
		// 1: can move or attack
		// 2: can move but not attack
		// 3: can only move to tile in an attack

	public:

		PieceClass( std::string typeName, std::string fileName, PieceClass* upgradeClass = nullptr, int upgradeMin = 0, int upgradeMax = BOARD_SIZE-1 );

		void getMoveSet( int moveArray[15][15] );

		std::string getName()
		{
			return name;
		}

		bool checkJump()
		{
			return this->canJump;
		}

		PieceClass* getUpgradeType()
		{
			return this->upgradeClass;
		}

		int getUpgradeMin()
		{
			return this->upgradeRequirementMin;
		}

		int getUpgradeMax()
		{
			return this->upgradeRequirementMax;
		}
};

#include "Types.cpp"
