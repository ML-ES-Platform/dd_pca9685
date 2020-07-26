/*
 * dd_servo_demo.cpp
 *
 *  Created on: May 11, 2020
 *      Author: Andrei Bragarenco
 */
 
#include "dd_pca9685_demo.h"
#include "dd_pca9685.h"


#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define PWM_MIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define PWM_MAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define PCA9685_PWM_FREQ 50 // Analog servos run at ~50 Hz updates

//The setup function is called once at startup of the sketch
void dd_pca9685_demo_setup() {
// Add your initialization code here
	Serial.begin(9600);
	Serial.println("DD pca9685 demo !");
	Std_ReturnType error = E_OK;

	error = PCA9685_DeviceInit(PCA9685_PWM_FREQ);

	error += DD_PCA9685_ChannelSetup(PCA9685_PWM_1, 0);
	error += DD_PCA9685_ChannelSetup(PCA9685_PWM_2, 4);
	error += DD_PCA9685_ChannelSetup(PCA9685_PWM_3, 6);
	// error += DD_PCA9685_ChannelSetup(PCA9685_PWM_4, 11);

	Serial.print("DD pca9685 configured - Error : ");
	Serial.println(error);

	delay(10);
}

void dd_pca9685_demo_loop() {

	// our channel # counter
	static uint8_t channelNum = 0;

	Serial.print("DD pca9685 -> Operating channel : ");
	Serial.println(channelNum);

//  // Drive each servo one at a time using setPWM()
//  Serial.println(servoNum);
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
//    dd_pca9685.setPWM(servoNum, 0, pulselen);
//  }
//
//  delay(500);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//    dd_pca9685.setPWM(servoNum, 0, pulselen);
//  }
//
//  delay(500);

// Drive each servo one at a time using writeMicroseconds(), it's not precise due to calculation rounding!
// The writeMicroseconds() function is used to mimic the Arduino Servo library writeMicroseconds() behavior.
	for (uint16_t microsec = PWM_MIN; microsec < PWM_MAX; microsec++) {
		PCA9685_WriteChannel(channelNum, microsec);
	}

	delay(500);
	for (uint16_t microsec = PWM_MAX; microsec > PWM_MIN; microsec--) {
		PCA9685_WriteChannel(channelNum, microsec);
	}

	delay(500);

	channelNum++;
	if (channelNum >= DD_PCA9685_CHANNEL_NR_OF)
		channelNum = 0; // Testing the first 8 servo channels
}
