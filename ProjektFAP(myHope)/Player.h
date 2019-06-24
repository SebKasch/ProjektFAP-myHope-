#pragma once

#include <string>
#include <sstream>
#include "Insel.h"
#include "Transport.h"

class Player
{
private:
	const std::string m_Name;
	int m_Geld;
	int m_steps;
	Insel *m_Ort;
public:
	std::string giveName();
	std::string givePerson();
	int giveMoney();
	Insel* givePos() { return m_Ort; }

	void changePos(const Insel &newPos);

	void changeMoney(int costs);

	Player(std::string name, Insel *startinsel, int startguthaben = 30);
	~Player();
};

class ErrChangeMoney
{};
