////////////////////////////////////////////////////////////////////////////////
//
// HKLBlk.cpp
// 
// Copyright 2025 HKL
// All Rights Reserved.
//
// This software is the confidential and proprietary information of HKL
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the license
// agreement you entered into with HKL.
// 
// Description:  Implementation of the HKLBlk
// 
// Revision History:
//   Date         Version         Name    Description
//   20250825     r1              -       Initial version
//
////////////////////////////////////////////////////////////////////////////////

#include "hkl/HKLBlk.h"

//------------------------------------------------------------------------------
//	Public interface of HKLBlk Constructor & Destructor

// Default HKLBlk constructor
HKLBlk::HKLBlk(Int32 iGrowthSize)
{
    m_puBuffer = NULL;
	m_uDataSize = 0;
	
	m_puDataStart = NULL;
	m_puDataEnd = NULL;
	m_uBufSize = 0;
	
	m_bAutoDelete = true;
	m_uGrowthSize = iGrowthSize;
}

// HKLBlk constructor
// Initialize with a given buffer
HKLBlk::HKLBlk(const void* pBuf, UInt32 uLength, Int32 iGrowthSize)
{
   	m_puBuffer = NULL;
	m_uDataSize = 0;
	
	m_puDataStart = NULL;
	m_puDataEnd = NULL;
	m_uBufSize = 0;
	
	m_bAutoDelete = true;
	m_uGrowthSize = iGrowthSize;
	
	Add(pBuf, uLength);
}

// HKLBlk copy constructor
HKLBlk::HKLBlk(const HKLBlk& oBlock)
{
   	m_puBuffer = NULL;
	m_uDataSize = 0;
	
	m_puDataStart = NULL;
	m_puDataEnd = NULL;
	m_uBufSize = 0;
	
	m_bAutoDelete = true;
	m_uGrowthSize = oBlock.m_uGrowthSize;
	Add(oBlock);
}
		
// HKLBlk destructor		
HKLBlk::~HKLBlk()
{
    if (m_puBuffer != 0 && m_bAutoDelete)
	    delete [] m_puBuffer;
	
 	m_puBuffer = NULL;
}

//------------------------------------------------------------------------------
// Public interface to manipulate buffer in HKLBlk


// Attach the given buffer to HKLBlk buffer.  
void HKLBlk::AttachBuffer(void* pBuffer, UInt32 uLength, bool bAutoDelete)
{
	// Delete old data before attaching new buffer if bAutoDelete is true
	if (m_puBuffer != NULL && m_bAutoDelete)
	{
		delete [] m_puBuffer;		
	}
	
	// Attach the given buffer to HKLBlk buffer
	m_puBuffer = m_puDataStart = (UInt8*)pBuffer;
	m_uBufSize = m_uDataSize = uLength;
    m_puDataEnd = m_puDataStart + m_uDataSize;

	m_bAutoDelete = bAutoDelete;
}

// Detach current buffer from HKLBlk
void* HKLBlk::DetachBuffer()
{
	void* pBuffer;
	pBuffer = m_bAutoDelete ? m_puBuffer : NULL;	//if it is not autodelete, return NULL
	m_puBuffer = NULL;
	m_puDataStart = NULL;
	m_puDataEnd = NULL;
	m_uBufSize = 0;
	m_uDataSize = 0;	
	m_bAutoDelete = true;

	return pBuffer;
}

// Get buffer pointer from the HKLBlk with specified size
// The buffer will be created/reallocated within the HKLBlk depending on the specified size and current buffer size
void* HKLBlk::MapView(UInt32 uDataSize)
{
	// Return immediately if the given size is 0
	if (uDataSize == 0)
	{
		return NULL;
	}
	
	void* pBufferRet = NULL;
	
	// Case 1: No buffer is available	
	if (m_puBuffer == NULL)
	{
		// Calculate buffer size and initialize the buffer				
		initBuffer(uDataSize);
		
		// Update buffer related info
		m_uDataSize = uDataSize;
		m_puDataStart = m_puBuffer;
		m_puDataEnd = m_puBuffer + m_uDataSize;
		
		// Update return buffer pointer
		pBufferRet = m_puBuffer;
	}
	else 
	{
		// Space left for new data
		UInt32 uSpaceLeft = m_puBuffer + m_uBufSize - m_puDataEnd;
		
		// Case 2: Buffer available and there are enough space left for new data 
		if (uSpaceLeft >= uDataSize)
		{				
			// Update return buffer pointer
			pBufferRet = m_puDataEnd;
			
			// update buffer related info		
			m_uDataSize += uDataSize;
			m_puDataEnd += uDataSize;
		}
		else
		{
			// Case 3a: Buffer available and there are not enough space left for new data
			// 			Entire buffer is enough for old AND new data
			if (m_uBufSize >= m_uDataSize + uDataSize)
			{
				// whole buffer enough for old + new data ->
				// move the data to the begining of buffer
				// p.s. no need to move if realloc() is used
				// and new and delete are replaced by malloc() and free()
				
			    if (m_uDataSize > 0 && m_puBuffer != m_puDataStart)
				{
					memmove(m_puBuffer, m_puDataStart, m_uDataSize);
				}
								
				// Update return buffer pointer
				pBufferRet = m_puBuffer + m_uDataSize;
				
				// update buffer related info		
				m_uDataSize += uDataSize;
				m_puDataStart = m_puBuffer;
				m_puDataEnd = m_puBuffer + m_uDataSize;
			}
			else
			{
				// Case 3b: Buffer available and there are not enough space left for new data
				// 			Entire buffer is not enough for old AND new data
				
				// Reallocate memory
				UInt32 uNoOfBuffer = (m_uDataSize + uDataSize + m_uGrowthSize - 1) / m_uGrowthSize;
				UInt8* pBuf = new UInt8[m_uGrowthSize * uNoOfBuffer];

				// Copy old data to newly allocated memory
				if (m_uDataSize > 0)
				{
					memcpy(pBuf, m_puDataStart, m_uDataSize);
				}
				
				// Update return buffer pointer
				pBufferRet = pBuf + m_uDataSize;

				// update buffer related info		
				m_uBufSize = m_uGrowthSize * uNoOfBuffer;
				
				// Delete previously created buffer if m_bAutiDelete is true
				if (m_bAutoDelete)
				{
					delete [] m_puBuffer;
				}

				// update buffer related info		
				m_puBuffer = pBuf;
				
				m_uDataSize += uDataSize;
				m_puDataStart = m_puBuffer;
				m_puDataEnd = m_puBuffer + m_uDataSize;
			}
		}
	}

	return pBufferRet;	
}

// Set the Buffer size
// If the original size is larger than the size to be set, size of buffer will not be changed
void HKLBlk::SetSize(UInt32 uSize)
{
	// Return immediately if buffer size in HKLBlk is greater than the specified size
	// as the buffer has at least 'Size' bytes
	if (m_uBufSize >= uSize)
	{
		return;
	}
	
	// Allocate new buffer with the specified size
	UInt8* pBuf = new UInt8[uSize];
	
	// Copy the old data to the newly allocated buffer
	if (m_uDataSize > 0)
	{
		memcpy(pBuf, m_puDataStart, m_uDataSize);
	}
	
	// Clean the old buffer if it is not empty and m_bAutoDelete is true
	if (m_puBuffer != NULL && m_bAutoDelete)
	{
		delete [] m_puBuffer;
	}
	
	// Update buffer related info
	m_puDataStart = m_puBuffer = pBuf;
	m_puDataEnd = m_puDataStart + m_uDataSize;
	
	m_uBufSize = uSize;
}


// Calculate buffer size and initlialize internal buffer
void HKLBlk::initBuffer(const UInt32 uLength)
{
	// Calculate buffer size and initialize the buffer		
	// Get floor of no. of block ulength need, then add one additinal block	
	UInt32 uNoOfBuffer = (uLength + m_uGrowthSize - 1) / m_uGrowthSize;		
	m_uBufSize = uNoOfBuffer * m_uGrowthSize;
	m_puBuffer = new UInt8[m_uBufSize];
}


//------------------------------------------------------------------------------
// Public interface to cut/destroy buffer in HKLBlk

//  Cut the data from the beginning of the data block	
UInt32 HKLBlk::Cut(UInt32 uDataSize)
{
	// Return immediately if the specified size is 0
	if (uDataSize == 0)
	{
		return 0;		//no need to do anything
	}

	// If the cut size is greater than actual buffer size, 
	// the actual buffer size will be used
	if (uDataSize > m_uDataSize)
	{
		uDataSize = m_uDataSize;
	}
	
	// Update buffer related info
	m_uDataSize -= uDataSize;		// reduce buffer size by the specified size
			
	if (m_uDataSize == 0)
	{		
		// No data left after buffer size updated
		m_puDataStart = m_puDataEnd = m_puBuffer;
	}
	else
	{
		// move buffer start pointer forward by the specified size
		m_puDataStart += uDataSize;
	}
	
	// return the cut size
	return uDataSize;	
}

// Destroy the raw buffer and all data are lost
// The raw buffer data might be deleted here
void HKLBlk::DestroyBuffer()
{
	// Clean the buffer if it is not empty and m_bAutoDelete is true
	if (m_puBuffer != NULL && m_bAutoDelete)
	{
		delete [] m_puBuffer;
	}
	
	// Reset buffer related info
	m_puDataStart = m_puDataEnd = m_puBuffer = NULL;
	m_uBufSize = m_uDataSize = 0;
	m_bAutoDelete = true;
}

// Clear the data block, all data will lost
// The raw buffer data will not be deleted here
void HKLBlk::Clear()
{
	m_puDataStart = m_puDataEnd = m_puBuffer;
	m_uDataSize = 0;
}

//------------------------------------------------------------------------------
// Public interface to add buffer/value to HKLBlk

// Add and append buffer to current buffer in the HKLBlk
// The buffer will be created/reallocated within the HKLBlk depending on the specified size and current buffer size
bool HKLBlk::Add( const void* pBuffer, UInt32 uLength )
{
	// Return immediately if the given size is 0
	if (uLength == 0)
	{
		return false;	//no need to do anything
	}
		
	// Case 1: No buffer is available	
	if (m_puBuffer == NULL)
	{ 		
		// Calculate buffer size and initialize the buffer	
		initBuffer(uLength);
		
		// Copy the given buffer to the newly created buffer
		memcpy(m_puBuffer, pBuffer, uLength);
		
		// Update buffer related info
		m_uDataSize = uLength;
		m_puDataStart = m_puBuffer;
		m_puDataEnd = m_puBuffer + m_uDataSize;
	}
	else 
	{
		// Space left for new data
		UInt32 uSpaceLeft = m_puBuffer + m_uBufSize - m_puDataEnd;
		
		// Case 2: Buffer available and there are enough space left for new buffer 
		if (uSpaceLeft >= uLength)
		{
			// space left enough, just copy the data
			memcpy(m_puDataEnd, pBuffer, uLength);
			
			// Update buffer related info
			m_uDataSize += uLength;
			m_puDataEnd += uLength;
		}
		else
		{			
			// Case 3a: Buffer available and there are not enough space left for new buffer
			// 			Entire buffer is enough for old AND new data
			if (m_uBufSize >= m_uDataSize + uLength)
			{
				// whole buffer enough for old + new data ->
				// move the data to the begining of buffer
				// p.s. no need to move if realloc() is used
				// and new and delete are replaced by malloc() and free()
				
			    if (m_uDataSize > 0 && m_puBuffer != m_puDataStart)
				{
				    memmove(m_puBuffer, m_puDataStart, m_uDataSize);
				}
				
				// Append the new buffer to end of current buffer
				memcpy(m_puBuffer + m_uDataSize, pBuffer, uLength);
				
				// Update buffer related info
				m_uDataSize += uLength;
				m_puDataStart = m_puBuffer;
				m_puDataEnd = m_puBuffer + m_uDataSize;
			}
			else
			{
				// Case 3b: Buffer available and there are not enough space left for new data
				// 			Entire buffer is not enough for old AND new data				
				
				// Reallocate memory
				UInt32 uNoOfBuffer = (m_uDataSize + uLength + m_uGrowthSize - 1) / m_uGrowthSize;
				UInt8* pBuf = new UInt8[m_uGrowthSize * uNoOfBuffer];

				// Copy old data to newly allocated memory
				if (m_uDataSize > 0)
				{
				    memcpy(pBuf, m_puDataStart, m_uDataSize);
				}
				
				// Append the new buffer to end of current buffer
				memcpy(pBuf + m_uDataSize, pBuffer, uLength);

				// update buffer related info	
				m_uBufSize = m_uGrowthSize * uNoOfBuffer;
				
				// Delete previously created buffer if m_bAutiDelete is true
				if (m_bAutoDelete)
				{
					delete [] m_puBuffer;
				}
				
				// update buffer related info		
				m_puBuffer = pBuf;
				
				m_uDataSize += uLength;
				m_puDataStart = m_puBuffer;
				m_puDataEnd = m_puBuffer + m_uDataSize;
			}
		}
	}
	return true;
}
	
// Add and append HKLBlk to the HKLBlk
// Internal buffer from the given HKLBlk retreived and passed to HKLBlk::Add(const void* pBuffer, UInt32 uLength)
bool HKLBlk::Add( const HKLBlk& oBlock)
{
	return HKLBlk::Add(oBlock.GetDataBuffer(), oBlock.GetSize());
}

// Add and append a unsigned int value to the buffer
bool HKLBlk::AddValue( UInt32 uValue)
{
	// Retrieve buffer pointer from HKLBlk
	void* pBuf = MapView(sizeof(uValue));
	
	// Return immediately if buffer pointer is not available
	if (pBuf == NULL)
	{
		return false;
	}
	
	// Copy the data to the buffer pointer
	memcpy(pBuf, &uValue, sizeof(uValue));
	return true;
}

//------------------------------------------------------------------------------
// Public interface to pop buffer/value from HKLBlk

//  Get and remove the data from the block
UInt32 HKLBlk::Pop( void* pBuffer, UInt32 uDataSize)
{
	// Return immediately if the specified size is 0
	if (uDataSize == 0)
	{
		return 0;		//no need to do anything
	}
	
	// If the retrieval size is greater than actual buffer size, 
	// the actual buffer size will be used
	if (uDataSize > m_uDataSize)
	{
		uDataSize = m_uDataSize;
	}
	
	// Copy buffer within HKLBlk to the given buffer pointer using the specified size
	memcpy(pBuffer, m_puDataStart, uDataSize);
		
	// Cut the popped data
	Cut(uDataSize);
	
	// Return popped data size
	return uDataSize;
}

//  Get and remove the data from the block
UInt32 HKLBlk::Pop(HKLBlk& oBlock, UInt32 uDataSize)
{
	// Return immediately if the specified size is 0
	if (uDataSize == 0)
	{
		return 0;		//no need to do anything
	}
	
	// If the retrieval size is greater than actual buffer size, 
	// the actual buffer size will be used
	if (uDataSize > m_uDataSize)
	{
		uDataSize = m_uDataSize;
	}
	
	// Copy buffer within HKLBlk to the given HKLBlk object using the specified size
	oBlock.Add(m_puDataStart, uDataSize);
	
	// Cut the popped data
	Cut(uDataSize);
	
	// Return popped data size	
	return uDataSize;
}

//  Get a unsigned integer value and remove the data from the block
bool HKLBlk::PopValue(UInt32& uValue)
{
	// Get size of UInt32
	const UInt32 uDataSize = sizeof(UInt32);
	
	// Return immediately if retrieval size is greater than data size
	if (uDataSize > m_uDataSize)
	{
		return false;
	}
	
	// Copy the value from the buffer in HKLBlk
	memcpy(&uValue, m_puDataStart, uDataSize);
	
	// Cut the popped data
	Cut(uDataSize);
	
	return true;
}

//------------------------------------------------------------------------------
// Public interface to peek buffer/value from HKLBlk

// Peek the data from HKLBlk
UInt32 HKLBlk::Peek( void* pBuffer, UInt32 uDataSize) const
{
	// Return immediately if the specified size is 0
	if (uDataSize == 0)
	{
		return 0;		//no need to do anything
	}

	// If the retrieval size is greater than actual buffer size, 
	// the actual buffer size will be used
	if (uDataSize > m_uDataSize)
	{
		uDataSize = m_uDataSize;
	}
	
	// Copy the data to the given buffer
	memcpy(pBuffer, m_puDataStart, uDataSize);
	
	// Return retrieval size
	return uDataSize;
}

// Peek the data from HKLBlk
UInt32 HKLBlk::Peek( HKLBlk& oBlock, UInt32 uDataSize) const
{
	// Return immediately if the specified size is 0
	if (uDataSize == 0)
	{
		return 0;		//no need to do anything
	}
	
	// If the retrieval size is greater than actual buffer size, 
	// the actual buffer size will be used
	if (uDataSize > m_uDataSize)
	{
		uDataSize = m_uDataSize;
	}
	
	// Copy the data to the given buffer
	oBlock.Add(m_puDataStart, uDataSize);
	
	// Return retrieval size
	return uDataSize;
}

// Peek an unsigned integer from the block
bool HKLBlk::PeekValue( UInt32& uValue) const
{
	// Get size of UInt32
	const UInt32 uDataSize = sizeof(UInt32);

	// Return immediately if retrieval size is greater than data size
	if (uDataSize > m_uDataSize)
	{
		return false;
	}
	
	// Copy the data to the given UInt32
	memcpy(&uValue, m_puDataStart, uDataSize);
	
	return true;
}

//------------------------------------------------------------------------------
// Operator overload in HKLBlk

// HKLBlk assignment operator
const HKLBlk& HKLBlk::operator=(const HKLBlk& oBlock)
{
	if (this != &oBlock)
	{
		Clear();
		Add(oBlock);
	}
	return *this;
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(Int8 iValue)
{
	Add(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(UInt8 uValue)
{
	Add(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(Int16 iValue)
{
	Add(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(UInt16 uValue)
{
	Add(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(Int32 iValue)
{
	Add(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(UInt32 uValue)
{
	Add(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(Int64 iValue)
{
	Add(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(UInt64 uValue)
{
	Add(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(Float32 fValue)
{
	Add(&fValue, sizeof(fValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(Float64 fValue)
{
	Add(&fValue, sizeof(fValue));
}

// HKLBlk overloads bitwise left shit as add value to buffer within HKLBlk
void HKLBlk::operator<<(bool bValue)
{
	Add(&bValue, sizeof(bValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(Int8& iValue)
{
	Pop(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(UInt8& uValue)
{
	Pop(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(Int16& iValue)
{
	Pop(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(UInt16& uValue)
{
	Pop(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(Int32& iValue)
{
	Pop(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(UInt32& uValue)
{
	Pop(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(Int64& iValue)
{
	Pop(&iValue, sizeof(iValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(UInt64& uValue)
{
	Pop(&uValue, sizeof(uValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(Float32& fValue)
{
	Pop(&fValue, sizeof(fValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(Float64& fValue)
{
	Pop(&fValue, sizeof(fValue));
}

// HKLBlk overloads bitwise right shit as pop value from buffer within HKLBlk
void HKLBlk::operator>>(bool& bValue)
{
	Pop(&bValue, sizeof(bValue));
}
