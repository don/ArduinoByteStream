// Copyright 2013 Don Coleman
// Arduino Stream from a byte array

#ifndef ByteStream_h
#define ByteStream_h

#include "Arduino.h"
#include "Stream.h"

class ByteStream : public Stream {
public:
    ByteStream(byte *data, const int size);
    ~ByteStream();
    
    virtual int available();
    virtual int read();
    virtual int peek();
    
    virtual void flush();
    virtual size_t write(uint8_t); 
private:
    byte *data;
    int bytesAvailable;
    byte *data_ptr;
};

#endif