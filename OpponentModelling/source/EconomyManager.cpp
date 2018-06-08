#include "EconomyManager.h"

using namespace OpponentModelling;

CEconomyManager::CEconomyManager() {
	
}

void CEconomyManager::unitRemoved(CObjectInfo *unit) {
	MineralsLost += unit->UnitType.mineralPrice();
	GasLost += unit->UnitType.gasPrice();
}

int CEconomyManager::getMineralsLost()const {
	return MineralsLost;
}

int CEconomyManager::getGasLost()const {
	return GasLost;
}