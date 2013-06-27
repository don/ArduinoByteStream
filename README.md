Arduino ByteStream

Read-only Stream from a byte array.

Installing
    
    $ cd ~/Documents/Arduino/libraries
    $ git clone https://github.com/don/ArduinoByteStream.git

This is a proof of concept.
See the [tests](tests/test/test.ino) for examples.

Tests

To run the tests, you'll need [ArduinoUnit](https://github.com/mmurdoch/arduinounit). To "install", I clone the repo to my home directory and symlink the source into ~/Documents/Arduino/libraries/ArduinoUnit.

    $ cd ~
    $ git clone git@github.com:mmurdoch/arduinounit.git
    $ cd ~/Documents/Arduino/libraries/
    $ ln -s ~/arduinounit/src ArduinoUnit
    
Once arduinounit is installed, open test.ino in the ArduinoIDE, upload to your Arduino and open the Serial Monitor. You should see a message that all tests have passed.

I use nodejs to create the arrays for the tests.
    
    $ node
    > JSON.stringify(Buffer("hello, world"))
    '[104,101,108,108,111,44,32,119,111,114,108,100]'

Arduino

    byte data[] = { 104,101,108,108,111,44,32,119,111,114,108,100 };
    ByteStream stream = ByteStream(data, sizeof(data0);
