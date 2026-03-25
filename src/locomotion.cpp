/**
 * @file locomotion.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief locomotion class implementation.
 *
 * @date 04/2025
 */

#include "locomotion.hpp"

Locomotion::Locomotion(Motor& motor_left, Motor& motor_right) {
    this->stop();
    this->motor_left = motor_left;
    this->motor_right = motor_right;
}

void Locomotion::set_speed(int8_t left_speed, int8_t right_speed) {
    this->motor_left.set_speed(left_speed);
    this->motor_right.set_speed(right_speed);
}

void Locomotion::stop() {
    this->motor_left.stop();
    this->motor_right.stop();
}
