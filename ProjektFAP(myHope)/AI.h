#pragma once
#include "Player.h"
#include <list>
#include "Insel.h"
#include <random>

class AI :
	public Player
{
public:
	Insel *target();
	AI(const std::list<Node*> &copyInsel, Insel &startinsel, int startguthaben);
	~AI();

//private:
	std::list<Insel*> m_besuchteInseln;
};

