#include "bumptex.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>
#include "gl_arb_multitexture.h"
#include <math.h>
#include "cmatrix4x4f.h"

void BumpTex::glBumpedVertex(vector3f vertex,float u,float v,vector3f tang,vector3f bino,vector3f norm)
{
	//vertex_to_light = light_pos - vertex;
	
	vertex_to_light = vertex - light_pos;
	//vertex_to_light = mv3f(0,0,0);
	//vertex_to_light.x = light_pos.x - vertex.x;
	//vertex_to_light.y = light_pos.y - vertex.y;
	//vertex_to_light.z = light_pos.z - vertex.z;

	vector3f son;
	son.x =dot(tang,vertex_to_light);
	son.y =dot(bino,vertex_to_light);
	son.z =dot(norm,vertex_to_light);
	/*

		torus.vertices[i].tangentSpaceLight.x=
		torus.vertices[i].sTangent.DotProduct(lightVector);
		torus.vertices[i].tangentSpaceLight.y=
		torus.vertices[i].tTangent.DotProduct(lightVector);
		torus.vertices[i].tangentSpaceLight.z=
		torus.vertices[i].normal.DotProduct(lightVector);

	*/
	glMultiTexCoord3f(GL_TEXTURE0, son.x, son.y, son.z);
		
		glMultiTexCoord2f(GL_TEXTURE1, u, v);
		glMultiTexCoord2f(GL_TEXTURE2, u, v);

		glVertex3f(vertex.x, vertex.y, vertex.z);	
}
void BumpTex::AttachTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE) ;

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bumpmap);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_DOT3_RGB) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE) ;

	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, basemap);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
									// Flush The GL Rendering Pipeline


}
void DisableBumpMap()
{
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

int BumpTex::GenNormalizationCubeMap(unsigned int size)
{
	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	unsigned char* data = new unsigned char[size*size*3];
	vector3f add;
	add.set(0.5f,0.5f,0.5f);
	float carp = 0.5f;

	float offset = 0.5f;
	float halfSize = size * 0.5f;
	vector3f temp;
	unsigned int bytePtr = 0;

	for(unsigned int j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp.x = halfSize;
			temp.y = (j+offset-halfSize);
			temp.z = -(i+offset-halfSize);
			temp.normalize();
			temp = temp * carp;
			temp = temp + add;

			data[bytePtr] = (unsigned char)(temp.x * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp.y * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp.z * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp.x = -halfSize;
			temp.y = (j+offset-halfSize);
			temp.z = (i+offset-halfSize);
			temp.normalize();
			temp = temp * carp;
			temp = temp + add;


			data[bytePtr] = (unsigned char)(temp.x * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp.y * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp.z * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp.x = i+offset-halfSize;
			temp.y = -halfSize;
			temp.z = j+offset-halfSize;
			temp.normalize();
			temp = temp * carp;
			temp = temp + add;

			data[bytePtr] = (unsigned char)(temp.x * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp.y * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp.z * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp.x = i+offset-halfSize;
			temp.y = halfSize;
			temp.z = -(j+offset-halfSize);
			temp.normalize();
			temp = temp * carp;
			temp = temp + add;

			data[bytePtr] = (unsigned char)(temp.x * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp.y * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp.z * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp.x = i+offset-halfSize;
			temp.y = (j+offset-halfSize);
			temp.z = halfSize;
			temp.normalize();
			temp = temp * carp;
			temp = temp + add;

			data[bytePtr] = (unsigned char)(temp.x * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp.y * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp.z * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp.x = -(i+offset-halfSize);
			temp.y = (j+offset-halfSize);
			temp.z = -halfSize;
			temp.normalize();
			temp = temp * carp;
			temp = temp + add;

			data[bytePtr] = (unsigned char)(temp.x * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp.y * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp.z * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete [] data;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return true;
}
