#ifndef __MCP3021_RK_H
#define __MCP3021_RK_H

#include "Particle.h"

/**
 * You typically instantiate one of these as a global object:
 *
 * MCP3021 adc(Wire);
 *
 */
class MCP3021 {
public:
	/**
	 * The parameter is the I2C interface to use, either Wire (D0/D1) on all devices
	 * or Wire1 (C4/C5) on the Electron.
	 *
	 * Most MCP3021 ship with the address 0b101 or 5). There are no configurable address
	 * pins, but it is possible to get other addresses from the factory. If you have
	 * an alternate address you can specify that as the optional second parameter to
	 * the constructor.
	 *
	 * Also, the MCP3021 has 0b1001 in the higher bits, but if you're using a similar
	 * but different chip, you can actually pass the full 7-bit I2C address in addr. If
	 * addr >= 8, then the addr is passed directly, not ORing in the 0b1001000 part.
	 */
	MCP3021(TwoWire &wire, uint8_t addr = 0b101);
	virtual ~MCP3021();

	/**
	 * Be sure to call begin or wire.begin(). If you don't initialize the I2C interface
	 * somewhere, you'll SOS when you use it the first time.
	 */
	void begin();

	/**
	 * Checks to see if the I2C device is present. You don't have to call this, but you
	 * can use it to see if the device is present without getting a value.
	 */
	bool check();

	/**
	 * Gets a sample of data, 0-1023. Note: If the I2C device cannot be communicated with
	 * this function returns 0xffff (65535).
	 */
	uint16_t getSample();

	/**
	 * Used internally to get the I2C address. If the addr passed to the constructor is
	 * < 8, then it's addr | DEVICE_ADDR. If addr >= 8, then addr is used directly.
	 */
	uint8_t getAddr();

	static const uint8_t DEVICE_ADDR = 0b1001000;

protected:
	TwoWire &wire;
	uint8_t addr;
};

#endif /* __MCP3021_RK_H */
