#include "Transport.h"

#define COSTbridge 3
#define COSTtunnel 5
#define COSTferry 3


int Transport::testType(std::string type)
{
	if (type == "Faehre") return COSTferry;
	if (type == "Tunnel") return COSTtunnel;
	if (type == "Bruecke") return COSTbridge;

	ErrNoTransport a;
	throw a;
}

std::string Transport::toString() const
{
	std::string a;
	a = Edge::toString() + "\nDer Weg per " + m_typ + " wird dich " + std::to_string(m_costs) + " Taler kosten.";
	return a;
}

Transport::Transport(int kosten, std::string typ, Insel &start, Insel &ziel): m_costs(kosten), Edge(start, ziel), m_typ(typ)
{

}

Transport::Transport(int kosten, std::string typ, Node & start, Node & ziel): m_costs(kosten), Edge(start, ziel), m_typ(typ)
{
}

Transport::~Transport()
{

}
