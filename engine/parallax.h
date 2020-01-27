#ifndef parallax_h
#define parallax_h

class plxmap // parallax map
{
public:
	unsigned int basemap; // base map
	unsigned int normmap; // normal map
	unsigned int heigmap; // height map

	unsigned int vertexp; // vertex program
	unsigned int fragmep; // fragment program

	void AttachTexture();
	void AttachProgram();

	void Attach();
	void Detach();
};


#endif