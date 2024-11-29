/*
 * sensor.c
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */
#include "sensor.h"

uint16_t adc_receive[5];

void sensor_init(){
	HAL_ADC_Start_DMA(&hadc1, (uint16_t*)adc_receive, 5);
}

void sensor_Read(){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_receive, 5);
}

uint16_t sensor_GetLight(){//do sang
	return adc_receive[2];
}

uint16_t sensor_GetPotentiometer(){
	return adc_receive[3];
}

float sensor_GetVoltage(){
	return ((float)adc_receive[0]*3.3*12)/(4095*1.565);
}

float sensor_GetCurrent(){
	return (((float)adc_receive[1]*3.3*1000)/(4095*0.647)-2.5)*5/2.5;
}

float sensor_GetTemperature(){//Nhiet do
	return ((float)adc_receive[4]*330)/(4095);
}

float getWattage(){
	return sensor_GetVoltage() * sensor_GetCurrent();
}

uint16_t isLight(){//> 0.5 nguoc anh sang manh
	if((float)sensor_GetLight()/4095 > 0.5)
		return 1;
	return 0;
}

uint16_t isHumidity(){//Do am (nut van bien tro)
	if((float)sensor_GetPotentiometer()/4094 > 0.7)
		return 1;
	return 0;
}
