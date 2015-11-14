#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <time.h>

#include "AesFileEnc.h"	
unsigned char * AesFileEnc::key ( )
{
	
	
	}
	
unsigned char* AesFileEnc::iv ( )
{
	unsigned char * IV;
	IV = new unsigned char[this->keyLength];
	srand(time(0));
	int j;
	for(int i = 0 ; i<this->keyLength; i++)
	{
		j = (int)(rand() / (RAND_MAX + 1.0) * 16);
		
		char *buffer;
		itoa(j, buffer, 16);
		IV[i] = *buffer;
	}
	return IV;
	}
	
AesFileEnc::AesFileEnc(Aes_type type, const char* keystore_path)
{
	this->type = type;
	this->keystore_path = keystore_path;	
		switch(this->type)
	{
		case cbc128:
			this->keyLength = 16;
			break;
		case cbc192:
			this->keyLength = 24;
		break;
		case cbc256:
			this->keyLength = 32;
			break;
		case ecb128:
			this->keyLength = 16;
			break;
		case ecb192:
			this->keyLength = 24;
			break;
		case ecb256:
			this->keyLength = 32;
			break;
		case cfb128:
			this->keyLength = 16;
			break;
		case cfb192:
			this->keyLength = 24;
			break;
		case cfb256:
			this->keyLength = 32;
			break;
		case ofb128:
			this->keyLength = 16;

			break;
		case ofb192:
			this->keyLength = 24;
			break;
		case ofb256:
			this->keyLength = 32;
			break;
	}
}
	
int AesFileEnc::do_crypt(FILE *in, FILE *out, int do_encrypt)
{
	/* Allow enough space in output buffer for additional block */
	unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
	int inlen, outlen;
	EVP_CIPHER_CTX ctx;
	/* Bogus key and IV: we'd normally set these from
	* another source.
	*/
	unsigned char key[] = this->key();
	unsigned char iv[] = this->iv();

	/* Don't set key or IV right away; we want to check lengths */
	EVP_CIPHER_CTX_init(&ctx);
	//EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
	//	do_encrypt);
			
	OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == this->keyLenght);
	OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == this->keyLenght);
	switch(this->type)
	{
		case cbc128:
			EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case cbc192:
			EVP_CipherInit_ex(&ctx, EVP_aes_192_cbc(), NULL, NULL, NULL,
				do_encrypt);
		break;
		case cbc256:
			EVP_CipherInit_ex(&ctx, EVP_aes_256_cbc(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case ecb128:
			EVP_CipherInit_ex(&ctx, EVP_aes_128_ecb(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case ecb192:
			EVP_CipherInit_ex(&ctx, EVP_aes_192_ecb(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case ecb256:
			EVP_CipherInit_ex(&ctx, EVP_aes_256_ecb(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case cfb128:
			EVP_CipherInit_ex(&ctx, EVP_aes_128_cfb(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case cfb192:
			EVP_CipherInit_ex(&ctx, EVP_aes_192_cfb(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case cfb256:
			EVP_CipherInit_ex(&ctx, EVP_aes_256_cfb(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case ofb128:
			EVP_CipherInit_ex(&ctx, EVP_aes_128_ofb(), NULL, NULL, NULL,
				do_encrypt);

			break;
		case ofb192:
			EVP_CipherInit_ex(&ctx, EVP_aes_192_ofb(), NULL, NULL, NULL,
				do_encrypt);
			break;
		case ofb256:
			EVP_CipherInit_ex(&ctx, EVP_aes_256_ofb(), NULL, NULL, NULL,
				do_encrypt);
			break;
	}
	

	


			/* Now we can set key and IV */
			EVP_CipherInit_ex(&ctx, NULL, NULL, key, iv, do_encrypt);

			for(;;)
					{
					inlen = fread(inbuf, 1, 1024, in);
					if(inlen <= 0) break;
					if(!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen))
							{
							/* Error */
							EVP_CIPHER_CTX_cleanup(&ctx);
							return 0;
							}
					fwrite(outbuf, 1, outlen, out);
					}
			if(!EVP_CipherFinal_ex(&ctx, outbuf, &outlen))
					{
					/* Error */
					EVP_CIPHER_CTX_cleanup(&ctx);
					return 0;
					}
			fwrite(outbuf, 1, outlen, out);

			EVP_CIPHER_CTX_cleanup(&ctx);
			return 1;
			}

