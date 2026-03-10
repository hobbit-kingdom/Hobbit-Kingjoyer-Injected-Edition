#ifndef __MERIDIAN_H__
#define __MERIDIAN_H__

typedef unsigned xbool;
typedef float f32;

typedef unsigned char u8;
typedef unsigned long long u64;

class bin_in;

struct vector3
{
	f32 X, Y, Z;
};

struct guid
{
	u64 Guid;
};

class obj_mgr
{
	public:
	guid CreateObject(const char *pObjectTypeName, guid GUID);
};

extern obj_mgr g_ObjMgr;

class object
{
	public:
	virtual ~object() = 0;
	virtual void OnInit() = 0;
	virtual void OnKill() = 0;
	virtual void __something1() = 0;
	virtual void OnAdvanceLogic(f32 DeltaTime) = 0;
	virtual void Move(vector3 &NewPos, xbool unk) = 0;
	virtual void MoveRel(vector3 &DeltaPos, xbool unk) = 0;
	virtual void __something2() = 0;
	virtual void __something3() = 0;
	virtual void __something4() = 0;
	virtual void __something5() = 0;
	virtual void __something6() = 0;
	virtual void __something7() = 0;
	virtual void __something8() = 0;
	virtual void __something9() = 0;
	virtual void __something10() = 0;
	virtual void __something11() = 0;
	virtual void __something12() = 0;
	virtual void __something13() = 0;
	virtual void __something14() = 0;
	virtual void __something15() = 0;
	virtual void __something16() = 0;
	virtual void OnImport(bin_in &BinIn) = 0;

	void SetObjSaveFlag(xbool flag);
};

class marker : public object
{
	public:
	void SetText(const char *pNewText);
};

class bin_in
{
	public:
	char data[8192];

	bin_in();
	~bin_in();
	xbool OpenFile(const char *pName);

	xbool ReadHeader();
	xbool ReadFields();
};

#endif
