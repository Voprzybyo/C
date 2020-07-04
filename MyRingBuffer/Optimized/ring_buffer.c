#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init(RingBuffer* ringBuffer, char* dataBuffer, size_t dataBufferSize)
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);

	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {

		ringBuffer->buffer = dataBuffer;
		ringBuffer->head = 0;
		ringBuffer->tail = 0;
		ringBuffer->BufferSize = dataBufferSize;
		ringBuffer->counter = 0;
		return true;
	}

	return false;
}

bool RingBuffer_Clear(RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		ringBuffer->head = ringBuffer->tail;
		ringBuffer->counter = 0;
		return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer->counter == 0) {
		return true;
	}
	return false;

}

size_t RingBuffer_GetLen(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		return ringBuffer->counter;
	}
	return 0;

}

size_t RingBuffer_GetCapacity(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		return ringBuffer->BufferSize;
	}
	return 0;
}


bool RingBuffer_PutChar(RingBuffer* ringBuffer, char c)
{
	assert(ringBuffer);

	if (ringBuffer) {

		if (ringBuffer->counter < ringBuffer->BufferSize) {

			ringBuffer->buffer[ringBuffer->head] = c;
			ringBuffer->counter++;
			ringBuffer->head = (ringBuffer->head + 1) % ringBuffer->BufferSize;

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

		if (RingBuffer_IsEmpty) {

			*c = ringBuffer->buffer[ringBuffer->tail];
			ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->BufferSize;
			ringBuffer->counter--;
			return true;
		}
	}
	return false;
}
