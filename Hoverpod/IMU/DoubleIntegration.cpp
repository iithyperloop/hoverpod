/*
This code originally belongs to Vectornav, any code with commennts like -->

//Panda: implementation Reason

represents that it has been written by me and the reason of implementation
*/

#include <iostream>

// Include this header file to get access to VectorNav sensors.
#include "vn/sensors.h"

// We need this file for our sleep function.
#include "vn/thread.h"

//#include <vector.h> //Panda: we need this to split accelertation into x y and z directions

using namespace std;
using namespace vn::math;
using namespace vn::sensors;
using namespace vn::protocol::uart;
using namespace vn::xplat;

// Method declarations for future use.
void asciiAsyncMessageReceived(void* userData, Packet& p, size_t index);
void asciiOrBinaryAsyncMessageReceived(void* userData, Packet& p, size_t index);
//Method for integrating two Acceleration
//points to get instantaneous velocity --> Question: What is my timestep
void integrate(vec3f prev_accel, vec3f curr_accel, float timestep);

vec3f prev_accel(0.0f, 0.0f, 0.0f); //prev acceleration = 0
uint64_t prev_timeStartup = 0; //prev time = 0
vec3f sumVelocity(0.0f, 0.0f, 0.0f);

const vec3f angleVec(0.0f, 0.0f, 1.0f);

mat3f rotMatrix(vec3f yawPitchRoll);

int main(int argc, char *argv[])
{
	const int maxFreq = 40; //Panda: this determines the output frequency

	// This example walks through using the VectorNav C++ Library to connect to
	// and interact with a VectorNav sensor.

	// First determine which COM port your sensor is attached to and update the
	// constant below. Also, if you have changed your sensor from the factory
	// default baudrate of 115200, you will need to update the baudrate
	// constant below as well.

	//This is Hyperloop's serial port information
	// string SensorPort = "COM4";                             // Windows format for physical and virtual (USB) serial port.
	// const string SensorPort = "/dev/ttyS3";                    // Linux format for physical serial port.
	// const string SensorPort = "/dev/ttyUSB0";                  // Linux format for virtual (USB) serial port.

	//Panda's serial port information
	const string SensorPort = "/dev/tty.usbserial-FT3JX4GV";    // Mac OS X format for virtual (USB) serial port.

	//const string SensorPort = "/dev/ttyS3";                    // CYGWIN format. Usually the Windows COM port number minus 1. This would connect to COM1.
	const uint32_t SensorBaudrate = 115200;

	// Now let's create a VnSensor object and use it to connect to our sensor.
	VnSensor vs;
	vs.connect(SensorPort, SensorBaudrate);

	// Let's query the sensor's model number.
	string mn = vs.readModelNumber();
	cout << "Model Number: " << mn << endl;

	// Get some orientation data from the sensor.
	vec3f ypr = vs.readYawPitchRoll();
	cout << "Current YPR: " << ypr << endl;

	// Get some orientation and IMU data.
	YawPitchRollMagneticAccelerationAndAngularRatesRegister reg;
	reg = vs.readYawPitchRollMagneticAccelerationAndAngularRates();
	cout << "Current YPR: " << reg.yawPitchRoll << endl;
	cout << "Current Magnetic: " << reg.mag << endl;
	cout << "Current Acceleration: " << reg.accel << endl;
	cout << "Current Angular Rates: " << reg.gyro << endl;

	// Let's do some simple reconfiguration of the sensor. As it comes from the
	// factory, the sensor outputs asynchronous data at 40 Hz. We will change
	// this to 2 Hz for demonstration purposes.
	uint32_t oldHz = vs.readAsyncDataOutputFrequency();
	vs.writeAsyncDataOutputFrequency(maxFreq); //val set by "const int maxFreq" on line 31
	uint32_t newHz = vs.readAsyncDataOutputFrequency();
	cout << "Old Async Frequency: " << oldHz << " Hz" << endl;
	cout << "New Async Frequency: " << newHz << " Hz" << endl;

	// For the registers that have more complex configuration options, it is
	// convenient to read the current existing register configuration, change
	// only the values of interest, and then write the configuration to the
	// register. This allows preserving the current settings for the register's
	// other fields. Below, we change the heading mode used by the sensor.
	VpeBasicControlRegister vpeReg = vs.readVpeBasicControl();
	cout << "Old Heading Mode: " << vpeReg.headingMode << endl;
	vpeReg.headingMode = HEADINGMODE_ABSOLUTE;
	vs.writeVpeBasicControl(vpeReg);
	vpeReg = vs.readVpeBasicControl();
	cout << "New Heading Mode: " << vpeReg.headingMode << endl;

	// Up to now, we have shown some examples of how to configure the sensor
	// and query for the latest measurements. However, this querying is a
	// relatively slow method for getting measurements since the CPU has to
	// send out the command to the sensor and also wait for the command
	// response. An alternative way of receiving the sensor's latest
	// measurements without the waiting for a query response, you can configure
	// the library to alert you when new asynchronous data measurements are
	// received. We will illustrate hooking up to our current VnSensor to
	// receive these notifications of asynchronous messages.

	// First let's configure the sensor to output a known asynchronous data
	// message type.

	//vs.writeAsyncDataOutputType(VNYPR);

	// To try a different sensor output type, comment out the line for VNYPR and
  // uncomment one of the GPS output types

	//vs.writeAsyncDataOutputType(VNGPS);
  //vs.writeAsyncDataOutputType(VNG2S);
/*
	vs.writeAsyncDataOutputType(VNACC); //Panda: this is to try sensor's acceleration outputs
	//vs.writeAsyncDataOutputType(VNISL); //Panda: this is to try sensor's velocity outputs #DOES NOT WORK
	AsciiAsync asyncType = vs.readAsyncDataOutputType();
	cout << "ASCII Async Type: " << asyncType << endl;

	// You will need to define a method which has the appropriate
	// signature for receiving notifications. This is implemented with the
	// method asciiAsyncMessageReceived. Now we register the method with the
	// VnSensor object.
	vs.registerAsyncPacketReceivedHandler(NULL, asciiAsyncMessageReceived);

	// Now sleep for 5 seconds so that our asynchronous callback method can
	// receive and display receive yaw, pitch, roll packets.
	cout << "Starting sleep..." << endl;

	Thread::sleepSec(5);

	// Unregister our callback method.
	vs.unregisterAsyncPacketReceivedHandler();
*/
	// As an alternative to receiving notifications of new ASCII asynchronous
	// messages, the binary output configuration of the sensor is another
	// popular choice for receiving data since it is compact, fast to parse,
	// and can be output at faster rates over the same connection baudrate.
	// Here we will configure the binary output register and process packets
	// with a new callback method that can handle both ASCII and binary
	// packets.

	// First we create a structure for setting the configuration information
	// for the binary output register to send yaw, pitch, roll data out at
	// 4 Hz.
	BinaryOutputRegister bor(
		ASYNCMODE_PORT1,
		200,
		COMMONGROUP_TIMESTARTUP | COMMONGROUP_ACCEL | COMMONGROUP_YAWPITCHROLL,	// Note use of binary OR to configure flags.
		TIMEGROUP_NONE,
		IMUGROUP_NONE,
    GPSGROUP_NONE,
		ATTITUDEGROUP_NONE,
		INSGROUP_NONE,
    GPSGROUP_NONE);

	vs.writeBinaryOutput1(bor);

	vs.registerAsyncPacketReceivedHandler(NULL, asciiOrBinaryAsyncMessageReceived);

	cout << "Starting sleep..." << endl;
	Thread::sleepSec(20);

	vs.unregisterAsyncPacketReceivedHandler();

	vs.disconnect();

	return 0;
}

// This is our basic callback handler for notifications of new asynchronous
// data packets received. The userData parameter is a pointer to the data we
// supplied when we called registerAsyncPacketReceivedHandler. In this case
// we didn't need any user data so we just set this to NULL. Alternatively you
// can provide a pointer to user data which you can use in the callback method.
// One use for this is help in calling back to a member method instead of just
// a global or static method. The Packet p parameter is an encapsulation of
// the data packet. At this state, it has already been validated and identified
// as an asynchronous data message. However, some processing is required on the
// user side to make sure it is the right type of asynchronous message type so
// we can parse it correctly. The index parameter is an advanced usage item and
// can be safely ignored for now.
void asciiAsyncMessageReceived(void* userData, Packet& p, size_t index)
{
  // Make sure we have an ASCII packet and not a binary packet.
  if(p.type() != Packet::TYPE_ASCII)
    return;

  // Make sure we have a VNYPR data packet.
  if(p.determineAsciiAsyncType() == VNYPR) {

    // We now need to parse out the yaw, pitch, roll data.
    vec3f ypr;
    p.parseVNYPR(&ypr);

    // Now print out the yaw, pitch, roll measurements.
    cout << "ASCII Async YPR: " << ypr << endl;
  }

	//Panda's code
	if(p.determineAsciiAsyncType() == VNACC) {

    // We now need to parse out the acceleration data.
    vec3f accel;
    p.parseVNACC(&accel); //

    // Now print out the yaw, pitch, roll measurements.
    cout << "ASCII Async Acceleration: " << accel << endl;
  }

	//Panda's code
	if(p.determineAsciiAsyncType() == VNISL) {

		// We now need to parse out the acceleration data.
		vec3f vel;
		p.parseVNACC(&vel); //

		// Now print out the yaw, pitch, roll measurements.
		cout << "ASCII Async Velocity: " << vel << endl;
	}

  // If the VNGPS output type was selected, print out that data
  else if(p.determineAsciiAsyncType() == VNGPS) {

    double time;
    uint16_t week;
    uint8_t gpsFix;
    uint8_t numSats;
    vec3d lla;
    vec3f nedVel;
    vec3f nedAcc;
    float speedAcc;
    float timeAcc;

    p.parseVNGPS(&time, &week, &gpsFix, &numSats, &lla, &nedVel, &nedAcc, &speedAcc, &timeAcc);
    cout << "ASCII Async GPS: " << lla << endl;
		cout << "ASCII Async Time: " << time << endl;
		cout << "ASCII Async Week: " << week << endl;
		cout << "ASCII Async GPSFix: " << gpsFix << endl;
		cout << "ASCII Async nedVel: " << nedVel << endl;
		cout << "ASCII Async nedAcc: " << nedAcc << endl;
		cout << "ASCII Async speedAcc: " << speedAcc << endl;
		cout << "ASCII Async timeAcc: " << timeAcc << endl;
  }

  // If the VNG2S output type was selected, print out that data
  else if(p.determineAsciiAsyncType() == VNG2S) {
    double time;
    uint16_t week;
    uint8_t gpsFix;
    uint8_t numSats;
    vec3d lla;
    vec3f nedVel;
    vec3f nedAcc;
    float speedAcc;
    float timeAcc;

    p.parseVNGPS(&time, &week, &gpsFix, &numSats, &lla, &nedVel, &nedAcc, &speedAcc, &timeAcc);
    cout << "ASCII Async GPS2: " << lla << endl;
  }

  else {
    cout << "ASCII Async: Type(" << p.determineAsciiAsyncType() << ")" << endl;
  }
}

void asciiOrBinaryAsyncMessageReceived(void* userData, Packet& p, size_t index)
{
	if (p.type() == Packet::TYPE_ASCII && p.determineAsciiAsyncType() == VNACC)
	{
		vec3f accel;
		p.parseVNACC(&accel);
		// cout << "ASCII Async Acceleration from ASCII: " << accel << endl; --> Commented out for ease of tests
		return;
	}

	if (p.type() == Packet::TYPE_BINARY)
	{
		// First make sure we have a binary packet type we expect since there
		// are many types of binary output types that can be configured.
		if (!p.isCompatible(
			COMMONGROUP_TIMESTARTUP | COMMONGROUP_ACCEL | COMMONGROUP_YAWPITCHROLL,
			TIMEGROUP_NONE,
			IMUGROUP_NONE,
      GPSGROUP_NONE,
			ATTITUDEGROUP_NONE,
			INSGROUP_NONE,
      GPSGROUP_NONE))
      // Not the type of binary packet we are expecting.
			return;

		// Ok, we have our expected binary output packet. Since there are many
		// ways to configure the binary data output, the burden is on the user
		// to correctly parse the binary packet. However, we can make use of
		// the parsing convenience methods provided by the Packet structure.
		// When using these convenience methods, you have to extract them in
		// the order they are organized in the binary packet per the User Manual.
		uint64_t curr_timeStartup = p.extractUint64();
		vec3f ypr = p.extractVec3f();
		vec3f curr_accel = p.extractVec3f();
		float timestep;
		mat3f matrix = rotMatrix(ypr);
		
		if (prev_timeStartup == 0) {
			timestep = 0;
		}
		else {
			timestep = (float)(curr_timeStartup - prev_timeStartup);
		}
		timestep /= 1000000000.0; //timeStartup is in nano seconds multiply by 1e+09 to ger

		integrate(prev_accel, curr_accel, timestep);
		prev_accel = curr_accel;
		prev_timeStartup = curr_timeStartup;

	}
}

void integrate(vec3f prev_acc, vec3f curr_acc, float timestep) {

	vec3f velocity = timestep * ((curr_acc - prev_acc)/2.0);

//keeping a sum of all velocities calculated between timestep n and n-1
	sumVelocity += velocity;

	cout << "Binary Async Velocity: " << velocity << endl << endl;

}

mat3f rotMatrix(vec3f yawPitchRoll) {
	float yaw = yawPitchRoll[0];
	float pitch = yawPitchRoll[1];
	float roll = yawPitchRoll[2];

	float su = sin(roll);
	float cu = cos(roll);

	float sv = sin(pitch);
	float cv = cos(pitch);

	float sw = sin(yaw);
	float cw = cos(yaw);


	mat3f matrix( (cv * cw), (su * sv * cw - cu*sw), (su * sw + cu * sv * cw), (cv * sw), (cu * cv + su * sv * sw), (cu * sv * sw - su * cw), (-sv), (su * cv), (cu * cv) );

	return matrix; //returns inverse matrix
}
