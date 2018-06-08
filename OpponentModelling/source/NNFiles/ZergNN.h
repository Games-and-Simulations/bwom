#ifndef ___ZERGNN___
#define ___ZERGNN___

#include "NeuralNetworkModel.h"

namespace OpponentModelling {

	/// Class represents neural network for Zerg model.
	class CZergNN : public CNeuralNetworkModel {

	public:
		/// Default constructor for Zerg NN.
		CZergNN();

		/// Initialize the neural network. It should be called before using any other functionalities.
		void init();

		/// Saves the neural network into binary file.
		/// @param FileName Name of file we want that the binary has.
		void saveNeuralNetwork(std::string FileName);

		/// Loads binary file with network into our model.
		/// ! Before loading the NN, it must be constructed and ready. It means all layers and neurons must fit the binary model.
		/// @param FileName Name of the binary file with NN we want to load into our network.
		void loadNeuralNetwork(std::string FileName = DEFAULT_ZERG_NN);

		/// Creates the NN according to parameters.
		/// @param numOfLayers Represents number of hidden layers we want to have in the NN.
		/// @param neuronsInEachLayer Is a vector with numbers of neurons in each of the hidden layers.
		void createNN(unsigned int numOfHiddenLayers, std::vector<unsigned int> neuronsInEachLayer);

		/// Zerg name of the network.
		/// @return Zerg name of the network.
		std::string getName();

	private:
		/// Default construction of the Zerg NN.
		void createNN();

		/// Getter for the Zerg output values from our NN.
		/// @return The output vector with Zerg units and building according to their ID in BWAPI::UnitTypes
		std::vector<int> getOutputV();
	};

}
#endif //___ZERGNN___