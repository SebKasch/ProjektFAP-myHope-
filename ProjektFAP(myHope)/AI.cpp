#include "AI.h"



Insel * AI::target()
{
	std::random_device rnd;
	int num, i;
	Insel* choice = NULL;
	std::list<Insel*>::iterator it = m_besuchteInseln.begin();

	num = rnd()%(m_besuchteInseln.size());

	for (i = 0; i < num; i++)
	{
		//choice = *it;
		if(it!=m_besuchteInseln.end()) it++;
	}
	choice = *it;
	m_besuchteInseln.erase(it);

	return choice;
}

AI::AI(const std::list<Node*>& copyInsel, Insel &startinsel, int startguthaben): Player("KI", &startinsel)
{
	Node* ins = &startinsel;
	for (auto i : copyInsel)
	{
		if(i != ins) m_besuchteInseln.push_back(dynamic_cast<Insel*>(i));
	}
}


AI::~AI()
{
}
