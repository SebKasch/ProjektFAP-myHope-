#include "Edge.h"
#include <iostream>


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(Node& rSrc, Node& rDst) : m_rSrc(rSrc), m_rDst(rDst)
{

	std::list<Edge*> *EdgeList;

	// fügt die Edge (this) in m_outgoingEdges des Source-Node ein.
	EdgeList = &rSrc.getOutEdges();
	EdgeList->push_back(this);

	// fügt die Edge (this) in m_incomingEdges des Destination-Node ein.
	EdgeList = &rDst.getInEdges();
	EdgeList->push_back(this);


    // TEST:
    // Erstellen Sie in main.cpp eine Edge und prüfen Sie, ob die Edge
    // korrekt in m_outgoingEdges bzw. m_incomingEdges eingefügt wurde!

	//Test erfolgreich
}


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(const Edge& rOther) : m_rSrc(rOther.m_rSrc), m_rDst(rOther.m_rDst)
{
    // macht das Selbe wie 'Edge(Node& rSrc, Node& rDst)'
	std::list<Edge*> *EdgeList;

	// fügt die Edge (this) in m_outgoingEdges des Source-Node ein.
	EdgeList = &m_rSrc.getOutEdges();
	EdgeList->push_back(this);

	// fügt die Edge (this) in m_incomingEdges des Destination-Node ein.
	EdgeList = &m_rDst.getInEdges();
	EdgeList->push_back(this);
}


//---------------------------------------------------------------------------------------------------------------------

Edge::~Edge()
{
	std::list<Edge*> *EdgeList;
	std::list<Edge*>::iterator aktEdge;
	bool folgen=true;

	// - entfernt die Edge (this) aus m_outgoingEdges in Source-Node
	EdgeList = &m_rSrc.getOutEdges();
	aktEdge = EdgeList->begin();

	while (folgen)
	{
		if (*aktEdge == this)
		{
			aktEdge = EdgeList->erase(aktEdge);
			folgen = false;
		}
		if (folgen) aktEdge++;
		if (aktEdge == EdgeList->end()) folgen = false;
	}

	// - entfernt die Edge (this) aus m_incomingEdges im Destination-Node
	folgen = true;
	EdgeList = &m_rDst.getInEdges();
	aktEdge = EdgeList->begin();

	while (folgen)
	{
		if (*aktEdge == this)
		{
			aktEdge = EdgeList->erase(aktEdge);
			folgen = false;
		}
		if (folgen) aktEdge++;
		if (aktEdge == EdgeList->end()) folgen = false;
	}
	//Test erfolgreich
}


//---------------------------------------------------------------------------------------------------------------------

bool Edge::isConnectedTo(const Node& rNode) const
{
	if ((&rNode == &m_rDst) || (&rNode == &m_rSrc))
	{
		return true;
	}
    // - gibt true zurück, wenn rNode entweder m_rSrc und m_rDst ist.
    // Hinweis: Adressen vergleichen, um zu gucken, ob es wirklich das selbe Objekt ist!
    return false;
}


//---------------------------------------------------------------------------------------------------------------------

std::string Edge::toString() const
{
    std::string result;
    result = m_rSrc.getID() + " -> " + m_rDst.getID();
    return result;
}


//---------------------------------------------------------------------------------------------------------------------
