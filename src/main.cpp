#include <Arduino.h>
#include <TMCStepper.h>
#include <avr/io.h>

#define EN_PIN           10 // Enable
#define DIR_PIN          16 // Direction
#define STEP_PIN         14 // Step
#define SW_RX            0 // TMC2208/TMC2224 SoftwareSerial receive pin
#define SW_TX            1 // TMC2208/TMC2224 SoftwareSerial transmit pin
#define SERIAL_PORT Serial // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2

#define R_SENSE 0.11f // Match to your driver
// SilentStepStick series use 0.11
// UltiMachine Einsy and Archim2 boards use 0.2
// Panucatt BSD2660 uses 0.1
// Watterott TMC5160 uses 0.075

// Select your stepper driver type

TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2209Stepper driver(SW_RX, SW_TX, R_SENSE, DRIVER_ADDRESS);

void setup() {
	pinMode(EN_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
	digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

	// Enable one according to your setup
	//SPI.begin();                    // SPI drivers
	// SERIAL_PORT.begin(115200);      // HW UART drivers
	driver.beginSerial(115200);     // SW UART drivers

	driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
	// UART: Init SW UART (if selected) with default 115200 baudrate
	driver.toff(5);                 // Enables driver in software
	driver.rms_current(600);        // Set motor RMS current
	driver.microsteps(0);          // Set microsteps to 1/16th

	//driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
	//driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
	driver.pwm_autoscale(true);     // Needed for stealthChop
}

bool shaft = false;

void loop()
{

	uint32_t speed = 300;
	for (uint16_t i = 1000; i>0; i--)
	{
		digitalWrite(STEP_PIN, HIGH);
		delayMicroseconds(speed / 2);
		digitalWrite(STEP_PIN, LOW);
		delayMicroseconds(speed / 2);
	}
	// Serial.print("shaft : ");
	// Serial.println(shaft);
	// shaft = !shaft;
	// driver.shaft(shaft);
	// digitalWrite(DIR_PIN, shaft);
}
