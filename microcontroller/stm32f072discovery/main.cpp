#include <xpcc/architecture.hpp>
#include <xpcc/debug/logger.hpp>
#include "../../../ext/xpcc/examples/stm32f072_discovery/stm32f072_discovery.hpp"

// ----------------------------------------------------------------------------
// Set the log level
#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG


// Create an IODeviceWrapper around the Uart Peripheral we want to use
xpcc::IODeviceWrapper< Usart1, xpcc::IOBuffer::BlockIfFull > loggerDevice;

// Set all four logger streams to use the UART
xpcc::log::Logger xpcc::log::debug(loggerDevice);
xpcc::log::Logger xpcc::log::info(loggerDevice);
xpcc::log::Logger xpcc::log::warning(loggerDevice);
xpcc::log::Logger xpcc::log::error(loggerDevice);


// Dummy Clock
struct DummyClock {
	static constexpr int Usart1 = 8 * 1000 * 1000;
};

MAIN_FUNCTION
{
	// initialize Uart1 for XPCC_LOG_
	GpioOutputA9::connect(Usart1::Tx);
	GpioInputA10::connect(Usart1::Rx, Gpio::InputType::PullUp);
	Usart1::initialize<DummyClock, 115200>();

	XPCC_LOG_INFO << "smup badup dada dumbun dum" << xpcc::endl;

	return 0;
}
