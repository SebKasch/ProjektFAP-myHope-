#pragma once

#include <iostream>
#include <string>
#include <list>
#include "Player.h"
#include "UI.h"
#include "AI.h"
#include "Insel.h"
#include "transport.h"
#include <Graph.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>

class Controller
{
private:
	Player *m_winner;
	Player *m_player;
	AI *m_enemy;
	//std::list<Insel> m_islands;
	UI m_interface;
	Graph *m_g;
	Insel *Startinsel;
	bool m_doing;	//Variable f�r Laufzeit

	void pushInsel(const std::string name, int lager = 0, bool schatz = false);
	void pushTransport(std::string ziel, std::string start, std::string type);

	void zugSpieler(Player *spieler);
	void zugAI();
	void findAWay(Insel* start, Insel* ziel, std::deque<Transport*> &refQueue);

	void startGame();
	void endGame();
	
	//File Reading Process
	void fileRead();	//Control-Program, liest Zeile f�r Zeile ein und aktiviert f�r jede Zeile 

	//Steuer-Programme f�r auszuf�hrende Interpretationen und Erstellung von Objekten
	void addPlayer(std::string &textToInterpret);
	void addAI(std::string & textToInterpret);
	void addIsland(std::string & textToInterpret);
	void addEdge(std::string & type, std::string & textToInterpret);
	void changeSchatz(std::string & InselName);
	void changeLager(std::string &textToInterpret);
public:


	Controller();
	~Controller();
};

class ErrFalscheInselwahl{};
class ErrNichtGenugGeld{};