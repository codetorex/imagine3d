#ifndef _MDLMODEL_H_
#define _MDLMODEL_H_

#include <windows.h>

#define	MAXVERTICES		2048
#define	MAXBONES		128

typedef	float	vec3_t[3];	// x,y,z
typedef	float	vec4_t[4];	// x,y,z,w

#define	EPSILON	0.001f
#define	Q_PI	3.14159265358979323846f

#define DotProduct(x,y) ((x)[0] * (y)[0] + (x)[1] * (y)[1] + (x)[2] * (y)[2])

BOOL VectorCompare(vec3_t Vector1, vec3_t Vector2);
void CrossProduct(vec3_t Vector1, vec3_t Vector2, vec3_t Cross);
void R_ConcatTransforms(const float In1[3][4], const float In2[3][4], float Out[3][4]);
void VectorIRotate(const vec3_t In1, const float In2[3][4], vec3_t Out);
void VectorTransform(const vec3_t In1, const float In2[3][4], vec3_t Out);
void AngleQuaternion(const vec3_t Angles, vec4_t Quaternion);
void QuaternionMatrix(const vec4_t Quaternion, float (*Matrix)[4]);
void QuaternionSlerp(const vec4_t In1, vec4_t In2, float Time, vec4_t Out);

// Lighting defines
#define LIGHT_FLATSHADE		0x0001
#define LIGHT_FULLBRIGHT	0x0004

// Transition defines
#define	TRANSITION_X		0x0001
#define	TRANSITION_Y		0x0002	
#define	TRANSITION_Z		0x0004
#define	TRANSITION_XR		0x0008
#define	TRANSITION_YR		0x0010
#define	TRANSITION_ZR		0x0020
#define	TRANSITION_TYPES	0x7FFF
#define	TRANSITION_RLOOP	0x8000

struct tagMDLHeader
{
	long	ID;						// File id
	long	Version;				// File version
	char	Name[64];				// Model name
	long	Length;					// File length
	vec3_t	EyePosition;			// Eye position
	vec3_t	Minimum;				// Ideal movement hull size
	vec3_t	Maximum;	
	vec3_t	BoundingBoxMinimum;		// Bounding box
	vec3_t	BoundingBoxMaximum;		
	long	Flags;					// Flags
	long	NumBones;				// Number of bones
	long	BoneOffset;				// Offset to bone data
	long	NumBoneControllers;		// Number of bone controllers
	long	BoneControllerOffset;	// Offset to bone controller data
	long	NumHitBoxes;			// Complex bounding boxes
	long	HitBoxOffset;				
	long	NumSequences;			// Animation sequences
	long	SequenceOffset;
	long	NumSeqGroups;			// Demand loaded sequences
	long	SeqGroupOffset;
	long	NumTextures;			// Number of textures
	long	TextureOffset;			// File texture offset
	long	TextureData;			// Texture data
	long	NumSkinReferences;		// Replaceable textures
	long	NumSkinFamilies;
	long	SkinOffset;
	long	NumBodyParts;		
	long	BodyPartOffset;
	long	NumAttachments;			// Queryable attachable points
	long	AttachmentOffset;
	long	SoundTable;
	long	SoundOffset;
	long	NumSoundGroups;
	long	SoundGroupOffset;
	long	NumTransitions;			// Animation node to animation node transition graph
	long	TransitionOffset;
};

struct tagMDLCacheUser
{
	void	*Data;
};

struct tagMDLSeqHeader
{
	long	ID;
	long	Version;
	char	Name[64];
	long	Length;
};

struct tagMDLSeqGroup
{
	char			Label[32];		// Textual name
	char			Name[64];		// Filename
	tagMDLCacheUser	Cache;			// Cache index pointer
	long			Data;			// Hack for group 0
};

struct tagMDLSeqDescription
{
	char	Name[32];				// Sequence label
	float	Timing;					// Frame time
	long	Flags;					// Flags
	long	Activity;
	long	Actweight;
	long	NumEvents;
	long	EventIndex;
	long	NumFrames;				// Number of frames
	long	NumPivots;				// Number of foot pivots
	long	PivotOffset;
	long	MotionType;	
	long	MotionBone;
	vec3_t	LinearMovement;
	long	AutoMovePosIndex;
	long	AutoMoveAngleIndex;
	vec3_t	BoundingBoxMinimum;		// Bounding box
	vec3_t	BoundingBoxMaximum;		
	long	NumBlends;
	long	AnimOffset;				// mstudioanim_t pointer relative to start of sequence group 
									// data[blend][bone][X, Y, Z, XR, YR, ZR]
	long	BlendType[2];			// X, Y, Z, XR, YR, ZR
	float	BlendStart[2];			// Starting value
	float	BlendEnd[2];			// Ending value
	long	BlendParent;
	long	SeqGroup;				// Sequence group for demand loading
	long	EntryNode;				// Transition node at entry
	long	ExitNode;				// Transition node at exit
	long	NodeFlags;				// Transition rules	
	long	NextSeq;				// Auto advancing sequences
};

struct tagMDLBone
{
	char	Name[32];				// Bone name for symbolic links
	long	Parent;					// Parent bone
	long	Flags;					// ??
	long	BoneController[6];		// Bone controller index, -1 == none
	float	Value[6];				// Default DoF values
	float	Scale[6];				// Scale for delta DoF values
};

struct tagMDLBoneController
{
	long	Bone;					// -1 == 0
	long	Type;					// X, Y, Z, XR, YR, ZR, M
	float	Start;
	float	End;
	long	Rest;					// Byte index value at rest
	long	Index;					// 0-3 user set controller, 4 mouth
};

struct tagAnimation
{
	WORD	Offset[6];
};

union tagMDLAnimFrame
{
	struct
	{
		BYTE	Valid;
		BYTE	Total;
	};

	short	Value;
};

struct tagMDLBodyPart
{
	char	Name[64];
	long	NumModels;
	long	Base;
	long	ModelOffset;			// Index into models array
};

struct tagMDLTexture
{
	char	Name[64];
	long	Flags;
	long	Width;
	long	Height;
	long	Index;
};

struct tagMDLModel
{
	char	Name[64];
	long	Type;
	float	BoundingRadius;
	long	NumMesh;
	long	MeshOffset;
	long	NumVertices;			// Number of unique vertices
	long	VertexInfoOffset;		// Vertex bone info
	long	VertexOffset;			// Vertex offset
	long	NumNormals;				// number of unique surface normals
	long	NormalInfoOffset;		// Normal bone info
	long	NormalOffset;			// Normal offset
	long	NumGroups;				// Deformation groups
	long	GroupOffset;
};

struct tagMDLMesh
{
	long	NumTriangles;
	long	TriangleOffset;
	long	SkinReference;
	long	NumNormals;				// Per mesh normals
	long	NormalOffset;			// Normal offset
};
class TMDLModel
{
  protected:
	vec3_t			Origin;					// Origin
	vec3_t			Rotation;				// Rotation
	long			CurrentSequence;		// Current sequence
	float			CurrentFrame;			// Current frame
	long			CurrentBodyPart;		// Current body part
	long			CurrentSkin;			// Current skin
	BYTE			Controller[4];			// Controllers
	BYTE			Blending[2];			// Animation blending
	BYTE			MouthPosition;			// Mouth position
	tagMDLHeader	*Header;				// Model header
	tagMDLModel		*Model;					// Model
	tagMDLHeader	*TextureHeader;			// Texture
	tagMDLSeqHeader	*AnimationHeader[32];	// Animation header
		
  public:
	void Init(char *Filename);
	
	void DrawModel();
	
	void AdvanceFrame(float Time);

	void ExtractBoundBox(float *Minimums, float *Maximums);

	long SetSequence(long Sequence);
	
	long GetSequence();
	
	void GetSequenceInfo(float *FrameRate, float *GroundSpeed);
	
	float SetController(long ControllerIndex, float Value);
	
	float SetMouth(float Value);
	
	float SetBlending(long Blender, float Value);
	
	long SetBodyGroup(long Group, long Value);
	
	long SetSkin(long Value);

  protected:
	tagMDLHeader *LoadModel(char *Filename);

	tagMDLSeqHeader *LoadDemandSequences(char *Filename);

	void CalcBoneQuaternion(long Frame, float Value, tagMDLBone *Bone, tagAnimation *Anim, 
		float *Q);

	void CalcBonePosition(long Frame, float Value, tagMDLBone *Bone, tagAnimation *Anim, 
		float *Pos);

	void CalcRotations (vec3_t *Pos, vec4_t *Q, tagMDLSeqDescription *SeqDescription, 
		tagAnimation *Anim, float FrameValue);

	tagAnimation *GetAnim(tagMDLSeqDescription *SeqDescription);

	void SlerpBones(vec4_t Q1[], vec3_t Pos1[], vec4_t Q2[], vec3_t Pos2[], float Value);
	
	void SetUpBones();
	
	void DrawPoints();
	
	void Lighting(float *lv, long Bone, long Flags, vec3_t Normal);
	
	void SetupLighting();
	
	void SetupModel(long BodyPart);
	
	void UploadTexture(tagMDLTexture *Texture, BYTE *Data, BYTE *Palette);
};

#endif