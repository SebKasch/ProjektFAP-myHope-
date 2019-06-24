#include "Controller.h"



void Controller::pushInsel(const std::string name, int lager, bool schatz)
{
	Node *newIsland = new Insel(name, lager);

	m_g->addNode(newIsland);
}

void Controller::pushTransport(std::string start, std::string ziel, std::string type)
{
	try 
	{
		Node* startN = m_g->findNode(start);
		Node* zielN = m_g->findNode(ziel);
		if ((startN == NULL) || (zielN == NULL)) 
		{
			ErrInselnotFound a;
			throw a;
		}
		Edge *newTransport = new Transport(Transport::testType(type), type, *m_g->findNode(start), *m_g->findNode(ziel));
		m_interface.printInfo(newTransport->toString());
		m_g->addEdge(newTransport);
	}

	catch (ErrNoTransport)
	{
		m_interface.errRequest("Transport konnte nicht erstellt werden.");
	}
	catch (ErrInselnotFound)
	{
		m_interface.errRequest("Eine der Inseln existiert nicht.");
	}
	catch (ErrNodeVorhanden)
	{

	}
}

void Controller::zugSpieler(Player *spieler)
{
	int i = 0, w;
	Insel* ziel = NULL;
	std::stringstream ausgabef;
	std::deque<Transport*> way;
	way.clear();


	ausgabef << "Du befindest dich aktuell auf " << spieler->givePos()->getID() << ".\n";
	ausgabef << "Waehle dein naechstes Ziel:\n";
	m_interface.printing(ausgabef.str());

	for (auto a : m_g->getNodes())
	{
		if (a != spieler->givePos())
		{
			i++;
			ausgabef.str("");
			ausgabef << "[" << i << "] " << a->getID();
			m_interface.printing(ausgabef.str());
		}
	}

	w = m_interface.stringToInt(m_interface.getInformation());

	try 
	{
		if ((w < 1) || (w > i))
		{
			ErrFalscheInselwahl a;
			throw a;
		}

		i = 0;

		for (auto a : m_g->getNodes())
		{
			if (a != spieler->givePos())
			{
				i++;
				if (i == w) ziel = dynamic_cast<Insel*>(a);
			}
		}
	}
	catch (ErrFalscheInselwahl)
	{
		m_interface.errRequest("Unerlaubte Insel gewaehlt");
	}

	m_interface.printing(ziel->getID());
	m_interface.printInfo(std::to_string(w));

	findAWay(m_player->givePos(), ziel, way);

	ausgabef.str("");
	ausgabef << "Dein Zug sieht so aus:";
	m_interface.printing(ausgabef.str());

	m_interface.printList(way);
	//m_interface.printList(m_g->getEdges());

	ausgabef.str("");
	ausgabef << "Kosten: ";
	ausgabef.width(3);
	std::right(ausgabef);
	ausgabef << ziel->dist << " Taler\n";
	ausgabef << "Du besitzt ";
	ausgabef.width(3);
	std::right(ausgabef);
	ausgabef << spieler->giveMoney() << " Taler. Zug ausfuehren?\n[1] Ja\n[0] Nein - neues Ziel waehlen";
	m_interface.printing(ausgabef.str());

	//Entscheidung noch nicht implementiert

	try {
		int cAdds = 0, cAdd, bilance = 0;
		Node* toCast;
		Insel* aktInsel;

		for (Transport* i : way)
		{
			if (i->getWeight() > spieler->giveMoney())
			{
				ErrNichtGenugGeld ErrCla;
				throw ErrCla;
			}
			cAdd = 0;
			toCast = &i->getDstNode();
			aktInsel = dynamic_cast<Insel*>(toCast);
			cAdd = aktInsel->clearLager();
			cAdds += cAdd;
			spieler->changePos(*aktInsel); //Hier passierts, dass einfach die erste Node im Graph überschrieben wird
			spieler->changeMoney(cAdd);
		}
		bilance = cAdds - ziel->dist;

		ausgabef.str("");
		ausgabef << "Du befindest dich nun auf ";
		ausgabef << spieler->givePos()->getID();
		ausgabef << ". Durch Lager hast du " << cAdds << " Taler erhalten. Bilanz des Zuges: " << bilance<<" Taler.";
		m_interface.printing(ausgabef.str());
		m_interface.printing(spieler->givePerson());

		if (spieler->givePos()->giveSchatz())
		{
			m_doing = false;
		}
	}

	catch (ErrNichtGenugGeld)
	{

	}

}

void Controller::zugAI()
{
	Insel* choosenDest;
	choosenDest = m_enemy->target();
	std::deque<Transport*> way;
	way.clear();
	std::stringstream ausgabef;

	int i;
	for(i = 0; i > 15; i++)
	{
		ausgabef << "AI ";
	}

	m_interface.printInfo(ausgabef.str());
	ausgabef.str("");

	findAWay(m_player->givePos(), choosenDest, way);

	ausgabef.str("");
	ausgabef << "KI Zug sieht so aus:";
	m_interface.printing(ausgabef.str());

	m_interface.printList(way);

	try {
		int cAdds = 0, cAdd, bilance = 0;
		Node* toCast;
		Insel* aktInsel;

		for (Transport* i : way)
		{
			if (i->getWeight() > m_enemy->giveMoney())
			{
				ErrNichtGenugGeld ErrCla;
				throw ErrCla;
			}
			cAdd = 0;
			toCast = &i->getDstNode();
			aktInsel = dynamic_cast<Insel*>(toCast);
			cAdd = aktInsel->clearLager();
			cAdds += cAdd;
			m_enemy->changePos(*aktInsel); 
			m_enemy->changeMoney(cAdd);
		}
		bilance = cAdds - choosenDest->dist;

		ausgabef.str("");
		ausgabef << "KI ist nun auf ";
		ausgabef << m_enemy->givePos()->getID();
		ausgabef << ". Durch Lager hat KI " << cAdds << " Taler erhalten. Bilanz des Zuges: " << bilance << " Taler.";
		m_interface.printing(ausgabef.str());
		m_interface.printing(m_enemy->givePerson());

		if (m_enemy->givePos()->giveSchatz())
		{
			m_doing = false;
		}
	}

	catch (ErrNichtGenugGeld)
	{

	}
}

void Controller::findAWay(Insel *start, Insel *ziel, std::deque<Transport*> &refQueue)
{
	std::deque<Edge*> refEdges;
	refEdges.clear();
	Node *begin = start, *end = ziel;
	m_g->findShortestPathDijkstra(refEdges, *begin, *end);

	for (auto i : refEdges)
	{
		refQueue.push_back(dynamic_cast<Transport*>(refEdges.front()));
		refEdges.pop_front();
	}
}

void Controller::startGame()
{
	m_interface.waitForUser();
	m_interface.clearScreen();

	while (m_doing)
	{
		zugSpieler(m_player);
		if (m_doing) zugAI();

		m_interface.clearScreen();
	}
	endGame();
}

void Controller::endGame()
{
	m_interface.clearScreen();
	std::stringstream ausgabef;

	if (m_player->givePos()->giveSchatz()) m_winner = m_player;
	if (m_enemy->givePos()->giveSchatz()) m_winner = m_enemy;

	if (m_winner != NULL)
	{
		ausgabef << m_winner->giveName() << " hat das Spiel gewonnen.";
		m_interface.printing(ausgabef.str());
	}

	m_interface.printing("Das Spiel wird nun beendet.");
	m_interface.waitForUser();
}

void Controller::fileRead()
{
	std::ifstream stream;
	std::string filename = "C23_Projekt_19SS_Inseln.txt", outgoing, txt;
	std::vector<std::string> islandsToPush;
	std::deque<std::string> transportToPush;
	std::vector<std::string> playerToPush;
	std::vector<std::string> AIToPush;
	std::vector<std::string> lagerToPush;
	std::string schatzinsel;
	//m_interface.printInfo("Welche Datei soll eingelesen werden?");
	//std::string filename = m_interface.getInformation();
	m_interface.printInfo(filename);
	stream.open(filename);
	while (!stream.eof()) 
	{
		std::getline(stream, outgoing);
		m_interface.printInfo(outgoing);
		//addToGraph(outgoing);

		txt = outgoing.substr(0, outgoing.find(' '));
		outgoing.erase(0, outgoing.find(' ') + 1);
		if (txt == "Insel") islandsToPush.push_back(outgoing);
		if (txt == "Schatz") schatzinsel = outgoing;
		if ((txt == "Tunnel") || (txt == "Bruecke") || (txt == "Faehre")) 
		{ 
			transportToPush.push_front(txt);	//Typ des Transportwegs
			transportToPush.push_front(outgoing); //Definition des Transportwegs
		}
		if (txt == "Lager") lagerToPush.push_back(outgoing);
		if (txt == "Mensch") playerToPush.push_back(outgoing);  //mit string.find("Mensch")-> mehrere Objekte initialisieren
		if (txt == "Computer") AIToPush.push_back(outgoing);
	}

	stream.close();

	while (!islandsToPush.empty())
	{
		addIsland(islandsToPush.back());
		islandsToPush.pop_back();
	}
	

	while (!transportToPush.empty())
	{
		std::string type, rest;
		type = transportToPush.back();
		transportToPush.pop_back();
		rest = transportToPush.back();
		transportToPush.pop_back();

		addEdge(type, rest);
	}

	while (!playerToPush.empty())
	{
		addPlayer(playerToPush.back());
		playerToPush.pop_back();
	}

	while (!AIToPush.empty())
	{
		addAI(AIToPush.back());
		AIToPush.pop_back();
	}

	while (!lagerToPush.empty())
	{
		changeLager(lagerToPush.back());
		lagerToPush.pop_back();
	}

	changeSchatz(schatzinsel);
}

void Controller::addPlayer(std::string & textToInterpret)
{
	std::string insel, geld, rest = textToInterpret;
	Insel* startInsel;
	int iGeld = 0, i;

	insel = rest.substr(0, rest.find(' '));
	rest.erase(0, rest.find(' ') + 1);
	startInsel = dynamic_cast<Insel*>(m_g->findNode(insel));

	geld = rest.substr(0, rest.find(' '));
	rest.erase(0, rest.find(' ') + 1);

	iGeld = m_interface.stringToInt(geld);

	m_player = new Player("Spieler", startInsel, iGeld);
	m_interface.printInfo("Hier wurde ein Spieler erstellt");
}

void Controller::addAI(std::string & textToInterpret)
{
	std::string insel, geld, rest = textToInterpret;
	Insel* startInsel;
	int iGeld = 0, i;

	insel = rest.substr(0, rest.find(' '));
	rest.erase(0, rest.find(' ') + 1);
	startInsel = dynamic_cast<Insel*>(m_g->findNode(insel));

	geld = rest.substr(0, rest.find(' '));

	rest.erase(0, rest.find(' ') + 1);

	for (i = 0; i < geld.length(); i++)
	{
		iGeld += pow(10, i)*std::atoi(&geld[i]);
	}

	m_enemy = new AI(m_g->getNodes(), *startInsel, iGeld);
	m_interface.printInfo("Hier wurde ein Spieler erstellt");
	m_interface.printInfo("Hier wurde ein Gegner erstellt");
}

void Controller::addIsland(std::string & textToInterpret)
{ 
	pushInsel(textToInterpret);
	m_interface.printInfo("Hier wurde eine Insel erstellt");
}

void Controller::addEdge(std::string & type, std::string & textToInterpret)
{
	std::string IslandA, IslandB;
	IslandB = textToInterpret;
	IslandA = IslandB.substr(0, IslandB.find(' '));
	IslandB.erase(0, IslandB.find(' ') + 1);

	pushTransport(IslandA, IslandB, type);
	pushTransport(IslandB, IslandA, type);

	m_interface.printInfo("Hier wurde ein Transportweg erstellt");
}

void Controller::changeSchatz(std::string & InselName)
{
	Insel* schatz = dynamic_cast<Insel*>(m_g->findNode(InselName));
	schatz->setToTreasure();

	m_interface.printInfo("Hier wurde ein Schatz erstellt");
}

void Controller::changeLager(std::string & textToInterpret)
{
	std::string nameLager, rest = textToInterpret;
	
	int iGeld = 0, i;
	Insel* neuesLager;

	nameLager = rest.substr(0, rest.find(' '));
	rest.erase(0, rest.find(' ') + 1);

	const std::string geld = rest.substr(0, rest.find(' '));

	rest.erase(0, rest.find(' ') + 1);

	for (i = 0; i < geld.length(); i++)
	{
		iGeld += pow(10, i)*std::atoi(&geld[i]);
	}
	
	neuesLager = dynamic_cast<Insel*>(m_g->findNode(nameLager));
	neuesLager->changeLagerValue(iGeld);

	m_interface.printInfo("Hier wurde ein Lager erstellt");
}

Controller::Controller()
{
	Startinsel = NULL;
	m_g = new Graph;
	m_player = NULL;
	m_enemy = NULL;
	m_winner = NULL;
	m_doing = true;
	
	/*
	pushInsel("Insel A", 5, false);
	pushInsel("Insel B", 3, true);
	pushTransport("Insel A", "Insel B", "Bruecke");
	m_player = new Player("Spieler", *Startinsel);
	m_enemy = new AI(m_g->getNodes(), *Startinsel);

	m_interface.printList(m_enemy->m_besuchteInseln);
	m_interface.printList(m_g->getNodes());
	m_interface.printList(m_g->getEdges());

	m_interface.printing(m_player->givePerson());
	m_interface.printing(m_enemy->givePerson());*/

	fileRead();

	m_interface.printList(m_g->getNodes());
	m_interface.printList(m_g->getEdges());
	m_interface.printInfo(m_player->givePerson());
	m_interface.printInfo(m_enemy->givePerson());

	startGame();
}


Controller::~Controller()
{
	delete m_g;

}
