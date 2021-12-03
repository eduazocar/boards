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
 * @ingroup   boards_m4a-mb
 * @{
 * @file
 * @brief     Board specific configuration of direct mapped GPIOs
 */
#ifndef GPIO_PARAMS_H
#define GPIO_PARAMS_H

#include "board.h"
#include "saul/periph.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * ## Saul GPIO params
 *
 * @brief Saul Settings
 * @see [[S]ensor [A]ctuator [U]ber [L]ayer](https://doc.riot-os.org/group__drivers__saul.html)
 * 
 * ### LED0
 *
 * @param name "LED (Orange)"
 * @param pin LED0_PIN
 * @param mode GPIO_OUT
 *
 * ### LED1
 *
 * @param name "LED (Green)"
 * @param pin LED1_PIN
 * @param mode SAUL_GPIO_INVERTED
 */
static const saul_gpio_params_t saul_gpio_params[] = {
    {
        .name = "LED (Orange)",
        .pin = LED0_PIN,
        .mode = GPIO_OUT,
    },
    {
        .name = "LED (Green)",
        .pin = LED1_PIN,
        .mode = GPIO_OUT,
        .flags = SAUL_GPIO_INVERTED,
    },
    {
        .name = "LED (Yellow)",
        .pin = LED2_PIN,
        .mode = GPIO_OUT,
        .flags = SAUL_GPIO_INVERTED,
    },
    {
        .name = "Button (SW0)",
        .pin = BTN0_PIN,
        .mode = BTN0_MODE,
    },
};

#ifdef __cplusplus
}
#endif

#endif /* GPIO_PARAMS_H */
/** @} */
