#include "ProtossNN.h"

namespace OpponentModelling {
	using namespace tiny_dnn;
	using namespace tiny_dnn::activation;
	using namespace tiny_dnn::layers;

	CProtossNN::CProtossNN() : CNeuralNetworkModel() {
		init();
	}

	void CProtossNN::init() {
		if (!created)
			createNN();
	}

	void CProtossNN::createNN() {
		int numOfHiddenLayers = 4;
		std::vector<unsigned int> neuronsInEachLayer = {30,35,35,30};
		createNN(numOfHiddenLayers, neuronsInEachLayer);
	}

	void CProtossNN::createNN(unsigned int numOfHiddenLayers, std::vector<unsigned int> neuronsInEachLayer) {

		network<sequential> netTmp;

		numOfNeurons.clear();
		numOfNeurons.push_back(CPlayerProtoss::inputUnitVector.size());
		for (int i = 0; i < numOfHiddenLayers; i++)
			numOfNeurons.push_back(neuronsInEachLayer.at(i));
		numOfNeurons.push_back(CPlayerProtoss::outputUnitVector.size());

		// Input layer
		netTmp << tiny_dnn::fully_connected_layer(CPlayerProtoss::inputUnitVector.size(), numOfNeurons.at(1));

		// Hidden layers
		for (int i = 1; i < numOfHiddenLayers; i++)
			netTmp << tiny_dnn::fully_connected_layer(numOfNeurons.at(i), numOfNeurons.at(i + 1));

		// Ouptut layer
		netTmp << tiny_dnn::fully_connected_layer(numOfNeurons.at(numOfNeurons.size() - 2), CPlayerProtoss::outputUnitVector.size());

		created = 1;
		numOfLayers = 2 + numOfHiddenLayers;
		net = netTmp;
	}

	void CProtossNN::saveNeuralNetwork(std::string FileName) {
		std::string wheretoSave = std::string(NNPATHTOBINFILE) + FileName;
		net.save(wheretoSave);
	}

	void CProtossNN::loadNeuralNetwork(std::string FileName) {
		net.load(FileName);
	}

	std::string CProtossNN::getName() {
		return "ProtossNN";
	}

	std::vector<int> CProtossNN::getOutputV() {
		return CPlayerProtoss::outputUnitVector;
	}
}