#include "ZergNN.h"

namespace OpponentModelling {

	CZergNN::CZergNN() : CNeuralNetworkModel() {
		init();
	}

	void CZergNN::init() {
		if (!created)
			createNN();
	}

	void CZergNN::createNN() {
		int numOfHiddenLayers = 4;
		std::vector<unsigned int> neuronsInEachLayer = { 35,50,50,35 };
		createNN(numOfHiddenLayers, neuronsInEachLayer);
	}

	void CZergNN::createNN(unsigned int numOfHiddenLayers, std::vector<unsigned int> neuronsInEachLayer) {

		network<sequential> netTmp;

		numOfNeurons.clear();
		numOfNeurons.push_back(CPlayerZerg::inputUnitVector.size());
		for (int i = 0; i < numOfHiddenLayers; i++)
			numOfNeurons.push_back(neuronsInEachLayer.at(i));
		numOfNeurons.push_back(CPlayerZerg::outputUnitVector.size());

		netTmp << tiny_dnn::fully_connected_layer(CPlayerZerg::inputUnitVector.size(), numOfNeurons.at(1));
		//net << tiny_dnn::tanh_layer();

		for (int i = 1; i < numOfHiddenLayers; i++)
		{
			netTmp << tiny_dnn::fully_connected_layer(numOfNeurons.at(i), numOfNeurons.at(i + 1));
			//net << tiny_dnn::tanh_layer();
		}

		netTmp << tiny_dnn::fully_connected_layer(numOfNeurons.at(numOfNeurons.size() - 2), CPlayerZerg::outputUnitVector.size());

		created = 1;
		numOfLayers = 2 + numOfHiddenLayers;
		net = netTmp;
	}


	void CZergNN::saveNeuralNetwork(std::string FileName) {
		std::string wheretoSave = std::string(NNPATHTOBINFILE) + FileName;
		net.save(wheretoSave);
	}

	void CZergNN::loadNeuralNetwork(std::string FileName) {
		net.load(FileName);
	}

	std::string CZergNN::getName() {
		return "ZergNN";
	}

	std::vector<int> CZergNN::getOutputV() {
		return CPlayerZerg::outputUnitVector;
	}
}