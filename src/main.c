#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_timer.h"
#include "../inc/myEmbededTemp.h"
#include "../inc/myTemp.h"
#include "../inc/myOled.h"
#include "../inc/myJoystick.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "LPC17xx.h"
#include "../inc/eeprom.h"

static uint32_t msTicks = 0;
void SysTick_Handler(void) { msTicks++; }
uint32_t getTicks(void) { return msTicks; }

void init_i2c(void) {
    PINSEL_CFG_Type PinCfg;
    // SCL (P0.19)
    PinCfg.Funcnum = 3;
    PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
    PinCfg.Pinnum = 19;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);

    // SDA (P0.27)
    PinCfg.Pinnum = 27;
    PINSEL_ConfigPin(&PinCfg);

    I2C_Init(LPC_I2C1, 100000);
    I2C_Cmd(LPC_I2C1, ENABLE);
}

void init_ssp(void) {
    PINSEL_CFG_Type PinCfg;

    // P0.7 - SCK1
    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
    PinCfg.Pinnum = 7;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);

    // P0.8 - MISO1
    PinCfg.Pinnum = 8;
    PINSEL_ConfigPin(&PinCfg);

    // P0.9 - MOSI1
    PinCfg.Pinnum = 9;
    PINSEL_ConfigPin(&PinCfg);

    // CS (chip select) – osobny GPIO, np. P0.6
    LPC_GPIO0->FIODIR |= (1 << 6); // Ustaw jako wyjście
    LPC_GPIO0->FIOSET |= (1 << 6); // Ustaw stan wysoki (nieaktywne)

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
