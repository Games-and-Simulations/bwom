#include "FileIOHandler.h"

using namespace OpponentModelling;
using json = nlohmann::json;

CFileIOHandler::~CFileIOHandler() {
	deleteDataSet();	
}

void CFileIOHandler::deleteDataSet() {

	for (auto it : vectorOfAllIODataCreated) {
		for (auto i : it)
			delete i;
	}
	vectorOfAllIODataCreated.clear();
}

bool CFileIOHandler::LoadJsonFileInput(const char * FileName) {
	

	if (LoadFileIntoSet(FileName).empty())
		return 0;

	if (!openFile(FileName))
		return 0;


	j.clear();

	FileCode >> j;
	
	closeFile();

	return 1;
}


bool CFileIOHandler::openFile(const char * FileName) {

	FileCode.open(FileName);

	if (!FileCode.is_open())
	{
		ErrorMess(CANT_OPEN_FILE);
		return 0;
	}

	return 1;
}

void CFileIOHandler::ErrorMess(std::string message) {

	std::fstream ErroFile;
	std::string FileName = ERROR_FILE_PATH_NAME;

	ErroFile.open(FileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
	ErroFile << message;
	ErroFile.close();

}

void CFileIOHandler::closeFile() {
	FileCode.close();
}

json CFileIOHandler::getJsonObject() {
	return j;
}


std::vector<InputOutputData*> CFileIOHandler::ParseJsonToInputOutput() {
	
	std::vector<InputOutputData*> vectorReturn;

	if (j.find(RACE) == j.end())
		return vectorReturn;

	const std::string Race = j[RACE];

	CPlayerModel *model = nullptr;
	if (Race == BWAPI::Races::Zerg.getName())
		model = new CPlayerZerg();
	else if (Race == BWAPI::Races::Terran.getName())
		model = new CPlayerTerran();
	else if (Race == BWAPI::Races::Protoss.getName())
		model = new CPlayerProtoss();
	
	deleteDataSet();
	
	int i = 0;
	while (true)
	{

		std::stringstream ss;
		ss << std::setw(5) << std::setfill('0') << i;
		std::string prediction = std::string("Prediction ") + ss.str();

		if (j.find(prediction) == j.end())
			break;

		InputOutputData *tmp = new InputOutputData();

		ParseOnlyInput(model, prediction, tmp);
		ParseOnlyOutput(model, prediction, tmp);

		vectorReturn.push_back(tmp);

		++i;
	}
	if (model != nullptr)
		delete model;

	vectorOfAllIODataCreated.push_back(vectorReturn);
	return vectorReturn;
}

void CFileIOHandler::ParseOnlyInput(CPlayerModel * model, std::string prediction, InputOutputData * tmp) {
	
	const std::string INPUT = "Input";

	for (auto it : model->getInputUnitVector())
	{

		if (it == -1) // SUPPLY case
		{
			tmp->InputData.push_back(j[prediction][INPUT]["SUPPLY"].get<int>());
			continue;
		}

		BWAPI::UnitType tmpUnitType(it);
		tmp->InputData.push_back(j[prediction][INPUT][tmpUnitType.getName()].get<int>());
	}
	
}

void CFileIOHandler::ParseOnlyOutput(CPlayerModel * model, std::string prediction, InputOutputData * tmp) {

	const std::string OUTPUT = "Output";

	for (auto it : model->getOutputUnitVector())
	{
		BWAPI::UnitType tmpUnitType(it);
		tmp->OutputData.push_back(j[prediction][OUTPUT][tmpUnitType.getName()].get<int>());
	}
	
}

void CFileIOHandler::WriteIntoFile(const char * FilePath, const std::string & message) {

	std::ofstream NewFile;
	NewFile.open(FilePath, std::ios::out | std::ios::app);

	NewFile << message << std::endl;
	NewFile.close();
}

std::set<std::string> CFileIOHandler::LoadFileIntoSet(const char * FilePath) {

	std::ifstream iFile;
	iFile.open(FilePath);
	std::set<std::string> returnSet;
	std::string tmpStr;
	if (!iFile.is_open())
		return returnSet;

	while (getline(iFile, tmpStr)) {
		returnSet.insert(tmpStr);
	}
	iFile.close();
	return returnSet;
}