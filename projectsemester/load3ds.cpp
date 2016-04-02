#include "groundwork.h"


class submodel
{
public:
	USHORT *indizes;
	int ianz;
	SimpleVertex *vertices;
	int vanz;
	submodel()
	{
		indizes = NULL;
		ianz = 0;
		vertices = NULL;
		vanz = 0;
	}
	~submodel()
	{
		int z;
		z = 0;
		//if (indizes)	delete[]indizes;
		//if (vertices)	delete[]vertices;
	}
};
bool Load3DS(char *filename, ID3D11Device* g_pd3dDevice, ID3D11Buffer **ppVertexBuffer, int *vertex_count)
{
	ID3D11Buffer *pVertexBuffer = NULL;
	bool firstinit = TRUE;
	int i; //Index variable
	FILE *l_file = fopen(filename, "rb"); //File pointer
	if (l_file == NULL) return FALSE; //Open the file

	vector<submodel> submodels;

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk


	char ready = 0;
	unsigned short l_face_flags; //Flag that stores some face information
	char str[1000];
	while (ftell(l_file) < filelength(fileno(l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread(&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n", l_chunk_id);
		fread(&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n", l_chunk_lenght);

		switch (l_chunk_id)
		{
		case 0x0002://version
		{
			int ver;
			fread(&ver, sizeof(int), 1, l_file); //Read the lenght of the chunk
			int z;
			z = 0;
		}
		break;
		case 0x3d3e://meshversion
		{
			int ver;
			fread(&ver, sizeof(int), 1, l_file); //Read the lenght of the chunk
			int z;
			z = 0;
		}
		break;
		case 0x0100://?????????????
		{
			int ver;
			fread(&ver, sizeof(int), 1, l_file); //Read the lenght of the chunk
			int z;
			z = 0;
		}
		break;
		//----------------- 1group -----------------
		// Description: bitmap
		// Chunk ID: a300
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0xa300:
		{
			fscanf(l_file, "%s", str);
		}
		break;
		//----------------- MAIN3DS -----------------
		// Description: Main chunk, contains all the other chunks
		// Chunk ID: 4d4d 
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0x4d4d:
		{
			int z = 0;
		}
		break;

		//----------------- EDIT3DS -----------------
		// Description: 3D Editor chunk, objects layout info 
		// Chunk ID: 3d3d (hex)
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
		case 0x4000:

		{
			submodel subm;
			submodels.push_back(subm);

		}
		ready++;
		i = 0;
		do
		{
			fread(&l_char, 1, 1, l_file);
			//p_object->name[i] = l_char;
			i++;
		} while (l_char != '\0' && i < 20);

		//name.settext(p_object->name);
		firstinit = FALSE;
		break;
		break;

		//--------------- OBJ_TRIMESH ---------------
		// Description: Triangular mesh, contains chunks for 3d mesh info
		// Chunk ID: 4100 (hex)
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0x4100:
		{
			int i = 0;
			i = 9;
		}
		break;

		//--------------- TRI_VERTEXL ---------------
		// Description: Vertices list
		// Chunk ID: 4110 (hex)
		// Chunk Lenght: 1 x unsigned short (number of vertices) 
		//             + 3 x float (vertex coordinates) x (number of vertices)
		//             + sub chunks
		//-------------------------------------------
		case 0x4110:
		{

			int elem_no = submodels.size() - 1;


			fread(&l_qty, sizeof(unsigned short), 1, l_file);
			submodels[elem_no].vanz = l_qty;
			submodels[elem_no].vertices = new SimpleVertex[submodels[elem_no].vanz];
			for (int ii = 0; ii < submodels[elem_no].vanz; ii++)
			{
				fread(&submodels[elem_no].vertices[ii].Pos.x, sizeof(float), 1, l_file);
				fread(&submodels[elem_no].vertices[ii].Pos.y, sizeof(float), 1, l_file);
				fread(&submodels[elem_no].vertices[ii].Pos.z, sizeof(float), 1, l_file);
			}
		}
		break;
		case 0x4160://local koordinate system
		{
			char ver[100];
			fread(&ver, sizeof(BYTE) * 48, 1, l_file); //Read the lenght of the chunk
			int z;
			z = 0;
		}
		break;
		//--------------- TRI_FACEL1 ----------------
		// Description: Polygons (faces) list
		// Chunk ID: 4120 (hex)
		// Chunk Lenght: 1 x unsigned short (number of polygons) 
		//             + 3 x unsigned short (polygon points) x (number of polygons)
		//             + sub chunks
		//-------------------------------------------
		case 0x4120:
		{
			int elem_no = submodels.size() - 1;




			fread(&l_qty, sizeof(unsigned short), 1, l_file);
			submodels[elem_no].ianz = l_qty * 3;
			submodels[elem_no].indizes = new USHORT[submodels[elem_no].ianz];
			for (int ii = 0; ii < l_qty; ii++)
			{
				fread(&submodels[elem_no].indizes[ii * 3], sizeof(USHORT), 1, l_file);
				fread(&submodels[elem_no].indizes[ii * 3 + 1], sizeof(USHORT), 1, l_file);
				fread(&submodels[elem_no].indizes[ii * 3 + 2], sizeof(USHORT), 1, l_file);
				fread(&l_face_flags, sizeof(USHORT), 1, l_file);
			}
		}
		break;

		//------------- TRI_MAPPINGCOORS ------------
		// Description: Vertices list
		// Chunk ID: 4140 (hex)
		// Chunk Lenght: 1 x unsigned short (number of mapping points) 
		//             + 2 x float (mapping coordinates) x (number of mapping points)
		//             + sub chunks
		//-------------------------------------------
		case 0x4140:
		{
			int elem_no = submodels.size() - 1;

			fread(&l_qty, sizeof(unsigned short), 1, l_file);
			for (int ii = 0; ii < submodels[elem_no].vanz; ii++)
			{
				fread(&submodels[elem_no].vertices[ii].Tex.x, sizeof(float), 1, l_file);
				fread(&submodels[elem_no].vertices[ii].Tex.y, sizeof(float), 1, l_file);
			}
		}
		break;

		//----------- Skip unknow chunks ------------
		//We need to skip all the chunks that currently we don't use
		//We use the chunk lenght information to set the file pointer
		//to the same level next chunk
		//-------------------------------------------
		default:
			fseek(l_file, l_chunk_lenght - 6, SEEK_CUR);
		}


	}

	int vertex_anz = 0;
	for (int ii = 0; ii < submodels.size(); ii++)
		vertex_anz += submodels[ii].ianz;

	SimpleVertex *noIndexVer = new SimpleVertex[vertex_anz];

	int vv = 0;
	for (int uu = 0; uu < submodels.size(); uu++)
		for (int ii = 0; ii< submodels[uu].ianz; ii++)//weil 1.dreieck nix data.... anz--;oder eben ii=1 und net 0
			noIndexVer[vv++] = submodels[uu].vertices[submodels[uu].indizes[ii]];
	*vertex_count = vertex_anz;

	//perform flat light:
	for (int ii = 0; ii < vertex_anz; ii += 3)
	{
		XMFLOAT3 a, b, c;
		a = noIndexVer[ii + 1].Pos - noIndexVer[ii + 0].Pos;
		b = noIndexVer[ii + 2].Pos - noIndexVer[ii + 0].Pos;
		c = Vec3Cross(a, b);
		c = Vec3Normalize(c);

		noIndexVer[ii + 0].Norm = c;
		noIndexVer[ii + 1].Norm = c;
		noIndexVer[ii + 2].Norm = c;
	}
	//initialize d3dx verexbuff:
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertex_anz;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = noIndexVer;
	HRESULT hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &pVertexBuffer);
	if (FAILED(hr))
		return FALSE;
	*ppVertexBuffer = pVertexBuffer;
	return TRUE;
}
//***************************************************************
float Vec3Length(const XMFLOAT3 &v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
float Vec3Dot(XMFLOAT3 a, XMFLOAT3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

XMFLOAT3 Vec3Cross(XMFLOAT3 a, XMFLOAT3 b)
{
	XMFLOAT3 c = XMFLOAT3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	return c;
}

XMFLOAT3 Vec3Normalize(const  XMFLOAT3 &a)
{
	XMFLOAT3 c = a;
	float len = Vec3Length(a);
	c.x /= len;
	c.y /= len;
	c.z /= len;
	return c;
}

XMFLOAT3 operator+(const XMFLOAT3 lhs, const XMFLOAT3 rhs)
{
	XMFLOAT3 c = XMFLOAT3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	return c;
}
XMFLOAT3 operator-(const XMFLOAT3 lhs, const XMFLOAT3 rhs)
{
	XMFLOAT3 c = XMFLOAT3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	return c;
}