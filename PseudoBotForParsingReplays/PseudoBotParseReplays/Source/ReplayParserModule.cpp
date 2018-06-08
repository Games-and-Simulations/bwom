#include "ReplayParserModule.h"

//BWAPI 420

using namespace BWAPI;
using namespace Filter;

void ReplayParserModule::onStart()
{
	// Get all replays we already parsed
	set<string> tmpSet = file.LoadFile(FileReplayOriginalNames);

	//If we have already parsed this replay, leave the game
	if ((tmpSet.find(BWAPI::Broodwar->mapFileName()) != tmpSet.end()))
	{
		ReplayAlreadySeen = 1;
		BWAPI::Broodwar->leaveGame();
		return;
	}

	ReplayAlreadySeen = 0;
	// Print current replay we are parsing into file.
	file.WriteIntoFile(FileReplayOriginalNames, BWAPI::Broodwar->mapFileName());

	// for fast replay speed
	BWAPI::Broodwar->setLocalSpeed(0);
	BWAPI::Broodwar->setFrameSkip(1);

  Broodwar->enableFlag(Flag::CompleteMapInformation);

  Playerset players = Broodwar->getPlayers();
  std::vector<Player> tmp;

  // We want only two players that are currently playing.
  for (auto a : players)
	  if (!a->isObserver())
		  tmp.push_back(a);

  if (Broodwar->isReplay())
  {
	  if (tmp.size() == 2)	// 1v1 replay, we can init the data.
	  {
		  p1 = tmp[0];
		  p2 = tmp[1];
		  model = new COpponentModelling(p2, p1);
		  model1 = new COpponentModelling(p1, p2);
	  }
	  else  // not 1v1 replay, leave the game, nothing to parse here.
	  {
		 // file.WriteIntoFile(ErrorFilePath, NUMBER_OF_PLAYERS_REPLAY);
		  ReplayAlreadySeen = 1;
		  BWAPI::Broodwar->leaveGame();
		  return;
	  }

	  // setting players we want to save data about + map name
	  GSHandler.setPlayer(p2, p1, BWAPI::Broodwar->mapName()); 
	  GSHandler1.setPlayer(p1, p2, BWAPI::Broodwar->mapName());
	  // setting prediction time (difference in seconds between input and output data in our prediction)
	  GSHandler.setPredictionTime(240);
	  GSHandler1.setPredictionTime(240);
  }

  // Using chaos launcher we can parse a very large number of replays.
  // This iterator will help us to keep track of the number of parsed replays
  int currentIteration = file.loadIterator();

  std::string ReplayName1 = p1->getName() + string(" vs ") + p2->getName() + string(" ") + to_string(currentIteration + 1) + string(".log");
  std::string ReplayName2 = p2->getName() + string(" vs ") + p1->getName() + string(" ") + to_string(currentIteration + 2) + string(".log");
  std::string FileName1 = FilePathBotOutput + ReplayName1;
  std::string FileName2 = FilePathBotOutput + ReplayName2;

  // All replay logs names are saved into special file
  // So we can see which replays were parsed using this pseudo bot
  file.WriteIntoFile(FileReplayParsedNames, ReplayName1);
  file1.WriteIntoFile(FileReplayParsedNames, ReplayName2);

  // Saves the iterator into the file
  // In 1v1 there are 2 players we want to observe
  // So there will be 2 log files, because of that we increase the iterator value by 2
  file.saveIterator(currentIteration + 2);

  // init file handlers and opp models
  file.Init(FileName1.c_str());
  file1.Init(FileName2.c_str());
  model->init(p1,p2);
  model1->init(p2,p1);

}

// Because we are observing 2 players, there are controlers for 2 players.

void ReplayParserModule::onEnd(bool isWinner)
{
	// Dont print data into config file, if this replay was already seen
	if (ReplayAlreadySeen)
		return;
	
	// Print the harvested data into the log file
	file.PrintGameState(GSHandler, *model);
	file1.PrintGameState(GSHandler1, *model1);
	
	// Close the file
	file.Finish();
	file1.Finish();

	// Clean
	delete model;
	delete model1;
}

void ReplayParserModule::onFrame()
{
	if (ReplayAlreadySeen)
		return;

	// Check if time pased to save output game state with corresponding input game state
	if (BWAPI::Broodwar->elapsedTime() >= GSHandler.getNextTime())
		GSHandler.saveBothIOGameStates();

	if (BWAPI::Broodwar->elapsedTime() >= GSHandler1.getNextTime())
		GSHandler1.saveBothIOGameStates();

}

void ReplayParserModule::onSendText(std::string text)
{
}

void ReplayParserModule::onReceiveText(BWAPI::Player player, std::string text)
{
}

void ReplayParserModule::onPlayerLeft(BWAPI::Player player)
{
}

void ReplayParserModule::onNukeDetect(BWAPI::Position target)
{
}

void ReplayParserModule::onUnitDiscover(BWAPI::Unit unit)
{
	if (ReplayAlreadySeen)
		return;

	// In this replay settings we have acces to all units and there is no fog of war for us
	
	// Update opponent model
	model->onUnitDiscover(unit);
	model1->onUnitDiscover(unit);

	if (unit->getPlayer() == p1) {
		// New unit seen, update current game state - add unit into it
		GSHandler.updateCurrentGameState(*model);
		// Add unit to all output game states that were created in less then 3 minutes 
		GSHandler.addUnitOutputGameState(unit, *model);
		// Add new game state and wait 3 minutes for its output game state
		GSHandler.addNewGameState();
	}
	else if (unit->getPlayer() == p2){
		GSHandler1.updateCurrentGameState(*model1);
		GSHandler1.addUnitOutputGameState(unit, *model1);	
		GSHandler1.addNewGameState();
	}
}

void ReplayParserModule::onUnitEvade(BWAPI::Unit unit)
{
}

void ReplayParserModule::onUnitShow(BWAPI::Unit unit)
{
}

void ReplayParserModule::onUnitHide(BWAPI::Unit unit)
{
}

void ReplayParserModule::onUnitCreate(BWAPI::Unit unit)
{
}

void ReplayParserModule::onUnitDestroy(BWAPI::Unit unit)
{
	if (ReplayAlreadySeen)
		return;
	
	// Remove the unit from opponent model
	model->onUnitDestroy(unit);
	model1->onUnitDestroy(unit);

	// Remove the unit only from current game state
	// NOT from output game states
	// in input state Supply is always less or equal as supply in output state 
	GSHandler.updateCurrentGameState(*model);
	GSHandler1.updateCurrentGameState(*model1);
}

void ReplayParserModule::onUnitMorph(BWAPI::Unit unit)
{
	if (ReplayAlreadySeen)
		return;

	// Update game state
	model->onUnitMorph(unit);
	model1->onUnitMorph(unit);

	if (unit->getPlayer() == p1) {
		// New unit seen, update current game state - add unit into it
		GSHandler.updateCurrentGameState(*model);
		// Add unit to all output game states that were created in less then 3 minutes 
		GSHandler.addUnitOutputGameState(unit, *model);
		// Add new game state and wait 3 minutes for its output game state
		if (unit->getType().getID() != BWAPI::UnitTypes::Zerg_Egg)
			GSHandler.addNewGameState();

	}
	else if (unit->getPlayer() == p2) {
		GSHandler1.updateCurrentGameState(*model1);
		GSHandler1.addUnitOutputGameState(unit, *model1);
		if (unit->getType().getID() != BWAPI::UnitTypes::Zerg_Egg)
			GSHandler1.addNewGameState();
	}

}

void ReplayParserModule::onUnitRenegade(BWAPI::Unit unit)
{
	model->onUnitRenegade(unit);
	model1->onUnitRenegade(unit);
}

void ReplayParserModule::onSaveGame(std::string gameName)
{
}

void ReplayParserModule::onUnitComplete(BWAPI::Unit unit)
{
}
