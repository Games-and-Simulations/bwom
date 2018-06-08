#ifndef ___PLAYERMODEL___
#define ___PLAYERMODEL___

#include "ObjectInfo.h"
#include "EconomyManager.h"
#include "ConfigurationFile.h"
#include <math.h>

namespace OpponentModelling {

	typedef std::vector<CObjectInfo*>			ObjectInfoVector;
	typedef std::map<int, ObjectInfoVector>		MapUnitTypeVector;

	/// Function used for lower and upper bound comparison
	bool cmpO(const CObjectInfo * a, const CObjectInfo * b);
	/// Function used for lower and upper bound comparison
	bool cmpI(const CObjectInfo * a, const int & b);

	/// Superclass that models the opponent.
	/// This class stores the information about his economy and all units scouted.
	class CPlayerModel {

	public:

		/// Default constructor. Initialize the object.
		CPlayerModel();
		
		/// Default destructor. Destroys all allocated memory by this object.
		~CPlayerModel();
		
		/// Getter of the vector that holds all scouted enemy units.
		/// @return The vector of all enemy units scouted.
		ObjectInfoVector getAllUnits()const;

		/// Getter of the map that holds all scouted enemy units.
		/// Key value is BWAPI::UnitType.
		/// Saved value is a vector of all scouted enemy units of given type.
		/// @return The map of all enemy units scouted.
		MapUnitTypeVector getMapOfAllUnits()const;

		/// Updates the information of a given unit
		/// At first the method checks if it's the first time we saw this unit.
		/// @param unitToBeUpdated The unit we want the information to update.

		/// Getter for current player supply.
		/// @return Returns current player supply. Dont forget, BWAPI supply is doubled.
		int getSupply();

		/// Updates information about given unit
		/// @param unitToBeUpdated If it is the first time we see this unit, add it into our database. Update the info otherwise.
		void unitUpdate(BWAPI::Unit unitToBeUpdated);
		
		/// Checks if opponent has at least one unit of given type.
		/// @param unitTypeID BWAPI Enum UnitType.
		/// @return true if opponent has at least one unit of given type, returns false otherwise.
		bool containsUnit(BWAPI::UnitTypes::Enum::Enum unitTypeID);

		/// Getter for 
		/// @param unitID ID of the unit we want to get.
		/// @return Pointer on CObjectInfo instance that represents the unit.
		CObjectInfo *getUnitByID(const int unitID);

		/// Removes unit from our database.
		/// @param uniID ID of the unit we want to remove from our database.
		void removeUnit(const int unitID);

		/// Initialize the object. Should be called whenever before using.
		void init();

		/// Adds given unit to the database.
		/// @param unitToBeAdded Pointer to CObjectInfo instance that represents the info about unit to be added.
		/// @see OpponentModelling::CObjectInfo.
		void addUnit(CObjectInfo *unitToBeAdded);

		/// Input vector for neural network.
		/// @return Vector of everything we want as an input into the NN.
		virtual std::vector<int> getInputUnitVector();

		/// Output vector for neural network.
		/// @return Vector of everything we want as an output from the NN.
		virtual std::vector<int> getOutputUnitVector();

		/// @return race of opponent.
		virtual BWAPI::Race getRace();

		/// @return True if opponent race is known. False otherwise.
		bool isRandom();

	protected:

		/// Current player supply
		int supply;

		/// Inherence of additional informance when a unit is scouted.
		/// E.g.: Dragoon scouted, so we check if in our databse is gateway, cyber, assimilator. If not, add them.
		/// @return Vector with all buildings that were needed to build currently scouted unit.
		ObjectInfoVector virtual InherenceAdditionalInfo(CObjectInfo *unitToBeAdded);

		/// Inherence information at the beggining of the game.
		/// Adds starting units + depot for opponents race.
		/// @return Vector with all buildings and units at the start of the game. If opponets race is not known. returns empty vector.
		ObjectInfoVector virtual InherenceInitialInfo();

		/// Vector holding every enemy units we scouted.
		/// Units are sorted by ID
		ObjectInfoVector AllUnitsStored;

		/// Map with all enemy units we scouted.
		/// Units are sorted into vectors in the map, where the key value is the BWAPI::UnitType
		MapUnitTypeVector UnitsMap;

		/// True if opponents race is known, false otherwise.
		bool randomOpponent;
	private:
		
		/// Object that handles opponents economy
		/// @see OpponentModelling::CEconomyManager
		CEconomyManager *EconomyHandler;

		/// Lower or upper bound iterator that helps finding units in our database.
		std::vector<CObjectInfo*>::iterator bound;

		/// Updates the information of a given unit we have previously seen.
		/// @param unitToBeUpdated The unit we want the information to update.
		void updateKnownUnit(BWAPI::Unit unitToBeUpdated);

		/// Adds given unit to the database.
		/// @param unitToBeAdded BWAPI Unit that represents the unit to be added.
		void addUnit(BWAPI::Unit unitToBeAdded);

		/// Getter of gas lost during game.
		/// @return Number of gas our opponent lost during the game.
		int getGasLost();

		/// Getter of minerals lost during game.
		/// @return Number of minerals our opponent lost during the game.
		int getMineralsLost();
	};
}


#endif // ___PLAYERMODEL___