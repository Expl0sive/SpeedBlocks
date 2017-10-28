#ifndef TESTFIELD_H
#define TESTFIELD_H

#include "gameField.h"

class Resources;

struct MoveInfo {
	uint8_t posX, rot;
	std::vector<uint8_t> path;
	bool use_path;
	int32_t score;

	void clear();
};

class TestField : public BasicField {
public:
	TestField(Resources& _resources);

	std::array<std::array<sf::Uint8, 10>, 22> backupField, holeMap;
	MoveInfo move, finesseMove;

	std::array<double, 10> weights;
	std::vector<uint8_t> test_path;

	// Scoring values
	std::array<uint8_t, 10> heights;
	uint8_t totalHeight;
	uint8_t openHoles, closedHoles, openHolesBeforePiece, closedHolesBeforePiece;
	double onTopOfHoles;
	uint8_t bumpiness;
	uint8_t totalLines, totalLines_first;
	uint8_t well2Wide;
	uint8_t well1Wide;
	uint8_t highestPoint;
	bool pieceNextToWall;

	uint8_t holeCount;

	sf::Vector2i well2Pos;

	void backup();
	void restore();

	void removePiece();
	void setPiece(int piece);

	void checkForHoles(int y, int x);
	void calcOnTopOfHoles();
	void calcHolesBeforePiece();
	void calcHeightsAndHoles();
	void calcOpenHoles();
	void findOpenHoles(uint8_t x, uint8_t y);
	void calcBumpiness();
	void calc2Wide();
	void calc1Wide();
	void calcScore();
	int32_t checkScore();

	void calcMove(int addTotalLines=0);
	void findBestMove(int addTotalLines=0);
	void tryAllMoves(TestField& field, uint8_t nextpiece);
	void findNextMove(TestField& field, uint8_t nextpiece);
	bool nextToWall();
	void checkNextMove(TestField& field, uint8_t nextpiece);
	void findFinesseMove(int addTotalLines=0);
	void useFinesseMove(int32_t newscore);
	bool setFinesseMove();
	void tryAllFinesseMoves(TestField& field, uint8_t nextpiece);
	bool finesseIsPossible();
	bool tryLeft(bool clearTestPath=false);
	bool tryRight(bool clearTestPath=false);
	bool tryUp(int turnVal);
	bool reverseWallkick();
	bool doWallKick();
	void r180KeepPos();
	uint8_t moveUp();
	bool restorePiece(basePieces p, bool returnValue);
};

#endif