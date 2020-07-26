/*
 * dd_pca9685.h
 *
 *  Created on: May 10, 2020
 *      Author: Andrei Bragarenco
 */

#ifndef _DD_PCA9685_H_
#define _DD_PCA9685_H_


#include "dd_pca9685_cfg.h"

enum PCA9685_PinType {PCA9685_PIN_1,PCA9685_PIN_2, PCA9685_PIN_3, PCA9685_PIN_NR_OF};


#ifndef DD_PCA9685_CONFIG
enum DD_PCA9685_IdType { PCA9685_CHANNEL_NR_OF = 0};
#endif


typedef struct PCA9685_ChannelType_t{
	uint8_t pwm_pin;
}  PCA9685_ChannelType;

Std_ReturnType PCA9685_DeviceInit(Std_PhyDataType pwmFreq);

Std_ReturnType DD_PCA9685_ChannelSetup(Std_ChannelIdType channelId, uint8_t pwm_pin);
Std_ReturnType PCA9685_GroupSetup(Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels);

PCA9685_ChannelType * PCA9685_GetChannelRef(Std_ChannelIdType channelId);
Std_ReturnType PCA9685_WriteChannelByRef( PCA9685_ChannelType * channelRef, Std_RawDataType pulse);
Std_ReturnType PCA9685_WriteChannel( Std_ChannelIdType channelId, Std_RawDataType pulse);


#endif /* _DD_PCA9685_H_ */
