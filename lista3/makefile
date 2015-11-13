all: AesFileEnc.o zad1.o
	g++ zad1.o AesFileEnc.o -L/usr/lib -lssl -lcrypto -o zad1

zad1.o: zad1.cpp
	g++ -c zad1.cpp -o zad1.o

AesFileEnc.o: AesFileEnc.cpp
	g++ -c AesFileEnc.cpp  -o AesFileEnc.o
