/**
 * @file test_locomotion.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for locomotion class.
 *
 * @date 04/2025
 */

#include "motor.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "led.hpp"
#include "locomotion.hpp"

int main() {
    mcu::init();
    Led led(GPIOA, GPIO_PIN_4);
    locomotion locomotion(motor_left, motor_right);

    for (;;) {
        //Para frente
        led.on();
        locomotion.set_speed(100, 100);
        HAL_Delay(2000);

        //Parar
        locomotion.stop();
        HAL_Delay(1000);

        //Para trás
        led.toggle();
        locomotion.set_speed(-100, -100);
        HAL_Delay(2000);

        //Parar
        locomotion.stop();
        HAL_Delay(1000);

        //Para direita
        led.toggle();
        locomotion.set_speed(100, -100);
        HAL_Delay(1500);

        //Parar
        locomotion.stop();
        HAL_Delay(1000);

        //Para esquerda
        led.toggle();
        locomotion.set_speed(-100, 100);
        HAL_Delay(1500);

        //Parar
        locomotion.stop();
        HAL_Delay(1000);
    }
}
