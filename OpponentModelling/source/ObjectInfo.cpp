#include "ObjectInfo.h"

using namespace OpponentModelling;

int IDUnitCounter::counter = -1;

CObjectInfo::CObjectInfo()
{
	ID			= 0;
	Health		= 0;
	Shields		= 0;
	Energy		= 0;
	Completed	= true;
	IsTraining	= false;
	IsMorphing	= false;
	isHalucination = false;
	Frame		= 0;
	
	
	Unit	 = nullptr;
	UnitType = BWAPI::UnitTypes::None;
	Position = BWAPI::Positions::None;
	TilePosition = BWAPI::TilePositions::None;
	Player	 = nullptr;
}

CObjectInfo::CObjectInfo(BWAPI::Unit unit)
{
	ID			= unit->getID();
	Health		= unit->getHitPoints();
	Shields		= unit->getShields();
	Energy		= unit->getEnergy();
	Completed	= unit->isCompleted();
	IsTraining	= unit->isTraining();
	IsMorphing	= unit->isMorphing();
	Frame		= BWAPI::Broodwar->getFrameCount();
	isHalucination = unit->isHallucination();
	
	Unit	 = unit;
	UnitType = unit->getType();
	Position = unit->getPosition();
	TilePosition = unit->getTilePosition();
	Player	 = unit->getPlayer();
}

void CObjectInfo::updateUnit(BWAPI::Unit unit) {
	Health = unit->getHitPoints();
	Shields = unit->getShields();
	Energy = unit->getEnergy();
	Completed = unit->isCompleted();
	IsTraining = unit->isTraining();
	IsMorphing = unit->isMorphing();
	Frame = BWAPI::Broodwar->getFrameCount();
	isHalucination = unit->isHallucination();

	Unit = unit;
	UnitType = unit->getType();
	Position = unit->getPosition();
	TilePosition = unit->getTilePosition();
	Player = unit->getPlayer();
}

CObjectInfo::CObjectInfo(BWAPI::UnitType unit, bool AddInAnyCase) {
	ID = getID(AddInAnyCase);
	Health = unit.maxHitPoints();
	Shields = unit.maxShields();
	Energy = unit.maxEnergy();
	Completed = true;
	IsTraining = false;
	IsMorphing = false;
	Frame = BWAPI::Broodwar->getFrameCount();
	isHalucination = false;

	Unit = nullptr;
	UnitType = unit;
	Position = BWAPI::Positions::Unknown;
	TilePosition = BWAPI::TilePositions::Unknown;
	Player = BWAPI::Broodwar->enemy();
}

const bool CObjectInfo::operator == (BWAPI::Unit unit) const
{
	return ID == unit->getID();
}

int CObjectInfo::getID(bool AddInAnyCase) {

	if (AddInAnyCase) {
		if (IDUnitCounter::getValue() % 2 == 0)
		{
			IDUnitCounter::getValueAndIncrease();
			return IDUnitCounter::getValueAndIncrease();
		}
		else {
			return IDUnitCounter::getValueAndIncrease();
		}
	}
	else
	{
		if (IDUnitCounter::getValue() % 2 == 0)
		{
			return IDUnitCounter::getValueAndIncrease();
		}
		else {
			IDUnitCounter::getValueAndIncrease();
			return IDUnitCounter::getValueAndIncrease();
		}
	}
}

