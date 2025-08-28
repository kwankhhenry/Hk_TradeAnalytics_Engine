////////////////////////////////////////////////////////////////////////////////
//
// HKLType.h
//
// Copyright 2025 MarketPrizm
// All Rights Reserved.
//
// This software is the confidential and proprietary information of HKL
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the license
// agreement you entered into with HKL.
//
// Description: Header of foundation class library basic data type
//
// Revision History:
//   Date         Version         Name    Description
//   20250825     r1              -       Initial version
//
////////////////////////////////////////////////////////////////////////////////

#ifndef HKLTYPE_H
#define HKLTYPE_H

#include "HKLSimpleType.h"		//mpl simple data type
#include "hkl/HKLStr.h"		//mpl string type

//  Move IString definition to HKLType.h.  Need to wait after HKLStr is fully defined
using IString = HKLStr<IChar, std::char_traits< IChar >, HKLStrAlloc >;

//#include "MPLLimit.h"		//mpl data type limitation and no-value

// it is strange that gcc don't provide hash for String and it is essential
//	for HashMap operation
/*#ifdef USE_HASHMAP
	#if defined(__GLIBCXX__) || defined(__GNUC__)
		#ifndef HASH_ISTRING_COMPLEMENT
		#define HASH_ISTRING_COMPLEMENT

        namespace std
        {
        	inline size_t hash_char_array(const char* __s)
            {
            	unsigned long __h = 0;
                for ( ; *__s; ++__s)
                	__h = 5 * __h + static_cast<unsigned long>(*__s);
                return size_t(__h);
            }
                
            template<> struct hash< IString >
            {
                size_t operator()(IString __s) const
                {   return hash_char_array(__s.c_str()); }
            };
                
            template<> struct hash<const IString>
            {
                size_t operator()(IString __s) const
                {   return hash_char_array(__s.c_str()); }
            };
        }


		#endif //HASH_ISTRING_COMPLEMENT
	//#else
	// solaris-specific
	#endif
#endif	// USE_HASHMAP

template<class T> class MPLDecimalNum;
		
typedef MPLDecimalNum<Int32> CFTDecNum32;
typedef MPLDecimalNum<Int64> CFTDecNum64;
*/

#endif  //HKLTYPE_H