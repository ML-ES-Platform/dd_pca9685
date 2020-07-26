/*
 * dd_pca9685_cfg.h
 *
 *  Created on: May 10, 2020
 *      Author: Andrei Bragarenco
 */

#ifndef _DD_PCA9685_CFG_H_
#define _DD_PCA9685_CFG_H_

#include "platform_config.h"

#ifndef DD_PCA9685_CONFIG
#define DD_PCA9685_CONFIG
//for demo application purpose
//shall be defined in the platform
enum DD_PCA9685_IdType {PCA9685_PWM_1,PCA9685_PWM_2, PCA9685_PWM_3, PCA9685_PWM_4, DD_PCA9685_CHANNEL_NR_OF};
#endif

#endif /* _DD_PCA9685_CFG_H_ */
