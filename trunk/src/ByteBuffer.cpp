/**
   ByteBuffer
   ByteBuffer.cpp
   Copyright 2011 Ramsey Kant

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "ByteBuffer.h"

/**
 * ByteBuffer constructor
 * Reserves specified size in internal vector
 * 
 * @param size Size of space to preallocate internally. Default is 4096 bytes
 */
ByteBuffer::ByteBuffer(int size) {
	rpos = 0;
	wpos = 0;
	buf.reserve(size);
#ifdef BB_UTILITY
	name = "";
#endif
}

/**
 * ByteBuffer constructor
 * Consume an entire byte array of length len in the ByteBuffer
 * 
 * @param arr byte array of data (should be of length len)
 * @param size Size of space to allocate
 */
ByteBuffer::ByteBuffer(byte* arr, int size) {
	rpos = 0;
	wpos = 0;
	buf.reserve(size);
	putBytes(arr, size);
#ifdef BB_UTILITY
	name = "";
#endif
}

/**
 * ByteBuffer Deconstructor
 *
 */
ByteBuffer::~ByteBuffer() {
}

/**
 * Clear
 * Clears out all data from the internal vector (original preallocated size remains), resets the positions to 0
 */
void ByteBuffer::clear() {
	rpos = 0;
	wpos = 0;
	buf.clear();
}

/**
 * Clone
 * Allocate an exact copy of the ByteBuffer on the heap and return a pointer
 *
 * @return A pointer to the newly cloned ByteBuffer. NULL if no more memory available
 */
ByteBuffer* ByteBuffer::clone() {
	ByteBuffer* ret = new ByteBuffer(buf.size());

	// Copy data
	for(int i = 0; i < buf.size(); i++) {
		ret->put(i, (byte)get(i));
	}

	// Reset positions
	ret->setReadPos(0);
	ret->setWritePos(0);

	return ret;
}

/**
 * Equals, test for data equivilancy
 * Compare this ByteBuffer to another by looking at each byte in the internal buffers and making sure they are the same
 *
 * @param other A pointer to a ByteBuffer to compare to this one
 * @return True if the internal buffers match. False if otherwise
 */
bool ByteBuffer::equals(ByteBuffer* other) {
	// If sizes aren't equal, they can't be equal
	if(size() != other->size())
		return false;

	// Compare byte by byte
	int len = size();
	for(int i = 0; i < len; i++) {
		if((byte)get(i) != (byte)other->get(i))
			return false;
	}

	return true;
}

/**
 * Resize
 * Reallocates memory for the internal buffer of size newSize. Read and write positions will also be reset
 *
 * @param newSize The amount of memory to allocate
 */
void ByteBuffer::resize(int newSize) {
	buf.resize(newSize);
	rpos = 0;
	wpos = 0;
}

/**
 * Size
 * Returns the size of the internal buffer...not necessarily the length of bytes used as data!
 *
 * @return size of the internal buffer
 */
int ByteBuffer::size() {
	return buf.size();
}

// Read Functions

byte ByteBuffer::get() {
	return read<byte>();
}

byte ByteBuffer::get(int index) {
	return read<byte>(index);
}

void ByteBuffer::getBytes(byte* buf, int len) {
	for(int i = 0; i < len; i++) {
		buf[i] = read<byte>();
	}
}

char ByteBuffer::getChar() {
	return read<char>();
}

char ByteBuffer::getChar(int index) {
	return read<char>(index);
}

double ByteBuffer::getDouble() {
	return read<double>();
}

double ByteBuffer::getDouble(int index) {
	return read<double>(index);
}

float ByteBuffer::getFloat() {
	return read<float>();
}

float ByteBuffer::getFloat(int index) {
	return read<float>(index);
}

int ByteBuffer::getInt() {
	return read<int>();
}

int ByteBuffer::getInt(int index) {
	return read<int>(index);
}

long ByteBuffer::getLong() {
	return read<long>();
}

long ByteBuffer::getLong(int index) {
	return read<long>(index);
}

short ByteBuffer::getShort() {
	return read<short>();
}

short ByteBuffer::getShort(int index) {
	return read<short>(index);
}


// Write Functions

void ByteBuffer::put(ByteBuffer* src) {
	int len = src->size();
	for(int i = 0; i < len; i++)
		append<byte>(src->get(i));
}

void ByteBuffer::put(byte b) {
	append<byte>(b);
}

void ByteBuffer::put(byte b, int index) {
	insert<byte>(b, index);
}

void ByteBuffer::putBytes(byte* b, int len, int index) {
	// Default index value (-1) indicates to start writing at the current write position
	if(index == -1)
		index = wpos;
	else // Otherwise, change the write position
		wpos = index;

	// Ending write position must be within the bounds
	/*if((index+len) >= size())
		return;*/

	// Insert the data one byte at a time into the internal buffer at position i+starting index
	for(int i = 0; i < len; i++)
		append<byte>(b[i]);
}

void ByteBuffer::putChar(char value) {
	append<char>(value);
}

void ByteBuffer::putChar(char value, int index) {
	insert<char>(value, index);
}

void ByteBuffer::putDouble(double value) {
	append<double>(value);
}

void ByteBuffer::putDouble(double value, int index) {
	insert<double>(value, index);
}
void ByteBuffer::putFloat(float value) {
	append<float>(value);
}

void ByteBuffer::putFloat(float value, int index) {
	insert<float>(value, index);
}

void ByteBuffer::putInt(int value) {
	append<int>(value);
}

void ByteBuffer::putInt(int value, int index) {
	insert<int>(value, index);
}

void ByteBuffer::putLong(long value) {
	append<long>(value);
}

void ByteBuffer::putLong(long value, int index) {
	insert<long>(value, index);
}

void ByteBuffer::putShort(short value) {
	append<short>(value);
}

void ByteBuffer::putShort(short value, int index) {
	insert<short>(value, index);
}

// Utility Functions
#ifdef BB_UTILITY
void ByteBuffer::setName(std::string n) {
	name = n;
}

std::string ByteBuffer::getName() {
	return name;
}

void ByteBuffer::printAscii() {
	int length = buf.size();
	std::cout << "ByteBuffer " << name.c_str() << ", Length: " << length << ". ASCII Print" << std::endl;
	for(int i = 0; i < length; i++) {
		printf("%c ", buf[i]);
	}
	printf("\n");
}

void ByteBuffer::printHex() {
	int length = buf.size();
	std::cout << "ByteBuffer " << name.c_str() << ", Length: " << length << ". Hex Print" << std::endl;
	for(int i = 0; i < length; i++) {
		printf("0x%02x ", buf[i]);
	}
	printf("\n");
}

void ByteBuffer::printPosition() {
	int length = buf.size();
	std::cout << "ByteBuffer " << name.c_str() << ", Length: " << length << " Read Pos: " << rpos << ". Write Pos: " << wpos << std::endl;
}
#endif
