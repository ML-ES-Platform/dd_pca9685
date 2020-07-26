/*
 * dd_pca9685.cpp
 *
 *  Created on: May 10, 2020
 *      Author: Andrei Bragarenco
 */


#include "dd_pca9685.h"


#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver dd_pca9685 = Adafruit_PWMServoDriver();

PCA9685_ChannelType PCA9685_Channels[DD_PCA9685_CHANNEL_NR_OF];

#define PCA9685_PWM_FREQ 50 // Analog servos run at ~50 Hz updates


Std_ReturnType PCA9685_DeviceInit(Std_PhyDataType pwmFreq){
	  dd_pca9685.begin();
	  // In theory the internal oscillator is 25MHz but it really isn't
	  // that precise. You can 'calibrate' by tweaking this number till
	  // you get the frequency you're expecting!
	  dd_pca9685.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
	  dd_pca9685.setPWMFreq(pwmFreq);  // Analog servos run at ~50 Hz updates
	  return E_OK;
}



PCA9685_ChannelType * PCA9685_GetChannelRef(Std_ChannelIdType channelId){
	PCA9685_ChannelType *channelRef = &PCA9685_Channels[channelId];
	return channelRef;

}

Std_ReturnType DD_PCA9685_ChannelSetup(Std_ChannelIdType channelId, uint8_t pwm_pin){
	Std_ReturnType error;
	if (channelId < DD_PCA9685_CHANNEL_NR_OF) {
		PCA9685_ChannelType *channelRef = PCA9685_GetChannelRef(channelId);
		channelRef->pwm_pin = pwm_pin;
		error = E_OK;
	} else {
		error = E_NOT_OK;
	}
	return error;

}


Std_ReturnType PCA9685_GroupSetup(Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		Std_ChannelIdType targhetId = targhetIds[i];
		error += DD_PCA9685_ChannelSetup(srcId, targhetId);
	}
	return error;
}


Std_ReturnType PCA9685_WriteChannelByRef( PCA9685_ChannelType * channelRef, Std_RawDataType pulse){
	dd_pca9685.writeMicroseconds(channelRef->pwm_pin, pulse);
	return E_OK;
}

Std_ReturnType PCA9685_WriteChannel( Std_ChannelIdType channelId, Std_RawDataType pulse){
	PCA9685_ChannelType *channelRef = PCA9685_GetChannelRef(channelId);
	Std_ReturnType error = PCA9685_WriteChannelByRef(channelRef, pulse );
	return error;
}

