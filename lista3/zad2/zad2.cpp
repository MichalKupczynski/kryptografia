#include <iostream>
#include <string>
#include <openssl/sha.h>
#include "bass.h"
#include "AesFileEnc"

using std::cout;
using std::cin;
using std::string;

int play()
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

void config(AesFIleEnc enc)
{
	FILE* config;
	config = fopen("config", "r");
	unsigned char key[] = "a58f8b91c230fe83"
	if(config == NULL)
	{
		config = fopen("config", "r+");
		config = fopen("config", "w+");
		cout<<"Witamy w odtwarzaczu muzyki zaszyfrowanej!"<<std::endl;
		std::string path;
		cout<<"Podaj ścieżkę do keystora: "<<endl;
		cin>>path;
		std::string prompt;
		prompt = getpass("Podaj swoje hasło: " );
		fscanf(config,"%s \n", path);
		char pass1[256];
		char pass2[256];
		for(int i = 0; i<255;i++)
		{
			pass1[i]= "0";
			pass2[i] = "0";
		}
		pass1[255] = "0";
		pass2[255] = "1";
		for(int i = 0; i<prompt.size();i++)
		{
			pass1[i]= prompt.substring(i,1);
			pass2[i] = prompt.substring(i,1);
		}
		sha1 = SHA256(pass1, 32, NULL);
		sha2 = SHA256(pass2, 32, NULL);
		fscanf(config,"%s \n", sha1);
		fscanf(config,"%s \n", sha2);

		encdo_crypt(config, config, 1, unsigned char* key);
	}
		encdo_crypt(config, config, 0, unsigned char* key);
	}
