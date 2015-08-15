#include "../../ext/xpcc/examples/arduino_uno/arduino_uno.hpp"
#include "../smup.hpp"

MAIN_FUNCTION {
	DigitalOutput13::setOutput();

	// initialize the serial communication module
	DigitalInput0::connect(Uart0::Rx);
	DigitalOutput1::connect(Uart0::Tx);
	Uart0::initialize<clock, 38400>();
	sei();

	xpcc::IODeviceWrapper< Uart0, xpcc::IOBuffer::BlockIfFull > ioDevice;
	smup::Stream io(ioDevice);
	while(!io.isConnected()) {
		;
	}

	io << "Hello World";

	io << static_cast<int32_t>(1337);

	uint8_t bytes[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	io << smup::array(10) << bytes;


//	int32_t integerArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//	io << smup::array(10) << integerArray;

//	float ftest = 2.5f;

//	io << ftest;
//	io << "Test String";
//	char* receiveString;

//	// data will be dropped untill a string is received
//	io >> receiveString;

//	uint8_t data[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde};
//	// you can also send binary data
//	io.send(data, 7);

//	// and receive binary data, of caus
//	io.receive(data, 7);

	while(true) {
		DigitalOutput13::toggle();
		xpcc::delayMilliseconds(500);
	}
}
