# smup

The goal of this project is to implement a simple protocol, that can be
used to exchange data between an application running on a microcontroller
and a python application running on the host pc.

## Microcontroller Example

~~~{.cpp}
xpcc::IODeviceWrapper< Usart1, xpcc::IOBuffer::BlockIfFull > ioDevice;

smup::Stream io(ioDevice);

while(!io.isConnected()) {
	;
}

float ftest = 2.5f;

io << ftest;
io << "Test String";
char* receiveString;

// data will be dropped untill a string is received
io >> receiveString;

uint8_t data[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde};
// you can also send binary data
io.send(data, 7);

// and receive binary data, of caus
io.receive(data, 7);
~~~

## Host Python Example

~~~{.py}


~~~

## Packet Types

Type Identifier |   Length |  C++ Type | Python Type |
----------------|----------|-----------|-------------|
            0x0 |        1 |      bool |        bool |
            0x1 |        1 |      bool |        bool |
            0x2 |        4 |   int32_t |         int |
            0x3 | variable |     char* |         str |
            0x4 | variable | uint8_t[] |        list |

