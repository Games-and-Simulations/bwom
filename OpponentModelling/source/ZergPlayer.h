#ifndef ___ZERGPLAYER___
#define ___ZERGPLAYER___

#include "PlayerModel.h"

namespace OpponentModelling {

	/// Class representing model of a zerg player. 
	class CPlayerZerg : public CPlayerModel {

	public:
		/// Default constructor, initialize input and output vector for most important data
		CPlayerZerg();

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
		/// Inherence initial information at the start of the game
		/// @return Initial inherenced information in a vector. (Hatchery, overlord and 4 drones).
		ObjectInfoVector InherenceInitialInfo();

		/// Method inherence additional inforamtion about our opponent.
		/// @return Vector holding inherence units based on our scouting. E.g.: Mutalisk seen -> opponent must have a lair and spire
		ObjectInfoVector InherenceAdditionalInfo(CObjectInfo *unitToBeAdded);

	};
}

#endif //___ZERGPLAYER___