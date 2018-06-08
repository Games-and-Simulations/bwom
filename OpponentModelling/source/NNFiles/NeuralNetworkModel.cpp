#include "./NNFiles/NeuralNetworkModel.h"

namespace OpponentModelling {

	CNeuralNetworkModel::CNeuralNetworkModel() {
		created = 0;
		batch_size = 20;
		epochs = 10;
		predictedOppModel = nullptr;
	}

	CNeuralNetworkModel::~CNeuralNetworkModel() {
		if (predictedOppModel != nullptr)
			delete predictedOppModel;
	}

	double CNeuralNetworkModel::trainNN(std::vector<InputOutputData*> & loadedData) {

		std::vector<tiny_dnn::vec_t> inputVector;
		std::vector<tiny_dnn::vec_t> outputVector;
		tiny_dnn::vec_t inputTmp;
		tiny_dnn::vec_t outputTmp;

		// printf loss to file
		double lossS = 0;
		int epochsTmp = 0;
		auto on_enumerate_batch = [&]() {
				lossS += net.get_loss<tiny_dnn::mse>(inputVector, outputVector);
		};

		for (auto it : loadedData) {

			inputTmp.clear();
			outputTmp.clear();

			for (auto intData : it->InputData)
				inputTmp.push_back(intData);

			for (auto intData : it->OutputData)
				outputTmp.push_back(intData);

			inputVector.push_back(inputTmp);
			outputVector.push_back(outputTmp);

		}

		// train
		if (loadedData.size() != 0)
			net.fit<tiny_dnn::mse>(optimizerForNN, inputVector, outputVector, batch_size, epochs,
				on_enumerate_batch,[]() {});
		return lossS;
	}


	float CNeuralNetworkModel::testNN(std::vector<InputOutputData*> & loadedData) {

		float fError = 0;
		float predSum = 0;
		tiny_dnn::vec_t inputTmp;
		tiny_dnn::vec_t outputTmp;


		for (auto it : loadedData) {

			inputTmp.clear();
			outputTmp.clear();

			for (auto intData : it->InputData)
				inputTmp.push_back(intData);

			for (auto intData : it->OutputData)
				outputTmp.push_back(intData);

			tiny_dnn::vec_t predicted = net.predict(inputTmp);

			std::string ResultFile = NN_FILES_PATH + createNameFile() + std::string(" RESULT.txt");
			for (unsigned int i = 0; i < outputTmp.size(); i++)
			{
				BWAPI::UnitType a(getOutputV().at(i));
				fileHandler.WriteIntoFile(ResultFile.c_str(), a.getName() + std::string(" pred = ") + to_string(predicted.at(i)) + std::string("  desired = ") + to_string(outputTmp.at(i)));
			}
			fileHandler.WriteIntoFile(ResultFile.c_str(), std::string("\n"));

			for (int i = 0; i < outputTmp.size(); i++)
			{
				predSum += outputTmp.at(i);
				fError += fabs(predicted.at(i) - outputTmp.at(i));
			}

		}
		std::string FileNameErr = NN_FILES_PATH + createNameFile() + std::string(" TEST_ERROR.txt");
		fileHandler.WriteIntoFile(FileNameErr.c_str(), std::string("Error: ") + to_string(fError) + std::string(" Predicted Sum Value: ") + to_string(predSum));

		return fError;
	}


	void CNeuralNetworkModel::setNumOfEpochs(unsigned int numEpochs) {
		epochs = numEpochs;
	}

	void CNeuralNetworkModel::setBatchSize(unsigned int batchSize) {
		batch_size = batchSize;
	}
	void CNeuralNetworkModel::setlearningRate(double learningRate) {
		optimizerForNN.alpha = learningRate;
	}

	unsigned int CNeuralNetworkModel::getNumOfLayers() const{
		return numOfLayers;
	}

	std::vector<unsigned int> CNeuralNetworkModel::getNeuronsNumberEachLayer() const {
		return numOfNeurons;
	}

	std::string CNeuralNetworkModel::createNameFile() {
		std::string FileNameNetwork = getName() + std::string(" ") + to_string(getNumOfLayers());

		FileNameNetwork += std::string(" layers ");

		for (int i = 0; i < getNumOfLayers() - 1; i++)
		{
			FileNameNetwork += to_string(getNeuronsNumberEachLayer().at(i));
			FileNameNetwork += std::string(" ");
		}

		FileNameNetwork += to_string(getNeuronsNumberEachLayer().at(getNumOfLayers() - 1));
		FileNameNetwork += std::string(" learning rate_ ") + to_string(optimizerForNN.alpha) + std::string("_");
		return FileNameNetwork;
	}

	CPlayerModel* CNeuralNetworkModel::predictOpponetGameState(CPlayerModel * currentState) {

		if (currentState == nullptr || currentState->getAllUnits().size() == 0)
			return nullptr;

		if (predictedOppModel != nullptr)
			delete predictedOppModel;

		BWAPI::Race oppRace = currentState->getAllUnits().at(0)->UnitType.getRace();

		if (oppRace == BWAPI::Races::Zerg)
			predictedOppModel = new CPlayerZerg();
		else if (oppRace == BWAPI::Races::Terran)
			predictedOppModel = new CPlayerTerran();
		else if (oppRace == BWAPI::Races::Protoss)
			predictedOppModel = new CPlayerProtoss();

		tiny_dnn::vec_t inputTmp;

		for (auto it : currentState->getInputUnitVector())
		{
			if (it == SUPPLY)
			{
				inputTmp.push_back(currentState->getSupply());
				continue;
			}

			inputTmp.push_back(currentState->getMapOfAllUnits().at(it).size());
		}

		std::vector<tiny_dnn::vec_t> inputVector;
		inputVector.push_back(inputTmp);
		tiny_dnn::vec_t predicted = net.predict(inputVector)[0];

		for (unsigned int i = 0; i < currentState->getOutputUnitVector().size(); i++)
		{
			BWAPI::UnitType a(currentState->getOutputUnitVector().at(i));
			for (int k = 0; k < round(predicted.at(i)); k++)
				predictedOppModel->addUnit(new CObjectInfo(a, ADD_UNIT_ANY_CASE));
		}

		return predictedOppModel;
	}
}