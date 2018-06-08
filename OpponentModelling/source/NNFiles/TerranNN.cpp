#include "TerranNN.h"

namespace OpponentModelling {

	CTerranNN::CTerranNN() : CNeuralNetworkModel() {
		init();
	}

	void CTerranNN::init() {
		if (!created)
			createNN();
	}

	void CTerranNN::createNN() {
		int numOfHiddenLayers = 4;
		std::vector<unsigned int> neuronsInEachLayer = { 40,45,45,40 };
		createNN(numOfHiddenLayers, neuronsInEachLayer);
	}

	void CTerranNN::createNN(unsigned int numOfHiddenLayers, std::vector<unsigned int> neuronsInEachLayer) {

		network<sequential> netTmp;

		numOfNeurons.clear();
		numOfNeurons.push_back(CPlayerTerran::inputUnitVector.size());
		for (int i = 0; i < numOfHiddenLayers; i++)
			numOfNeurons.push_back(neuronsInEachLayer.at(i));
		numOfNeurons.push_back(CPlayerTerran::outputUnitVector.size());

		netTmp << tiny_dnn::fully_connected_layer(CPlayerTerran::inputUnitVector.size(), numOfNeurons.at(1));
		//net << tiny_dnn::tanh_layer();

		for (int i = 1; i < numOfHiddenLayers; i++)
		{
			netTmp << tiny_dnn::fully_connected_layer(numOfNeurons.at(i), numOfNeurons.at(i + 1));
			//net << tiny_dnn::tanh_layer();
		}

		netTmp << tiny_dnn::fully_connected_layer(numOfNeurons.at(numOfNeurons.size() - 2), CPlayerTerran::outputUnitVector.size());

		created = 1;
		numOfLayers = 2 + numOfHiddenLayers;
		net = netTmp;
	}


	void CTerranNN::saveNeuralNetwork(std::string FileName) {
		std::string wheretoSave = std::string(NNPATHTOBINFILE) + FileName;
		net.save(wheretoSave);
	}

	void CTerranNN::loadNeuralNetwork(std::string FileName) {
		net.load(FileName);
	}

	std::string CTerranNN::getName() {
		return "TerranNN";
	}

	std::vector<int> CTerranNN::getOutputV() {
		return CPlayerTerran::outputUnitVector;
	}
}