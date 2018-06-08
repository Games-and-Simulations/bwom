#ifndef ___NEURALNETWORKHANDLER___
#define ___NEURALNETWORKHANDLER___

#include "./NNFiles/ProtossNN.h"
#include "./NNFiles/TerranNN.h"
#include "./NNFiles/ZergNN.h"
#include "./NNFiles/NeuralNetworkModel.h"

namespace OpponentModelling {

	/// Class that handles all operations with neural networks. It is used for creating own net, training it
	/// and testing. It also handles networks used for prediction during the game.    
	class CNeuralNetworkHandler {

	public:
		/// Default constructor, initializes the object.
		CNeuralNetworkHandler();

		/// Train all networks object holds with given data set.
		/// @param FilePath File with names of all log files you want to train the NN with.
		/// @param LogFilePath Path to folder where all log files with training data are located.
		void trainNNWithDataSet(std::string FilePath, std::string LogFilePath);

		/// Tests all NNs with given data set.
		/// @param FilePath File with names of all log files you want to test the NN with.
		/// @param LogFilePath Path to folder where all log files with test data are located.
		void testNN(std::string FilePath, std::string LogFilePath);

		/// Sets number of epochs for NNs.
		/// @param epochs Int with number of epochs you want for the NNs.
		void setEpochs(unsigned int epochs);

		/// Sets batch size for NNs.
		/// @param batchSize Batch size you want for your NNs.
		void setBatchSize(unsigned int batchSize);

		/// Predicts opponents game state based on given input data. It youses train NNs for the prediction.
		/// @param currentState Current state of the game. Knowledge of your opponent represented as CPlayerModel object.
		/// @return CPlayerModel object with predicted state for which are the NNs trained. Default time is 3 minutes.
		CPlayerModel * predictOpponetGameState(CPlayerModel * currentState);

		/// Creates NNs based on given parameters.
		/// @param numOfLayers Represents number of hidden layers.
		/// @param neuronsInEachLayer Is a vector with number of neurons for each hidden layer.
		void createNN(unsigned int numOfLayers, std::vector<unsigned int> neuronsInEachLayer);

		/// Sets the learning rate for our NNs.
		/// @param learningRate Learning rate for our NN.
		void setlearningRate(double learningRate);

	private:
		/// Creates a name for our neural network. The name of the file is based on type of neural network, number of layers, learning rate and number of neurons in each layer.
		/// @param netModel The NN type for Protoss, Zerg or Terran.
		std::string createNameFile(CNeuralNetworkModel * netModel);

		/// Handler of IO operations
		CFileIOHandler fileHandler;
		
		/// Protoss NN.
		CProtossNN pNN;

		///Terran NN.
		CTerranNN tNN;
		
		/// Zerg NN.
		CZergNN zNN;

	};

}
#endif // ___NEURALNETWORKHANDLER___