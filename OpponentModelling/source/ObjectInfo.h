#ifndef ___OBJECTINFO___
#define ___OBJECTINFO___

#include "BWAPI.h"

namespace OpponentModelling {

	/// Unit database keystone.
	/// Every unit in our opponent model is stored as CObjectInfo object.
	/// It represents the unit. When a unit is in FOG and we cant reach it, 
	/// necessary information about it are saved in this object and we can acces them.
	struct CObjectInfo {

		/// Default constructor. Creater unit object.
		CObjectInfo();

		/// Constructor that makes similar CObjectInfo instance according to given unit
		/// @param unit Unit we want to copy and create instance representing it.
		CObjectInfo(BWAPI::Unit unit);

		/// Constructor for creating unit based only on UnitType.
		/// @param unit UnitType that says which kind of unit we want to create.
		/// @param AddInAnyCase Because we created this unit based only on a unit type, we must
		/// specify if we want to add this unit into our database in any case or not. If parameter is set to false
		/// addUnit function will first check if there exists at least 1 type of unit for our opponent. If yes, unit
		/// wont be added. If the parameter is set to true, unit will be add into our database no matter the circumstances.
		CObjectInfo(BWAPI::UnitType unit, bool AddInAnyCase);

		/// Update our known information about unit.
		void updateUnit(BWAPI::Unit unit);

		const bool operator == (BWAPI::Unit unit) const;

		int  ID;
		int  Health;
		int  Shields;
		int	 Energy;
		bool Completed;
		bool IsMorphing;
		bool IsTraining;
		bool isHalucination;
		int	 Frame;

		BWAPI::Unit     Unit;
		BWAPI::UnitType UnitType;
		BWAPI::Position Position;
		BWAPI::TilePosition TilePosition;
		BWAPI::Player   Player;

	private:

		/// returns ID that fits for the given iherenced unit.
		/// @see IDUnitCounter
		int getID(bool AddInAnyCase);
	};

	/// Class that gives ids to inherenced units
	/// We differentiate inherenced units on two types.
	/// The first one is that we want to add to our database in any case.
	/// The second one where we first check, if opponent already has this kind of unit and then we decied to add it or not.
	/// This units are differentiate by their IDS.
	/// All inherenced units has negative ID values but Units of first type has odd negative IDS and units of second type has even negative IDS.
	class IDUnitCounter
	{
		/// counter for unique negative IDS.
		static int counter;

	public:

		/// Get the id and decreases the counter.
		/// @return ID counter.
		static int getValueAndIncrease()
		{
			return counter--;
		}
		
		/// Get the ID,
		/// @return ID counter.
		static int getValue()
		{
			return counter;
		}
	};
}

#endif //___OBJECTINFO___