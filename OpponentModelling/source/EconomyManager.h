#ifndef ___ECONOMYMANAGER___
#define ___ECONOMYMANAGER___

#include "ObjectInfo.h"

namespace OpponentModelling {
	/// Class representing economy situation of our opponent.
	class CEconomyManager {

	public:

		/// Default constructor.
		CEconomyManager();

		/// This method should be called when an enemy unit dies.
		/// @param unit Pointer to CObjectInfo unit. It represents the unit that died.
		void unitRemoved(CObjectInfo *unit);

		/// Getter of gas minerals during game.
		/// @return Number of minerals our opponent lost during the game.
		int getMineralsLost()const;

		/// Getter of gas lost during game.
		/// @return Number of gas our opponent lost during the game.
		int getGasLost()const;

	private:

		/// Minerals lost during the game.
		int MineralsLost;

		/// Gas lost during the game.
		int GasLost;

	};
}

#endif // ___ECONOMYMANAGER___