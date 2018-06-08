#include "WriteToFileHandler.h"

CWriteToFileHandler::CWriteToFileHandler() {}

void CWriteToFileHandler::Init(const char * FileName) {
	OpenFile(FileName);
}

void CWriteToFileHandler::Finish() {
	CloseFile();
}

void CWriteToFileHandler::PrintGameState(CGameStateHandler & GSHandler, COpponentModelling & model) {

	const string input = "Input";
	const string output = "Output";

	vector<string> keyValues;
	vector<string> insertValues;

	addData(keyValues, insertValues, GSHandler);

	additionalDataToBeAdded(keyValues, insertValues);

	vector <map <int, int > > tmpMap;
	tmpMap = GSHandler.getInputGameStateVector();

	for (int i = 0; i < GSHandler.getIterator(); i++) // iterate through gamestates
	{
		std::stringstream ss;
		ss << std::setw(5) << std::setfill('0') << i;
		std::string s = ss.str();

		string tmp = string("Prediction ") + s;

			for (auto it : model.getOpponentModel()->getInputUnitVector())	// iterate through map
			{
				if (it == -1) // SUPPLY case
				{
					jObject[tmp][input]["SUPPLY"] = tmpMap.at(i).at(it);
					continue;
				}

				BWAPI::UnitType tmpUnitType(it);

				if (it == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode)
				{
					jObject[tmp][input][tmpUnitType.getName()] = tmpMap.at(i).at(it) + tmpMap.at(i).at(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode);
					continue;
				}

				if (it == BWAPI::UnitTypes::Zerg_Lurker)
				{
					jObject[tmp][input][tmpUnitType.getName()] = tmpMap.at(i).at(it) + tmpMap.at(i).at(BWAPI::UnitTypes::Zerg_Lurker_Egg);
					continue;
				}

				jObject[tmp][input][tmpUnitType.getName()] = tmpMap.at(i).at(it);
			}
	}

	tmpMap = GSHandler.getOutputGameStateVector();

	for (int i = 0; i < GSHandler.getIterator(); i++) // iterate through gamestates
	{
		std::stringstream ss;
		ss << std::setw(5) << std::setfill('0') << i;
		std::string s = ss.str();

		string tmp = string("Prediction ") + s;
		
		for (auto it : model.getOpponentModel()->getOutputUnitVector())	// iterate through map
		{
			BWAPI::UnitType tmpUnitType(it);

			if (it == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode)
			{
				jObject[tmp][output][tmpUnitType.getName()] = tmpMap.at(i).at(it) + tmpMap.at(i).at(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode);
				continue;
			}

			if (it == BWAPI::UnitTypes::Zerg_Lurker)
			{
				jObject[tmp][output][tmpUnitType.getName()] = tmpMap.at(i).at(it) + tmpMap.at(i).at(BWAPI::UnitTypes::Zerg_Lurker_Egg);
				continue;
			}

			jObject[tmp][output][tmpUnitType.getName()] = tmpMap.at(i).at(it);
		}
	}
	
	FileCode << std::setw(4) << jObject << std::endl;

}

void CWriteToFileHandler::WriteIntoFile(const char * FilePath, const string & message) {

	std::ofstream NewFile;
	NewFile.open(FilePath, ios::out | ios::app);
	
	NewFile << message << endl;
	NewFile.close();
}

bool CWriteToFileHandler::OpenFile(const char * FileName) {

	FileCode.open(FileName, std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (!FileCode.is_open())
	{
		ErrorMess(CANT_OPEN_FILE);
		return 0;
	}

	return 1;
}

bool CWriteToFileHandler::CloseFile() {
	FileCode.close();
	return 0;
}

void CWriteToFileHandler::ErrorMess(string message) {

	std::fstream ErroFile;
	std::string FileName = ErrorFilePath;

	ErroFile.open(FileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
	ErroFile << message;
	ErroFile.close();

}

int CWriteToFileHandler::loadIterator() {
	
	std::ifstream IterFile;
	IterFile.open(FilePathLogIterator, std::ifstream::out);

	int tmp;
	IterFile >> tmp;

	return tmp;
}

void CWriteToFileHandler::saveIterator(int iter) {
	
	std::fstream IterFile;
	IterFile.open(FilePathLogIterator, std::fstream::in | std::fstream::out | std::fstream::trunc);

	IterFile << iter;
}

set<string> CWriteToFileHandler::LoadFile(const char * FilePath) {

	std::ifstream iFile;
	iFile.open(FilePath);
	set<string> returnSet;
	string tmpStr;


	while (getline(iFile, tmpStr)) {
		returnSet.insert(tmpStr);
	}
	iFile.close();
	return returnSet;
}

template <class T>
void CWriteToFileHandler::additionalDataToBeAdded(std::vector<T> &KeyValue, std::vector<T> &insertValue) {
	for (int i = 0; i < KeyValue.size(); i++)
		jObject[GAMEINFO][KeyValue.at(i)] = insertValue.at(i);
}

template <class T>
void CWriteToFileHandler::addData(std::vector<T> &KeyValue, std::vector<T> &insertValue, CGameStateHandler & GSHandler) {

	KeyValue.push_back(RACE);
	KeyValue.push_back(OPPRACE);
	KeyValue.push_back(PLAYER_NICK);
	KeyValue.push_back(OPPONENTS_NICK);

	insertValue.push_back(GSHandler.currentPlayer->getRace().getName());
	insertValue.push_back(GSHandler.opponentPlayer->getRace().getName());
	insertValue.push_back(GSHandler.currentPlayer->getName());
	insertValue.push_back(GSHandler.opponentPlayer->getName());
}