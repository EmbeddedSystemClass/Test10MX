/*
 * testdf1.c
 *
 *  Created on: 22.10.2018
 *      Author: Dirk
 */

#include <stdio.h>
#include <string.h>
#include "testdf1.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "xprintf.h"

static void Tast01(const void *params);
static void Task02(const void *params);

osThreadId Task01TaskHandle;
osThreadId Task02TaskHandle;

void Task01_Init(void)
{
    // Create task
    osThreadDef(Task01ThreadDef, Tast01, osPriorityNormal, 0, 256);
    Task01TaskHandle = osThreadCreate(osThread(Task01ThreadDef), NULL);
    if (Task01TaskHandle == NULL) {
        printf("Failed to create LCD task.\n");
    }
}

void Task02_Init(void)
{
    // Create task
    osThreadDef(Task02ThreadDef, Task02, osPriorityNormal, 0, 256);
    Task02TaskHandle = osThreadCreate(osThread(Task02ThreadDef), NULL);
    if (Task02TaskHandle == NULL) {
        printf("Failed to create LCD task.\n");
    }
}

static void Tast01(const void *params)
{
	while(1)
	{
		static uint32_t c=200;

		c=c-5;
		if(c<30)
			c=200;
		xprintf("%d ms\n",c);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET );
		osDelay(c);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		osDelay(c);
	}
}

static void Task02(const void *params)
{
	while(1)
	{
//		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		xprintf("    -> TASK02\n");
		osDelay(500);
//		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
//		osDelay(500);
//		if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
//			print("ok");
        printf("Task02.\n");
	}
}


