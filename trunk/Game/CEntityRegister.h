//////////////////////////////////////////////////////////////////////////////////////////////////
//	Copyright (c) 2010 Harry Pidcock
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CENTITYREGISTER_H__
#define __CENTITYREGISTER_H__

#define MAX_ENTS 2048

#define RegisterEntity(Class)	\
	CClassFactory<CEntityRegister, Class> Factory##Class ( #Class );

class CBaseEntity;

class CEntityRegister : public CSingleton<CEntityRegister>, public CRegister<CEntityRegister, CBaseEntity>
{
public:
	void Init(void);
	void Cleanup(void);

	CBaseEntity *CreateFromClassname(const char *classname);
	void Destroy(CBaseEntity *entity, int index);
	bool IsValid(CBaseEntity *entity, int index, int uniqueIndex);

	void ThinkAll(void);
	void DrawAll(void);

private:
	int m_iUniqueIndex;
	CBaseEntity *m_pEnts[MAX_ENTS];
};

#endif // __CENTITYREGISTER_H__