#include "GameStateHandler.h"

CGameStateHandler::CGameStateHandler() {
	iterator = 0;
	prevTime = 1;
	predictionTime = 240;
}

int CGameStateHandler::getNextTime()const{
	if (!timerQueue.empty())
		return timerQueue.front();
	return INT_MAX;
}

void CGameStateHandler::setPredictionTime(int predT) {
	predictionTime = predT;
}

void CGameStateHandler::popQueue() {
	if (!timerQueue.empty())
		timerQueue.pop();
}

int CGameStateHandler::getIterator()const{
	return iterator;
}

void CGameStateHandler::addTime(const int time) {
	timerQueue.push(time);
}

void  CGameStateHandler::updateCurrentGameState(COpponentModelling &model){
	
	for (auto it : model.getOpponentModel()->getInputUnitVector())
		currentGameState[it] = model.getOpponentModel()->getMapOfAllUnits().at(it).size();

	// Lurker and Tank are special cases in BWAPI::UnitTypes
	// We want to save number of tanks/lurkers in one variable and not two(TankMode/SiegeMode, LurkerEgg/Lurker)
	currentGameState[BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode] = model.getOpponentModel()->getMapOfAllUnits().at(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode).size();
	currentGameState[BWAPI::UnitTypes::Zerg_Lurker_Egg] = model.getOpponentModel()->getMapOfAllUnits().at(BWAPI::UnitTypes::Zerg_Lurker_Egg).size();

	currentGameState[SUPPLY] = model.getOpponentModel()->getSupply();
}

void CGameStateHandler::addNewGameState() {
	
	int currentTime = BWAPI::Broodwar->elapsedTime();

	// minimum delay between two game states can be saved
	if (currentTime < prevTime)
		return;

	//prevTime = currentTime;
	addTime(currentTime + predictionTime);
	inputGameState.push_back(currentGameState);
	outputGameState.push_back(currentGameState);
}

void CGameStateHandler::addUnitOutputGameState(BWAPI::Unit unit, COpponentModelling & model) {

	if (unit->getPlayer() != model.enemyP() || unit->isHallucination())
		return;

	for (unsigned int i = iterator; i < outputGameState.size(); i++)
	{
		if (outputGameState.at(i).at(SUPPLY) + unit->getType().supplyRequired() > 400)
			continue;

		outputGameState.at(i)[(unit->getType().getID())];
		outputGameState.at(i)[SUPPLY];

		outputGameState.at(i)[(unit->getType().getID())] = outputGameState.at(i).at(unit->getType().getID()) + 1;
		outputGameState.at(i)[SUPPLY] = outputGameState.at(i).at(SUPPLY) + unit->getType().supplyRequired();

		if (unit->getType() == BWAPI::UnitTypes::Zerg_Lurker_Egg)
		{
			BWAPI::UnitType tmp(BWAPI::UnitTypes::Zerg_Hydralisk);
			outputGameState.at(i)[SUPPLY] = outputGameState.at(i).at(SUPPLY) - tmp.supplyRequired();
			outputGameState.at(i)[BWAPI::UnitTypes::Zerg_Hydralisk] = outputGameState.at(i)[BWAPI::UnitTypes::Zerg_Hydralisk] - 1;
		}
		
		if (unit->getType() == BWAPI::UnitTypes::Protoss_Archon)
		{
			BWAPI::UnitType tmp(BWAPI::UnitTypes::Protoss_High_Templar);
			outputGameState.at(i)[SUPPLY] = outputGameState.at(i).at(SUPPLY) - tmp.supplyRequired();
			outputGameState.at(i)[BWAPI::UnitTypes::Protoss_High_Templar] = outputGameState.at(i)[BWAPI::UnitTypes::Protoss_High_Templar] - 2;
		}
		
		if (unit->getType() == BWAPI::UnitTypes::Protoss_Dark_Archon)
		{
			BWAPI::UnitType tmp(BWAPI::UnitTypes::Protoss_Dark_Templar);
			outputGameState.at(i)[SUPPLY] = outputGameState.at(i).at(SUPPLY) - tmp.supplyRequired();
			outputGameState.at(i)[BWAPI::UnitTypes::Protoss_Dark_Templar] = outputGameState.at(i)[BWAPI::UnitTypes::Protoss_Dark_Templar] - 2;
		}
		
		if (unit->getType() == BWAPI::UnitTypes::Zerg_Cocoon)
		{
			BWAPI::UnitType tmp(BWAPI::UnitTypes::Zerg_Mutalisk);
			outputGameState.at(i)[SUPPLY] = outputGameState.at(i).at(SUPPLY) - tmp.supplyRequired();
			outputGameState.at(i)[BWAPI::UnitTypes::Zerg_Mutalisk] = outputGameState.at(i)[BWAPI::UnitTypes::Zerg_Mutalisk] - 1;

		}

	}
}

vector <map <int, int> > CGameStateHandler::getInputGameStateVector() {
	return inputGameState;
}

vector <map <int, int> > CGameStateHandler::getOutputGameStateVector() {
	return outputGameState;
}

void CGameStateHandler::saveBothIOGameStates() {
	++iterator;
	popQueue();
}

void CGameStateHandler::setPlayer(BWAPI::Player o, BWAPI::Player p, std::string mpName) {
	currentPlayer = p;
	opponentPlayer = o;
	mapName = mpName;
}
