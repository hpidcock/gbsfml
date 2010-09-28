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

#ifndef __CKEYVALUES_H__
#define __CKEYVALUES_H__

class CKeyValues
{
public:
	CKeyValues(void)
	{
	};
	
	CKeyValues(const CKeyValues &other)
	{
		m_KV = other.m_KV;
	};

	void SetValue(const char *key, float value)
	{
		char buffer[32] = {0};
		sprintf_s(buffer, "%f", value);
		m_KV[key] = buffer;
	};

	void SetValue(const char *key, int value)
	{
		char buffer[32] = {0};
		sprintf_s(buffer, "%d", value);
		m_KV[key] = buffer;
	};

	void SetValue(const char *key, std::string value)
	{
		m_KV[key] = value;
	};

	int GetInt(const char *key, int default_value)
	{
		std::map<std::string, std::string>::iterator itor = m_KV.find(key);
		if(itor != m_KV.end())
		{
			int val = 0;
			sscanf_s(m_KV[key].c_str(), "%d", &val);
			return val;
		}

		return default_value;
	};

	float GetFloat(const char *key, float default_value)
	{
		std::map<std::string, std::string>::iterator itor = m_KV.find(key);
		if(itor != m_KV.end())
		{
			float val = 0;
			sscanf_s(m_KV[key].c_str(), "%f", &val);
			return val;
		}

		return default_value;
	};

	std::string GetString(const char *key, std::string default_value)
	{
		std::map<std::string, std::string>::iterator itor = m_KV.find(key);
		if(itor != m_KV.end())
		{
			return m_KV[key];
		}

		return default_value;
	};

private:
	std::map<std::string, std::string> m_KV;
};

#endif // __CKEYVALUES_H__