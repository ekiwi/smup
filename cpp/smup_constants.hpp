/*
 * smup_constants.hpp
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

#ifndef SMUP_CONSTANTS_HPP
#define SMUP_CONSTANTS_HPP


namespace smup {

struct Constants {
	static constexpr uint8_t Flag = 0xaa;
	static constexpr uint8_t Escape = 0x1b;

	enum class PacketType : uint8_t {
		Ping          = 0x0,
		GetName       = 0x1,
		UserData      = 0x2,
		UserDataArray = 0x3,
	};

	enum class DataType : uint8_t {
		Bool        = 0x0,
		Int32       = 0x2,
		UInt32      = 0x3,
		AsciiString = 0x8,
		Bytes       = 0x9,
	};

	static constexpr uint8_t True = 1;
	static constexpr uint8_t False = 0;
};	// class Constants

}	// namespace smup

#endif // SMUP_CONSTANTS_HPP
