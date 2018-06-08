#ifndef ___NEURALNETWORKMODEL___
#define ___NEURALNETWORKMODEL___

#include "tiny_dnn.h"
#include "FileIOHandler.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;

namespace OpponentModelling {

	/// Class representing model of neural network. It has all necessary information stored for the proper run of the NN.
	/// It also handles training and testing methods, setting NN parameters and printing results into files.
	class CNeuralNetworkModel {

	public:
		/// Default constructor.
		CNeuralNetworkModel();

		/// Destructor for deallocating the memory.
		~CNeuralNetworkModel();

		/// Initializes the NN to the default state.
		virtual void init() = 0;

		/// Tests the NN with given set of data.
		/// @param loadedData Is a vector of InputOutputData objects that are loaded as input and proper output for the network.
		/// it tests the nn and compare predicted values with desired values.
		/// @return It returs the overall error for the given data set.
		float testNN(std::vector<InputOutputData*> & loadedData);

		/// Predicts opponent game state based on currently known information.
		/// @param currentState Represents current state of game which holds information about the opponent.
		/// @return Model representing opponents game state in the future. Default setings are set to 3 minuts.
		CPlayerModel * predictOpponetGameState(CPlayerModel * currentState);

		/// Trains the NN with given data.
		/// @param loadedData Represents input and output data loaded in vetor of InputOutputData objects.
		/// @return The overall loss for the given dataset.
		double trainNN(std::vector<InputOutputData*> & loadedData);

		/// Creates the NN according to parameters.
		/// @param numOfLayers Represents number of hidden layers we want to have in the NN.
		/// @param neuronsInEachLayer Is a vector with numbers of neurons in each of the hidden layers.
		void virtual createNN(unsigned int numOfLayers, std::vector<unsigned int> neuronsInEachLayer) = 0;

		/// Sets the number of Epochs.
		/// @param numEpochs Number of epochs we want to run for training.
		void setNumOfEpochs(unsigned int numEpochs);

		/// Sets the batch size.
		/// @param batchSize Represents the size of batch.
		void setBatchSize(unsigned int batchSize);

		/// Getter of number of layers. all hidden layers + input layer + output layers.
		/// @return Number of all layers in our NN.
		unsigned int getNumOfLayers()const;

		/// Getter for numbers of neurons in each layer.
		/// @return vector with numbers of neurons for each layers of our feed-forward NN. It starst with input layer number.
		std::vector<unsigned int> getNeuronsNumberEachLayer()const;

		/// Get the name of the NN. It depends which type of NN it is (Protoss, Terran, Zerg)
		/// @return string name of the network.
		virtual std::string getName() = 0;

		/// Creates a name for our neural network. The name of the file is based on type of neural network, number of layers, learning rate and number of neurons in each layer.
		/// @param netModel The NN type for Protoss, Zerg or Terran.
		std::string createNameFile();

		/// Sets the learning rate for our NNs.
		/// @param learningRate Learning rate for our NN.
		void setlearningRate(double learningRate);

	protected:
		/// Get the output vector of the neural network.
		/// @return The output vector with units and building according to their ID in BWAPI::UnitTypes
		virtual std::vector<int> getOutputV() = 0;

		/// Network with all loaded information.
		network<sequential> net;

		/// Object for I/O operations with files.
		CFileIOHandler fileHandler;

		/// Create default NN.
		virtual void createNN() = 0;

		/// True if the network is initialized and created. False otherwise.
		bool created;

		/// Number of all layers in our NN.
		unsigned int numOfLayers;

		/// Number of neurons in each layer of our NN.
		std::vector<unsigned int> numOfNeurons;

	private:
		/// Last predicted model of our opponent.
		CPlayerModel * predictedOppModel;

		/// Tiny_dnn optimizer for the NN.
		adagrad optimizerForNN;

		/// Batch size.
		size_t batch_size;

		/// Number of epochs.
		unsigned int epochs;

	};

}
#endif // ___NEURALNETWORKMODEL___