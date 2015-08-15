/*
 * smup.hpp
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

#ifndef SMUP_HPP
#define SMUP_HPP

#include <xpcc/io/iodevice.hpp>
#include <xpcc/math/utils/endianness.hpp>
#include <xpcc/utils/arithmetic_traits.hpp>

#include "smup_constants.hpp"

namespace smup {


template<typename T>
struct Buffer {
	T* data;
	size_t count;
};

template<typename T, size_t N>
inline Buffer<T> buffer(T (&data)[N]) {
	Buffer<T> b;
	b.data = data;
	b.count = N;
	return b;
}

class Stream : private Constants {

public:
	enum class Error {
		None,
		StringTooLong,
		BufferTooLong,
	};

	Stream(xpcc::IODevice& device) :
		device(device),
		connected(true),	// TODO: connected should be false until a connection is established
		lastError(Error::None)
		{}


	inline bool isConnected() const { return this->connected; }

	Stream& operator << (const bool& v) {
		this->start(PacketType::UserData, DataType::Bool);
		this->send(v? True : False);
		this->end();
		return *this;
	}

	inline Stream& operator << (const int8_t& v) {
		return (*this) << static_cast<int32_t>(v);
	}

	inline Stream& operator << (const int16_t& v) {
		return (*this) << static_cast<int32_t>(v);
	}

	Stream& operator << (const int32_t& v) {
		this->start(PacketType::UserData, DataType::Int32);
		this->send(v);
		this->end();
		return (*this);
	}

	inline Stream& operator << (const uint8_t& v) {
		return (*this) << static_cast<uint32_t>(v);
	}

	inline Stream& operator << (const uint16_t& v) {
		return (*this) << static_cast<uint32_t>(v);
	}

	Stream& operator << (const uint32_t& v) {
		this->start(PacketType::UserData, DataType::UInt32);
		this->send(v);
		this->end();
		return (*this);
	}

	Stream& operator << (const char* s) {
		size_t stringLength = strlen(s);
		if(stringLength > xpcc::ArithmeticTraits<uint16_t>::max) {
			this->error(Error::StringTooLong);
		} else {
			this->start(PacketType::UserData, DataType::AsciiString);
			this->send(static_cast<uint16_t>(stringLength));
			this->send(reinterpret_cast<const uint8_t*>(s), stringLength);
			this->end();
		}
		return (*this);
	}

	Stream& operator << (const Buffer<uint8_t>& b) {
		if(b.count > xpcc::ArithmeticTraits<uint16_t>::max) {
			this->error(Error::BufferTooLong);
		} else {
			this->start(PacketType::UserData, DataType::Bytes);
			this->send(static_cast<uint16_t>(b.count));
			this->send(b.data, b.count);
			this->end();
		}
		return (*this);
	}


private:
	void error(Error err) {
		this->lastError = err;
	}

	xpcc::IODevice& device;
	/// true if there is reason to belief, that a connection exists
	bool connected;
	///< contains the last error detected
	Error lastError;

private:
	static inline constexpr DataType getDataType(bool) {
		return DataType::Bool;
	}
	static inline constexpr DataType getDataType(int32_t) {
		return DataType::Int32;
	}
	static inline constexpr DataType getDataType(uint32_t) {
		return DataType::UInt32;
	}
	static inline constexpr DataType getDataType(char*) {
		return DataType::AsciiString;
	}
	static inline constexpr DataType getDataType(uint8_t*) {
		return DataType::Bytes;
	}

	/// needs to be called to start a package
	inline void start(PacketType packetType, DataType dataType) {
		uint8_t header = ((static_cast<uint8_t>(packetType) & 0xf) << 4) |
		                  (static_cast<uint8_t>(dataType)   & 0xf);
		this->device.write(Flag);
		this->send(header);
	}

	/// needs to be called to end a package
	inline void end() {
		// TODO: send CRC?
	}

	inline void send(const uint8_t* data, const size_t length) {
		for(size_t ii = 0; ii < length; ++ii) {
			this->send(data[ii]);
		}
	}

	// this does bitstuffing
	// see e.g. Computer Networks by Tanenbaum in Section 3.1
	inline void send(const uint8_t data) {
		if(data == Flag || data == Escape) {
			this->device.write(Escape);
		}
		this->device.write(data);
	}

	inline void send(const int32_t v) {
		int32_t data = xpcc::toLittleEndian(v);
		this->send(reinterpret_cast<uint8_t*>(&data), sizeof(data));
	}

	inline void send(const uint32_t v) {
		uint32_t data = xpcc::toLittleEndian(v);
		this->send(reinterpret_cast<uint8_t*>(&data), sizeof(data));
	}

	inline void send(const uint16_t v) {
		uint16_t data = xpcc::toLittleEndian(v);
		this->send(reinterpret_cast<uint8_t*>(&data), sizeof(data));
	}
};	// class Stream

}	// namespace smup

#endif // SMUP_HPP
