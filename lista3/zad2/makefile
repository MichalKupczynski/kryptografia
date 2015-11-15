all: AesFileEnc.o zad2.o
	g++ zad1.o AesFileEnc.o -L/ -o zad2

zad1.o: zad2.cpp
	g++ zad2.cpp -I . -L. x64/libbass.so -o zad2.o


AesFileEnc.o: AesFileEnc.cpp
	g++ -c AesFileEnc.cpp  -o AesFileEnc.o
