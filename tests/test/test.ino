#line 2 "test.ino"

// https://github.com/mmurdoch/arduinounit
#include <ArduinoUnit.h>
#include <ByteStream.h>

test(read)
{
    // "abc"
    byte data[] = {97,98,99};
    ByteStream s = ByteStream(data, sizeof(data));
    
    assertEqual(3, s.available());
    assertEqual('a', s.read());
    assertEqual('b', s.read());
    assertEqual('c', s.read());
    assertEqual(0, s.available());

    // reading an empty buffer always returns -1
    assertEqual(-1, s.read());
    assertEqual(-1, s.read());
    assertEqual(-1, s.read());    
}

test(peek)
{
    // "abc"
    byte data[] = {97,98,99};
    ByteStream s = ByteStream(data, sizeof(data));
    
    assertEqual(3, s.available());
    assertEqual('a', s.peek());
    assertEqual('a', s.read());

    assertEqual('b', s.peek());
    assertEqual('b', s.read());
    
    assertEqual(1, s.available());
    assertEqual('c', s.peek());
    assertEqual('c', s.read());
    
    assertEqual(0, s.available());
    assertEqual(-1, s.peek());
    assertEqual(-1, s.read());
}

test(parseInt)
{
    byte data[] = { 49 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    assertEqual(1, s.parseInt());
}

test(parseInts)
{
    // "1,2,3,17,255,1000"
    byte data[] = {49,44,50,44,51,44,49,55,44,50,53,53,44,49,48,48,48 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    assertEqual(1, s.parseInt());
    assertEqual(2, s.parseInt());
    assertEqual(3, s.parseInt());
    assertEqual(17, s.parseInt());
    assertEqual(255, s.parseInt());
    assertEqual(1000, s.parseInt());
}

test(parseIntsWithOtherData)
{
    // "100foo512bar6043"
    byte data[] = {49,48,48,102,111,111,53,49,50,98,97,114,54,48,52,51 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    assertEqual(100, s.parseInt());
    assertEqual(512, s.parseInt());
    assertEqual(6043, s.parseInt());
}

test(textRecordPayload)
{
    // payload of a NDEF text record
    // ndef.textRecord("hello, world")
    // 2 + en + "hello, world"
    byte data[] = { 2,101,110,104,101,108,108,111,44,32,119,111,114,108,100 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    int languageCodeLength = s.read(); // TODO ignore 3 high bits
    assertEqual(2, languageCodeLength);

    char languageCode[languageCodeLength];
    for (int i = 0; i < languageCodeLength; i++) {
        languageCode[i] = s.read();
    }
    assertEqual('e', languageCode[0]);
    assertEqual('n', languageCode[1]);

    assertEqual("hello, world", s.readString());
}

test(uriRecordPayload)
{
    // payload of a NDEF uri record
    // ndef.uriRecord("http://arduino.cc")
    // 0 + "http://arduino.cc"
    byte data[] = { 0,104,116,116,112,58,47,47,97,114,100,117,105,110,111,46,99,99 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    int prefix = s.read();
    assertEqual(0, prefix);
    assertEqual("http://arduino.cc", s.readString());
    
    // retry with "proper" prefix
    // 3 + "arduino.cc"
    byte data2[] = { 3,97,114,100,117,105,110,111,46,99,99 };
    ByteStream s2 = ByteStream(data2, sizeof(data2));
    
    prefix = s2.read();
    assertEqual(3, prefix);
    assertEqual("arduino.cc", s2.readString());   
}

test(colorApi)
{
    // hypothetical API to pass colors 
    // "c0,0,255\n"
    byte data[] = { 99,48,44,48,44,50,53,53,10 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    //assertTrue(s.findUntil('c'));
    assertEqual('c', s.read());
    int red = s.parseInt();
    int green = s.parseInt();
    int blue = s.parseInt();
    
    assertEqual(0, red);
    assertEqual(0, green);
    assertEqual(255, blue);
}

test(delimitedString)
{
    // "pipe|delimited|string"
    byte data[] = { 112,105,112,101,124,100,101,108,105,109,105,116,101,100,124,115,116,114,105,110,103 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    assertEqual("pipe", s.readStringUntil('|'));
    assertEqual("delimited", s.readStringUntil('|'));
    assertEqual("string", s.readStringUntil('|'));    
}

test(readBytes)
{
    byte data[] = { 100,97,116,97 };
    ByteStream s = ByteStream(data, sizeof(data));
    
    byte d[s.available()];

    // shouldn't need to cast d according to the docs http://arduino.cc/en/Reference/StreamReadBytes
    s.readBytes((char*)d, s.available());

    // ugh, is there a better way to do this?
    assertEqual(100, d[0]);
    assertEqual(97, d[1]);
    assertEqual(116, d[2]);
    assertEqual(97, d[3]);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Test::run();
}