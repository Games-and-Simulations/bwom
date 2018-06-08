#include "OpponentModelling.h"

using namespace OpponentModelling;

COpponentModelling::COpponentModelling() {
	Opponent = new CPlayerModel();
	SelfGameModel = new CPlayerModel();
}

COpponentModelling::COpponentModelling(BWAPI::Player selfP, BWAPI::Player enemyP) {
	
	if (selfP->getRace() == BWAPI::Races::Zerg)
		SelfGameModel = new CPlayerZerg();
	else if (selfP->getRace() == BWAPI::Races::Terran)
		SelfGameModel = new CPlayerTerran();
	else if (selfP->getRace() == BWAPI::Races::Protoss)
		SelfGameModel = new CPlayerProtoss();
	else
		SelfGameModel = new CPlayerModel();

	if (enemyP->getRace() == BWAPI::Races::Zerg)
		Opponent = new CPlayerZerg();
	else if (enemyP->getRace() == BWAPI::Races::Terran)
		Opponent = new CPlayerTerran();
	else if (enemyP->getRace() == BWAPI::Races::Protoss)
		Opponent = new CPlayerProtoss();
	else
		Opponent = new CPlayerModel();

	enemy = enemyP;
	self = selfP;
}

COpponentModelling::~COpponentModelling() {

	if (Opponent != nullptr)
		delete Opponent;
	if (SelfGameModel != nullptr)
		delete SelfGameModel;
}

CPlayerModel *COpponentModelling::getOpponentModel() const {
	return Opponent;
}

CPlayerModel *COpponentModelling::getSelfModel() const {
	return SelfGameModel;
}

void COpponentModelling::updateUnit(BWAPI::Unit unit) {
	if (unit->getPlayer() == self)
		SelfGameModel->unitUpdate(unit);		 // Unit I own
	else if (unit->getPlayer() == enemy)
	{
		if (Opponent->isRandom())
		{
		if (Opponent != nullptr)
			delete Opponent;
		if (enemy->getRace() == BWAPI::Races::Zerg)
			Opponent = new CPlayerZerg();
		else if (enemy->getRace() == BWAPI::Races::Terran)
			Opponent = new CPlayerTerran();
		else if (enemy->getRace() == BWAPI::Races::Protoss)
			Opponent = new CPlayerProtoss();
		}
		Opponent->unitUpdate(unit); // Unit my opponent owns
	}
}

void COpponentModelling::removeUnit(BWAPI::Unit unit) {
	if (unit->getPlayer() == self)
		SelfGameModel->removeUnit(unit->getID());		 // Unit I own
	else if (unit->getPlayer() == enemy)
		Opponent->removeUnit(unit->getID()); // Unit my opponent owns
}

/* --------------- BWAPI BOT FUNCTIONS --------------- */
void COpponentModelling::onStart(BWAPI::Player self, BWAPI::Player enemy) {
	init(self, enemy);
}

void COpponentModelling::onEnd(bool isWinner) {

}

void COpponentModelling::onFrame() {
	for (auto it : BWAPI::Broodwar->getAllUnits())
		updateUnit(it);
}

void COpponentModelling::onUnitDiscover(BWAPI::Unit unit) {
	updateUnit(unit);
}
void COpponentModelling::onUnitShow(BWAPI::Unit unit) {
	updateUnit(unit);
}

void COpponentModelling::onUnitCreate(BWAPI::Unit unit) {
	updateUnit(unit);
}
void COpponentModelling::onUnitDestroy(BWAPI::Unit unit) {
	removeUnit(unit);
}
void COpponentModelling::onUnitMorph(BWAPI::Unit unit) {
	removeUnit(unit);
	updateUnit(unit);
}
void COpponentModelling::onUnitRenegade(BWAPI::Unit unit) {
	SelfGameModel->removeUnit(unit->getID());
	Opponent->removeUnit(unit->getID());
	updateUnit(unit);
}

void COpponentModelling::onUnitComplete(BWAPI::Unit unit) {
	updateUnit(unit);
}

/* --------------- BWAPI BOT FUNCTIONS --------------- */

void COpponentModelling::init(BWAPI::Player selfP, BWAPI::Player enemyP) {
	
	if (SelfGameModel != nullptr)
		delete SelfGameModel;

	if (Opponent != nullptr)
		delete Opponent;

	if (selfP->getRace() == BWAPI::Races::Zerg)
		SelfGameModel = new CPlayerZerg();
	else if (selfP->getRace() == BWAPI::Races::Terran)
		SelfGameModel = new CPlayerTerran();
	else if (selfP->getRace() == BWAPI::Races::Protoss)
		SelfGameModel = new CPlayerProtoss();
	else
		SelfGameModel = new CPlayerModel();

	if (enemyP->getRace() == BWAPI::Races::Zerg)
		Opponent = new CPlayerZerg();
	else if (enemyP->getRace() == BWAPI::Races::Terran)
		Opponent = new CPlayerTerran();
	else if (enemyP->getRace() == BWAPI::Races::Protoss)
		Opponent = new CPlayerProtoss();
	else
		Opponent = new CPlayerModel();

	enemy = enemyP;
	self = selfP;
	Opponent->init();
	SelfGameModel->init();
}

BWAPI::Player COpponentModelling::enemyP() const{
	return enemy;
}

CPlayerModel *COpponentModelling::PredictOpponentsGameState() {
	return NNForOpponentPrediction.predictOpponetGameState(Opponent);
}

