/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"
#include "stdio.h"

bool RingBuffer_Init(RingBuffer* ringBuffer, char* dataBuffer, size_t dataBufferSize)
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);

	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
	    
		ringBuffer->buffer = dataBuffer;
		ringBuffer->length = dataBufferSize;
		ringBuffer->head = 0;
		ringBuffer->tail = 0;
		ringBuffer->full = 0;
		ringBuffer->dod = 0;
		ringBuffer->odej = 0;

		return true;
	}else{
		return false;
	}
}

bool RingBuffer_Clear(RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		ringBuffer->tail = ringBuffer->head;
		ringBuffer->dod = 0;
		ringBuffer->odej = 0;
		ringBuffer->full = 0;
		return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer->head == ringBuffer->tail && ringBuffer->full == 0)
	    return true;
	else
	    return false;
	
}


size_t RingBuffer_GetLen(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) 
		return ((ringBuffer->dod) - (ringBuffer->odej)) ;
    else    
	    return false;
}


size_t RingBuffer_GetCapacity(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) 
		return (ringBuffer->length);
	else
		return 0;
}


bool RingBuffer_PutChar(RingBuffer* ringBuffer, char c)
{
	assert(ringBuffer);

	if (ringBuffer) {

		 if (ringBuffer->full == 1)
			return false;
		else
		{

			ringBuffer->buffer[ringBuffer->head] = c;

			ringBuffer->head = ((ringBuffer->head) + 1) % (ringBuffer->length);

			if ((ringBuffer->head == ringBuffer->tail))
            	ringBuffer->full = 1;
			
		ringBuffer->dod++;
		return true;

		}
	}
	return false;
}


bool RingBuffer_GetChar(RingBuffer* ringBuffer, char* c)
{

	assert(ringBuffer);
	assert(c);

	if ((ringBuffer) && (c)) {

		*c = ringBuffer->buffer[ringBuffer->tail];
		ringBuffer->tail = ((ringBuffer->tail) + 1) % (ringBuffer->length);
		ringBuffer->full = 0;
		ringBuffer->odej++;
		return true;
	}
	return false;
}