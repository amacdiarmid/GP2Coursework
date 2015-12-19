#ifndef _CUBETEXTURE_H
#define _CUBETEXTURE_H

#include "Texture.h"

GLuint loadCubeMap(const string& filenamePosZ, const string& filenameNegZ, const string& filenamePosX, const string& filenameNegX, const string& filenamePosY, const string& filenameNegY);

class CubeTexture : public Texture
{

public:

	CubeTexture(){};
	CubeTexture(string tempName){};
	~CubeTexture(){};

	void loadSkyBoxTextures(const string& filenamePosZ, const string& filenameNegZ, const string& filenamePosX, const string& filenameNegX, const string& filenamePosY, const string& filenameNegY);
	GLuint getEnvironmentMap(){ return environmentMap; }

private:

	GLuint environmentMap = 0;


	
};

#endif