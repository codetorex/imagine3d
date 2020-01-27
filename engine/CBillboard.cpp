#include "cbillboard.h"
#include "cmatrix4x4f.h"
#include "cvision.h"

/*
Vector3f Matrix44f::operator*(const Vector3f &v) const
{
	return Vector3f
		(float(matrix[0] * v.x + matrix[4] * v.y + matrix[8] * v.z + matrix[12]),
		 float(matrix[1] * v.x + matrix[5] * v.y + matrix[9] * v.z + matrix[13]),
		 float(matrix[2] * v.x + matrix[6] * v.y + matrix[10] * v.z + matrix[14])
		);
}*/
CBBoard::CBBoard()
{
	color.x = 1;
	color.y = 1;
	color.z = 1;
	autogetcampos = false;
	camPos.x = 0;
	camPos.y = 0;
	camPos.z = 0;
}
/*



void BillboardAxis(const Vertex3f &pos, const Vector3f &axis, const Vertex3f &camPos)
{	// create the look vector: pos -> camPos
	Vector3f	look	= camPos - pos;
	look.Normalize();

	// billboard about the direction vector
	Vector3f	up		= axis;
	Vector3f	right	= up.Cross(look);

	// watch out when the look vector is almost equal to the up vector the right
	// vector gets close to zeroed, normalize it
	right.Normalize();

	// the billboard won't actually face the direction of the look vector we
	// created earlier, that was just used as a tempory vector to create the
	// right vector so we could calculate the correct look vector from that.
	look = right.Cross(up);

	Matrix44f	bbmat;
	CreateBillboardMatrix(bbmat, right, up, look, pos);

	// apply the billboard
	glMultMatrixf(bbmat.matrix);
};
*/
void CBBoard::render(vector3f pos,float scale,vector3f axis)
{

	if ( autogetcampos )
	{
	vector3f camPos,camUp;

	matrix4x4f		view;
	glGetFloatv(GL_MODELVIEW_MATRIX, view.m);

	camPos	= vector3f(-view.m[12], -view.m[13], -view.m[14]);
	camUp	= vector3f(view.m[1], view.m[5], view.m[9]);

	view.m[12] = view.m[13] = view.m[14] = 0;
	view.transposerotation();
	camPos	= view * camPos;
	}

	
	glPushMatrix();
	matrixset(pos,axis);

		glBindTexture(GL_TEXTURE_2D,texid);
		enTP();
		glDepthMask(false);
		//float laz=1*scale;

			glBegin(GL_TRIANGLE_FAN);
			glColor3f(color.x,color.y,color.z);
			glTexCoord2i(1,0);	glVertex3f(scale, -scale, 0);
			glTexCoord2i(1,1);	glVertex3f(scale, scale, 0);
			glTexCoord2i(0,1);	glVertex3f(-scale, scale, 0);
			glTexCoord2i(0,0);	glVertex3f(-scale, -scale, 0);
			glEnd();
		
		diTP();
		glDepthMask(true);

	glPopMatrix();


}

void CBBoard::matrixset(vector3f pos,vector3f axis)
{
	if ( autogetcampos )
	{
	vector3f camPos,camUp;

	matrix4x4f		view;
	glGetFloatv(GL_MODELVIEW_MATRIX, view.m);

	camPos	= vector3f(-view.m[12], -view.m[13], -view.m[14]);
	camUp	= vector3f(view.m[1], view.m[5], view.m[9]);

	view.m[12] = view.m[13] = view.m[14] = 0;
	view.transposerotation();
	camPos	= view * camPos;
	}

	vector3f look = camPos - pos;
	look.normalize();

	vector3f up = axis;
	vector3f right = cross(up,look);

	right.normalize();

	look = cross(right,up);

	matrix4x4f bbmat;

	bbmat.m[0] = right.x;
	bbmat.m[1] = right.y;
	bbmat.m[2] = right.z;
	bbmat.m[3] = 0;
	bbmat.m[4] = up.x;
	bbmat.m[5] = up.y;
	bbmat.m[6] = up.z;
	bbmat.m[7] = 0;
	bbmat.m[8] = look.x;
	bbmat.m[9] = look.y;
	bbmat.m[10] = look.z;
	bbmat.m[11] = 0;
	// Add the translation in as well.
	bbmat.m[12] = pos.x;
	bbmat.m[13] = pos.y;
	bbmat.m[14] = pos.z;
	bbmat.m[15] = 1;
	glMultMatrixf(bbmat.m);
}