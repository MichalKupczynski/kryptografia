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

std::string config(AesFIleEnc enc)
{
	FILE* config;
	config = fopen("config", "r");
	unsigned char key[] = "a58f8b91c230fe83"
	configuration conf;
	if(config == NULL)
	{
		config = fopen("config", "r+");
		config = fopen("config", "w+");
		cout<<"Witamy w odtwarzaczu muzyki zaszyfrowanej!"<<std::endl;
		std::string path;
		cout<<"Podaj ścieżkę do keystora: "<<endl;
		cin>>path;
		conf.keystore_path = path;
		std::string prompt;
		prompt = getpass("Podaj swoje hasło: " );
		fprintf(config,"%s \n", path);
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
		fprintf(config,"%s \n", sha1);
		fprintf(config,"%s \n", sha2);

		enc.do_crypt(config, config, 1, unsigned char* key);
		return path;
	}
	else{
	
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
		char pass1test[256];
		char pass2test[256];
		std::string path;
		encdo_crypt(config, config, 0, key);
		fscanf(config, "%s \n", path);
		fscanf(config, "%s \n", pass1test);
		fscanf(config, "%s \n", pass2test);
		enc.do_crypt(config, config, 1, key);
		std::string p1 = std::string(pass1test);
		std::string p2 = std::string(pass2test);
		if(p1.compare(sha1) && p2.compare(sha2 pass2test)
			return path;
		else 
			return NULL;
		
	}
}
