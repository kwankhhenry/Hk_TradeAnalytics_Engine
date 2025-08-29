////////////////////////////////////////////////////////////////////////////////
//
// HKLBlk.h
//
// Copyright 2025 HKL
// All Rights Reserved.
//
// This software is the confidential and proprietary information of HKL
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the license
// agreement you entered into with HKL.
//
// Description: Buffer management. Class HKLBlk is able to store and manage a dynamic buffer of data.
//				Data can be added, removed, and accessed in a flexible manner.
//				Accept char arrays, strings, and integers.
//
// Revision History:
//   Date         Version         Name    Description
//   20250825     r1              -       Initial version
//
////////////////////////////////////////////////////////////////////////////////

#ifndef HKLBLOCK_H
#define HKLBLOCK_H

//#include <string.h>
#include "HKLSimpleType.h"

class HKLBlk
{
public:
	enum
	{
		DEFAULT_GROWTHSIZE = 1024
	};

	//* 
	//  Default constructor
	//  @return		none
	//  @param		iGrowthSize	- growth size of the internal buffer
	//* 
	HKLBlk(Int32 iGrowthSize = DEFAULT_GROWTHSIZE);

	//* 
	//  Constructor
	//  @return		none
	//  @param		pBuf	- pointer to the buffer to copy
	//  @param		uLength	- lenght of the buffer
	//  @param		iGrowthSize - growth size of the buffer
	//* 
	HKLBlk(const void* pBuf, UInt32 uLength, Int32 iGrowthSize = DEFAULT_GROWTHSIZE);

	//* 
	//  Copy constructor
	//  @return		none
	//  @param		oBlock	- HKLBlk object to copy
	//* 
	HKLBlk(const HKLBlk& oBlock);

	//* 
	//  Destructor
	//  @return		none
	//  @param		none
	//* 
	~HKLBlk();

public:

	//* 
	//  Assignment operator
	//  @return		internal reference of HKLBlk
	//  @param		oBlock - HKLBlk
	//* 
	const HKLBlk& operator=(const HKLBlk& oBlock);

	//* 
	//  Get the data Buffer
	//  @return		const reference of buffer.
	//  @param			
	//* 
	const UInt8* GetDataBuffer() const;

	//* 
	//  Get the data Buffer
	//  @return		buffer reference
	//  @param			
	//* 
	UInt8* GetDataBuffer();
	
	//* 
	//  Get the data Size
	//  @return		Buffer Size
	//  @param			
	//* 
	UInt32 GetSize() const;

	//* 
	//  Get the raw buffer 
	//  @return		Buffer Size
	//  @param			
	//* 
	const UInt8* GetRawBuffer() const;

	//* 
	//  Get the raw buffer 
	//  @return		Buffer Size
	//  @param			
	//* 
	UInt8* GetRawBuffer();

	//* 
	//  Get the buffer Size
	//  @return		Buffer Size
	//  @param			
	//* 
	UInt32 GetBufferSize() const;
	
	//* 
	//  Attach buffer to the memory buffer, old data will be lost
	//  @return		None
	//  @param		pBuffer	- Buffer referece
	//  @param		uLength	- Buffer Size
	//  @param		bAutoDelete - Assigned to member variable
	//* 
	void AttachBuffer(void* pBuf, UInt32 uLength, bool bAutoDelete);

	//* 
	//  Detach the Buffer from the HKLBlk
	//  @return		the raw buffer pointer
	//  @param			
	//* 
	void* DetachBuffer();
		
	//* 
	//  return a buffer of specific size
	//  @return		the buffer pointer 
	//  @param		uDataSize	- Buffer Length.
	//* 
	void* MapView(UInt32 uDataSize);
	
	//* 
	//  Add and append buffer to current buffer.
	//  @return		boolean indicates if operation is success.
	//  @param		pBuffer	- Buffer
	//  @param		uLength	- Buffer Length.
	//* 
	bool Add(const void* pBuffer, UInt32 uLength);

	//* 
	//  Add and append buffer to current buffer.
	//  @return		boolean indicates if operation is success.
	//  @param		oBlock	- memory block
	//* 
	bool Add(const HKLBlk& oBlock);
	
	//* 
	//  Add and append a unsigned int value to the buffer
	//  @return		boolean indicates if operation is success.
	//  @param		uValue	- value to add
	//* 
	bool AddValue(UInt32 uValue);
	
	//* 
	//  Get and remove the data from the block
	//  @return		number of bytes pop
	//  @param		pBuffer		- buffer to store the data
	//  @param		uDataSize	- Size of data to get.
	//* 
	UInt32 Pop(void* pBuffer, UInt32 uDataSize);
	
	//* 
	//  Get and remove the data from the block
	//  @return		number of bytes pop
	//  @param		oBlock		- HKLBlk to store the data
	//  @param		uDataSize	- Size of data to get.
	//* 
	UInt32 Pop(HKLBlk& oBlock, UInt32 uDataSize);

	//* 
	//  Get a unsigned integer value and
	// 					remove the data from the block
	//  @return		boolean indicates if operation is success.
	//  @param		uValue	- store the value
	//* 
	bool PopValue(UInt32& uValue);
	
	//* 
	//  Cut the data from the beginning of data of the block
	//  @return		No. of data cut
	//  @param		uDataSize	- Size of data to cut
	//* 
	UInt32 Cut(UInt32 uDataSize);
	
	//* 
	//  Peek data from the block
	//  @return		Size of data got 
	//  @param		pBuffer		- Pointer to buffer
	//  @param		uDataSize	- Size of data to get.
	//* 
	UInt32 Peek(void* pBuffer, UInt32 uDataSize) const;
	
	//* 
	//  Peek data from the block
	//  @return		Size of data got 
	//  @param		oBlock		- HKLBlk to store the data
	//  @param		uDataSize	- Size of data to get.
	//* 
	UInt32 Peek(HKLBlk& oBlock, UInt32 uDataSize) const;
	
	//* 
	//  Peek a unsigned integer from the block
	//  @return		Successful or not
	//  @param		uValue		- Item to get
	//* 
	bool PeekValue(UInt32& uValue) const;
	
	//* 
	//  Set the Buffer size. If the original size is larger than
	// 					the size to be set, size of buffer will not be changed
	//  @return		None
	//  @param		uSize	- Size of buffer.
	//* 
	void SetSize(UInt32 uSize);
	
	//* 
	//  Destroy the raw buffer and all data are lost
	//  @return		none
	//  @param		none
	//* 
	void DestroyBuffer();
	
	//* 
	//  clear the data block, all data will lost,
	// 					buffer is not deleted
	//  @return		none
	//  @param		none
	//* 
	void Clear();
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(Int8 iValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(UInt8 uValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(Int16 iValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(UInt16 uValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(Int32 iValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(UInt32 uValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(Float32 fValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(Float64 fValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(bool bValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(Int64 iValue);
	
	//
	// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
	//
	void operator<<(UInt64 iValue);	
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(Int8& iValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(UInt8& uValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(Int16& iValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(UInt16& uValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(Int32& iValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(UInt32& uValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(Float32& fValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(Float64& fValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(bool& bValue);
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(Int64& iValue);	
	
	//
	// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
	//
	void operator>>(UInt64& iValue);

private:
	//
	// Calculate buffer size and initlialize internal buffer
	//
	void initBuffer(const UInt32 uLength);
	
protected:
	UInt8*	m_puBuffer;		//storage for the data

	UInt8* m_puDataStart;	//Start index of the data in the buffer
	UInt8* m_puDataEnd;		//End index of the data in the buffer

	UInt32	m_uDataSize;	//data size
	UInt32	m_uBufSize;		//buffer size
	UInt32  m_uGrowthSize;	//Growth size for each extending of the buffer
	
		
	bool 	m_bAutoDelete;	//the buffer need to be deleted
};

inline const UInt8* HKLBlk::GetDataBuffer() const
{
	    return m_puDataStart;
}

inline UInt8* HKLBlk::GetDataBuffer()
{
	    return m_puDataStart;
}

inline UInt32 HKLBlk::GetSize() const
{
	    return m_uDataSize;
}

inline const UInt8* HKLBlk::GetRawBuffer() const
{
	    return m_puBuffer;
}

inline UInt8* HKLBlk::GetRawBuffer()
{
	    return m_puBuffer;
}

inline UInt32 HKLBlk::GetBufferSize() const
{
	    return m_uBufSize;
}

#endif //HKLBLOCK_H
