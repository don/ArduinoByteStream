// Copyright 2013 Don Coleman
// Arduino Stream from a byte array

#include "ByteStream.h"

ByteStream::ByteStream(byte *data, const int size)
{   
    this->data = data;
    this->bytesAvailable = size;
    this->data_ptr = &this->data[0];
}

ByteStream::~ByteStream()
{
}

int ByteStream::available() {
    return bytesAvailable;
}

int ByteStream::read() {

    int value = -1;
    
    if (available()) { 
        value = *data_ptr;
        bytesAvailable -= 1;
        *data_ptr++;
    }
    
    return value;
}

int ByteStream::peek() {
    int value = -1;

    if (available()) {
        value = *data_ptr;
    }

    return value;
}

void ByteStream::flush() {
    // stream is read only, do nothing
}

size_t ByteStream::write(uint8_t) {
    // stream is read only    
    return -1;
}
