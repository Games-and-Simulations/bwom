#ifndef __OPPMODELING___
#define __OPPMODELING___

#include "./NNFiles/NeuralNetworkHandler.h"
#include "BWAPI.h"

/*! \mainpage Opponent Modelling Library for StarCraft AI
*
* \section Description
*
* A C++ library written on top of BWAPI framework for Starcraft AI bots.
* It allows easy modelling of their opponent,
* inference additional information based on scouting and 
* predict opponents future game state based using a feedforward neural network.
* Library is provided with all the source codes and many parts of it, such as creating own neural network
* can be easily extended by the programmer.
*
*
* \subsection UnitDatabase Unit Database
* Because BWAPI does not allow AI agents to access any unit covered by the fog of war,
* the library allows programmers to save all previously seen units as its special objects.
* It copies all necessary information and provides it, whenever there is a request
* by the AI module.
* 
* \subsection Inference Inference
* Based on scouted information, library automatically inference additional data about an opponent.
* Whenever bot scouts a unit, using each race technology tree, we can deduce all requirements needed  
* and add them into our database if they are not already in it.
*
* \subsection Prediction Prediction
* Using trained feedforward network we predict opponents units and building in near future (default configuration is 3 minutes). 
* We pass currently scouted information into the network and it gives us back opponents numbers in the future.
* 
*
* \subsection thirdParty Used third party libraries
* In the implementation are used two external libraries. The first one, Niels Lohmann's JSON,
* is used for input and output operations with files using JSON format. The second one, Tiny_dnn,
* is used for creating neural networks and learning them the ability to predict opponent's future unit composition
* 
* Niels Lohmann's JSON is written for Modern C++ and C++11 as header-only JSON class.
* It is very intuitive for usage, especially because it works similarly as C++11 STL containers. 
* In fact, it even satisfies the ReversibleContainer requirement ReverSibleCont. 
* Usage in Opponent Modelling is for saving data into files in JSON format in order to make it easy for humans 
* to read and for machines to parse and generate.
*	
* Tiny_dnn is a C++14 implementation of deep learning. It is suitable for deep learning on limited computational resource,
* embedded systems and IoT devices. Tiny_dnn is pure C++ portable and header-only implementation which requires no installation
* of any additional software. It has clear understandable documentation with tutorial guide and usage explanation on various examples.
* All of the advantages are the reason why it has been chosen for implementing neural network in Opponent Modelling library.
*
* \subsection GettingStarted Getting started
* BWOM is avaible from https://github.com/Games-and-Simulations/bwom, it is a visual studio project avaible with all the source code 
* that can be adjusted for programmers requirements. This tutorial helps integrating project into your bot and setting everything, such as
* environmental variables, for proper run.
* - Download the Opponent Modelling library
*	-# Go to https://github.com/Games-and-Simulations/bwom and download the project as a zip file.
*	-# Create your own custom folder and extract downloaded zip file there.
* - Donwload Tiny_dnn library
*	-# Tiny_dnn can be downloaded directly from https://github.com/tiny-dnn/tiny-dnn. Download the zip file and extract it in 
*   ./OpponentModelling/source folder.
	-# Rename the extracted folder "tiny-dnn-master" to "tiny-dnn".
	 -# Now you should have tiny-dnn folder with extracted content in the source folder of the project.
* - Set environmental variables and configurate the project
*	-# Visual studio project uses environmental variables for BWAPI and Tiny_dnn library. You have to either
*		adjust the paths in the project or set them in your computer.
*	-# to set them in your computer, follow this tutorial: https://www.java.com/en/download/help/path.xml and add two more variables.
*	-# Create new environmental variable called "BWAPI_DIR" with path to your BWAPI directory.
*	-# If you don't want to create new environmental variable, you can just adjust project settings and set the path directly to your BWAPI directory.
*	-# Now you must change paths in Configuration.h. It contains paths to the solution folder and its files. Change them to the location where you have OpponentModelling project downloaded
* - Build the library
*	-# Open the visual studio solution file (./OpponentModelling/OpponentModelling.sln) and build the library.
*	-# The created file OpponentModelling_r.lib or OpponentModelling_d.lib is created and located based on your build option release/debug in 
*		./OpponentModelling/OpponentModelling/Release or ./OpponentModelling/OpponentModelling/Debug folder.
* - Use in your project
*   -# Include OpponentModelling.h file located in ./OpponentModelling/source folder.
*	-# Link the created .lib file to your project.
*
* \section Examples Usage with examples
*
* - Integration with AI module
*	-# Create an instance of COpponentModelling class. This instance will be used for all functionalities library provides.
*	-# In order to initialize and update this object, you must call specific methods in BWAPI AI module methods. Their names
*		corresponds with your module function's names. Those methods are onStart(BWAPI::Player self, BWAPI::Player enemy), onEnd(bool isWinner)
*		onFrame(), onUnitDiscover(BWAPI::Unit unit), onUnitShow(BWAPI::Unit unit), onUnitCreate(BWAPI::Unit unit),onUnitDestroy(BWAPI::Unit unit),
*		onUnitMorph(BWAPI::Unit unit), onUnitRenegade(BWAPI::Unit unit) and onUnitComplete(BWAPI::Unit unit). \n 
*		Example:\n \n
*		void onUnitDiscover(BWAPI::Unit unit){\n
*		\*\*\* \n
*		\t myOppModelObject.onUnitDiscover(unit);
*		\n 
*		\*\*\* \n
*		} \n
*	-# Now you can use the object methods for your bot. For accessing the unit database, use your COpponentModelling object.
*
* - CreateOwnNN Creating and Training custom neural network
*	-# At first, make sure you set all paths in the ConfigurationFile.h to match the location where you extracted the project
*	-# For creating custom NN, we recommend to create a new project.
*	-# For creating a neural network, you need CNeuralNetworkHandler instance. It allows you to set networks parameters, number of 
*		hidden layers and number of neurons in each layer.\n
	Example:\n \n
	unsigned int numOfHiddenLayers = 2;\n
	std::vector <unsigned int> NumOfNeuronsVector;\n
	\n
	NumOfNeuronsVector.push_back(30);\n
	NumOfNeuronsVector.push_back(25);\n
	CNeuralNetworkHandler MyCustomNN;\n
	MyCustomNN.setEpochs(1);\n
	MyCustomNN.setlearningRate(0.001);\n
	MyCustomNN.createNN(numOfHiddenLayers, NumOfNeuronsVector);\n
	\n \n
	-# For Training and Testing the network, you need a set of parsed log files parsed using ReplayPseudoBot also located in https://github.com/Games-and-Simulations/bwom
*	-# You can start training your network by calling function:\n \n
	MyCustomNN.trainNNWithDataSet(PathToFolderWithLogFiles, PathToFileWithLogNames);\n \n
	where PathToFolderWithLogFiles represents path to the folder where you have parsed log files you want to train your NN with and 
	PathToFileWithLogNames represents path to file with names of all log files you want to train your NN with from the directory.
	-# For testing your neural network use the CNeuralNetworkHandler instance like this:\n \n
	MyCustomNN.testNN(PathToFolderWithTestLogFiles, PathToFileWithTestLogNames);\n \n
	where PathToFolderWithTestLogFiles represents path to the folder where you have parsed log files you want to test your NN with and
	PathToFileWithTestLogNames represents path to file with names of all test log files you want to test your NN with from the directory.
	-# This process saves important information during training and testing such as MSE from each log file or results from testing in OpponentModelling folder
	called NeuralNetworkInfoFiles. The trained bin network is saved in directory called binNeuralNetworks.
*
*
*/

namespace OpponentModelling {

	/// Class that handles all necessary action for opponent modelling.
	/// It has all functions name similar to BWAPI::AIModule.
	/// Those functions should be called in AIModule functions acording to their name.
	class COpponentModelling {

	public:

		/// Default constructor. Initialize the object. However, you should always 
		/// call function init() before using COpponentsModeling object.
		/// @see init(BWAPI::Player self, BWAPI::Player enemy).
		COpponentModelling();

		/// Overloaded constructor for creating the object and initializing its values. However, you should always 
		/// call function init() before using COpponentsModeling object.
		/// @see init(BWAPI::Player self, BWAPI::Player enemy).
		COpponentModelling(BWAPI::Player self, BWAPI::Player enemy);

		/// Default destructor. Deallocetes memory used by this object.
		~COpponentModelling();

		/// Getter for opponents game model holding all information about him.
		/// @return CPlayerModel object representing an opponent.
		CPlayerModel *COpponentModelling::getOpponentModel() const;

		/// Getter for selff game model holding all information about ourselves.
		/// @return CPlayerModel object representing self player.
		CPlayerModel *COpponentModelling::getSelfModel() const;

		/// Init function that should be called to initialize this object.
		void init(BWAPI::Player self, BWAPI::Player enemy);

		/// Function for getting enemy player.
		/// @return BWAPI Enemy player 
		BWAPI::Player enemyP()const;

		/// Funciton returns predicted opponents game state 
		CPlayerModel *PredictOpponentsGameState();

		/* BWAPI Bot funcitons */
		/// BWAPI AI Module function. Should be called in onStart method.
		void onStart(BWAPI::Player self, BWAPI::Player enemy);

		/// BWAPI AI Module function. Should be called in onEnd method.
		void onEnd(bool isWinner);
		
		/// BWAPI AI Module function. Should be called in onFrame method.
		void onFrame();

		/// BWAPI AI Module function. Should be called in onUnitDiscover method.
		void onUnitDiscover(BWAPI::Unit unit);

		/// BWAPI AI Module function. Should be called in onUnitShow method.
		void onUnitShow(BWAPI::Unit unit);
		
		/// BWAPI AI Module function. Should be called in onUnitCreate method.
		void onUnitCreate(BWAPI::Unit unit);

		/// BWAPI AI Module function. Should be called in onUnitDestroy method.
		void onUnitDestroy(BWAPI::Unit unit);

		/// BWAPI AI Module function. Should be called in onUnitMorph method.
		void onUnitMorph(BWAPI::Unit unit);

		/// BWAPI AI Module function. Should be called in onUnitRenegade method.
		void onUnitRenegade(BWAPI::Unit unit);

		/// BWAPI AI Module function. Should be called in onUnitComplete method.
		void onUnitComplete(BWAPI::Unit unit);
		/* BWAPI Bot funcitons */

	private:

		/// Handler for neural network prediction. Using this object, we can access created NNs and use them for prediction of our opponents future game state.
		CNeuralNetworkHandler NNForOpponentPrediction;

		/// Pointer to opponent object
		CPlayerModel *Opponent;
		
		/// Self storing data object
		CPlayerModel *SelfGameModel;
		
		/// Last predicted state return by function Predict opponents state.
		/// @see PredictOpponentsGameState
		CPlayerModel *PredictedState;
		
		/// Self player.
		BWAPI::Player self;

		/// Enemy player.
		BWAPI::Player enemy;

		/// Update unit in our game state
		void updateUnit(BWAPI::Unit unit);

		/// Remove unit from our game state
		void removeUnit(BWAPI::Unit unitID);

	};
}


#endif // __OPPMODELING___