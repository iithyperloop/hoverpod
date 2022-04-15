#pragma once

enum class OBJ2Pid : uint16_t {
	STATUS = 0xF004, // relay status
	SIGNED_PACK_CURRENT = 0xF00C, // amps
	UNSIGNED_PACK_CURRENT = 0xF015, // amps
	VOLTAGE = 0xF00D, // volts
	OPEN_VOLTAGE = 0xF00E, // volts
	STATE_OF_CHARGE = 0xF00F, // % charge
	PACK_TEMP = 0xF02A // avg temp of battery pack
};

class BatteryPack {

	int16_t id = 0x7E3;
	int8_t can_len = 0x8;
	int8_t obj2_len = 0x4;
	int8_t mod = 0x22;
	uint32_t padding = 0x0;

	template <typename T>
	void cp_and_iter(int* off, uint8_t* arr, T val) {
		memcpy(&arr[*off], &val, sizeof(val)); // this is copying var to arr
		*off += sizeof(T);
	}

public:
	uint8_t* serialize(OBJ2Pid pid);

	uint16_t getSOCVal(uint8_t arr[12]);

	uint16_t GetValue(OBJ2Pid pid);
};