/*
 * Gyro_Driver.c
 *
 *  Created on: Apr 9, 2025
 *      Author: joelrsilva
 */


#include "Gyro_Driver.h"
#include <stdlib.h>
#include "stm32f4xx_hal_spi.h"

extern SPI_HandleTypeDef hspi5;
static HAL_StatusTypeDef HAL_Status;

void Gyro_Init(){
    Gyro_Power_On();
    //HAL_Delay(100);
    Gyro_Config_Regs();
    Gyro_Reboot();
}

void Gyro_Power_On(){
    uint8_t cmd = (GYRO_READ | CTRL_REG1);
    uint8_t rx_buff = 0;
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&cmd);
    Gyro_Receive_Data(&rx_buff);
    Gyro_Slave_Disable();

    cmd = (GYRO_WRITE | CTRL_REG1);
    uint8_t tx_buff = (rx_buff | (1 << 3));
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&cmd);
    Gyro_Transmit_Data(&tx_buff);
    Gyro_Slave_Disable();

    if (HAL_Status != HAL_OK) {
        printf("HAL NOT OK\n");
        while(1);
    }
}

void Gyro_Reboot(){
    uint8_t cmd = (GYRO_READ | CTRL_REG5);
    uint8_t rx_buff = 0;
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&cmd);
    Gyro_Receive_Data(&rx_buff);
    Gyro_Slave_Disable();

    cmd = (GYRO_WRITE | CTRL_REG5);
    uint8_t tx_buff = (rx_buff | (1 << 7));
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&cmd);
    Gyro_Transmit_Data(&tx_buff);
    Gyro_Slave_Disable();
}

int16_t Gyro_Get_Velocity(){
    int16_t yval = 0;
    uint8_t cmd = (GYRO_READ | MS_BIT | OUT_Y_L);
    uint8_t rxbuff_yl = 0;
    uint8_t rxbuff_yh = 0;

    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&cmd);
    Gyro_Receive_Data(&rxbuff_yl);
    Gyro_Receive_Data(&rxbuff_yh);
    Gyro_Slave_Disable();

    yval = (int16_t)((rxbuff_yh << 8) | rxbuff_yl);
    return yval;
}

void Gyro_Config_Regs(){
    uint8_t addr_cmd = (GYRO_WRITE | CTRL_REG1);
    uint8_t reg_cmd = 0x1A;
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&addr_cmd);
    Gyro_Transmit_Data(&reg_cmd);
    Gyro_Slave_Disable();

    addr_cmd = (GYRO_WRITE | CTRL_REG4);
    reg_cmd = 0x10;
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&addr_cmd);
    Gyro_Transmit_Data(&reg_cmd);
    Gyro_Slave_Disable();

    addr_cmd = (GYRO_WRITE | CTRL_REG5);
    reg_cmd = 0xC0;
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&addr_cmd);
    Gyro_Transmit_Data(&reg_cmd);
    Gyro_Slave_Disable();

    addr_cmd = (GYRO_WRITE | FIFO_CTRL_REG);
    reg_cmd = 0x00;
    Gyro_Slave_Enable();
    Gyro_Transmit_Data(&addr_cmd);
    Gyro_Transmit_Data(&reg_cmd);
    Gyro_Slave_Disable();
}

void Gyro_HAL_Check(){
    if (HAL_Status != HAL_OK) {
        printf("HAL Error: %d\n", HAL_Status);
        while(1);
    }
}

void Gyro_Slave_Enable(){
    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
}

void Gyro_Slave_Disable(){
    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

void Gyro_Receive_Data(uint8_t *rx_buff){
    HAL_Status = HAL_SPI_Receive(&hspi5, rx_buff, 1, TIMEOUT);
    Gyro_HAL_Check();
}

void Gyro_Transmit_Data(uint8_t *tx_buff){
    HAL_Status = HAL_SPI_Transmit(&hspi5, tx_buff, 1, TIMEOUT);
    Gyro_HAL_Check();
}
