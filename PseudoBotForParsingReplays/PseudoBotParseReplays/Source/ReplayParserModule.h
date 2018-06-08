#pragma once
#include <BWAPI.h>
#include "WriteToFileHandler.h"
#include "GameStateHandler.h"
#include "ConfigPseudoBot.h"
#include <iostream>
#include "OpponentModelling.h"

// Remember not to use "Broodwar" in any global class constructor!

/** \mainpage Replay Parser Pseudo Bot
*
* \section Description
* Pseudo bot is an AI module used for parsing replays into log files that serves as an input for Opponent Modelling neural network.
* Whenever a new unit is created pseudo bot saves two new game states (input and output game state) and adds current
* time plus three minutes into its time queue. Every next created unit in those three minutes is added to the output game state. 
* The implemented time queue checks game time every frame and if it matches with time on the front of the queue, 
* it saves the original input state and modified one, which contains all units as the input state plus units created in three minutes. 
* Game states are saved into file using JSON format for easy machine parsing and human reading. Both projects with all the source code
* can be download from https://github.com/Games-and-Simulations/bwom.
*
*\subsection setting Setting pseudo bot
* Pseudo bot for parsing replays operates with four text files and one directory. 
* Pseudo bot output JSON file can be modified by adding or removing source code from addData method located in CWriteToFileHandler class.
* The method takes two vectors, where the first one describes key values for saved JSON and the second one their corresponding values.
* The default settings of this method can be seen in addData method.
*
*	- ReplayLogs is a directory containing all log files parsed by pseudo bot. Parsed data are saved there directly as text files if the location is not specified to a different folder.
*	- Iterator.txt This file contains a single digit number. It is a counter value in order to numerize parsed replays.
*	- ReplayLogNames.txt is a text file containing names of log files parsed by the bot.
*	- ReplayOriginalNames.txt is a text file containing names of all parsed replays. It helps to keep track about already parsed replays.
*	- ConfigPseudoBot.h is a configuration file defining paths to locations of previously mentioned files.
*
*	
*/


class ReplayParserModule : public BWAPI::AIModule
{
public:
  // Virtual functions for callbacks, leave these as they are.
  virtual void onStart();
  virtual void onEnd(bool isWinner);
  virtual void onFrame();
  virtual void onSendText(std::string text);
  virtual void onReceiveText(BWAPI::Player player, std::string text);
  virtual void onPlayerLeft(BWAPI::Player player);
  virtual void onNukeDetect(BWAPI::Position target);
  virtual void onUnitDiscover(BWAPI::Unit unit);
  virtual void onUnitEvade(BWAPI::Unit unit);
  virtual void onUnitShow(BWAPI::Unit unit);
  virtual void onUnitHide(BWAPI::Unit unit);
  virtual void onUnitCreate(BWAPI::Unit unit);
  virtual void onUnitDestroy(BWAPI::Unit unit);
  virtual void onUnitMorph(BWAPI::Unit unit);
  virtual void onUnitRenegade(BWAPI::Unit unit);
  virtual void onSaveGame(std::string gameName);
  virtual void onUnitComplete(BWAPI::Unit unit);
  // Everything below this line is safe to modify.

  COpponentModelling *model;
  COpponentModelling *model1;

  CWriteToFileHandler file;
  CWriteToFileHandler file1;

  CGameStateHandler GSHandler;
  CGameStateHandler GSHandler1;

  // Detects if we have already seen this replay
  bool ReplayAlreadySeen;
  BWAPI::Player p1;
  BWAPI::Player p2;


};
