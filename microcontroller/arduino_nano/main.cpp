/*
 * main.cpp
 *
 * Copyright (c) 2015, Kevin Laeufer <kevin.laeufer@rwth-aachen.de>
 *
 * This file is part of smup.
 *
 * smup is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * smup is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with smup.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "../../ext/xpcc/examples/arduino_uno/arduino_uno.hpp"
#include "../../cpp/smup.hpp"

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
