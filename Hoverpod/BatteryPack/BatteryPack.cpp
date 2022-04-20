#include "BatteryPack.hpp"

BatteryPack::BatteryPack() : 
	BMSConnection(
		"/dev/tty.usbserial-AB0N4FFO", 
		9600, 
		serial::Timeout::simpleTimeout(1000), 
		serial::eightbits, 
		serial::parity_even, 
		serial::stopbits_one) {}

uint16_t BatteryPack::getSOCVal(uint8_t arr[12]) {
	// 7th byte in array is soc array (2 bytes long, bytes 7 and 8)
	uint16_t val = 0;
	memcpy(&val, &arr[7], 2);
	return val;
}

// ex:
// BMS.GetValue(OBJ2Pid::VOLTAGE)
// BMS.GetValue(OBJ2Pid::STATE_OF_CHARGE)

uint16_t BatteryPack::GetValue(OBJ2Pid pid) {
	//serial.send(serialize(pid));
	//return getSOCVal(serial.recv());
	/// TODO: replace or something idk im ty
	return 0;
}

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