#ifndef ___PROTOSSPLAYER___
#define ___PROTOSSPLAYER___
#include "PlayerModel.h"

namespace OpponentModelling {

	/// Class representing model of a protoss player. 
	class CPlayerProtoss : public CPlayerModel {

	public:
		/// Default constructor, initialize input and output vector for most important data
		CPlayerProtoss();

		/// @return race of opponent.
		BWAPI::Race CPlayerProtoss::getRace()const;

		/// Vector with input values into the neural network
		static std::vector<int> inputUnitVector;

		/// Vector with output values into the neural network
		static std::vector<int> outputUnitVector;

		/// Input vector for neural network.
		/// @return Vector of everything we want as an input into the NN.
		std::vector<int> getInputUnitVector();

		/// Output vector for neural network.
		/// @return Vector of everything we want as an output from the NN.
		std::vector<int> getOutputUnitVector();
	private:
		/// Inherence initial information at the start of the game
		/// @return Initial inherenced information in a vector. (Nexus, and 4 probes).
		ObjectInfoVector InherenceInitialInfo();

		/// Method inherence additional inforamtion about our opponent.
		/// @return Vector holding inherence units based on our scouting. E.g.: Observer seen -> opponent must have an observatory
		ObjectInfoVector InherenceAdditionalInfo(CObjectInfo *unitToBeAdded);
		
	};
}

#endif //___PROTOSSPLAYER___