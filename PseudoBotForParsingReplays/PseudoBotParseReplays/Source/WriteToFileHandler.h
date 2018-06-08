#pragma once
#include "OpponentModelling.h"
#include "GameStateHandler.h"
#include "ConfigPseudoBot.h"
#include "json.hpp"
#include <vector>
#include <BWAPI.h>
#include <iostream>
#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <map>
#include <set>

 using namespace OpponentModelling;
 using namespace std;
 using json = nlohmann::json;

/// Handler used for output operations.
/// We want to save harvested data into some file.
/// All data are saved in json format using json object from external library:
/// https://github.com/nlohmann/json

class CWriteToFileHandler {

public:
	CWriteToFileHandler();

	/// Final output function. It creates a new log file for the game
	/// and outputs all game states and corresponding + 3 minutes game states.
	/// @param GSHandler Object with all game states data. Those data will be printed into file.
	/// @param model Opponent model object that holds all input/output requirements. Basically all data we want to store&save
	void PrintGameState(CGameStateHandler & GSHandler, COpponentModelling & model);

	/// Init function opens log file and sets the file stream.
	/// @param FileName Name of the file we want to store the data to.
	void Init(const char * FileName);

	/// Function notifies that we are done with saving data. Closes the filestream and the file.
	void Finish();

	/// Loads the iterator from external file.
	/// Iterator is used for marking replays our bot has parsed.
	int loadIterator();

	/// Saves the new iterator value into the iterator file.
	/// @param iter New iterator value to be saved.
	void saveIterator(int iter);

	/// Function outputs given string to the end of a given file.
	/// @param FilePath Path to the file where we want to output the data.
	/// @param message String we want to print in the file.
	void WriteIntoFile(const char * FilePath, const std::string & message);

	/// Loads all strings in given file into set.
	/// @return set of strings that given file contains.
	std::set<std::string> LoadFile(const char * FilePath);

private:

	/// Stream for file operations - open file, input data ...
	std::fstream FileCode;

	/// Object from external library. Using it, we are able to save data easily in json format into the file.
	json jObject;

	/// Opens file and sets it rdy for use.
	/// @param FileName Name of file we want to open.
	bool OpenFile(const char * FileName);

	/// Closes file that is currently oppened using FileCode stream.
	bool CloseFile();
	
	/// Error messege. It creates an errorFile and prints the error that occured into it.
	void ErrorMess(string message);

	template <class T>
	void additionalDataToBeAdded(std::vector<T> &KeyValue, std::vector<T> &insertValue);

	template <class T>
	void addData(std::vector<T> &KeyValue, std::vector<T> &insertValue, CGameStateHandler & GSHandler);
};
