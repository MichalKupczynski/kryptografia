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
	if(argc >=5)
	{
		std::string stype = std::string(argv[5]);
		if (stype == "cbc128")
			type = cbc128;
		else if(stype == "cbc192")
			type = cbc192;
		else if(stype == "cbc256")
			type = cbc256;
		else if(stype == "ecb128")
			type = ecb128;
		else if(stype == "ecb192")
			type = ecb192;
		else if(stype == "ecb256")
			type = ecb256;
		else if(stype == "cfb128")
			type = cfb128;
		else if(stype == "cfb192")
			type = cfb192;
		else if(stype == "cfb256")
			type = cfb256;
		else if(stype == "ofb128")
			type = ofb128;
		else if(stype == "ofb192")
			type = ofb192;
		else if(stype == "ofb256")
			type = ofb256;
		else
			std::cout<< "unknown parameter " << argv[5] << " type is set for cbc128" <<std::endl;
	}
	


	in = fopen(Data, "r");
	out = fopen(Result, "w");
	int p = 1;

	if (!std::string(option).compare("-d"))
		p = 0;
	AesFileEnc Aes(type,keystore_path);
    Aes.do_crypt(in, out, p);

	fclose(in);
	fclose(out);

	return 0;
}
