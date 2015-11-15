#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include "AesFileEnc.h"	

unsigned char * AesFileEnc::key ( )
{
	FILE* keystore;
	keystore = fopen(this->keystore_path, "r");
	unsigned char *iv = this->iv(32);
	unsigned char* key = new unsigned char[32];
	const char *prompt;
	prompt = getpass("Your password to keystore: " );
	unsigned char* sha;
   sha = SHA256(reinterpret_cast<const unsigned char*>(prompt), 32, NULL); //uwaga
   //printf("SHA %s aaa",(char *)sha);
	delete prompt;
	

  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);
  
	if(keystore == NULL)
	{
		keystore = fopen(this->keystore_path, "w+");
		std::cout<<this->keystore_path;
		srand(time(0));
		int j;
		char *buffer;
		buffer = new char;
		for(int i = 0 ; i<32; i++)
		{
			j = (int)(rand() / (RAND_MAX + 1.0) * 16);		
			sprintf(buffer,"%x",j);
			key[i] = *buffer;
		}
		 delete(buffer);

  unsigned char ciphertext[512];

  int ciphertext_len;

  ciphertext_len = this->encrypt (key, 32, sha, iv,
                            ciphertext);
	fprintf(keystore, "%s" ,(const char *)ciphertext);	
	//printf("KLUCZ zapisywany:%s KKK   %i" ,(const char *)ciphertext, ciphertext_len);	
}
else{

  unsigned char * decryptedtext = new unsigned char[512];
  unsigned char* keycipher = new unsigned char[512];
  int ciphertext_len = 0;
  int buff;
  while((buff = getc(keystore))!= EOF)
	{
		keycipher[ciphertext_len] = (unsigned char)buff;
		ciphertext_len++;
	}
	ciphertext_len--;
  //fscanf(keystore, "%512c", keycipher);
  int decryptedtext_len;
	//printf("KLUCZ wczytany:%s KKK   %i" ,(const char *)keycipher, ciphertext_len);	


  decryptedtext_len = decrypt(keycipher, ciphertext_len, sha, iv,
    decryptedtext);
  key = ( unsigned char *)decryptedtext;
}

  unsigned char* KEY;
  KEY = new unsigned char[this->keyLength];
  KEY[this->keyLength] = '\0';
  printf("%s        PIES \n",KEY);
  for(int i =0; i<this->keyLength; i++)
	{KEY[i] = key[i];}

  //delete(key);
  //delete(sha);
    	//std::cout << "tutajkhjghjfghyt" <<std::endl;
  fclose(keystore);
  //std::cout<<this->keyLength <<std::endl;
   //printf("KLUCZ %s",KEY);
  std::cout << (const char *)KEY<<"PIES"<<std::endl;
    std::cout <<key<<"PIES"<<std::endl;
   EVP_cleanup();
  ERR_free_strings();
  return KEY;
	}
	
unsigned char* AesFileEnc::iv ( )
{
	unsigned char * IV;
	IV = new unsigned char[this->keyLength];
	IV[this->keyLength] = '\0';
	srand(time(0));
	int j;	
	char *buffer;
	buffer = new char;
	for(int i = 0 ; i<this->keyLength; i++)
	{
		j = (int)(rand() / (RAND_MAX + 1.0) * 16);
		

		sprintf(buffer,"%x",i);
		IV[i] = *buffer;
	}
	delete buffer;
	return IV;
}
unsigned char* AesFileEnc::iv (int keyLength )
{
	unsigned char * IV;
	IV = new unsigned char[keyLength];
	IV[this->keyLength] = '\0';
	srand(time(0));
	int j;
	char *buffer;
	buffer = new char;
	for(int i = 0 ; i< keyLength; i++)
	{
		j = (int)(rand() / (RAND_MAX +1.0) * 16);
		sprintf(buffer, "%x",i);
		IV[i] = *buffer;
		
	}
	delete buffer;
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

	std::cout << "tutaj";
	unsigned char* key = this->key();
	//	std::cout <<key<<std::endl;
	//unsigned char key[] = "0123456789abcdeF";
	std::cout <<key<< std::endl;
	unsigned char *iv = this->iv();
		std::cout <<iv<<std::endl;
	//unsigned char iv[] = "1234567887654321";
	EVP_CIPHER_CTX_init(&ctx);
			
	switch(this->type)
	{
		case cbc128:
			std::cout << "TUTU";
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

			OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == this->keyLength);
			OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == this->keyLength);
			EVP_CipherInit_ex(&ctx, NULL, NULL, key, iv, do_encrypt);
	
			for(;;)
					{
					inlen = fread(inbuf, 1, 1024, in);
					if(inlen <= 0) break;
					if(!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen))
							{
	
							EVP_CIPHER_CTX_cleanup(&ctx);
							return 0;
							}
					fwrite(outbuf, 1, outlen, out);
					}
			if(!EVP_CipherFinal_ex(&ctx, outbuf, &outlen))
					{

					EVP_CIPHER_CTX_cleanup(&ctx);
					return 0;
					}
			fwrite(outbuf, 1, outlen, out);

			EVP_CIPHER_CTX_cleanup(&ctx);
			return 1;
			}
			
int AesFileEnc::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) this->handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int AesFileEnc::decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}


void AesFileEnc::handleErrors()
{
  ERR_print_errors_fp(stderr);
  abort();
}
