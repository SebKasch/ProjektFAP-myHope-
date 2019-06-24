#include "Graph.h"
#include <list>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iostream>


//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
	// - soll einen Node mit der gegebenen id in m_nodes suchen
	// - gibt den Pointer auf den Node zurück, wenn er gefunden wurde.
	// - gibt NULL zurück, falls kein Node mit der id gefunden wurde.
		for (auto aNode : m_nodes)
		{
			if (aNode->getID() == id)
			{
				return aNode;
			}
		}
    return NULL;

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Nodes im Graph suchen.
    // Prüfen Sie, ob der Node gefunden wurden und geben Sie die ID auf der Kommandozeile aus!
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
    // bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
    //return *new Node("");
	try {
		//if (this->m_nodes.size()!=0) {
			if (this->findNode(pNewNode->getID()) == pNewNode)
			{
				ErrNodeVorhanden er1(pNewNode);
				throw er1;
			}
		//}
	}
	
	catch (ErrNodeVorhanden &err)
	{
		std::cout << "Node vorhanden - addNode" << std::endl;
		return *new Node("");
	}

	m_nodes.push_back(pNewNode);
	return *pNewNode;

	
    // Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
    // Falls ja:
    //  - Exception werfen
    // Falls nein:
    //  - den neuen Node 'pNewNode' in m_nodes einfügen
    //  - Referenz auf den neuen Node zurück geben

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes in main.cpp erstellen
    // Testen Sie mit der Funktion 'findNode', ob die hinzugefügten Nodes im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{

	for (auto edge : m_edges)
	{
		if (edge == pNewEdge)
		{
			return *edge;
		}
	}

	m_edges.push_back(pNewEdge);

	if (!(this->findNode(pNewEdge->getSrcNode().getID()) == &pNewEdge->getSrcNode()))
	{
		addNode(&pNewEdge->getSrcNode());
	}

	if (!(this->findNode(pNewEdge->getDstNode().getID()) == &pNewEdge->getDstNode()))
	{
		addNode(&pNewEdge->getDstNode());
	}

	return *pNewEdge;
    // - die neue Edge 'pNewEdge' in m_edges einfügen
    // - Referenz auf die neue Edge zurück geben

	// - Testen Sie ob der Source- und Destination-Node von 'pNewEdge' schon im Graph vorhanden ist.
	// -> fügen Sie diese Nodes hinzu, falls nicht (nutzen Sie dafür Graph::addNode)

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // Testen Sie mit der Funktion 'findEdges', ob die hinzugefügten Edges im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
    // - soll alle Edges im Graph löschen (delete)
    // - soll alle Nodes im Graph löschen (delete)

	std::list<Edge*>::iterator aktEdge;
	aktEdge = m_edges.begin();
	auto e = m_edges.end();
	
	while (aktEdge != e)
	{
		delete *aktEdge;
		aktEdge = m_edges.erase(aktEdge);
	}

	std::list<Node*>::iterator aktNode;
	aktNode = m_nodes.begin();
	auto n = m_nodes.end();

	while (aktNode != n)
	{
		delete *aktNode;
		aktNode = m_nodes.erase(aktNode);
	}
}

/*Graph::Graph()
{
}*/


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node& rNode)
{
	Node *delNode = &rNode; 
	std::list<Node*>::iterator node;

	node = m_nodes.begin();
	while(node!=m_nodes.end())
	{
		if (*node == delNode)
		{
			node = m_nodes.erase(node);
			break;
		}
		node++;
	}

	std::list<Edge*>::iterator its;
	its = delNode->getOutEdges().begin();
	Edge* edgi;

	while (its != delNode->getOutEdges().end())
	{
		edgi = *its;
		remove(*edgi);
		if (!(delNode->getOutEdges().end() == delNode->getOutEdges().begin()))
		{
			its++;
		}
		else
		{
			its = delNode->getOutEdges().end();
		}
	}

	its = delNode->getInEdges().begin();

	while (its != delNode->getInEdges().end())
	{
		edgi = *its;
		remove(*edgi);
		if (!(delNode->getInEdges().end() == delNode->getInEdges().begin()))
		{
			its++;
		}
		else
		{
			its = delNode->getInEdges().end();
		}
	}


	delete delNode;

    // - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!
	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
    // 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
    // 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Nodes wieder löschen.
    // Testen Sie mit der Funktion 'findNode', ob die gelöschten Nodes noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge)
{
    // - der Pointer auf rEdge muss aus m_edges entfernt werden!
    // - der Pointer auf rEdge muss mit 'delete' freigegeben werden!

	std::list<Edge*>::iterator it;
	it = m_edges.begin();

	while(it!=m_edges.end())	//Sucht Edge in m_edges und entfernt es aus der Liste
	{
		if (&rEdge == *it)
		{
			it = m_edges.erase(it);
			break;
		}
		it++;
	}

	delete &rEdge;	//Entfernt die Edge und somit auch alle Verbindungen in den Nodes
    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Edges wieder löschen.
    // Testen Sie mit der Funktion 'findEdges', ob die gelöschten Edges noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
{
    std::vector<Edge*> ret;
	const Node *Src = &rSrc;
	const Node *Dst = &rDst;
    // - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
    // - füge die Zeiger der Edges in den vector 'ret' ein.

	for (Edge *edge : m_edges)
	{
		if ((&edge->getSrcNode() == Src) && (&edge->getDstNode() == Dst)) ret.push_back(edge); 	
	}

    return ret;

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Edges im Graph suchen.
    // Prüfen Sie, ob Edges gefunden wurden und geben Sie die gefunden Edges auf der Kommandozeile aus!

	//Test erfolgreich
}

//---------------------------------------------------------------------------------------------------------------------

void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
{
	if (&rSrcNode == &rDstNode) 
	{ 
		std::cout << "Eingangsnode kann nicht Ausgangsnode sein" << std::endl; 
		return; 
	}

	std::deque<Node*> Q;
	bool isSrc = false;
	bool isDst = false;
	Node *aktNode, *aktDstNode;

	//Setzen von Standartwerten, damit Echtheit garantiert ist
	for (Node* i : m_nodes)
	{
		aktNode = i;
		aktNode->dist = -1;
		aktNode->parent = NULL;

		if (aktNode == &rSrcNode)
		{
			isSrc = true; 
			aktNode->dist = 0; 
			Q.push_front(aktNode); 
		}
		else
		{
			if (aktNode == &rDstNode) isDst = true;

			Q.push_back(aktNode);
		}
	}

	if ((isSrc == false) || isDst == false) return;	//Falls entweder Source-Knoten oder End-Knoten nicht enthalten sind, kann direkt beendet werden

	double newDist;

	std::list<Node*> insertSort;
	std::list<Node*>::iterator it;

	while (Q.size() > 0)
	{
		//Sortieralgorithmus

		//erstes Element für Insertion Sort
		insertSort.push_back(Q.front());
		Q.pop_front();

		while (Q.size() > 0)
		{
			if (Q.front()->dist < 0)
			{
				insertSort.push_back(Q.front());
				Q.pop_front();
			}
			else
			{
				it = insertSort.begin();
				aktNode = *it;
				while ((aktNode->dist > 0) && (aktNode->dist < Q.front()->dist) && (it != insertSort.end()))
				{
					it++;
					if (it != insertSort.end())aktNode = *it;
				}
				insertSort.insert(it, Q.front());
				Q.pop_front();
			}
		}

		it = insertSort.begin();
		while(it!=insertSort.end())
		{
			it++;
			Q.push_back(insertSort.front());
			insertSort.pop_front();
		}
		

		aktNode = Q.front(); //hier muss noch nach der kleinsten Distanz gesucht werden
		Q.pop_front();

		//Sortierung Ende

		if (aktNode->dist >= 0)
		{
			for (Edge* i : aktNode->getOutEdges())
			{
				aktDstNode = &i->getDstNode();
				if (!(findEdges(*aktNode, *aktDstNode).empty()))
				{
					newDist = aktNode->dist + i->getWeight();
						if (aktDstNode->dist < 0)
						{
							aktDstNode->dist = newDist;
								aktDstNode->parent = aktNode;
						}

						else
						{
							if (newDist < aktDstNode->dist)
							{
								aktDstNode->dist = newDist;
								aktDstNode->parent = aktNode;
							}
						}
				}
			}
		}
	}

	//Hinzufügen der Edges (von hinten) der Verbindung der Nodes
	aktNode = findNode(rDstNode.getID());
	if (!(findEdges(*aktNode->parent, *aktNode).empty())) {
		rPath.push_front(findEdges(*aktNode->parent, *aktNode).back());	//Das letzte Element des Vektors der Verbinungen des Parent zum aktuellen Knoten, Welche Verbindung der Nodes es ist spielt keine Rolle

			aktNode = aktNode->parent;

			while (aktNode != &rSrcNode)
			{
				rPath.push_front(findEdges(*aktNode->parent, *aktNode).back());
					aktNode = aktNode->parent;
			}
	}
/*
Ein häufiges Anwendungsproblem für Graphen-Anwendungen besteht darin, 
den Pfad zwischen verschiedenen Nodes zu finden, die direkt oder indirekt über Edges miteinander verbunden sind.
Um den optimalsten Pfad(den mit den geringsten Kantengewichten) zu finden, gibt es den Dijkstra-Algorithmus!
Pseudocode (Quelle: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
>>>
function Dijkstra(Graph, source):

      create vertex set Q

      for each vertex v in Graph:             // Initialization
          dist[v] ← INFINITY                  // Unknown distance from source to v
          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
          add v to Q                          // All nodes initially in Q (unvisited nodes)

      dist[source] ← 0                        // Distance from source to source

      while Q is not empty:
          u ← vertex in Q with min dist[u]    // Source node will be selected first
          remove u from Q

          for each neighbor v of u:           // where v is still in Q.
              alt ← dist[u] + length(u, v)
              if alt < dist[v]:               // A shorter path to v has been found
                  dist[v] ← alt
                  prev[v] ← u

      return dist[], prev[]
<<<

Betrachten Sie den Pseudocode und setzen Sie ihn in C++ um.
Sortieren Sie am Ende das Ergebnis in die richtige Reihenfolge um 
und geben sie die kürzeste Route zwischen rSrcNode und rDstNode als Liste von Edges zurück.

TEST:
Testen Sie diese Funktion, indem Sie einen Graph in main.cpp erstellen
und sich die kürzesteste Route zwischen 2 Nodes zurückgeben lassen.
*/

}


//---------------------------------------------------------------------------------------------------------------------

