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
    hal::mcu::init();
    Led led(GPIOA, GPIO_PIN_4);

    Motor leftMotor(
        MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH
    );

    Motor rightMotor(
        MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER,
        RIGHT_MOTOR_BACKWARD_TIM_CH
    );

    Locomotion locomotion(leftMotor, rightMotor);

    for (;;) {
        //Para frente
        led.on();
        locomotion.set_speed(-70, -70);
        HAL_Delay(2000);

        locomotion.set_speed(-50, -50);
        HAL_Delay(2000);

        locomotion.set_speed(-30, -30);
        HAL_Delay(2000);

        locomotion.set_speed(-50, -50);
        HAL_Delay(2000);
        /*

        //Parar
        locomotion.stop();
        HAL_Delay(700);

        //Para trás
        led.toggle();
        locomotion.set_speed(70, 70);
        HAL_Delay(2000);

        //Parar
        locomotion.stop();
        HAL_Delay(700);

        //Para direita
        led.toggle();
        locomotion.set_speed(70, -70);
        HAL_Delay(1500);

        //Parar
        locomotion.stop();
        HAL_Delay(700);

        //Para esquerda
        led.toggle();
        locomotion.set_speed(-70, 70);
        HAL_Delay(1500);

        //Parar
        locomotion.stop();
        HAL_Delay(700);
        */
    }
}
