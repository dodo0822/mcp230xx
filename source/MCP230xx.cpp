#include "mcp230xx/MCP230xx.h"

const bool MCP23008::IN = true;
const bool MCP23008::OUT = false;

const bool MCP23008::HIGH = true;
const bool MCP23008::LOW = false;

void MCP23008::setup(uint8_t pin, bool type) {
	if(pin >= 8) return;

	if(type == IN) {
		iodir[0] |= 1 << pin;
	} else {
		iodir[0] &= ~(1 << pin);
	}

	write_iodir();
}

void MCP23008::output(uint8_t pin, bool value) {
	if(pin >= 8) return;

	if(value == HIGH) {
		gpio[0] |= 1 << pin;
	} else {
		gpio[0] &= ~(1 << pin);
	}

	write_gpio();
}

bool MCP23008::input(uint8_t pin) {
	if(pin >= 8) false;

	uint8_t states = read_gpio(0x09);

	return (((states & 1) << pin) > 0);
}

void MCP23008::pullup(uint8_t pin, bool en) {
	if(pin >= 8) return;

	if(en) {
		gppu[0] |= 1 << pin;
	} else {
		gppu[0] &= ~(1 << pin);
	}

	write_gppu();
}

void MCP23008::write_gpio() {
	char buf[2];
	for(unsigned i = 0; i < gpio.size(); ++i) {
		buf[0] = (0x09 + i);
		buf[1] = gpio[i];
		i2c.write(address, buf, sizeof(buf), false);
	}

	return;
}

void MCP23008::write_iodir() {
	char buf[2];
	for(int i = 0; i < iodir.size(); ++i) {
		buf[0] = (0x00 + i);
		buf[1] = iodir[i];
		i2c.write(address, buf, sizeof(buf), false);
	}

	return;
}

void MCP23008::write_gppu() {
	char buf[2];
	for(int i = 0; i < gppu.size(); ++i) {
		buf[0] = (0x06 + i);
		buf[1] = gppu[i];
		i2c.write(address, buf, sizeof(buf), false);
	}

	return;
}

uint8_t MCP23008::read_gpio(uint8_t reg) {
	char cmd[1];
	cmd[0] = reg;

	char result[1];

	i2c.write(address, cmd, 1, true);
	i2c.read(address, result, 1);

	return result[0];
}