/*
 * smup_test.cpp
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

#include "smup_test.hpp"
#include "../mockiodevice.hpp"
#include "../../cpp/smup.hpp"

#include <iostream>

#define TEST_ASSERT_SENT_BYTES(...) \
{ \
uint8_t expected[] = {__VA_ARGS__}; \
TEST_ASSERT_EQUALS(ioDevice.getTxBufferCount(), sizeof(expected)); \
TEST_ASSERT_EQUALS_ARRAY(ioDevice.getTxBufferStart(), expected, sizeof(expected)); \
}



void
SmupTest::testBasicOutput()
{
	MockIODevice<100,100> ioDevice;
	smup::Stream io(ioDevice);

	io << "Hello";
	TEST_ASSERT_SENT_BYTES(0xaa, 0x28, 5, 0, 'H', 'e', 'l', 'l', 'o');

	TEST_ASSERT_EQUALS(2 + 2, 4);
}
