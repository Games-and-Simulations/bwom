#include "./NNFiles/NeuralNetworkHandler.h"

namespace OpponentModelling {

	CNeuralNetworkHandler::CNeuralNetworkHandler() {
		pNN.loadNeuralNetwork();
		zNN.loadNeuralNetwork();
		tNN.loadNeuralNetwork();
	}

	void CNeuralNetworkHandler::trainNNWithDataSet(std::string FilePath = LOG_REPLAYS_PATH, std::string LogFilePath = LOG_REPLAY_NAMES_FILE) {

		std::set<std::string> tmpSet = fileHandler.LoadFileIntoSet(LogFilePath.c_str());
		std::set<std::string>::iterator it;
		int i = 0;
		double sumedLossZ = 0;
		double sumedLossT = 0;
		double sumedLossP = 0;

		for (auto it : tmpSet)
		{
			std::string FileName = FilePath + it;
			if (!fileHandler.LoadJsonFileInput(FileName.c_str()))
				continue;

			if (fileHandler.getJsonObject()[RACE] == BWAPI::Races::Protoss.getName())
				sumedLossP += pNN.trainNN(fileHandler.ParseJsonToInputOutput());
			else if (fileHandler.getJsonObject()[RACE] == BWAPI::Races::Terran.getName())
				sumedLossT += tNN.trainNN(fileHandler.ParseJsonToInputOutput());
			else if (fileHandler.getJsonObject()[RACE] == BWAPI::Races::Zerg.getName())
				sumedLossZ += zNN.trainNN(fileHandler.ParseJsonToInputOutput());

			if (++i % 20 == 0)
			{
				pNN.saveNeuralNetwork(createNameFile(&pNN) + std::string("_bin"));
				tNN.saveNeuralNetwork(createNameFile(&tNN) + std::string("_bin"));
				zNN.saveNeuralNetwork(createNameFile(&zNN) + std::string("_bin"));
			}
		}
		std::string FileNameErr = NN_FILES_PATH + pNN.createNameFile() + std::string(" LOSS.txt");
		fileHandler.WriteIntoFile(FileNameErr.c_str(), std::string("Summed Error: ") + to_string(sumedLossP));

		FileNameErr = NN_FILES_PATH + tNN.createNameFile() + std::string(" LOSS.txt");
		fileHandler.WriteIntoFile(FileNameErr.c_str(), std::string("Summed Error: ") + to_string(sumedLossT));

		FileNameErr = NN_FILES_PATH + zNN.createNameFile() + std::string(" LOSS.txt");
		fileHandler.WriteIntoFile(FileNameErr.c_str(), std::string("Summed Error: ") + to_string(sumedLossZ));

		pNN.saveNeuralNetwork(createNameFile(&pNN) + std::string("_bin"));
		tNN.saveNeuralNetwork(createNameFile(&tNN) + std::string("_bin"));
		zNN.saveNeuralNetwork(createNameFile(&zNN) + std::string("_bin"));
	}

	std::string CNeuralNetworkHandler::createNameFile(CNeuralNetworkModel * netModel) {

		return netModel->createNameFile();
	}

	void CNeuralNetworkHandler::testNN(std::string FilePath, std::string LogFilePath) {

		std::set<std::string> tmpSet = fileHandler.LoadFileIntoSet(LogFilePath.c_str());
		std::set<std::string>::iterator it;
		double fErrorProtossNet = 0;
		double fErrorTerranNet = 0;
		double fErrorZergNet = 0;

		for (auto it : tmpSet)
		{
			std::string FileName = FilePath + it;
			if (!fileHandler.LoadJsonFileInput(FileName.c_str()))
				continue;

			if (fileHandler.getJsonObject()[RACE] == BWAPI::Races::Protoss.getName())
				fErrorProtossNet += pNN.testNN(fileHandler.ParseJsonToInputOutput());
			else if (fileHandler.getJsonObject()[RACE] == BWAPI::Races::Terran.getName())
				fErrorTerranNet += tNN.testNN(fileHandler.ParseJsonToInputOutput());
			else if (fileHandler.getJsonObject()[RACE] == BWAPI::Races::Zerg.getName())
				fErrorZergNet += zNN.testNN(fileHandler.ParseJsonToInputOutput());
		}

		std::string FileNameErr = NN_FILES_PATH + pNN.createNameFile() + std::string(" TEST_ERROR.txt");
		fileHandler.WriteIntoFile(FileNameErr.c_str(), std::string("Summed Error: ") + to_string(fErrorProtossNet));

		FileNameErr = NN_FILES_PATH + tNN.createNameFile() + std::string(" TEST_ERROR.txt");
		fileHandler.WriteIntoFile(FileNameErr.c_str(), std::string("Summed Error: ") + to_string(fErrorTerranNet));

		FileNameErr = NN_FILES_PATH + zNN.createNameFile() + std::string(" TEST_ERROR.txt");
		fileHandler.WriteIntoFile(FileNameErr.c_str(), std::string("Summed Error: ") + to_string(fErrorZergNet));

	}

	void CNeuralNetworkHandler::setEpochs(unsigned int epochs) {
		pNN.setNumOfEpochs(epochs);
		tNN.setNumOfEpochs(epochs);
		zNN.setNumOfEpochs(epochs);
	}

	void CNeuralNetworkHandler::setBatchSize(unsigned int batchSize) {
		pNN.setBatchSize(batchSize);
		tNN.setBatchSize(batchSize);
		zNN.setBatchSize(batchSize);
	}

	CPlayerModel * CNeuralNetworkHandler::predictOpponetGameState(CPlayerModel * currentState) {

		if (currentState == nullptr || currentState->getAllUnits().size() == 0)
			return nullptr;

		BWAPI::Race oppRace = currentState->getAllUnits().at(0)->UnitType.getRace();

		if (oppRace == BWAPI::Races::Zerg)
			return zNN.predictOpponetGameState(currentState);
		else if (oppRace == BWAPI::Races::Terran)
			return tNN.predictOpponetGameState(currentState);
		else if (oppRace == BWAPI::Races::Protoss)
			return pNN.predictOpponetGameState(currentState);

		return nullptr;
	}


	void CNeuralNetworkHandler::createNN(unsigned int numOfLayers, std::vector<unsigned int> neuronsInEachLayer) {
		pNN.createNN(numOfLayers, neuronsInEachLayer);
		tNN.createNN(numOfLayers, neuronsInEachLayer);
		zNN.createNN(numOfLayers, neuronsInEachLayer);
	}


	void CNeuralNetworkHandler::setlearningRate(double learningRate) {
		pNN.setlearningRate(learningRate);
		tNN.setlearningRate(learningRate);
		zNN.setlearningRate(learningRate);
	}
}
