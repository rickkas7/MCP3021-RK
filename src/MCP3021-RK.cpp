
#include "MCP3021-RK.h"

MCP3021::MCP3021(TwoWire &wire, uint8_t addr) : wire(wire), addr(addr) {
}

MCP3021::~MCP3021() {
}

void MCP3021::begin() {
	wire.begin();
}

bool MCP3021::check() {
	wire.beginTransmission(getAddr());
	int stat = wire.endTransmission(true);
	return (stat == 0);
}

uint16_t MCP3021::getSample() {
	uint16_t value = 0xffff;

	int count = wire.requestFrom(getAddr(), 2, true);
	if (count == 2) {
		value = (wire.read() << 8) | wire.read();
		value >>= 2;
	}

	return value;
}

uint8_t MCP3021::getAddr() {
	if (addr < 8) {
		return DEVICE_ADDR | addr;
	}
	else {
		return addr;
	}
}

