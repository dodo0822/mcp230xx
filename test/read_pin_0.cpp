#include <stdio.h>

#include "mbed.h"

#include "mcp230xx/MCP230xx.h"

MCP23008* mcpPtr;
static int i = 0;

static void do_nothing(void) {
	bool result = mcpPtr->input(0);
	bool r2 = mcpPtr->input(1);
	bool r3 = mcpPtr->input(2);
	bool r4 = mcpPtr->input(3);
	printf("hello world: %d %d,%d,%d,%d\r\n", i++, result, r2, r3, r4);
}

void app_start(int, char**) {
	static I2C i2c(YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SDA, YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SCL);
	i2c.frequency(100000);
	static MCP23008 mcp(i2c);
	mcp.setup(0, MCP23008::IN);
	mcp.setup(1, MCP23008::IN);
	mcp.setup(2, MCP23008::IN);
	mcp.setup(3, MCP23008::IN);
	mcp.pullup(0, true);
	mcp.pullup(1, true);
	mcp.pullup(2, true);
	mcp.pullup(3, true);
	mcp.pullup(4, true);
	mcp.pullup(5, true);
	mcp.pullup(6, true);
	mcp.pullup(7, true);
	mcpPtr = &mcp;
	
	minar::Scheduler::postCallback(do_nothing).period(minar::milliseconds(1000));
}