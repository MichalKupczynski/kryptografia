#include <iostream>
#include <string>

#include "bass.h"

using std::cout;
using std::cin;
using std::string;

int main(int argc, char *argv[])
{
string sciezka;
HSTREAM strumien;

		//inicjacja BASS'a
	if (!BASS_Init(-1, 44100, 0, 0, 0))  //urzadzenie domyslne dzwieku
	{
		BASS_Init(0, 44100, 0, 0, 0);  //blad, to bez dzwieku
		cout << "Blad";
	}
		cout << "Podaj sciezke do pliku muzycznego: ";
	getline(cin, sciezka);
		//tworzenie strumienia dzwieku
	strumien = BASS_StreamCreateFile(false, sciezka.c_str(), 0, 0, 0);
	BASS_ChannelPlay(strumien, true);  //start odtwarzania strumienia
do
{
	}while(BASS_ChannelIsActive(strumien));  //odtwarzanie do konca pliku
		BASS_Stop();
	BASS_Free();
		
	return 1;
}
