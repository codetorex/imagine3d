#include "cbitmap.h"

#define SIZE 256
#define MASK 0xFF

float Mtx[9];
void Initialize(UINT nSeed);
float Noise1(float x);
float Noise2(float x, float y);
float Noise3(float x, float y, float z);
BYTE p[SIZE];
float gx[SIZE];
float gy[SIZE];
float gz[SIZE];

float Axis[3] = {0.16f, 0.67f, 0.43f};
void InitRotationMatrix(const float *pAxis, float r);


void InitRotationMatrix(const float *pAxis, float r)
{
  // The axis vector must be of unit length
  float x, y, z, m;
  m = sqrtf(pAxis[0]*pAxis[0] + pAxis[1]*pAxis[1] + pAxis[2]*pAxis[2]);
  x = pAxis[0]/m;
  y = pAxis[1]/m;
  z = pAxis[2]/m;

  // Compute the rotation matrix  
  float c = (float)cos(r);
  float s = (float)sin(r);

  Mtx[0] = (x * x) * (1.0f - c) + c;
  Mtx[1] = (y * x) * (1.0f - c) + (z * s);
  Mtx[2] = (z * x) * (1.0f - c) - (y * s);

  Mtx[3] = (x * y) * (1.0f - c) - (z * s);
  Mtx[4] = (y * y) * (1.0f - c) + c;
  Mtx[5] = (z * y) * (1.0f - c) + (x * s);

  Mtx[6] = (x * z) * (1.0f - c) + (y * s);
  Mtx[7] = (y * z) * (1.0f - c) - (x * s);
  Mtx[8] = (z * z) * (1.0f - c) + c;
} 



//=============================================================================

//=============================================================================
void Initialize(UINT nSeed)
{
	int i, j, nSwap;

	srand(nSeed);

	// Initialize the permutation table
	for(i = 0; i < SIZE; i++)
		p[i] = i;

	for(i = 0; i < SIZE; i++)
	{
		j = rand() & MASK;

		nSwap = p[i];
		p[i]  = p[j];
		p[j]  = nSwap;
	}

	// Generate the gradient lookup tables
	for(i = 0; i < SIZE; i++)
	{
		// Ken Perlin proposes that the gradients are taken from the unit 
		// circle/sphere for 2D/3D, but there are no noticable difference 
		// between that and what I'm doing here. For the sake of generality 
		// I will not do that.

		gx[i] = float(rand())/(RAND_MAX/2) - 1.0f; 
		gy[i] = float(rand())/(RAND_MAX/2) - 1.0f;
		gz[i] = float(rand())/(RAND_MAX/2) - 1.0f;
	}
}

//=============================================================================
float Noise1(float x)
{
	// Compute what gradients to use
	int qx0 = (int)floorf(x);
	int qx1 = qx0 + 1;
	float tx0 = x - (float)qx0;
	float tx1 = tx0 - 1;

	// Make sure we don't come outside the lookup table
	qx0 = qx0 & MASK;
	qx1 = qx1 & MASK;

	// Compute the dotproduct between the vectors and the gradients
	float v0 = gx[qx0]*tx0;
	float v1 = gx[qx1]*tx1;

	// Modulate with the weight function
	float wx = (3 - 2*tx0)*tx0*tx0;
	float v = v0 - wx*(v0 - v1);

	return v;
}

//=============================================================================
float Noise2(float x, float y)
{
	// Compute what gradients to use
	int qx0 = (int)floorf(x);
	int qx1 = qx0 + 1;
	float tx0 = x - (float)qx0;
	float tx1 = tx0 - 1;

	int qy0 = (int)floorf(y);
	int qy1 = qy0 + 1;
	float ty0 = y - (float)qy0;
	float ty1 = ty0 - 1;

	// Make sure we don't come outside the lookup table
	qx0 = qx0 & MASK;
	qx1 = qx1 & MASK;

	qy0 = qy0 & MASK;
	qy1 = qy1 & MASK;

	// Permutate values to get pseudo randomly chosen gradients
	int q00 = p[(qy0 + p[qx0]) & MASK];
	int q01 = p[(qy0 + p[qx1]) & MASK];

	int q10 = p[(qy1 + p[qx0]) & MASK];
	int q11 = p[(qy1 + p[qx1]) & MASK];

	// Compute the dotproduct between the vectors and the gradients
	float v00 = gx[q00]*tx0 + gy[q00]*ty0;
	float v01 = gx[q01]*tx1 + gy[q01]*ty0;

	float v10 = gx[q10]*tx0 + gy[q10]*ty1;
	float v11 = gx[q11]*tx1 + gy[q11]*ty1;

	// Modulate with the weight function
	float wx = (3 - 2*tx0)*tx0*tx0;
	float v0 = v00 - wx*(v00 - v01);
	float v1 = v10 - wx*(v10 - v11);

	float wy = (3 - 2*ty0)*ty0*ty0;
	float v = v0 - wy*(v0 - v1);

	return v;
}

//=============================================================================
float Noise3(float x, float y, float z)
{
	// Compute what gradients to use
	int qx0 = (int)floorf(x);
	int qx1 = qx0 + 1;
	float tx0 = x - (float)qx0;
	float tx1 = tx0 - 1;

	int qy0 = (int)floorf(y);
	int qy1 = qy0 + 1;
	float ty0 = y - (float)qy0;
	float ty1 = ty0 - 1;

	int qz0 = (int)floorf(z);
	int qz1 = qz0 + 1;
	float tz0 = z - (float)qz0;
	float tz1 = tz0 - 1;

	// Make sure we don't come outside the lookup table
	qx0 = qx0 & MASK;
	qx1 = qx1 & MASK;

	qy0 = qy0 & MASK;
	qy1 = qy1 & MASK;

	qz0 = qz0 & MASK;
	qz1 = qz1 & MASK;

	// Permutate values to get pseudo randomly chosen gradients
	int q000 = p[(qz0 + p[(qy0 + p[qx0]) & MASK]) & MASK];
	int q001 = p[(qz0 + p[(qy0 + p[qx1]) & MASK]) & MASK];

	int q010 = p[(qz0 + p[(qy1 + p[qx0]) & MASK]) & MASK];
	int q011 = p[(qz0 + p[(qy1 + p[qx1]) & MASK]) & MASK];

	int q100 = p[(qz1 + p[(qy0 + p[qx0]) & MASK]) & MASK];
	int q101 = p[(qz1 + p[(qy0 + p[qx1]) & MASK]) & MASK];

	int q110 = p[(qz1 + p[(qy1 + p[qx0]) & MASK]) & MASK];
	int q111 = p[(qz1 + p[(qy1 + p[qx1]) & MASK]) & MASK];

	// Compute the dotproduct between the vectors and the gradients
	float v000 = gx[q000]*tx0 + gy[q000]*ty0 + gz[q000]*tz0;
	float v001 = gx[q001]*tx1 + gy[q001]*ty0 + gz[q001]*tz0;  

	float v010 = gx[q010]*tx0 + gy[q010]*ty1 + gz[q010]*tz0;
	float v011 = gx[q011]*tx1 + gy[q011]*ty1 + gz[q011]*tz0;

	float v100 = gx[q100]*tx0 + gy[q100]*ty0 + gz[q100]*tz1;
	float v101 = gx[q101]*tx1 + gy[q101]*ty0 + gz[q101]*tz1;  

	float v110 = gx[q110]*tx0 + gy[q110]*ty1 + gz[q110]*tz1;
	float v111 = gx[q111]*tx1 + gy[q111]*ty1 + gz[q111]*tz1;

	// Modulate with the weight function
	float wx = (3 - 2*tx0)*tx0*tx0;
	float v00 = v000 - wx*(v000 - v001);
	float v01 = v010 - wx*(v010 - v011);
	float v10 = v100 - wx*(v100 - v101);
	float v11 = v110 - wx*(v110 - v111);

	float wy = (3 - 2*ty0)*ty0*ty0;
	float v0 = v00 - wy*(v00 - v01);
	float v1 = v10 - wy*(v10 - v11);

	float wz = (3 - 2*tz0)*tz0*tz0;
	float v = v0 - wz*(v0 - v1);

	return v;
}

void IBitmap::pnoise(float z,float scal)
{

	Initialize(0);
	InitRotationMatrix(Axis, 0.34521f);

	for( int iy = 1; iy < bh+1; iy++ )
	{
		// Compute the starting position from the y and z coordinate
		float y = iy/scal;
		float p[3] = { y*Mtx[1] + z*Mtx[2], 
			           y*Mtx[4] + z*Mtx[5], 
					   y*Mtx[7] + z*Mtx[8] };

		// This represents movements along the x axis
		float x = 1/scal;
		float d[3] = { x*Mtx[0], x*Mtx[3], x*Mtx[6] };

		for( int ix = 1; ix < bw+1; ix++ )
		{
			BYTE n = BYTE(255*0.5f*(Noise3(p[0], p[1], p[2]) + 1));

			setpixel(ix,iy,mono(n));
			//map[ix+iy*256] = (n<<16) | (n<<8) | n;

			p[0] += d[0];
			p[1] += d[1];
			p[2] += d[2];
		}
	}

}
/*
unsigned char p[512];
double	fade	(double t);
double	plerp	(double t,double a,double b);
double	grad	(long hash,double x,double y,double z);
double	pnoise	(double x,double y,double z);
void	genlist	();

double fade(double t){return (t * t * t * ( t * ( t * 6 - 15) + 10));}
double plerp(double t,double a,double b){return (a + t * (b-a));}
double grad(int hash,double x,double y,double z)
{
	int h=hash & 0xF;
	double u,v,g;
	g = 0;

	if (h<8 || h==12 || h==13){u = x;}else{u = y;}
	if (h<4 || h==12 || h==13){v = y;}else{y = z;}
	if ((h & 1) == 0){g=u;}else{g=-u;}
	if ((h & 2) == 0){g=g+v;}else{g=g-v;}
	return g;
}


unsigned char getp(int i)
{
	return p[i];
}
void genlist()
{
	for (int i=0;i<255;i++)
	{
		p[i] = rand()%255;
		p[256+i] = p[i];
	}
}

double penoise(double x,double y,double z)
{
	int iX,iY,iZ;
	double u,v,w;
	int a,aa,ab,b,ba,bb;
	double sonuc;
	double nx,ny,nz;
	iX = (int)floor(x) & 0xFF;
	iY = (int)floor(y) & 0xFF;
	iZ = (int)floor(z) & 0xFF;

	nx =x- floor(x);
	ny =y- floor(y);
	nz =z- floor(z);
	
	u = fade(nx);
	v = fade(ny);
	w = fade(nz);

	a	= p[iX]		+ iY;
	aa	= p[a]		+ iZ;
	ab	= p[a+1]	+ iZ;
	b	= p[iX+1]	+ iY;
	ba	= p[b]		+ iZ;
	bb	= p[b+1]	+ iZ;
	
	sonuc = plerp(w,plerp(v,plerp(u,grad(p[aa],x,y,z),grad(p[ba],x-1,y,z)),plerp(u,grad(p[ab],x,y-1,z),grad(p[bb],x-1,y-1,z))),plerp(v,plerp(u,grad(p[aa+1],x,y,z-1),grad(p[ba+1],x-1,y,z-1)),plerp(u,grad(p[ab+1],x,y-1,z-1),grad(p[bb+1],x-1,y-1,z-1))));
	return sonuc;
}

*/
   
/*
'***************************************************************************************************
'**************************                                 ****************************************
'**************************                                 ****************************************
'**************************                                 ****************************************
'**************************          -PERLIN NOISE-         ****************************************
'**************************                                 ****************************************
'**************************                                 ****************************************
'**************************                                 ****************************************
'***************************************************************************************************

Public Function GenerateNoise(octav As Long, scal As Long, m_bAbsolute As Boolean, rcomp As Single, gcomp As Single, bcomp As Single) As Direct3DTexture8
On Error Resume Next
Dim X As Double
Dim Y As Double
Dim xStep As Double
Dim yStep As Double
Dim xo As Double
Dim yo As Double
Dim zO As Double
Dim l As Double
Dim I As Double
Dim px As Long
Dim py As Long
Dim pxEnd As Long
Dim pyEnd As Long
Dim lTime As Long
Dim r As Double
Dim g As Double
Dim b As Double
generate
   octav = 2 ^ (octav - 1)
         m_z = 0.01
   m_zStep = 0.03

      pxEnd = wid
      pyEnd = hei
      xStep = 1# / (wid / (scal * 2#))
      yStep = 1# / (hei / (scal * 2#))
      
      ' Get the bits in the from DIB section:
         m_z = m_z + m_zStep
         px = 0
         For X = -scal To scal Step xStep
            py = 0
            For Y = -scal To scal Step yStep
               l = Noise(X, Y, m_z)
               If (m_bAbsolute) Then
                  l = Abs(l)
                  If (octav > 1) Then
                     xo = X
                     yo = Y
                     zO = m_z
                     I = 1#
                     Do
                        xo = xo + xo
                        yo = yo + yo
                        zO = zO + zO
                        I = I + I
                        l = l + Abs(Noise(xo, yo, zO) / I)
                     Loop While (I < octav)
                     If (l > 1#) Then l = 1#
                  End If
                  
                  r = 255 * l
                  
               Else
                  If (octav > 1) Then
                     xo = X
                     yo = Y
                     zO = m_z
                     I = 1#
                     Do
                        xo = xo + xo
                        yo = yo + yo
                     '   'xO = yO + xO - turn on for streaks
                     '   'yO = xO + yO - turn on for streaks
                        zO = zO + zO
                        I = I + I
                        l = l + Noise(xo, yo, zO) / I
                     Loop While (I < octav)
                  End If
                  
                  r = 128 + 128 * l
                  ' Check for out of bounds
                  If (r > 255) Then r = 255
                  If (r < 0) Then r = 0
               End If
            
               SetPixel px, py, r * rcomp, r * gcomp, r * bcomp
               
               py = py + 1
               If (py >= pyEnd) Then
                  Exit For
               End If
               
            Next Y
            
            px = px + 1
            If (px >= pxEnd) Then
               Exit For
            End If
            
         Next X
'Set GenerateNoise = CreateTexture
'WriteBMP App.path + "\perlin.bmp"
End Function


Private Function Noise(ByVal X As Double, ByVal Y As Double, ByVal Z As Double) As Double
Dim iX As Long
Dim iY As Long
Dim iZ As Long
Dim u As Double
Dim v As Double
Dim w As Double
Dim a As Long
Dim aa As Long
Dim ab As Long
Dim b As Long
Dim ba As Long
Dim bb As Long

   ' Find unit cube that contains point:
   iX = Int(X) And &HFF&
   iY = Int(Y) And &HFF&
   iZ = Int(Z) And &HFF&
   
   ' Find relative x,y,z of point in cube:
   X = X - Int(X)
   Y = Y - Int(Y)
   Z = Z - Int(Z)
   
   ' Compute fade curves for each of x,y,z
   u = fade(X)
   v = fade(Y)
   w = fade(Z)
   
   ' Hash coordinates of the 8 cube corners:
   a = p(iX) + iY
   aa = p(a) + iZ
   ab = p(a + 1) + iZ
   b = p(iX + 1) + iY
   ba = p(b) + iZ
   bb = p(b + 1) + iZ
   
   ' Add the blended results from 8 corners of the cube:
   Noise = lerp(w, lerp(v, lerp(u, grad(p(aa), X, Y, Z), _
                              grad(p(ba), X - 1, Y, Z)), _
                           lerp(u, grad(p(ab), X, Y - 1, Z), _
                              grad(p(bb), X - 1, Y - 1, Z))), _
                     lerp(v, lerp(u, grad(p(aa + 1), X, Y, Z - 1), _
                              grad(p(ba + 1), X - 1, Y, Z - 1)), _
                           lerp(u, grad(p(ab + 1), X, Y - 1, Z - 1), _
                              grad(p(bb + 1), X - 1, Y - 1, Z - 1))))
   
End Function

Private Function fade(ByVal t As Double) As Double
   fade = t * t * t * (t * (t * 6# - 15#) + 10#)
End Function
Private Function lerp(ByVal t As Double, ByVal a As Double, ByVal b As Double) As Double
   lerp = a + t * (b - a)
End Function
Private Function grad(ByVal hash As Long, ByVal X As Double, ByVal Y As Double, ByVal Z As Double) As Double
Dim h As Long
Dim u As Double
Dim v As Double
Dim g As Double

   '// CONVERT LO 4 BITS OF HASH CODE
   h = hash And &HF&
   
   '// INTO 12 GRADIENT DIRECTIONS.
   If (h < 8) Or (h = 12) Or (h = 13) Then
      u = X
   Else
      u = Y
   End If
   
   If (h < 4) Or (h = 12) Or (h = 13) Then
      v = Y
   Else
      Y = Z
   End If
   
   If ((h And 1) = 0) Then
      g = u
   Else
      g = -u
   End If
   
   If ((h And 2) = 0) Then
      g = g + v
   Else
      g = g - v
   End If
   
   grad = g
   
End Function



*/