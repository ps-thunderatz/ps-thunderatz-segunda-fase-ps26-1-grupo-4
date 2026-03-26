/**
 * @file test_motors.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for Motors class.
 *
 * @date 06/2024
 */

#include "motor.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "led.hpp"

int main() {
    hal::mcu::init();

    Motor leftMotor(
        MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER,
        LEFT_MOTOR_BACKWARD_TIM_CH
    );

    Motor rightMotor(
        MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER,
        RIGHT_MOTOR_BACKWARD_TIM_CH
    );


    for (;;) {
        leftMotor.set_speed(70);
        rightMotor.set_speed(70);
        mcu::sleep(1000);

        leftMotor.set_speed(-70);
        rightMotor.set_speed(-70);
        mcu::sleep(1000);
    }
}
