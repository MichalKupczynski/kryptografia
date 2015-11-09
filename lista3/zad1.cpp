#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <iostream>

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

 int do_crypt(FILE *in, FILE *out, int do_encrypt, Aes_type type)
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
        //switch(type)
		//{
		//	case cbc128:
		//		EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
		//			do_encrypt);
	//			break;
			/**case cbc192:
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
				break;*/
			//}
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

        
int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out;
	Aes_type type;
	
	std::cout <<argc;
	if (argc <4)
		return 1;
	
	const char * Data = argv[1];
	const char* Result = argv[2];
	const char* option = argv[3];
				type = cbc128;
	if(argc ==4)
	{
		if (argv[4] == "cbc128")
			type = cbc128;
		else if(argv[4] == "cbc192")
			type = cbc192;
		else if(argv[4] == "cbc256")
			type = cbc256;
		else if(argv[4] == "ecb128")
			type = ecb128;
		else if(argv[4] == "ecb192")
			type = ecb192;
		else if(argv[4] == "ecb256")
			type = ecb256;
		else if(argv[4] == "cfb128")
			type = cfb128;
		else if(argv[4] == "cfb192")
			type = cfb192;
		else if(argv[4] == "cfb256")
			type = cfb256;
		else if(argv[4] == "ofb128")
			type = ofb128;
		else if(argv[4] == "ofb192")
			type = ofb192;
		else if(argv[4] == "ofb256")
			type = ofb256;
			
	}
	
	in = fopen(Data, "r");
	out = fopen(Result, "w");
	int p = 1;
	std::cout << option;
	if (!std::string(option).compare("-d"))
		p = 0;
	std::cout <<p;
    do_crypt(in, out, p, type);

	fclose(in);
	fclose(out);

	return 0;
}
