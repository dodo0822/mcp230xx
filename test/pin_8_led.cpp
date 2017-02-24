#include <stdio.h>

#include "mbed.h"

#include "mcp230xx/MCP230xx.h"

MCP23017* mcpPtr;
static bool led;

static void do_nothing(void) {
	/*bool result = mcpPtr->input(0);
	bool r2 = mcpPtr->input(1);
	bool r3 = mcpPtr->input(2);
	bool r4 = mcpPtr->input(3);
	printf("hello world: %d %d,%d,%d,%d\r\n", i++, result, r2, r3, r4);*/
	if(led) mcpPtr->output(8, MCP23017::LOW);
	else mcpPtr->output(8, MCP23017::HIGH);
	led = !led;
}

void app_start(int, char**) {
	static I2C i2c(YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SDA, YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SCL);
	i2c.frequency(100000);
	static MCP23017 mcp(i2c);
	mcp.setup(8, MCP23017::OUT);
	mcp.output(8, MCP23017::HIGH);
	mcpPtr = &mcp;
	led = true;
	
	minar::Scheduler::postCallback(do_nothing).period(minar::milliseconds(500));
}