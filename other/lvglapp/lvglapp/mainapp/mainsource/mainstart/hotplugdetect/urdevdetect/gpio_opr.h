/*
 * gpio_opr.h
 *
 *  Created on: 2021年5月15日
 *      Author: careyZeng
 */
#ifndef _JNI_GPIO_OPR_H_
#define _JNI_GPIO_OPR_H_



int get_gpio_in_state(int gpionum);
void set_gpio_out_state(int gpionum, int iostate);
void release_gpio(int gpionum);


#endif/*_JNI_GPIO_OPR_H_*/
