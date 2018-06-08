#ifndef ___TERRANPLAYER___
#define ___TERRANPLAYER___

#include "PlayerModel.h"

namespace OpponentModelling {

	/// Class representing model of a terran player. 
	class CPlayerTerran : public CPlayerModel {

	public:
		/// Default constructor, initialize input and output vector for most important data
		CPlayerTerran();

		/// @return race of opponent.
		BWAPI::Race getRace()const;

		/// Vector with input values into the neural network
		static std::vector<int> inputUnitVector;

		/// Vector with output values into the neural network
		static std::vector<int> outputUnitVector;

		/// Input vector for neural network.
		/// @return Vector of everything we want as an input into the NN.
		std::vector<int> getOutputUnitVector();

		/// Output vector for neural network.
		/// @return Vector of everything we want as an output from the NN.
		std::vector<int> getInputUnitVector();

	private:
		/// Method inherence additional inforamtion about our opponent.
		/// @return Vector holding inherence units based on our scouting. E.g.: Tank seen -> opponent must have a Factory with machine shop
		ObjectInfoVector InherenceAdditionalInfo(CObjectInfo *unitToBeAdded);

		/// Inherence initial information at the start of the game
		/// @return Initial inherenced information in a vector. (CC, and 4 SCVs).
		ObjectInfoVector InherenceInitialInfo();

	};
}

#endif //___TERRANPLAYER___