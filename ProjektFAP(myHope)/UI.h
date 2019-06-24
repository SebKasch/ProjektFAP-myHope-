#pragma once

#include <iostream>
#include <string>
#include <windows.h> //Für Sleep-Funktion
#include <list>
#include "Insel.h"
#include "Transport.h"

class UI
{

public:
	void printInfo(std::string message);	//Text wird direkt ausgegeben
	void printInfo(char message);
	void printing(std::string text); //Funktion zum Drucken von folgenden Zeichen, Zeitversetzt

	void clearScreen() {std::system("@cls"); printInfo("Projektdatei von Marc Reinsberg (Matr. Nummer: 568241) und Sebastian Kasch (Matr. Nummer: 568744)\n");}
	void waitForUser() { std::system("pause"); }

	int stringToInt(std::string text);

	void printList(std::list<Node*> printedList);
	void printList(std::list<Insel*> printedList);
	void printList(std::list<Edge*> printedList);
	void printList(std::deque<Transport*> printedList);

	void errRequest(std::string meldung);

	std::string getInformation();

	UI();
	~UI();
};

