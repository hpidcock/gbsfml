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

#ifndef __CREGISTER_H__
#define __CREGISTER_H__

template<typename Register, typename Class>
class CClassFactory
{
public:
	CClassFactory(const char *classname)
	{
		Register::Get().Register(classname, (void *(*)(void))FactoryFunction);
	};

	static void *FactoryFunction(void)
	{
		return new Class();
	};
private:
	CClassFactory(void);
	CClassFactory(const CClassFactory &other);
};

template<typename Register, typename BaseClass>
class CRegister
{
	friend Register;
public:
	void Register(const char *classname, void *(* factory)(void))
	{
		std::string name = classname;
		std::transform(name.begin(), name.end(), name.begin(), toupper);

		m_Factories[name] = factory;
	};

	BaseClass *Create(const char *classname)
	{
		std::string name = classname;
		std::transform(name.begin(), name.end(), name.begin(), toupper);

		void *(* factory)(void) = m_Factories[name];

		assert(factory != NULL);

		BaseClass *base = static_cast<BaseClass *>(factory());

		assert(base != NULL);

		return base;
	};

	std::vector<std::string> GetNames(void)
	{
		std::vector<std::string> ret;

		std::map<std::string, void *(*)(void)>::iterator end = m_Factories.end();
		for(std::map<std::string, void *(*)(void)>::iterator i = m_Factories.begin(); i != end; ++i)
		{
			ret.push_back((*i).first);
		}

		return ret;
	};

private:
	std::map<std::string, void *(*)(void)> m_Factories;
};

#endif // __CREGISTER_H__