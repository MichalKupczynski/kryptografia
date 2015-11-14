
#include <string.h>
#include <iostream>
#include <cstdio>

enum Aes_type
{
	cbc128 = 0,
	cbc192 = 1,
	cbc256 = 2,
	cfb128 = 3,
	cfb192 = 4,
	cfb256 = 5,
	ecb128 = 6,
	ecb192 = 7,
	ecb256 = 8,
	ofb128 = 9,
	ofb192 = 10,
	ofb256 = 11
};

class AesFileEnc{
	
	private:
		Aes_type type;
		const char* keystore_path;
		unsigned int keyLength;
		unsigned char * key ( );
		unsigned char * iv ( );

	public:	
		AesFileEnc(Aes_type type, const char* keystore_path);
		int do_crypt(FILE *in, FILE *out, int do_encrypt);

};