#pragma once
#include "BWAPI.h"
#include <queue>
#include "OpponentModelling.h"

using namespace std;
using namespace OpponentModelling;

/// Class handles game states during the game and saves them.
/// For every saved game state, it saves another one with 3 minute delay.
/// To the second game state, there are new units added that were created by the player.
/// Game state is represented by a map. Key value is a BWAPI::UnitType (Marine, Zergling, Probe...) 
/// and the value is how many units of this given type player has.
class CGameStateHandler {

public:

	CGameStateHandler();

	/// Retrieves next time in the queue.
	/// @return Next time when the game states should be saved.
	int getNextTime()const;

	/// Retrieves iterator on last game state that will be saved.
	/// @ return Position of current game state that will be saved next.
	int getIterator()const;

	/// Pops element of the queue
	void popQueue();

	/// Adds new game state to both Input and Output vectors.
	/// To output vector game states units are being added for next 3 minutes.
	void addNewGameState();

	/// When time is up for current game state (3 minutes after initial save of it),
	/// we can save both - input and output - game states and print them into log file.
	void saveBothIOGameStates();

	/// Method Adds unit to output game state.
	/// the difference between input and output game state are units that were created during those 3 minutes.
	/// Time countdown for every game state starts at the time we save it.
	/// @param unit BWAPI unit we want to add to output state.
	/// @param model OpponentModelling object that hold info about out opponent.
	void addUnitOutputGameState(BWAPI::Unit unit, COpponentModelling &model);

	/// Class holds current game state.
	/// By calling this function we update its data.
	/// @param model OpponentModelling object that hold info about out opponent.
	void updateCurrentGameState(COpponentModelling &model);

	/// Sets the player we want to track.
	/// @param p Player we want to track.
	void setPlayer(BWAPI::Player p, BWAPI::Player o, std::string mpName);

	/// Sets seconds for prediction between Input and Output state.
	/// @param seconds between Input and corresponding Output games which states we want to save.
	void CGameStateHandler::setPredictionTime(int predT);

	/// Vector holding all saved game states in real time.
	/// For every game state in this vector should be other one created in Output vector.
	vector <map <int, int> > getInputGameStateVector();

	/// Vector holding all saved game states in real time + added information for 3 minutes after the save.
	vector <map <int, int> > getOutputGameStateVector();

	/// Current player we are saving the game states about.
	BWAPI::Player currentPlayer;

	/// Opponent that current player we are observing is plazing against.
	BWAPI::Player opponentPlayer;

	/// String holding map's name.
	std::string mapName;

private:
	/// Whenever a game state is saved, we need to remember time after three minutes.
	/// After a game state is saved a time when it will be ready for output file (+ 3 minutes)
	/// is stored in timerQueue.
	queue <int> timerQueue;

	/// Adds time for awakening next game state for final save.
	/// @param time Int that will be added to the queue
	void addTime(const int time);

	/// Iterator representing current position on output game states.
	int iterator;

	/// Current ingame state. It is being updated in real time using @updateCurrentGameState
	map <int, int> currentGameState;

	/// All input game states stored in vector.
	/// We need to remember them in order to output them into output file.
	vector <map <int, int> > inputGameState;

	/// All output game states stored in vector.
	/// We need to remember them in order to output them into output file.
	/// Every output game state coresponds to a certain input game state - 
	/// the game state on the same position in the vector.
	vector <map <int, int> > outputGameState;


	/// In order to prevent saving redundant game states. We will store two game states 
	/// with at least a small delay. The delay is checked using prevTime variable.
	int prevTime;

	/// This integer value defines how many seconds must pass after game state is saved, so corresponding output game state is saved with it.
	int predictionTime;
	

};