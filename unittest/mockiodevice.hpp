/*
 * mockiodevice.hpp
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

#ifndef MOCKIODEVICE_HPP
#define MOCKIODEVICE_HPP

#include <xpcc/io/iodevice.hpp>

template<size_t TxBufferSize=1024, size_t RxBufferSize=1024>
class MockIODevice : public xpcc::IODevice {
	bool loopback;
	size_t txBufferCount;
	uint8_t txBuffer[TxBufferSize];
	size_t rxBufferCount;
	uint8_t rxBuffer[RxBufferSize];

public:
	MockIODevice(bool loopback = false) :
		loopback(loopback),
		txBufferCount(0),
		rxBufferCount(0)
		{}

	void enableLoopbackMode()  { this->loopback = true; }
	void disableLoopbackMode() { this->loopback = false; }

	/// returns number of bytes written
	size_t getTxBufferCount() const {
		return this->txBufferCount;
	}

	const uint8_t* getTxBufferStart() const {
		return this->txBuffer;
	}

	void reset() {
		return this->txBufferCount = 0;
		return this->rxBufferCount = 0;
	}

	virtual void
	write(char c) {
		if(this->txBufferCount < TxBufferSize) {
			this->txBuffer[this->txBufferCount] = static_cast<uint8_t>(c);
		}
		++this->txBufferCount;
	}

	virtual void
	write(const char *s) {
		while(*s) {
			this->write(*s);
			++s;
		}
	}

	virtual void
	flush() { }

	virtual bool
	read(char& c) {

	}
};

#endif // MOCKIODEVICE_HPP
