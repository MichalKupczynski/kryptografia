#include "AesFileEnc.h"

        
int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out;
	Aes_type type;
	
	std::cout <<argc;
	if (argc <5)
		return 1;
	
	const char * Data = argv[1];
	const char* Result = argv[2];
	const char* keystore_path = argv[3];
	const char* option = argv[4];
	type = cbc128;
	std::cout<<argv[5];
	if(argc >=5)
	{
		std::cout << "tutaj";
		if (argv[5] == "cbc128")
			type = cbc128;
		else if(argv[5] == "cbc192")
			type = cbc192;
		else if(argv[5] == "cbc256")
			type = cbc256;
		else if(argv[5] == "ecb128")
			type = ecb128;
		else if(argv[5] == "ecb192")
			type = ecb192;
		else if(argv[5] == "ecb256")
			type = ecb256;
		else if(argv[5] == "cfb128")
			type = cfb128;
		else if(argv[5] == "cfb192")
			type = cfb192;
		else if(argv[5] == "cfb256")
			type = cfb256;
		else if(argv[5] == "ofb128")
			type = ofb128;
		else if(argv[5] == "ofb192")
			type = ofb192;
		else if(argv[5] == "ofb256")
			type = ofb256;
		else
			std::cout<< "unknown parameter" << argv[5] << "type is set for cbc128" <<std::endl;
	}
	


	in = fopen(Data, "r");
	out = fopen(Result, "w");
	int p = 1;

	/**std::cout << option;
	if (!std::string(option).compare("-d"))
		p = 0;
	std::cout <<p;
	AesFileEnc Aes(type,keystore_path);
    Aes.do_crypt(in, out, p);*/

	fclose(in);
	fclose(out);

	return 0;
}
