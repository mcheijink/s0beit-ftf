#pragma once

typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;

class Blip
{
public:
	__int32 iID; //0x0000 
	__int8 iID2; //0x0004 
	char _0x0005[3];
	BYTE N000010FB; //0x0008 (80 = moves with player, some values will turn icon into map cursor and break it)
	char _0x0009[7];
	float x;
	float y;
	float z;
	char _0x001C[6];
	BYTE N00001156; //0x0022   (Focused? 0100 0000)
	char _0x0023[5];
	char* szMessage; //0x0028 If not null, contains the string of whatever the blip says when selected.
	char _0x0030[16];
	BYTE bIcon; //0x0040 ("center_blip", "North_blip, etc. 0,1,2,3,4..., 6 is player icon)
	char _0x0041[7];
	DWORD dwColor; //0x0048 (Sometimes works?)
	char _0x004C[4];
	float fScale; //0x0050 
	__int16 iRotation; //0x0054 Heading
	BYTE bInfoIDType; //0x0056 GET_BLIP_INFO_ID_TYPE
	BYTE bZIndex; //0x0057 
	BYTE bDisplay; //0x0058  Also Visibility 0010
	BYTE bAlpha; //0x0059
};//Size=0x005A

class BlipEntry
{
public:
	Blip* m_pBlip; //0x0000 

};//Size=0x0008

class BlipList
{
public:
	BlipEntry m_Blips[1500]; //0x0000 
	char _0x2EE0[56];

};//Size=0x2F18

#pragma pack(push, 1)
typedef struct
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;
} Vector3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	BYTE red;
	BYTE green;
	BYTE blue;
	BYTE alpha;
} color_t;
#pragma pack(pop)

enum WeaponTints
{
	WEAPONTINT_NORMAL,
	WEAPONTINT_GREEN,
	WEAPONTINT_GOLD,
	WEAPONTINT_PINK,
	WEAPONTINT_ARMY,
	WEAPONTINT_LSPD,
	WEAPONTINT_ORANGE,
	WEAPONTINT_PLATINUM
};