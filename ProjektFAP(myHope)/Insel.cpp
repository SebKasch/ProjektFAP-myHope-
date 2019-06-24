#include "Insel.h"

Insel::Insel(std::string name, int lager) : m_schatz(false), Node(name)
{
	m_lager = lager;
}

std::string Insel::giveIsland()
{
	std::stringstream a;
	std::left(a);
	a.width(15);
	a << m_id << "Lager: ";
	a.width(3);
	std::right(a);
	a << m_lager << " Taler; Schatz? " << std::to_string(m_schatz);

	return a.str();
}
