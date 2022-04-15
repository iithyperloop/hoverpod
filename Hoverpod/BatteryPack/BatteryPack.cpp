#include <cstdint>
#include <string.h>
#include "BatteryPack.hpp"

enum class OBJ2Pid : uint16_t {
	STATUS = 0xF004, // relay status
	SIGNED_PACK_CURRENT = 0xF00C, // amps
	UNSIGNED_PACK_CURRENT = 0xF015, // amps
	VOLTAGE = 0xF00D, // volts
	OPEN_VOLTAGE = 0xF00E, // volts
	STATE_OF_CHARGE = 0xF00F, // % charge
	PACK_TEMP = 0xF02A // avg temp of battery pack
};

class BMS {
	int16_t id = 0x7E3;
	int8_t can_len = 0x8;
	int8_t obj2_len = 0x4;
	int8_t mod = 0x22;
	uint32_t padding = 0x0;

public:

	uint16_t getSOCVal(uint8_t arr[12]) {
		// 7th byte in array is soc array (2 bytes long, bytes 7 and 8)
		uint16_t val = 0;
		memcpy(&val, &arr[7], 2);
		return val;
	}

	// ex:
	// BMS.GetValue(OBJ2Pid::VOLTAGE)
	// BMS.GetValue(OBJ2Pid::STATE_OF_CHARGE)

	uint16_t GetValue(OBJ2Pid pid) {
		//serial.send(serialize(pid));
		//return getSOCVal(serial.recv());
		/// TODO: replace or something idk im ty
		return 0;
	}
};

uint8_t* BatteryPack::serialize(OBJ2Pid pid) {
	uint8_t arr[11] = {};
	int off = 0;
	cp_and_iter(&off, arr, id);
	cp_and_iter(&off, arr, can_len);
	cp_and_iter(&off, arr, obj2_len);
	cp_and_iter(&off, arr, mod);
	cp_and_iter(&off, arr, static_cast<uint16_t>(pid));
	cp_and_iter(&off, arr, padding);
	return arr;
}