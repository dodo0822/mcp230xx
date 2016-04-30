#pragma once

#include "mbed-drivers/mbed.h"
#include <vector>

using namespace std;

class MCP23008 {
public:
	MCP23008(I2C &_i2c, uint8_t _address = 0x40) : i2c(_i2c), address(_address) {
		gpio = vector<uint8_t>(1, 0);
		iodir = vector<uint8_t>(1, 0);
		gppu = vector<uint8_t>(1, 0);

		write_iodir();
		write_gppu();

		// wait for device to settle down
		wait_ms(5);
	}

	void setup(uint8_t, bool);
	void output(uint8_t, bool);
	bool input(uint8_t);
	void pullup(uint8_t, bool);

	static const bool OUT;
	static const bool IN;

	static const bool HIGH;
	static const bool LOW;

private:
	I2C &i2c;
	uint8_t address;

	vector<uint8_t> gpio;
	vector<uint8_t> iodir;
	vector<uint8_t> gppu;

	void write_gpio();
	void write_iodir();
	void write_gppu();

	uint8_t read_gpio(uint8_t);
};