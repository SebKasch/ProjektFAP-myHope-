#pragma once
#include <Graph.h>

#include <string>
#include "Insel.h"

class Transport : public Edge
{
private:
	const int m_costs;
	const std::string m_typ;

public:
	static int testType(std::string type);		//testType soll sowohl ermitteln, ob der angegebene Transporttyp korrekt ist und infolge dessen die Kosten zurück liefern
	virtual double getWeight() { return m_costs; }
	std::string toString() const;
	std::string toStringA() const { return Edge::toString(); }

	Transport(int kosten, std::string typ, Insel &start, Insel &ziel);
	Transport(int kosten, std::string typ, Node &start, Node &ziel);
	~Transport();
};

class ErrNoTransport {};