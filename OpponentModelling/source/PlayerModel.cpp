#include "PlayerModel.h"

using namespace OpponentModelling;

bool OpponentModelling::cmpO(const CObjectInfo * a, const CObjectInfo * b) {
	return a->ID < b->ID;
}

bool OpponentModelling::cmpI(const CObjectInfo *a, const int & b) {
	return a->ID < b;
}


CPlayerModel::CPlayerModel()  {
	EconomyHandler	= new CEconomyManager();
	supply = 0;
	randomOpponent = 1;

	// init the map for all types of units in broodwar according to BWAPI::UnitTypes
	for (int i = BWAPI::UnitTypes::Terran_Marine; i <= BWAPI::UnitTypes::Powerup_Terran_Gas_Tank_Type_2; i++)
		UnitsMap[i];
}

CPlayerModel::~CPlayerModel() {
	delete EconomyHandler;
}

ObjectInfoVector CPlayerModel::getAllUnits() const {
	return AllUnitsStored;
}

MapUnitTypeVector CPlayerModel::getMapOfAllUnits() const {
	return UnitsMap;
}

void CPlayerModel::updateKnownUnit(BWAPI::Unit unitToBeUpdated) {
	getUnitByID(unitToBeUpdated->getID())->updateUnit(unitToBeUpdated);
	if (getUnitByID(unitToBeUpdated->getID()) != nullptr && getUnitByID(unitToBeUpdated->getID())->isHalucination)
		removeUnit(unitToBeUpdated->getID());
}

void CPlayerModel::unitUpdate(BWAPI::Unit unitToBeUpdated) {

	/* check whether we have already saved this unit and just needs to be updated */
	if (getUnitByID(unitToBeUpdated->getID()) == nullptr)
		addUnit(unitToBeUpdated);
	else
		updateKnownUnit(unitToBeUpdated);

}

void CPlayerModel::addUnit(CObjectInfo *unitToBeAdded) { 

	/* If this type of unit wasnt added yet, add the key - creates initial vector */
	if (UnitsMap.find(unitToBeAdded->UnitType.getID()) == UnitsMap.end())
		UnitsMap[unitToBeAdded->UnitType.getID()];
	
	// If it is inherenced unit, we check if we already scouted this unit
	if (unitToBeAdded->isHalucination || (unitToBeAdded->ID < 0 && UnitsMap.at(unitToBeAdded->UnitType.getID()).size() > 0 && abs(unitToBeAdded->ID) % 2 == 0))
	{
		delete unitToBeAdded;
		return;
	}

	// check if there is a unit to be replaced(ID < 0) -> replace it.
	if (unitToBeAdded->ID >= 0 && UnitsMap.at(unitToBeAdded->UnitType.getID()).size() > 0)
	{
		int tmpID = UnitsMap.at(unitToBeAdded->UnitType.getID()).at(0)->ID;
		if (tmpID < 0) // Jednotka co chce nahradit, odstranime ji
			removeUnit(tmpID);
	}

	supply += unitToBeAdded->UnitType.supplyRequired();
	bound = std::upper_bound(UnitsMap.at(unitToBeAdded->UnitType.getID()).begin(), UnitsMap.at(unitToBeAdded->UnitType.getID()).end(), unitToBeAdded, cmpO);
	UnitsMap.at(unitToBeAdded->UnitType.getID()).insert(bound, unitToBeAdded);
	
	/* Find the place using upperbound, sorted units are by ID */
	bound = std::upper_bound(AllUnitsStored.begin(), AllUnitsStored.end(), unitToBeAdded, cmpO);
	AllUnitsStored.insert(bound, unitToBeAdded);

	/* This infer additional information about an opponent. The inferenced units have ID 
	 * set to negative value, so you dont mistake them with real ingame units which have positive IDs */
	//if (unitToBeAdded->ID >= 0)
		for (CObjectInfo * cur : InherenceAdditionalInfo(unitToBeAdded))
			addUnit(cur);
	
}

void CPlayerModel::addUnit(BWAPI::Unit unitToBeAdded) {
	CObjectInfo *tmp = new CObjectInfo(unitToBeAdded);
	addUnit(tmp);
}

void CPlayerModel::removeUnit(const int UnitID) {

	CObjectInfo * unit = getUnitByID(UnitID);

	/* Just in case we didnt store the unit */
	if (unit == nullptr)
		return;

	EconomyHandler->unitRemoved(unit);
	supply -= unit->UnitType.supplyRequired();

	/* Find the unit in vector and map using logn lower bound */
	bound = std::lower_bound(AllUnitsStored.begin(), AllUnitsStored.end(), UnitID, cmpI);
	CObjectInfo * tmp = AllUnitsStored.at(bound - AllUnitsStored.begin());
	AllUnitsStored.erase(bound);

	bound = std::lower_bound(UnitsMap.at(tmp->UnitType.getID()).begin(), UnitsMap.at(tmp->UnitType.getID()).end(), UnitID, cmpI);
	UnitsMap.at(tmp->UnitType.getID()).erase(bound);

	/* delete the mess, vector and map store only pointer type, so we delete the object only once */
	delete tmp;
}

bool CPlayerModel::containsUnit(BWAPI::UnitTypes::Enum::Enum unitTypeID) {
	return UnitsMap[unitTypeID].size() != 0;
}

CObjectInfo *CPlayerModel::getUnitByID(const int UnitID) {
	bound = std::lower_bound(AllUnitsStored.begin(), AllUnitsStored.end(), UnitID, cmpI);
	if (bound != AllUnitsStored.end() && AllUnitsStored.at(bound - AllUnitsStored.begin())->ID == UnitID )
		return AllUnitsStored.at(bound - AllUnitsStored.begin());
	return nullptr;
}


void CPlayerModel::init() {

	for (CObjectInfo * cur : InherenceInitialInfo())
		addUnit(cur);
}

int CPlayerModel::getSupply() {
	return supply;
}


std::vector<int> CPlayerModel::getInputUnitVector() {
	return std::vector<int>();
}
std::vector<int> CPlayerModel::getOutputUnitVector() {
	return std::vector<int>();
}

ObjectInfoVector CPlayerModel::InherenceAdditionalInfo(CObjectInfo *unitToBeAdded) {
	return ObjectInfoVector();
}

ObjectInfoVector CPlayerModel::InherenceInitialInfo() {
	return ObjectInfoVector();
}

bool CPlayerModel::isRandom() {
	return randomOpponent;
}

BWAPI::Race CPlayerModel::getRace() {
	return BWAPI::Races::Random;
}

int CPlayerModel::getMineralsLost() {
	return EconomyHandler->getMineralsLost();
}

int CPlayerModel::getGasLost() {
	return EconomyHandler->getGasLost();
}