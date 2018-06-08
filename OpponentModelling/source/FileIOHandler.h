#ifndef __LOADINPUTFROMFILE___
#define __LOADINPUTFROMFILE___

#include "./json/json.hpp"
#include <fstream>
#include <set>
#include "ProtossPlayer.h"
#include "ZergPlayer.h"
#include "TerranPlayer.h"
#include "BWAPI.h"

using json = nlohmann::json;

namespace OpponentModelling {

	/// Structure which is used for passing data as inputs into our neural network. 
	struct InputOutputData {
		
		/// Vector containing numbers of units player has. Those unit numbers positions corresponds to input vector in CPlayerModel child clases. 
		/// @see CProtossPlayer, @see CTerranPlayer, @see CZergPlayer
		std::vector <int> InputData;

		/// Vector containing numbers of units player had after a certain time. Those numbers corresponds to input numbers + units made in the given time. Positions in the vector corresponds to output vector in CPlayerModel child clases. 
		/// @see CProtossPlayer, @see CTerranPlayer, @see CZergPlayer
		std::vector <int> OutputData;

	};

	/// Class that takes care about I/O operations with files, json formating I/O operations
	/// and parsing loaded data into InputOutputData structure for our NN.
	class CFileIOHandler {
		
	public:
		/// Default destructor. Deallocates all previously created InputOutputData structure.
		~CFileIOHandler();

		/// Loads file into json object.
		/// @param FileName Descrives path with filename that should be loaded into json
		/// @return True if it succesed, false otherwise.
		bool LoadJsonFileInput(const char * FileName);

		/// Getter for json.
		/// @return class json object that handles json operations.
		json getJsonObject();

		/// Function that parses loadaed data in json into vector of InputOutputData structres.
		/// @return Vector of all predictions from json object previously loaded into it.
		std::vector<InputOutputData*> ParseJsonToInputOutput();

		/// Function that writes data into file.
		/// @param FilePath Specifies the path to file where data will be saved. If the file already exists, it puts output to the EOF.
		/// @param message String data that we want to print into file.
		void WriteIntoFile(const char * FilePath, const std::string & message);

		/// Loads all lines of file into set.
		/// @param FilePath Specifies the path to file from which we want to load the data.
		/// @return Set of strings where each line of the file is represented as a string.
		std::set<std::string> LoadFileIntoSet(const char * FilePath);

	private:

		/// Function deletes all previously allocated InputOutputData structrues.
		void deleteDataSet();

		/// Function opens a given file and opens an ifstream.
		/// @param FileName File we want to open.
		/// @return True if there was no problem with file oppening. False otherwise.
		bool openFile(const char * FileName);

		/// Vector of all previously allocated InputOutputData structures.
		std::vector <std::vector<InputOutputData*> > vectorOfAllIODataCreated;

		/// Prints given message into error file.
		/// @param message Message that will be printed into the file.
		void ErrorMess(std::string message);

		/// Closes file that was previously opened and closes the ifstream.
		void closeFile();

		/// Parses all loaded input data for the NN from json object.
		/// @param model It is used to know the input vector size and its values.
		/// @param tmp pointer to allocated structure where we want to save the input.
		void ParseOnlyInput(CPlayerModel * model, std::string prediction, InputOutputData * tmp);

		/// Parses all loaded output data for the NN from json object.
		/// @param model It is used to know the output vector size and its values.
		/// @param tmp pointer to allocated structure where we want to save the output.
		void ParseOnlyOutput(CPlayerModel * model, std::string prediction, InputOutputData * tmp);

		/// File stream used for input operations with files.
		std::ifstream FileCode;

		/// Json object from external library. It handles all json formating and I/O operations.
		/// Link to its documentation: https://github.com/nlohmann/json.
		json j;

	};
}

#endif // __LOADINPUTFROMFILE___