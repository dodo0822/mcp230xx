#include <stdio.h>

#include "mbed-drivers/mbed.h"

#include "mcp230xx/MCP230xx.h"

MCP23008* mcpPtr;
static int i = 0;

static void do_nothing(void) {
	bool result = mcpPtr->input(0);
	printf("hello world: %d %d\r\n", i++, result);
}

void app_start(int, char**) {
	static I2C i2c(YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SDA, YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SCL);
	i2c.frequency(400000);
	static MCP23008 mcp(i2c);
	mcp.setup(0, MCP23008::IN);
	mcp.pullup(0, true);
	mcpPtr = &mcp;
	
	minar::Scheduler::postCallback(do_nothing).period(minar::milliseconds(1000));
}