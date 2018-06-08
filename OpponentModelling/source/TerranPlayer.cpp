#include "TerranPlayer.h"

using namespace OpponentModelling;

CPlayerTerran::CPlayerTerran()
	:CPlayerModel()
{
	for (auto it : inputUnitVector)
		UnitsMap[it];
	randomOpponent = 0;
}

ObjectInfoVector CPlayerTerran::InherenceInitialInfo() {
	ObjectInfoVector inherenceUnits;
	inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Command_Center, DONT_ADD_UNIT_ANY_CASE));
	
	for (int i = 0; i < 4; i++)
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_SCV, ADD_UNIT_ANY_CASE));

	return inherenceUnits;
}

BWAPI::Race CPlayerTerran::getRace() const{
	return BWAPI::Races::Terran;
}

ObjectInfoVector CPlayerTerran::InherenceAdditionalInfo(CObjectInfo *unitToBeAdded) {
	// CC, SCV, Suply Depot, Refinery, Barracks, Factory, Academy, Bunker
	// Marine, Firebat, Medic, Tank, Vulture, Starport, Engineering bay, Wrath, Missile Turret
	// Dropship, BC, Valkier, Armory, Goliath,  Science Facility, Control tower,
	// Physics lab, Cover obs, Nuclear silo, Combat station, Science Vessel

	ObjectInfoVector inherenceUnits;

	if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Terran_Barracks)	// Barracks
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
	} 
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Factory) // Factory
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
	} 
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Marine) // Marine
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
	} 
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Academy) // Academy
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Bunker) // Bunker
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Firebat) // Firebat
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Academy, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Medic) // Medic
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Academy, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Missile_Turret) // Turret
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Engineering_Bay, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Vulture) // Vulture
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Siege_Tank_Tank_Mode
		|| unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Siege_Tank_Siege_Mode) // Tank
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Machine_Shop, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Starport) // Starport
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Wraith) // Wraith
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Dropship) // Dropship
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Control_Tower, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Valkyrie) // Valkyrie
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Control_Tower, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Armory, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Science_Facility) // Science Facility
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Science_Vessel) // Science Vessel
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Control_Tower, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Science_Facility, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Battlecruiser) // BC
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Supply_Depot, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Control_Tower, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Science_Facility, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Physics_Lab, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Goliath) // Goliath
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Machine_Shop, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Armory, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Armory) // Armory
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Nuclear_Silo) // Nuc silo
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Science_Facility, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Covert_Ops, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Ghost) // Ghost
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Science_Facility, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Covert_Ops, DONT_ADD_UNIT_ANY_CASE));
	}
	else if (unitToBeAdded->UnitType == BWAPI::UnitTypes::Enum::Enum::Terran_Physics_Lab) // Phy lab
	{
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Barracks, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Refinery, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Factory, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Starport, DONT_ADD_UNIT_ANY_CASE));
		inherenceUnits.push_back(new CObjectInfo(BWAPI::UnitTypes::Terran_Science_Facility, DONT_ADD_UNIT_ANY_CASE));
	}

	return inherenceUnits;
}

std::vector<int> CPlayerTerran::inputUnitVector = {
	SUPPLY,
	BWAPI::UnitTypes::Terran_SCV,
	BWAPI::UnitTypes::Terran_Marine,
	BWAPI::UnitTypes::Terran_Firebat,
	BWAPI::UnitTypes::Terran_Medic,
	BWAPI::UnitTypes::Terran_Ghost,
	BWAPI::UnitTypes::Terran_Vulture,
	BWAPI::UnitTypes::Terran_Goliath,
	BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode,
	BWAPI::UnitTypes::Terran_Wraith,
	BWAPI::UnitTypes::Terran_Science_Vessel,
	BWAPI::UnitTypes::Terran_Dropship,
	BWAPI::UnitTypes::Terran_Battlecruiser,
	BWAPI::UnitTypes::Terran_Valkyrie,
	BWAPI::UnitTypes::Terran_Command_Center,
	BWAPI::UnitTypes::Terran_Supply_Depot,
	BWAPI::UnitTypes::Terran_Refinery,
	BWAPI::UnitTypes::Terran_Barracks,
	BWAPI::UnitTypes::Terran_Academy,
	BWAPI::UnitTypes::Terran_Factory,
	BWAPI::UnitTypes::Terran_Engineering_Bay,
	BWAPI::UnitTypes::Terran_Bunker,
	BWAPI::UnitTypes::Terran_Starport,
	BWAPI::UnitTypes::Terran_Comsat_Station,
	BWAPI::UnitTypes::Terran_Nuclear_Silo,
	BWAPI::UnitTypes::Terran_Control_Tower,
	BWAPI::UnitTypes::Terran_Science_Facility,
	BWAPI::UnitTypes::Terran_Covert_Ops,
	BWAPI::UnitTypes::Terran_Physics_Lab,
	BWAPI::UnitTypes::Terran_Machine_Shop,
	BWAPI::UnitTypes::Terran_Armory,
	BWAPI::UnitTypes::Terran_Missile_Turret
};

std::vector<int> CPlayerTerran::outputUnitVector = {
	BWAPI::UnitTypes::Terran_SCV,
	BWAPI::UnitTypes::Terran_Marine,
	BWAPI::UnitTypes::Terran_Firebat,
	BWAPI::UnitTypes::Terran_Medic,
	BWAPI::UnitTypes::Terran_Ghost,
	BWAPI::UnitTypes::Terran_Vulture,
	BWAPI::UnitTypes::Terran_Goliath,
	BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode,
	BWAPI::UnitTypes::Terran_Wraith,
	BWAPI::UnitTypes::Terran_Science_Vessel,
	BWAPI::UnitTypes::Terran_Dropship,
	BWAPI::UnitTypes::Terran_Battlecruiser,
	BWAPI::UnitTypes::Terran_Valkyrie,
	BWAPI::UnitTypes::Terran_Command_Center,
	BWAPI::UnitTypes::Terran_Refinery,
	BWAPI::UnitTypes::Terran_Barracks,
	BWAPI::UnitTypes::Terran_Factory,
	BWAPI::UnitTypes::Terran_Bunker,
	BWAPI::UnitTypes::Terran_Starport,
	BWAPI::UnitTypes::Terran_Machine_Shop,
	BWAPI::UnitTypes::Terran_Missile_Turret
};

std::vector<int> CPlayerTerran::getInputUnitVector() {
	return inputUnitVector;
}

std::vector<int> CPlayerTerran::getOutputUnitVector() {
	return outputUnitVector;
}