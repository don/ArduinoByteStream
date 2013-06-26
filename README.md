Arduino ByteStream

Read-only Stream from a byte array.

Installing
    
    $ cd ~/Documents/Arduino/libraries
    $ git clone https://github.com/don/ArduinoByteStream.git

This is a proof of concept.
See the [tests](tests/test/test.ino) for examples.

I use nodejs to create the arrays for the tests
    
    $ node
    > JSON.stringify(Buffer("hello, world"))
    '[104,101,108,108,111,44,32,119,111,114,108,100]'
        
byte data[] = { 104,101,108,108,111,44,32,119,111,114,108,100 };
