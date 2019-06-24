#include "Player.h"


std::string Player::giveName()
{
	return m_Name;
}

std::string Player::givePerson()
{
	std::stringstream ausgabe;
	ausgabe << "Name: ";
	ausgabe.width(8);
	ausgabe.flags(std::ios::left);
	ausgabe << m_Name;
	ausgabe << " Geld: ";
	ausgabe.width(3);
	ausgabe.flags(std::ios::right);
	ausgabe << m_Geld;
	ausgabe << " Taler\nStandort: ";
	ausgabe << m_Ort->getID();
	return ausgabe.str();
}

int Player::giveMoney()
{
	return m_Geld;
}

void Player::changePos(const Insel &newPos)
{
	bool isPossible = false;
	Insel *castedI;
	Transport *castedT;
	int minPrice = -1;

	for (Edge* i : m_Ort->getOutEdges())
	{
		castedT = dynamic_cast<Transport*>(i);
		castedI = dynamic_cast<Insel*>(&i->getDstNode());

		if (castedI == &newPos)
		{
			if ((minPrice < 0) || (minPrice > castedT->getWeight())) 
			{
				minPrice = castedT->getWeight();
				isPossible = true;
				m_Ort = castedI;
			}
		}
	}

	if (isPossible == true)
	{
		//*m_Ort = newPos;
		m_steps++;
		m_Geld -= minPrice;
	}
}

void Player::changeMoney(int costs)
{
	try
	{
		if (-costs > m_Geld) 
		{ 
			ErrChangeMoney a;
			throw a; 
		}
		m_Geld += costs;
	}

	catch (ErrChangeMoney) {}
}

Player::Player(std::string name, Insel *startinsel, int startguthaben) : m_Name(name), m_Ort(startinsel)
{
	m_Geld = startguthaben;
	m_steps = 0;
}

Player::~Player()
{
}
