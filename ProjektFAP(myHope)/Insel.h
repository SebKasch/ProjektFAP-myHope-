#pragma once
#include <Graph.h>
#include <sstream>

class Insel : public Node
{
	bool m_schatz;
	int m_lager;
public:
	Insel(std::string name, int lager = 0);

	int giveLager() { return m_lager; }
	int clearLager() { int a = m_lager; m_lager = 0; return a; }
	bool giveSchatz() { return m_schatz; }
	void changeLagerValue(int new_value) { m_lager = new_value; }
	std::string giveIsland();
	void setToTreasure() { m_schatz = true; }
};

class ErrInselnotFound
{
};