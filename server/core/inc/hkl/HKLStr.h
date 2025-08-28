////////////////////////////////////////////////////////////////////////////////
//
// HKLStr.h
//
// Copyright 2025 HKL
// All Rights Reserved.
//
// This software is the confidential and proprietary information of HKL
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the license
// agreement you entered into with HKL.
//
// Description: Header of HKLStr
//
// Revision History:
//   Date         Version         Name    Description
//   20250825     r1              -       Initial version
//
////////////////////////////////////////////////////////////////////////////////

#ifndef HKLSTR_H
#define HKLSTR_H

//#include "HKLType.h"
#include "hkl/HKLBlk.h"		//  class to solve the bug of CC
class HKLBlk;

//  define I18N char, string to support Unicode 
//  not yet map the functions related to char/wchar_t
#ifdef UNICODE
typedef wchar_t IChar;	
#define IText(x) L ## x
#else
typedef char IChar;
#define IText(x) x
#endif

enum CFTStrCodeset
{
	HKL_CODESET_ASCII 	= 0x00,
	HKL_CODESET_BIG5	= 0x81,
	HKL_CODESET_GB	 	= 0x82,
	HKL_CODESET_JIS		= 0x83,
	HKL_CODESET_SHIFT_JIS	= 0x84,
	HKL_CODESET_UNICODE	= 0x85,
	HKL_CODESET_ISO2022 = 0x86,
	HKL_CODESET_ISO8859_1	= 0x87,	
	HKL_CODESET_UTF_8	= 0x88,		
	HKL_CODESET_UNDEFINE = 0xff
};

const Int32 HKL_STRING_MAX_FMTSIZE = 1024;
const CFTStrCodeset DEFAULT_HKLSTRING_CODESET = HKL_CODESET_UTF_8;

using HKLStrAlloc = std::allocator<IChar>;

template <class E,
		class T = std::char_traits<E>,
		class A = std::allocator<E> >
class HKLStr : public std::basic_string< E, T, A >
{
public:
 	typedef typename std::basic_string<E, T, A>::size_type size_type;

	//* 
	//  Default Constructor of class HKLStr
	//  @return		None
	//  @param			
	//* 
	HKLStr();

	//* 
	//  Constructor of class HKLStr
	//  @return			
	//  @param		pcSrc - char pointer to the source
	//  @param		tCodeset - codeset of the string
	//  @param		oAllocator	- allocator of E
	//* 
	explicit HKLStr(const E* pcSrc, CFTStrCodeset tCodeset = DEFAULT_HKLSTRING_CODESET, const A& oAllocator = A());
	
	//* 
	//  Constructor of class HKLStr
	//  @return			
	//  @param		pcSrc 		- char pointer to the source
	//  @param		tLen		- Length of the input source
	//  @param		tCodeset 	- codeset of the string
	//  @param		oAllocator	- allocator of E
	//* 
	HKLStr(const E* pcSrc, size_type tLen, CFTStrCodeset tCodeset = DEFAULT_HKLSTRING_CODESET, const A& oAllocator = A());

	//* 
	//  Constructor of class HKLStr
	//  @return			
	//  @param		tCount		- no. of E to set
	//  @param		eSrc 		- E 
	//  @param		tCodeset 	- codeset of the string
	//  @param		oAllocator	- allocator of E
	//* 
	HKLStr(size_type tCount, const E eSrc, CFTStrCodeset tCodeset = DEFAULT_HKLSTRING_CODESET, const A& oAllocator = A());
	
	//* 
	//  Destructor of class HKLStr
	//  @return			
	//  @param			
	//* 
	virtual ~HKLStr();
	
	//* 
	//  Copy Constructor of class HKLStr
	//  @return			
	//  @param		sSrc - source to copy
	//* 
	HKLStr(const HKLStr<E, T, A>& sSrc);

	//* 
	//  Move Constructor of class HKLStr
	//  @return			
	//  @param		sSrc - source to move
	//* 
	HKLStr(HKLStr<E, T, A>&& sSrc) noexcept;

	//* 
	//  Copy Constructor of class basic_string
	//  @return			
	//  @param		sSrc - source to copy
	//* 
	HKLStr(const std::basic_string<E, T, A>& sSrc);

	//* 
	//  operator= 
	//  @return		reference of the string 
	//  @param		sSrc - source of type HKLStr to copy
	//* 
	HKLStr& operator=(const HKLStr<E, T, A>& sSrc);

	//* 
	//  move operator= 
	//  @return		reference of the string 
	//  @param		sSrc - source of type HKLStr to copy
	//* 
	HKLStr& operator=(HKLStr<E, T, A>&& sSrc) noexcept;

	//* 
	//  operator= 
	//  @return		reference of the string 
	//  @param		sSrc - source of type basic_string to copy
	//* 
	HKLStr& operator=(const std::basic_string<E, T, A>& sSrc);

	//* 
	//  operator= 
	//  @return		reference of the string 
	//  @param		peSrc - source of type 'const E type'
	//* 
	HKLStr& operator=(const E* peSrc);

	//* 
	//  operator= 
	//  @return		reference of the string 
	//  @param		eSrc - source of type 'const E'
	//* 
	HKLStr& operator=(const E& eSrc);

	//* 
	//  operator+=, not added if sSrc's Codeset is different from the HKLStr
	//  @return		reference of the string 
	//  @param		sSrc - source of type HKLStr to copy
	//* 
	HKLStr& operator+=(const HKLStr& sSrc);

	//* 
	//  operator+= 
	//  @return		reference of the string 
	//  @param		sSrc - source of type basic_string to copy
	//* 
	HKLStr& operator+=(const std::basic_string<E, T, A>& sSrc);

	//* 
	//  operator+= 
	//  @return		reference of the string 
	//  @param		peSrc - source of type 'const E type'
	//* 
	HKLStr& operator+=(const E* peSrc);

	//* 
	//  operator+= 
	//  @return		reference of the string 
	//  @param		eSrc - source of type 'const E'
	//* 
	HKLStr& operator+=(const E& eSrc);
	
	//* 
	//  Formats and stores a series of characters and values in the HKLStr
	//  @return		number of character formated
	//  @param		pcFormat - pointer to the format-control string
	//  @param		tArgList - argument list of data to be formatted
	//*
	
	Int32 FormatArgList(const E* pcFormat, va_list tArgList);	
	
	//* 
	//  Formats and stores a series of characters and values in the HKLStr
	//  @return		number of character formated
	//  @param		pcFormat - pointer to the format-control string
	//* 
	Int32 Format(const E* pcFormat, ...);
	
	//* 
	//  Formats and stores a series of characters and values in the HKLStr
	//  @return		a formatted HKLStr
	//  @param		pcFormat - pointer to the format-control string
	//* 
	static HKLStr FormatString(const E* pcFormat, ...);
	
	//* 
	//  Serialize the content to HKLBlk
	//  @return		none
	//  @param		oBlock - HKLBlk to serialize in
	//* 
	void operator>>(HKLBlk& oBlock) const;
	
	//* 
	//  Serialize the content from HKLBlk
	//  @return		none
	//  @param		oBlock - HKLBlk to serialize out
	//* 
	void operator<<(HKLBlk& oBlock);

	//* 
	//  Trim all the specified character in the left
	//  @return		none
	//  @param		none
	//* 
	void TrimLeft(E eChar = ' ');

	//* 
	//  Trim all the specified character in the right
	//  @return		none
	//  @param		none
	//* 
	void TrimRight(E eChar = ' ');

	//* 
	//  Trim all the specified character in the left and right
	//  @return		none
	//  @param		none
	//* 
	void Trim(E eChar = ' ');

	//* 
	//  Set the codeset of the string
	//  @return		none 
	//  @param		tCodeset - codeset to set
	//*
	inline void SetCodeset(CFTStrCodeset tCodeset) { m_tCodeset = tCodeset; };
	
	//* 
	//  Get the codeset of the string
	//  @return		the codeset fo the string
	//  @param		none
	//*
	inline CFTStrCodeset GetCodeset() const { return m_tCodeset; };

	//* 
	//  Set string object into novalue 
	//  @return		none
	//  @param		none
	//*
	inline void SetNoValue() { std::basic_string<E, T, A>::erase(); m_tCodeset = HKL_CODESET_UNDEFINE; };
	
	//* 
	//  Check if string object is novalue
	//  @return		none
	//  @param		none
	//*
	inline bool IsNoValue() const { return (m_tCodeset == HKL_CODESET_UNDEFINE); };
			
	//* 
	//  Check if the codeset is super-set of ASCII
	//  @return		none
	//  @param		none
	//*
	inline bool IsASCIISuperset() const
	{
		return ( (m_tCodeset == HKL_CODESET_ASCII)
					|| (m_tCodeset == HKL_CODESET_ISO8859_1)
					|| (m_tCodeset == HKL_CODESET_UTF_8)
					|| (m_tCodeset == HKL_CODESET_BIG5) ); 
	};

	//*
	// Provide a read-only reference to std::basic_string
	// @return		read-only reference to std::basic_string
	// @param		none
	//*
	inline std::basic_string_view<E, T> view() const noexcept
	{
		return std::basic_string_view<E, T>(this->c_str(), this->length());
	}

	//*
	// Provide a read-only reference to std::basic_string.substr() but not null-terminated
	// @return		read-only reference to std::basic_string.substr()
	// @param		none
	//*
	inline std::basic_string_view<E, T> substr_view(size_t pos = 0, size_t n = std::string::npos) const noexcept {
		if (pos > this->length()) return std::string_view();
		return std::basic_string_view<E, T>(this->data() + pos, std::min(n, this->length() - pos));
	}

protected:
		
	CFTStrCodeset m_tCodeset;	
};		

//  Default Constructor of class HKLStr
template <class E, class T,	class A >
HKLStr<E, T, A >::HKLStr()
	: m_tCodeset(DEFAULT_HKLSTRING_CODESET)	
{
}

//  Constructor of class HKLStr
template <class E, class T,	class A>
HKLStr<E, T, A>::HKLStr(const E* pcSrc, CFTStrCodeset tCodeset, const A& oAllocator)
	: std::basic_string<E, T, A>(pcSrc, oAllocator), m_tCodeset(tCodeset)
{
}

//  Constructor of class HKLStr with specified tLen
template <class E, class T,	class A>
HKLStr<E, T, A>::HKLStr(const E* pcSrc, size_type tLen, CFTStrCodeset tCodeset, const A& oAllocator)
	: std::basic_string<E, T, A>(pcSrc, tLen, oAllocator), m_tCodeset(tCodeset)
{
}

//  Constructor of class HKLStr with specified tCount number of eSrc
template <class E, class T,	class A>
HKLStr<E, T, A>::HKLStr(size_type tCount, const E eSrc, CFTStrCodeset tCodeset, const A& oAllocator)	
	: std::basic_string<E, T, A>(tCount, eSrc, oAllocator), m_tCodeset(tCodeset)
{
}

//  Destructor of class HKLStr
template <class E, class T,	class A>
HKLStr<E, T, A>::~HKLStr()
{
}

// For old STL, Buffer sharing under reference counting/copy-on-write STL
// To safeguard against unintended modifications, we force deep copy of strings
// but may incur performance overhead due to additional deep copies.

//  Copy Constructor of class HKLStr
template <class E, class T,	class A>
HKLStr<E, T, A>::HKLStr(const HKLStr<E, T, A>& sSrc)
	: std::basic_string<E, T, A>(sSrc), m_tCodeset(sSrc.m_tCodeset)
{
}

//  Move Constructor of class HKLStr
template <class E, class T,	class A>
HKLStr<E, T, A>::HKLStr(HKLStr<E, T, A>&& sSrc) noexcept
	: std::basic_string<E, T, A>(std::move(sSrc)), m_tCodeset(sSrc.m_tCodeset)
{
	sSrc.m_tCodeset = DEFAULT_HKLSTRING_CODESET; // Optional: reset source
}

//  Copy Constructor of class basic_string
template <class E, class T,	class A>
HKLStr<E, T, A>::HKLStr(const std::basic_string<E, T, A>& sSrc)
	: std::basic_string<E, T, A>(sSrc), m_tCodeset(DEFAULT_HKLSTRING_CODESET)	
{
}

//  Assignment operator= to assign source sSrc of type HKLStr
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator=(const HKLStr<E, T, A>& sSrc)
{
	if (this != &sSrc)
	{
		this->assign(sSrc);
		m_tCodeset = sSrc.m_tCodeset;
	}
	return *this;
}

//  Move Assignment operator= to assign source sSrc of type HKLStr
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator=(HKLStr<E, T, A>&& sSrc) noexcept
{
    if (this != &sSrc) {
        std::basic_string<E, T, A>::operator=(std::move(sSrc));
        m_tCodeset = sSrc.m_tCodeset;
        sSrc.m_tCodeset = DEFAULT_HKLSTRING_CODESET; // Optional: reset source
    }
    return *this;
}

//  Assignment operator= to assign source sSrc of class basic_string
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator=(const std::basic_string<E, T, A>& sSrc)
{
	std::basic_string<E, T, A>::operator=(sSrc);
	m_tCodeset = DEFAULT_HKLSTRING_CODESET;
	return *this;
}

//  Assignment operator= to assign source of type pointer to 'const E type'
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator=(const E* peSrc)
{
	std::basic_string<E, T, A>::operator=(peSrc);
	m_tCodeset = DEFAULT_HKLSTRING_CODESET;
	return *this;
}

//  Assignment operator= to assign source of type reference to 'const E type'
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator=(const E& eSrc)
{
	std::basic_string<E, T, A>::operator=(eSrc);
	m_tCodeset = DEFAULT_HKLSTRING_CODESET;
	return *this;
}

//////////////////////////////////////////////////////////////////////////////// 
// 
// 		Class specific operators for HKLStr
// 
//////////////////////////////////////////////////////////////////////////////// 

//  operator+= to append source sSrc of type HKLStr, not appended if codeset is not the same
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator+=(const HKLStr<E, T, A>& sSrc)
{
	if (m_tCodeset == sSrc.m_tCodeset)
	{
		// Append string of same codeset
	}
	else if ( (m_tCodeset == HKL_CODESET_ASCII) && sSrc.IsASCIISuperset() )
	{
		// Promote itself to appended codeset if itself is ASCII
		m_tCodeset = sSrc.m_tCodeset;
	}
	else if ( IsASCIISuperset() && (sSrc.m_tCodeset == HKL_CODESET_ASCII))
	{
		// Append ASCII string if itself is superset of ASCII
	}
	else
	{		
		// ignore append string if codeset is not the same
		return *this;
	}
	
	this->append(sSrc);
	return *this;
}

//  operator+= to append source sSrc of type basic_string
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator+=(const std::basic_string<E, T, A>& sSrc)
{
	std::basic_string<E, T, A>::operator+=(sSrc);
	return *this;
}

//  operator+= to append source sSrc of type pointer to 'const E type'
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator+=(const E* peSrc)
{
	std::basic_string<E, T, A>::operator+=(peSrc);
	return *this;
}

//  operator+= to append source sSrc of type reference to 'const E type'
template <class E, class T,	class A>
HKLStr<E, T, A>& HKLStr<E, T, A>::operator+=(const E& eSrc)
{
	std::basic_string<E, T, A>::operator+=(eSrc);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////// 
// 
// 		Class helper functions for HKLStr
// 
//////////////////////////////////////////////////////////////////////////////// 

//  Format argument list that takes a format string and a variable argument list and return number of characters formatted
template <class E, class T,	class A>
Int32 HKLStr<E, T, A>::FormatArgList(const E* pcFormat, va_list tArgList) 
{
	E sStrBuf[HKL_STRING_MAX_FMTSIZE+1];
	Int32 iCharCnt;
	
	#ifdef UNICODE
		iCharCnt = vsnwprintf(
			sStrBuf, HKL_STRING_MAX_FMTSIZE, pcFormat, tArgList);
	#else
		iCharCnt = vsnprintf(
			sStrBuf, HKL_STRING_MAX_FMTSIZE, pcFormat, tArgList);
	#endif
		
	std::basic_string<E, T, A>::erase();
	if (iCharCnt > 0)
		this->append(sStrBuf, static_cast<size_type>(iCharCnt));
	return iCharCnt;
}

//  Format the calling string with any number of arguments and return number of characters formatted
template <class E, class T,	class A>
Int32 HKLStr<E, T, A>::Format(const E* pcFormat, ...)
{
	va_list tArgList;
	va_start(tArgList, pcFormat);
	return FormatArgList(pcFormat, tArgList);	
}	

//  Static function that creates a new HKLStr object and format the string of any number of arguments and return the HKLStr object
template <class E, class T,	class A>
HKLStr<E, T, A> HKLStr<E, T, A>::FormatString(const E* pcFormat, ...)
{
	va_list tArgList;
	va_start(tArgList, pcFormat);
	HKLStr<E, T, A> sTemp;
	sTemp.FormatArgList(pcFormat, tArgList);
	return sTemp;
}

//  Serialize the content into HKLBlk (IN)
template <class E, class T,	class A>
void HKLStr<E, T, A>::operator>>(HKLBlk& oBlock) const
{
	oBlock << static_cast<Int32>(m_tCodeset);
	Int32 iSize = std::basic_string<E, T, A>::size();
	oBlock << iSize;
	oBlock.Add(std::basic_string<E, T, A>::data(), iSize);
}

//  Serialize the content from HKLBlk (OUT)
template <class E, class T,	class A>
void HKLStr<E, T, A>::operator<<(HKLBlk& oBlock)
{
	Int32 tmp;
	oBlock >> tmp;
	m_tCodeset = static_cast<CFTStrCodeset>(tmp);
	Int32 iSize;
	oBlock >> iSize;
	std::basic_string<E, T, A>::assign(reinterpret_cast<IChar*>(oBlock.GetDataBuffer()), iSize);
	oBlock.Cut(iSize);
}

//  Trim the left whitespace characters
template <class E, class T,	class A>
void HKLStr<E, T, A>::TrimLeft(E eChar)
{
	size_type tPos = std::basic_string<E, T, A>::find_first_not_of(eChar);
	
	if (tPos != 0 && tPos != std::basic_string<E, T, A>::npos)
		this->erase(0, tPos);
	else if(tPos == std::basic_string<E, T, A>::npos)
		this->clear();	// all character of the string are the specified character
}

//  Trim the right whitespace characters
template <class E, class T,	class A>
void HKLStr<E, T, A>::TrimRight(E eChar)
{
	size_type tPos = std::basic_string<E, T, A>::find_last_not_of(eChar);
	
	if (tPos != std::basic_string<E, T, A>::size() - 1 && tPos != std::basic_string<E, T, A>::npos)
		this->erase(tPos + 1);
	else if(tPos == std::basic_string<E, T, A>::npos)
		this->clear();	// all character of the string are the specified character
}

//  Trim the whitespace characters
template <class E, class T,	class A>
void HKLStr<E, T, A>::Trim(E eChar)
{
	TrimLeft(eChar);
	TrimRight(eChar);
}

//////////////////////////////////////////////////////////////////////////////// 
// 
// 		Non-class specific operators for HKLStr
// 
//////////////////////////////////////////////////////////////////////////////// 

//* 
//  operator==
//  @return		true - two strings match, otherwiae false
//  @param		sStr1, sStr2 - strings to compare
//* 
template <class E, class T,	class A>
bool operator==(const HKLStr<E, T, A>& sStr1, const HKLStr<E, T, A>& sStr2)
{
	return (sStr1.compare(sStr2) == 0)
			&& (
				(sStr1.GetCodeset() == sStr2.GetCodeset())
				|| ( (sStr1.GetCodeset() == HKL_CODESET_ASCII) && sStr2.IsASCIISuperset() )
				|| ( (sStr2.GetCodeset() == HKL_CODESET_ASCII) && sStr1.IsASCIISuperset() )
				);
}

//* 
//  operator!=
//  @return		true - two strings mismatch, otherwiae false
//  @param		sStr1, sStr2 - strings to compare
//* 
template <class E, class T,	class A>
bool operator!=(const HKLStr<E, T, A>& sStr1,
				const HKLStr<E, T, A>& sStr2)
{
	return !(sStr1 == sStr2);
}

//* 
//  operator<
//  @return		true - the intput str1 is less than str2, otherwiae false
//  @param		sStr1, sStr2 - strings to compare
//* 
template <class E, class T,	class A>
bool operator<(const HKLStr<E, T, A>& sStr1,
				const HKLStr<E, T, A>& sStr2)
{
	if (sStr1.GetCodeset() == sStr2.GetCodeset()
		|| ((sStr1.GetCodeset() == HKL_CODESET_ASCII) && sStr2.IsASCIISuperset())
		|| ((sStr2.GetCodeset() == HKL_CODESET_ASCII) && sStr1.IsASCIISuperset())
		)
	{
		return sStr1.compare(sStr2) < 0;
	}
	return (sStr1.compare(sStr2) < 0) ||
		   (sStr1.compare(sStr2) == 0 && sStr1.GetCodeset() < sStr2.GetCodeset());
}

//* 
//  operator>
//  @return		true - the input str1 is greater than this str2, otherwiae false
//  @param		sStr1, sStr2 - strings to compare
//* 
template <class E, class T,	class A>
bool operator>(const HKLStr<E, T, A>& sStr1,
				const HKLStr<E, T, A>& sStr2)
{
	if (sStr1.GetCodeset() == sStr2.GetCodeset()
		|| ((sStr1.GetCodeset() == HKL_CODESET_ASCII) && sStr2.IsASCIISuperset())
		|| ((sStr2.GetCodeset() == HKL_CODESET_ASCII) && sStr1.IsASCIISuperset())
		)
	{
		return sStr1.compare(sStr2) > 0;
	}
	return (sStr1.compare(sStr2) > 0) ||
		   (sStr1.compare(sStr2) == 0 && sStr1.GetCodeset() > sStr2.GetCodeset());
}

//* 
//  operator<=
//  @return		true - the intput string is less than or equal to this string, otherwiae false
//  @param		sStr1, sStr2 - strings to compare
//* 
template <class E, class T,	class A>
bool operator<=(const HKLStr<E, T, A>& sStr1,
				const HKLStr<E, T, A>& sStr2)
{
	return !(sStr1 > sStr2);
}

//* 
//  operator>=
//  @return		true - the intput is greater than or equal to this string, otherwiae false
//  @param		sStr1, sStr2 - strings to compare
//* 
template <class E, class T,	class A>
bool operator>=(const HKLStr<E, T, A>& sStr1,
				const HKLStr<E, T, A>& sStr2)
{
	return !(sStr1 < sStr2);
}

//* 
//  operator+, return concatenation of -> HKLStr + HKLStr
//  @return		the concatenated HKLStr
//  @param		sStr1, sStr2 - strings to add
//* 
template <class E, class T,	class A>
HKLStr<E, T, A> operator+(const HKLStr<E, T, A>& sStr1,
								const HKLStr<E, T, A>& sStr2)
{
	HKLStr<E, T, A> sRet(sStr1);
	sRet += sStr2;
	return sRet;
}

//* 
//  operator+, return concatenation of -> std::basic_string + HKLStr
//  @return		the concatenated HKLStr
//  @param		sStr1, sStr2 - strings to add
//* 
template <class E, class T,	class A>
HKLStr<E, T, A> operator+(const std::basic_string<E, T, A>& sStr1,
								const HKLStr<E, T, A>& sStr2)
{
	HKLStr<E, T, A> sRet(sStr1);
	sRet += sStr2;
	return sRet;
}

//* 
//  operator+, return concatenation of -> HKLStr + std::basic_string
//  @return		the concatenated HKLStr
//  @param		sStr1, sStr2 - strings to add
//* 
template <class E, class T, class A>
HKLStr<E, T, A> operator+(const HKLStr<E, T, A>& sStr1, 
								const std::basic_string<E, T, A>& sStr2)
{
	HKLStr<E, T, A> sRet(sStr1);
	HKLStr<E, T, A> sStr(sStr2);
	sRet += sStr;
	return sRet;
}

//* 
//  operator+, return concatenation of -> const char* + HKLStr
//  @return		the concatenated HKLStr
//  @param		peSrc - source of type 'const E type'
//  @param		sStr2 - strings to add
//* 
template <class E, class T,	class A>
HKLStr<E, T, A> operator+(const E* peStr,
								const HKLStr<E, T, A>& sStr2)
{
	HKLStr<E, T, A> sRet(peStr);
	sRet += sStr2;
	return sRet;
}

//* 
//  operator+, return concatenation of -> HKLStr + const char*
//  @return		the concatenated HKLStr
//  @param		sStr1 - strings to add
//  @param		peSrc - source of type 'const E type'
//* 
template <class E, class T, class A>
HKLStr<E, T, A> operator+(const HKLStr<E, T, A>& sStr1, 
							const E* peStr)
{
	HKLStr<E, T, A> sRet(sStr1);
	HKLStr<E, T, A> sStr2(peStr);
	sRet += sStr2;
	return sRet;
}

//* 
//  operator+, return concatenation of -> char + HKLStr
//  @return		the concatenated HKLStr
//  @param		eSrc - source of type 'const E'
//  @param		sStr2 - strings to add
//* 
template <class E, class T,	class A>
HKLStr<E, T, A> operator+(E eSrc,
								const HKLStr<E, T, A>& sStr2)
{
	HKLStr<E, T, A> sRet(1, eSrc);
	sRet += sStr2;
	return sRet;
}

//* 
//  operator+, return concatenation of -> HKLStr + char
//  @return		the concatenated HKLStr
//  @param		sStr1 - strings to add
//  @param		eSrc - source of type 'const E'
//* 
template <class E, class T, class A>
HKLStr<E, T, A> operator+(const HKLStr<E, T, A>& sStr1, 
							E eSrc)
{
	HKLStr<E, T, A> sRet(sStr1);
	HKLStr<E, T, A> sStr2(1, eSrc);
	sRet += sStr2;
	return sRet;
}

#endif	// HKLSTR_H