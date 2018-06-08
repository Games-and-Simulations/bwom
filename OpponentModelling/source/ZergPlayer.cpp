#include "ZergPlayer.h"

using namespace OpponentModelling;

CPlayerZerg::CPlayerZerg()
	:CPlayerModel()
{
	for (auto it : inputUnitVector)
		UnitsMap[it];
	randomOpponent = 0;
}

ObjectInfoVector CPlayerZerg::InherenceInitialInfo() {
	ObjectInfoVector inherenceUnits;
	inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hatchery, DONT_ADD_UNIT_ANY_CASE));

	for (int i = 0; i < 4; i++)
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Drone, ADD_UNIT_ANY_CASE));

	return inherenceUnits;
}

BWAPI::Race CPlayerZerg::getRace() const{
	return BWAPI::Races::Zerg;
}

ObjectInfoVector CPlayerZerg::InherenceAdditionalInfo(CObjectInfo *unitToBeAdded) {

	// Hatchery, Spawning pool, Evolution chamber, Creep colony, Sunken colony, Spore colony, Extractor,
	// Hydra den, Ultralisk caver, Greater spire, Defilers nest, Queens nest,
	// Zergling, Hydra, Lurker, Mutalisk, Queen, Ultralisk, Defiler, Scourge, Devourer

	ObjectInfoVector inherenceUnits;

	if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Zerg_Spawning_Pool)					// Spawning pool
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hatchery, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Sunken_Colony	// Sunken colony
		|| unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Zergling)			// Zergling
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hatchery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Hydralisk_Den)	// Hydra den
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hatchery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Evolution_Chamber, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Spore_Colony)	// Spore colony
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hatchery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Evolution_Chamber, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Hydralisk)		// Hydralisk
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hatchery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hydralisk_Den, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Lurker
		|| unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Lurker_Egg)		// Lurker
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Lair, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hydralisk_Den, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Queens_Nest)		// Queens nest
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Lair, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Queen)			// Queen
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Lair, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Queens_Nest, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Mutalisk			// Mutalisk
		|| unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Scourge)			// Scourge 
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Lair, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spire, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Ultralisk)			// Ultralisk
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hive, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Queens_Nest, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Ultralisk_Cavern, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Ultralisk_Cavern		// Ultralisk Cavern
		  || unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Defiler_Mound		// Defiler Mound
		  || unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Nydus_Canal		    // Nydus canal
		  || unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Greater_Spire)		// Greater Spire
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hive, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Queens_Nest, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Defiler)				// Defiler
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hive, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Queens_Nest, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Defiler_Mound, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Guardian				// Guardian
		  || unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Zerg_Devourer)			// Devourer
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Hive, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Extractor, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Spawning_Pool, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Queens_Nest, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Zerg_Greater_Spire, DONT_ADD_UNIT_ANY_CASE));
	}

	return inherenceUnits;
}

std::vector<int> CPlayerZerg::inputUnitVector = {
	SUPPLY,
	BWAPI::UnitTypes::Zerg_Drone,
	BWAPI::UnitTypes::Zerg_Overlord,
	BWAPI::UnitTypes::Zerg_Zergling,
	BWAPI::UnitTypes::Zerg_Hydralisk,
	BWAPI::UnitTypes::Zerg_Lurker,
	BWAPI::UnitTypes::Zerg_Mutalisk,
	BWAPI::UnitTypes::Zerg_Scourge,
	BWAPI::UnitTypes::Zerg_Ultralisk,
	BWAPI::UnitTypes::Zerg_Guardian,
	BWAPI::UnitTypes::Zerg_Queen,
	BWAPI::UnitTypes::Zerg_Defiler,
	BWAPI::UnitTypes::Zerg_Devourer,
	BWAPI::UnitTypes::Zerg_Hatchery,
	BWAPI::UnitTypes::Zerg_Lair,
	BWAPI::UnitTypes::Zerg_Hive,
	BWAPI::UnitTypes::Zerg_Extractor,
	BWAPI::UnitTypes::Zerg_Spawning_Pool,
	BWAPI::UnitTypes::Zerg_Creep_Colony,
	BWAPI::UnitTypes::Zerg_Spore_Colony,
	BWAPI::UnitTypes::Zerg_Sunken_Colony,
	BWAPI::UnitTypes::Zerg_Hydralisk_Den,
	BWAPI::UnitTypes::Zerg_Evolution_Chamber,
	BWAPI::UnitTypes::Zerg_Spire,
	BWAPI::UnitTypes::Zerg_Nydus_Canal,
	BWAPI::UnitTypes::Zerg_Defiler_Mound,
	BWAPI::UnitTypes::Zerg_Greater_Spire,
	BWAPI::UnitTypes::Zerg_Queens_Nest,
	BWAPI::UnitTypes::Zerg_Ultralisk_Cavern
};

std::vector<int> CPlayerZerg::outputUnitVector = {
	BWAPI::UnitTypes::Zerg_Drone,
	BWAPI::UnitTypes::Zerg_Zergling,
	BWAPI::UnitTypes::Zerg_Hydralisk,
	BWAPI::UnitTypes::Zerg_Lurker,
	BWAPI::UnitTypes::Zerg_Mutalisk,
	BWAPI::UnitTypes::Zerg_Scourge,
	BWAPI::UnitTypes::Zerg_Ultralisk,
	BWAPI::UnitTypes::Zerg_Guardian,
	BWAPI::UnitTypes::Zerg_Queen,
	BWAPI::UnitTypes::Zerg_Defiler,
	BWAPI::UnitTypes::Zerg_Devourer,
	BWAPI::UnitTypes::Zerg_Hatchery,
	BWAPI::UnitTypes::Zerg_Lair,
	BWAPI::UnitTypes::Zerg_Hive,
	BWAPI::UnitTypes::Zerg_Extractor,
	BWAPI::UnitTypes::Zerg_Spore_Colony,
	BWAPI::UnitTypes::Zerg_Sunken_Colony
};

std::vector<int> CPlayerZerg::getInputUnitVector() {
	return inputUnitVector;
}

std::vector<int> CPlayerZerg::getOutputUnitVector() {
	return outputUnitVector;
}