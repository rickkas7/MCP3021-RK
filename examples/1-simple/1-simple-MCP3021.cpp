#include "Particle.h"

#include "MCP3021-RK.h"

const unsigned long SAMPLE_PERIOD_MS = 1000;

MCP3021 adc(Wire);
bool haveChip = false;
unsigned long lastSample = 0;


void setup() {
	Serial.begin(9600);
	adc.begin();
}

void loop() {
	if (millis() - lastSample >= SAMPLE_PERIOD_MS) {
		lastSample = millis();

		if (!haveChip) {
			haveChip = adc.check();
			Serial.printlnf("haveChip=%d", haveChip);
		}
		if (haveChip) {
			Serial.printlnf("value=%u", adc.getSample());
		} else {
			Serial.println("no MCP3021 detected");
		}
	}
}
