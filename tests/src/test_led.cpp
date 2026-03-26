/**
 * @file test_led.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for Led class.
 *
 * @date 06/2024
 */

#include "led.hpp"
#include "mcu.hpp"
#include "target.hpp"

int main() {
    hal::mcu::init();
    Led led(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    for (;;) {
        led.toggle();
        hal::mcu::sleep(500);
    }
}
