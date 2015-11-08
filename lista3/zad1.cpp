#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <iostream>

 int do_crypt(FILE *in, FILE *out, int do_encrypt)
        {
        /* Allow enough space in output buffer for additional block */
        unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
        int inlen, outlen;
        EVP_CIPHER_CTX ctx;
        /* Bogus key and IV: we'd normally set these from
         * another source.
         */
        unsigned char key[] = "0123456789abcdeF";
        unsigned char iv[] = "1234567887654321";

        /* Don't set key or IV right away; we want to check lengths */
        EVP_CIPHER_CTX_init(&ctx);
        EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
                do_encrypt);
        OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
        OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);

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
                   //std::cout << outbuf;
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
        

int do_decrypt(FILE *in, FILE *out, int do_encrypt)
        {
        /* Allow enough space in output buffer for additional block */
        unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
        int inlen, outlen;
        EVP_CIPHER_CTX ctx;
        /* Bogus key and IV: we'd normally set these from
         * another source.
         */
        unsigned char key[] = "0123456789abcdeF";
        unsigned char iv[] = "1234567887654321";

        /* Don't set key or IV right away; we want to check lengths */
        EVP_CIPHER_CTX_init(&ctx);
        EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
                do_encrypt);
        OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
        OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);

        /* Now we can set key and IV */
        EVP_DecryptInit_ex(&ctx, NULL, NULL, key, iv);

        for(;;)
                {
                inlen = fread(inbuf, 1, 1024, in);
                if(inlen <= 0) break;
                if(!EVP_DecryptUpdate(&ctx, outbuf, &outlen, inbuf, inlen))
                        {
                        /* Error */
                        EVP_CIPHER_CTX_cleanup(&ctx);
                        std::cout << 0;
                        return 0;
                        }
                fwrite(outbuf, 1, outlen, out);
                }
        if(!EVP_DecryptFinal_ex(&ctx, outbuf, &outlen))
                {
                /* Error */
                EVP_CIPHER_CTX_cleanup(&ctx);
                std::cout << 1;
                return 0;
                }
        fwrite(outbuf, 1, outlen, out);

        EVP_CIPHER_CTX_cleanup(&ctx);
        std::cout<<2;
        return 1;
        }
        
int main(int argc, char* argv[])
{
	FILE * out;
	FILE *in;
	FILE *result;
	in = fopen("dane", "rw");
	out = fopen("wynik", "rw");
	int p = 5;
    p =  do_crypt(in, out, 1);
	std::cout << p ;
	fclose(in);
	fclose(out);

	in = fopen("wynik", "rwb");
	result = fopen("rozszyforwany", "rwb");
	do_decrypt(in, result,1);
	//system("openssl aes-256-cbc -d -in out.enc -out m");
	return 0;
}
