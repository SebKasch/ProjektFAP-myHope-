#include "UI.h"



void UI::printInfo(std::string message)
{
	std::cout << message << std::endl;
}

void UI::printInfo(char message)
{
	std::cout << message << std::endl;
}

void UI::printing(std::string text)
{
	int i, l;
	l = text.length();
	for (i = 0; i < l; i++)
	{
		std::cout << text[i] << std::flush;
		Sleep(25);
	}
	std::cout << std::endl;
}

int UI::stringToInt(std::string text)
{
	/*int zahl = 0, i, j = 0;
	for (i = text.length() - 1; i >= 0; i--)
	{
		zahl += pow(10, j)*std::atoi(&text[i]);
		j++;
	}

	return zahl;*/
	return std::atoi(&text[0]);
}

void UI::printList(std::list<Node*> printedList)
{
	Insel* island;
	for (auto i : printedList)
	{
		island = dynamic_cast<Insel*>(i);
		printInfo(island->giveIsland());
	}
}

void UI::printList(std::list<Insel*> printedList)
{

	for (auto i : printedList)
	{
		printInfo(i->giveIsland());
	}
}

void UI::printList(std::list<Edge*> printedList)
{
	Transport* trans;
	for (auto i : printedList)
	{
		trans = dynamic_cast<Transport*>(i);
		printInfo(trans->toStringA());
	}
}

void UI::printList(std::deque<Transport*> printedList)
{
	for (auto i : printedList)
	{
		printInfo(i->toStringA());
	}
}

void UI::errRequest(std::string meldung)
{
	std::cerr << "[Fehler] " << meldung << std::endl;
}

std::string UI::getInformation()
{
	std::string b;
	std::cin >> b;
	std::cin.ignore();
	return b;
}

UI::UI()
{
	UI::printing("Projektdatei von Marc Reinsberg (Matr. Nummer: 568241) und Sebastian Kasch (Matr. Nummer: 568744)\n");
}


UI::~UI()
{
}
