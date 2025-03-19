#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_timer.h"
#include "../inc/myEmbededTemp.h"
#include "../inc/myTemp.h"
#include "../inc/myOled.h"
#include "../inc/myJoystick.h"

static uint32_t msTicks = 0;
void SysTick_Handler(void) { msTicks++; }
uint32_t getTicks(void) { return msTicks; }

static void init_i2c(void) {
    PINSEL_CFG_Type PinCfg;
    PinCfg.Funcnum = 1; PinCfg.Pinnum = 19; PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 20;
    PINSEL_ConfigPin(&PinCfg);
    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, ENABLE);
}

static void init_ssp(void) {
    PINSEL_CFG_Type PinCfg;
    PinCfg.Funcnum = 2; PinCfg.Pinnum = 22; PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 23; PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 24; PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 28; PinCfg.Funcnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    SSP_CFG_Type SSP_ConfigStruct;
    SSP_ConfigStructInit(&SSP_ConfigStruct);
    SSP_ConfigStruct.ClockRate = 1000000;
    SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
    SSP_Cmd(LPC_SSP1, ENABLE);
}

int main(void) {
    int embeded_temp, external_temp;
    uint8_t buf[16];
    uint8_t flag = 1;

    init_i2c();
    init_ssp();
    oled_init();
    joystick_init();
    temp_init(&getTicks);
    SysTick_Config(SystemCoreClock / 1000);

    oled_clearScreen(OLED_COLOR_WHITE);

    while (1) {
        uint8_t joy = joystick_read();
        if (joy == JOYSTICK_LEFT) flag = 1;
        if (joy == JOYSTICK_RIGHT) flag = 2;
        if (joy == JOYSTICK_CENTER) flag = 0;

        if (flag == 1) { // TEMPERATURE SCREEN
            embeded_temp = temp_read();
            sprintf(buf, "%02d.%d C", embeded_temp / 10, embeded_temp % 10);
            oled_fillRect(55, 1, 80, 8, OLED_COLOR_WHITE);
            oled_putString(55, 1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

            external_temp = Mytemp_read();
            sprintf(buf, "%02d.%d C", external_temp >> 1, (external_temp % 2) * 5);
            oled_fillRect(55, 9, 80, 16, OLED_COLOR_WHITE);
            oled_putString(55, 9, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
        }
    }
}
