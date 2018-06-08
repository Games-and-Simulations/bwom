#include "ProtossPlayer.h"

using namespace OpponentModelling;

CPlayerProtoss::CPlayerProtoss()
	:CPlayerModel()
{
	for (auto it : inputUnitVector)
		UnitsMap[it];
	randomOpponent = 0;
}

ObjectInfoVector CPlayerProtoss::InherenceInitialInfo() {
	ObjectInfoVector inherenceUnits;
	inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Nexus, DONT_ADD_UNIT_ANY_CASE));

	for (int i = 0; i < 4; i++)
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Probe, ADD_UNIT_ANY_CASE));

	return inherenceUnits;
}

BWAPI::Race CPlayerProtoss::getRace() const{
	return BWAPI::Races::Protoss;
}

ObjectInfoVector CPlayerProtoss::InherenceAdditionalInfo(CObjectInfo *unitToBeAdded) {
	// Nexus, Probe, Pylon, Assimilator, Gateway, Zealot, Dragoon, Forge, Cyber, Shield Baterry, Cannon
	// Stargate, Corsair, Scout, Carrier, Arbiter, Citadel of Adun, DT, HT, Fleet Beacon, Templar Archvies
	// Robotics Facility, Reavers, Robo Bay, Shuttle, Observatory, Observer, Arbiter Tribunal, Dark Arhcon, Archon

	ObjectInfoVector inherenceUnits;

	if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Protoss_Zealot)	// Zealot
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Dragoon) // Dragoon
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Cybernetics_Core) // Cyber
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Shield_Battery) // Shield baterry
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Photon_Cannon) // canon
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Forge, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Stargate)	// Stargate
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Corsair)	// Corsair
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Stargate, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Scout)	// Scout
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Stargate, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Carrier)	// Carrier
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Stargate, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Fleet_Beacon, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Fleet_Beacon)	// Fleet beacon
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Stargate, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Arbiter)	// Arbiter
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Stargate, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Fleet_Beacon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Templar_Archives, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Citadel_of_Adun) // Citadel of Adun
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Dark_Templar) // DT
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Citadel_of_Adun, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Templar_Archives, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_High_Templar)	// HT
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Citadel_of_Adun, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Templar_Archives, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Dark_Archon)	// Dark archon
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Citadel_of_Adun, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Templar_Archives, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Archon)	// Archon
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Citadel_of_Adun, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Templar_Archives, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Robotics_Facility)	// Robo
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Robotics_Support_Bay)	// Robo support bay
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Robotics_Facility, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Shuttle)	// Shuttle
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Robotics_Facility, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Reaver)	// Reaver
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Robotics_Facility, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Robotics_Support_Bay, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Observer)	// Observer
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Robotics_Facility, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Observatory, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Observatory)	// Observatory
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Robotics_Facility, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Protoss_Templar_Archives)  // Templar Archives
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Pylon, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Gateway, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Assimilator, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Cybernetics_Core, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Protoss_Citadel_of_Adun, DONT_ADD_UNIT_ANY_CASE));
	}
	
	return inherenceUnits;
}

std::vector<int> CPlayerProtoss::inputUnitVector = {
	SUPPLY,
	BWAPI::UnitTypes::Protoss_Probe,
	BWAPI::UnitTypes::Protoss_Zealot,
	BWAPI::UnitTypes::Protoss_Dragoon,
	BWAPI::UnitTypes::Protoss_Shuttle,
	BWAPI::UnitTypes::Protoss_Dark_Templar,
	BWAPI::UnitTypes::Protoss_High_Templar,
	BWAPI::UnitTypes::Protoss_Archon,
	BWAPI::UnitTypes::Protoss_Dark_Archon,
	BWAPI::UnitTypes::Protoss_Scout,
	BWAPI::UnitTypes::Protoss_Corsair,
	BWAPI::UnitTypes::Protoss_Arbiter,
	BWAPI::UnitTypes::Protoss_Carrier,
	BWAPI::UnitTypes::Protoss_Reaver,
	BWAPI::UnitTypes::Protoss_Observer,
	BWAPI::UnitTypes::Protoss_Nexus,
	BWAPI::UnitTypes::Protoss_Pylon,
	BWAPI::UnitTypes::Protoss_Assimilator,
	BWAPI::UnitTypes::Protoss_Gateway,
	BWAPI::UnitTypes::Protoss_Shield_Battery,
	BWAPI::UnitTypes::Protoss_Cybernetics_Core,
	BWAPI::UnitTypes::Protoss_Robotics_Facility,
	BWAPI::UnitTypes::Protoss_Observatory,
	BWAPI::UnitTypes::Protoss_Forge,
	BWAPI::UnitTypes::Protoss_Photon_Cannon,
	BWAPI::UnitTypes::Protoss_Citadel_of_Adun,
	BWAPI::UnitTypes::Protoss_Templar_Archives,
	BWAPI::UnitTypes::Protoss_Stargate,
	BWAPI::UnitTypes::Protoss_Fleet_Beacon,
	BWAPI::UnitTypes::Protoss_Arbiter_Tribunal,
	BWAPI::UnitTypes::Protoss_Robotics_Support_Bay
};

std::vector<int> CPlayerProtoss::outputUnitVector = {
	BWAPI::UnitTypes::Protoss_Probe,
	BWAPI::UnitTypes::Protoss_Zealot,
	BWAPI::UnitTypes::Protoss_Dragoon,
	BWAPI::UnitTypes::Protoss_Shuttle,
	BWAPI::UnitTypes::Protoss_Dark_Templar,
	BWAPI::UnitTypes::Protoss_High_Templar,
	BWAPI::UnitTypes::Protoss_Archon,
	BWAPI::UnitTypes::Protoss_Dark_Archon,
	BWAPI::UnitTypes::Protoss_Scout,
	BWAPI::UnitTypes::Protoss_Corsair,
	BWAPI::UnitTypes::Protoss_Arbiter,
	BWAPI::UnitTypes::Protoss_Carrier,
	BWAPI::UnitTypes::Protoss_Reaver,
	BWAPI::UnitTypes::Protoss_Observer,
	BWAPI::UnitTypes::Protoss_Nexus,
	BWAPI::UnitTypes::Protoss_Assimilator,
	BWAPI::UnitTypes::Protoss_Gateway,
	BWAPI::UnitTypes::Protoss_Shield_Battery,
	BWAPI::UnitTypes::Protoss_Robotics_Facility,
	BWAPI::UnitTypes::Protoss_Photon_Cannon,
	BWAPI::UnitTypes::Protoss_Stargate
};

std::vector<int> CPlayerProtoss::getInputUnitVector() {
	return inputUnitVector;
}

std::vector<int> CPlayerProtoss::getOutputUnitVector() {
	return outputUnitVector;
}