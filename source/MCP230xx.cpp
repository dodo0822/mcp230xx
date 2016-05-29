#include "mcp230xx/MCP230xx.h"

const bool MCP23008::IN = true;
const bool MCP23008::OUT = false;

const bool MCP23008::HIGH = true;
const bool MCP23008::LOW = false;

void MCP23008::setup(uint8_t pin, bool type) {
	if(pin >= 8) return;

	if(type == IN) {
		iodir |= 1 << pin;
	} else {
		iodir &= ~(1 << pin);
	}

	write_iodir();
	wait_ms(5);
}

void MCP23008::output(uint8_t pin, bool value) {
	if(pin >= 8) return;

	if(value == HIGH) {
		gpio |= 1 << pin;
	} else {
		gpio &= ~(1 << pin);
	}

	write_gpio();
	wait_ms(5);
}

bool MCP23008::input(uint8_t pin) {
	if(pin >= 8) return false;

	uint8_t states = read_gpio(0x09);
	wait_ms(5);

	return states & (1 << pin);
}

void MCP23008::pullup(uint8_t pin, bool en) {
	if(pin >= 8) return;

	if(en) {
		gppu |= 1 << pin;
	} else {
		gppu &= ~(1 << pin);
	}

	write_gppu();
	wait_ms(5);
}

void MCP23008::write_gpio() {
	char buf[2];
	buf[0] = 0x09;
	buf[1] = gpio;
	i2c.write(address, buf, sizeof(buf), false);

	return;
}

void MCP23008::write_iodir() {
	char buf[2];
	buf[0] = 0x00;
	buf[1] = iodir;
	i2c.write(address, buf, sizeof(buf), false);

	return;
}

void MCP23008::write_gppu() {
	char buf[2];
	buf[0] = 0x06;
	buf[1] = gppu;
	i2c.write(address, buf, sizeof(buf), false);

	return;
}

uint8_t MCP23008::read_gpio(uint8_t reg) {
	char cmd = reg;
	char result;

	i2c.write(address, &cmd, 1);
	i2c.read(address, &result, 1);

	return result;
}

const bool MCP23017::IN = true;
const bool MCP23017::OUT = false;

const bool MCP23017::HIGH = true;
const bool MCP23017::LOW = false;

void MCP23017::setup(uint8_t pin, bool type) {
	if(pin >= 16) return;

	uint8_t p = pin / 8;

	if(type == IN) {
		iodir[p] |= 1 << (pin % 8);
	} else {
		iodir[p] &= ~(1 << (pin % 8));
	}

	write_iodir();
	wait_ms(5);
}

void MCP23017::output(uint8_t pin, bool value) {
	if(pin >= 16) return;

	uint8_t p = pin / 8;

	if(value == HIGH) {
		gpio[p] |= 1 << (pin % 8);
	} else {
		gpio[p] &= ~(1 << (pin % 8));
	}

	write_gpio();
	wait_ms(5);
}

bool MCP23017::input(uint8_t pin) {
	if(pin >= 16) return false;

	uint8_t p = pin / 8;

	uint8_t states = read_gpio(0x12 + p);
	wait_ms(5);

	return states & (1 << (pin % 8));
}

void MCP23017::pullup(uint8_t pin, bool en) {
	if(pin >= 16) return;

	uint8_t p = pin / 8;

	if(en) {
		gppu[p] |= 1 << (pin % 8);
	} else {
		gppu[p] &= ~(1 << (pin % 8));
	}

	write_gppu();
	wait_ms(5);
}

void MCP23017::write_gpio() {
	char buf[2];
	buf[0] = 0x12;
	buf[1] = gpio[0];
	i2c.write(address, buf, sizeof(buf), false);

	wait_ms(5);

	buf[0] = 0x13;
	buf[1] = gpio[1];
	i2c.write(address, buf, sizeof(buf), false);

	return;
}

void MCP23017::write_iodir() {
	char buf[2];
	buf[0] = 0x00;
	buf[1] = iodir[0];
	i2c.write(address, buf, sizeof(buf), false);

	wait_ms(5);

	buf[0] = 0x01;
	buf[1] = iodir[1];
	i2c.write(address, buf, sizeof(buf), false);

	return;
}

void MCP23017::write_gppu() {
	char buf[2];
	buf[0] = 0x0C;
	buf[1] = gppu[0];
	i2c.write(address, buf, sizeof(buf), false);
	
	wait_ms(5);

	buf[0] = 0x0D;
	buf[1] = gppu[1];
	i2c.write(address, buf, sizeof(buf), false);

	return;
}

uint8_t MCP23017::read_gpio(uint8_t reg) {
	char cmd = reg;
	char result;

	i2c.write(address, &cmd, 1);
	i2c.read(address, &result, 1);

	return result;
}