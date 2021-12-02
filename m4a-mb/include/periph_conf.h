/*
 * Copyright (c) 2021 Mesh4all <mesh4all.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @ingroup         boards_m4a-mb
 *@{
 * @file
 * @brief           Peripheral MCU configuration for m4a_mb
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include <stdint.h>
#include "cpu.h"
#include "periph_cpu.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name Clock settings
 * @{
 * @brief   External oscillator and clock configuration
 *
 */
#define CLOCK_USE_PLL (1)
#define CLOCK_USE_XOSC32_DFLL (0)

#define GEN2_ULP32K (0)

#if CLOCK_USE_PLL
/* DO NOT EDIT; [PLL] output frequency */
/* [MUL] should be between 31 and 95, both numbers included */
#define CLOCK_PLL_MUL (47U)
/* [DIV] don't need to be changed by now but it can be adjusted */
/* for our requirements */
#define CLOCK_PLL_DIV (1U)
/* DO NOT EDIT; Generate the actual used core clock frequency */
#define CLOCK_CORECLOCK (((CLOCK_PLL_MUL + 1) * 1000000U) / CLOCK_PLL_DIV)
#elif CLOCK_USE_XOSC32_DFLL
/* DO NOT EDIT; 48 MHz core clock */
#define CLOCK_CORECLOCK (48000000U)
/* DO NOT EDIT; 32 kHz ext. oscillator */
#define CLOCK_XOSC32K (32768UL)
#define CLOCK_8MHZ (1)
#else
/* DO NOT EDIT */
#define CLOCK_DIV (1U)
#define CLOCK_CORECLOCK (8000000 / CLOCK_DIV)
#endif
/** @} */

/**
 * @name Timers
 * @{
 */

/**
 * @brief   Timer peripheral configuration
 */
static const tc32_conf_t timer_config[] = {
    {
        .dev = TC3,
        .irq = TC3_IRQn,
        .pm_mask = PM_APBCMASK_TC3,
        .gclk_ctrl = GCLK_CLKCTRL_ID_TCC2_TC3,
#if CLOCK_USE_PLL || CLOCK_USE_XOSC32_DFLL
        .gclk_src = SAM0_GCLK_1MHZ,
#else
        .gclk_src = SAM0_GCLK_MAIN,
#endif
        .flags = TC_CTRLA_MODE_COUNT16,
    },
    {
        .dev = TC4,
        .irq = TC4_IRQn,
        .pm_mask = PM_APBCMASK_TC4 | PM_APBCMASK_TC5,
        .gclk_ctrl = GCLK_CLKCTRL_ID_TC4_TC5,
#if CLOCK_USE_PLL || CLOCK_USE_XOSC32_DFLL
        .gclk_src = SAM0_GCLK_1MHZ,
#else
        .gclk_src = SAM0_GCLK_MAIN,
#endif
        .flags = TC_CTRLA_MODE_COUNT32,
    },
};

#define TIMER_0_MAX_VALUE 0xffff                /*!< -- */
#define TIMER_0_ISR isr_tc3                     /*!< Timer 0 ISR uses tc3 */
#define TIMER_1_ISR isr_tc4                     /*!< Timer 1 ISR uses tc4 */

/**
 * @brief Number of timers available, default: 2
 */
#define TIMER_NUMOF ARRAY_SIZE(timer_config)
/** @} */

/**
 * @name UART configuration
 * @{
 */

/**
 * @brief Settings for UART
 *
 * ## Pinout
 *
 * | UART | Function | GPIO pin  |
 * |:----:|----------|-----------|
 * | 0    | RX       | PA23      |
 * | ^    | TX       | PA22      |
 * | ^    | RTS      | Undefined |
 * | ^    | CTS      | Undefined |
 * | 1    | RX       | PA9       |
 * | ^    | TX       | PA8       |
 * | ^    | RTS      | Undefined |
 * | ^    | CTS      | Undefined |
 * | 2    | RX       | PA11      |
 * | ^    | TX       | PA10      |
 * | ^    | RTS      | Undefined |
 * | ^    | CTS      | Undefined |
 */
static const uart_conf_t uart_config[] = {
    {
        .dev = &SERCOM3->USART,
        .rx_pin = GPIO_PIN(PA, 23),
        .tx_pin = GPIO_PIN(PA, 22),
#ifdef MODULE_PERIPH_UART_HW_FC
        .rts_pin = GPIO_UNDEF,
        .cts_pin = GPIO_UNDEF,
#endif
        .mux = GPIO_MUX_C,
        .rx_pad = UART_PAD_RX_1,
        .tx_pad = UART_PAD_TX_0,
        .flags = UART_FLAG_NONE,
        .gclk_src = SAM0_GCLK_MAIN,
    },
    {
        .dev = &SERCOM4->USART,
        .rx_pin = GPIO_PIN(PB, 9),
        .tx_pin = GPIO_PIN(PB, 8),
#ifdef MODULE_PERIPH_UART_HW_FC
        .rts_pin = GPIO_UNDEF,
        .cts_pin = GPIO_UNDEF,
#endif
        .mux = GPIO_MUX_D,
        .rx_pad = UART_PAD_RX_1,
        .tx_pad = UART_PAD_TX_0,
        .flags = UART_FLAG_NONE,
        .gclk_src = SAM0_GCLK_MAIN,
    },
    {
        .dev = &SERCOM4->USART,
        .rx_pin = GPIO_PIN(PB, 11),
        .tx_pin = GPIO_PIN(PB, 10),
#ifdef MODULE_PERIPH_UART_HW_FC
        .rts_pin = GPIO_UNDEF,
        .cts_pin = GPIO_UNDEF,
#endif
        .mux = GPIO_MUX_D,
        .rx_pad = UART_PAD_RX_3,
        .tx_pad = UART_PAD_TX_2,
        .flags = UART_FLAG_NONE,
        .gclk_src = SAM0_GCLK_MAIN,
    },
};

#define UART_0_ISR isr_sercom3              /*!< UART 0 uses isr_sercom3 */
#define UART_1_ISR isr_sercom4              /*!< UART 1 uses isr_sercom4 */
#define UART_2_ISR isr_sercom5              /*!< UART 1 uses isr_sercom5 */

#define UART_NUMOF ARRAY_SIZE(uart_config)  /*!< Number of available UART ports */
/** @} */

/**
 * @name Enabled or Diabled PWM channels
 * @{
 */
#define PWM_0_EN 1              /*!< PWM 0 is enabled */
#define PWM_1_EN 0              /*!< PWM 1 is disabled */
#define PWM_2_EN 0              /*!< PWM 2 is disabled */

#if PWM_0_EN
/**
 * @brief By default only channel 0 is enabled
 *
 * ## Pinout
 *
 * | channel | pin  | TCC |
 * |:-------:|------|-----|
 * | 0       | PA12 | 0   |
 * | ^       | PA13 | 1   |
 */
static const pwm_conf_chan_t pwm_chan0_config[] = {
    {GPIO_PIN(PA, 12), GPIO_MUX_E, 0},
    {GPIO_PIN(PA, 13), GPIO_MUX_E, 1},
};
#endif
#if PWM_1_EN
/**
 * @brief Settings for PWM channel 1
 *
 * ## Pinout
 *
 * | channel | pin  | TCC |
 * |:-------:|------|-----|
 * | 1       | PB12 | 0   |
 * | ^       | PB13 | 1   |
 */
static const pwm_conf_chan_t pwm_chan1_config[] = {
    {GPIO_PIN(PB, 12), GPIO_MUX_E, 0},
    {GPIO_PIN(PB, 13), GPIO_MUX_E, 1},
};
#endif
#if PWM_2_EN
/**
 * @brief Settings for PWM channel 2
 *
 * ## Pinout
 *
 * | channel | pin  | TCC |
 * |:-------:|------|-----|
 * | 1       | PB02 | 0   |
 * | ^       | PB03 | 1   |
 */
static const pwm_conf_chan_t pwm_chan2_config[] = {
    {GPIO_PIN(PB, 02), GPIO_MUX_E, 0},
    {GPIO_PIN(PB, 03), GPIO_MUX_E, 1},
};
#endif
/** @} */

/**
 * @name PWM config
 * @{
 */

/**
 * @brief Setings for PWM peripheral
 */
static const pwm_conf_t pwm_config[] = {
#if PWM_0_EN
        {TCC_CONFIG(TCC2), pwm_chan0_config, ARRAY_SIZE(pwm_chan0_config), SAM0_GCLK_MAIN},
#endif
#if PWM_1_EN
        {TCC_CONFIG(TC4), pwm_chan1_config, ARRAY_SIZE(pwm_chan1_config), SAM0_GCLK_MAIN},
#endif
#if PWM_2_EN
        {TCC_CONFIG(TC6), pwm_chan2_config, ARRAY_SIZE(pwm_chan2_config), SAM0_GCLK_MAIN},
#endif
};

/**
 * @brief Number of PWM channels, by default only chan0
 */
#define PWM_NUMOF ARRAY_SIZE(pwm_config)
/** @} */

/**
 * @brief SPI configuration
 *
 * ## SPI Pinout
 *
 * | SPI | name | pin  |
 * |:---:|------|------|
 * | 0   | miso | PA4  |
 * | ^   | mosi | PA6  |
 * | ^   | clk  | PA7  |
 * | 1   | miso | PA16 |
 * | ^   | mosi | PA18 |
 * | ^   | clk  | PA19 |
 * | 2   | miso | PB16 |
 * | ^   | mosi | PB22 |
 * | ^   | clk  | PB23 |
 */
static const spi_conf_t spi_config[] = {
    {
        .dev = &SERCOM0->SPI,
        .miso_pin = GPIO_PIN(PA, 4),
        .mosi_pin = GPIO_PIN(PA, 6),
        .clk_pin = GPIO_PIN(PA, 7),
        .miso_mux = GPIO_MUX_D,
        .mosi_mux = GPIO_MUX_D,
        .clk_mux = GPIO_MUX_D,
        .miso_pad = SPI_PAD_MISO_0,
        .mosi_pad = SPI_PAD_MOSI_2_SCK_3,
        .gclk_src = SAM0_GCLK_MAIN,
#ifdef MODULE_PERIPH_DMA
        .tx_trigger = SERCOM0_DMAC_ID_TX,
        .rx_trigger = SERCOM0_DMAC_ID_RX,
#endif
    },
    {
        .dev = &SERCOM1->SPI,
        .miso_pin = GPIO_PIN(PA, 16),
        .mosi_pin = GPIO_PIN(PA, 18),
        .clk_pin = GPIO_PIN(PA, 19),
        .miso_mux = GPIO_MUX_C,
        .mosi_mux = GPIO_MUX_C,
        .clk_mux = GPIO_MUX_C,
        .miso_pad = SPI_PAD_MISO_0,
        .mosi_pad = SPI_PAD_MOSI_2_SCK_3,
        .gclk_src = SAM0_GCLK_MAIN,
#ifdef MODULE_PERIPH_DMA
        .tx_trigger = SERCOM1_DMAC_ID_TX,
        .rx_trigger = SERCOM1_DMAC_ID_RX,
#endif
    },
    {
        .dev = &SERCOM5->SPI,
        .miso_pin = GPIO_PIN(PB, 16),
        .mosi_pin = GPIO_PIN(PB, 22),
        .clk_pin = GPIO_PIN(PB, 23),
        .miso_mux = GPIO_MUX_C,
        .mosi_mux = GPIO_MUX_D,
        .clk_mux = GPIO_MUX_D,
        .miso_pad = SPI_PAD_MISO_0,
        .mosi_pad = SPI_PAD_MOSI_2_SCK_3,
        .gclk_src = SAM0_GCLK_MAIN,
#ifdef MODULE_PERIPH_DMA
        .tx_trigger = SERCOM5_DMAC_ID_TX,
        .rx_trigger = SERCOM5_DMAC_ID_RX,
#endif
    },
};

/**
 * @name Number of SPI
 * @{
 */
#define SPI_NUMOF ARRAY_SIZE(spi_config)                /*!< 3 SPI are available */
/** @} */

/**
 * @brief I2C configuration
 * 
 * ## Pinout
 * 
 * | device | name | pin |
 * |--------|------|-----|
 * | I2C_0  | SCL  | PA9 |
 * | I2C_0  | SDA  | PA8 |
 */
static const i2c_conf_t i2c_config[] = {
    {
        .dev = &(SERCOM2->I2CM),
        .speed = I2C_SPEED_NORMAL,
        .scl_pin = GPIO_PIN(PA, 9),
        .sda_pin = GPIO_PIN(PA, 8),
        .mux = GPIO_MUX_D,
        .gclk_src = SAM0_GCLK_MAIN,
        .flags = I2C_FLAG_NONE,
    },
};

/**
 * @name Number of I2C
 * @{
 */
#define I2C_NUMOF ARRAY_SIZE(i2c_config)                /*!< Number of I2C available */
/** @} */

/**
 * @name RTT configuration
 * @{
 */
#ifndef RTT_FREQUENCY
#define RTT_FREQUENCY (32768U)                          /*!< RTT is set to 32768 */
#endif
/** @} */

/**
 * @name ADC Configuration
 * @{
 */
#define ADC_PRESCALER ADC_CTRLB_PRESCALER_DIV512        /*!< Prescaler: DIV 512 */
#define ADC_NEG_INPUT ADC_INPUTCTRL_MUXNEG_GND          /*!< Neg. Input: GND */
#define ADC_GAIN_FACTOR_DEFAULT ADC_INPUTCTRL_GAIN_1X   /*!< Gain Factor: 1x */
#define ADC_REF_DEFAULT ADC_REFCTRL_REFSEL_INT1V        /*!< Reference: Internal 1.0 Volt */
/** @} */

/**
 * @brief ADC channels
 *
 * ## [A]nalog-to-[D]igital [C]onverter
 *
 * ### Pinout
 *
 * | Channel | GPIO pin |
 * |:-------:|----------|
 * | 0       | PB0      |
 * | 1       | PB1      |
 * | 2       | PA10     |
 * | 3       | PA11     |
 * | 4       | PA2      |
 * | 5       | PA3      |
 */
static const adc_conf_chan_t adc_channels[] = {
    {GPIO_PIN(PB, 0), ADC_INPUTCTRL_MUXPOS_PIN8},
    {GPIO_PIN(PB, 1), ADC_INPUTCTRL_MUXPOS_PIN9},
    {GPIO_PIN(PA, 10), ADC_INPUTCTRL_MUXPOS_PIN18},
    {GPIO_PIN(PA, 11), ADC_INPUTCTRL_MUXPOS_PIN19},
    {GPIO_PIN(PA, 2), ADC_INPUTCTRL_MUXPOS_PIN0},
    {GPIO_PIN(PA, 3), ADC_INPUTCTRL_MUXPOS_PIN1},
};

/**
 * @name Number of ADC channels
 * @{
 */
#define ADC_NUMOF ARRAY_SIZE(adc_channels)              /*!< Number of ADC channels is 6*/
/** @} */

/**
 * @name DAC Settings
 * @{
 */
#define DAC_CLOCK SAM0_GCLK_1MHZ                        /*!< Uses 1 MHz clock*/
#define DAC_VREF DAC_CTRLB_REFSEL_AVCC                  /*!< Select VCC as reference */
/** @} */

/**
 * @brief USB peripheral settings
 *
 * ### Pinout
 *
 * | function | pin  |
 * |----------|------|
 * | D-       | PA24 |
 * | D+       | PA25 |
 */
static const sam0_common_usb_config_t sam_usbdev_config[] = {
    {
        .dm = GPIO_PIN(PA, 24),
        .dp = GPIO_PIN(PA, 25),
        .d_mux = GPIO_MUX_G,
        .device = &USB->DEVICE,
        .gclk_src = SAM0_GCLK_MAIN,
    },
};

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
