/**
 * @file motor.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Motor class implementation.
 *
 * @date 06/2024
 */

#include "motor.hpp"
#include "utils.hpp"

#define BREAK_SPEED_THRESHOLD 5

Motor::Motor(
    void (*tim_init)(), TIM_HandleTypeDef* forward_tim_handle, uint8_t forward_tim_ch,
    TIM_HandleTypeDef* backward_tim_handle, uint8_t backward_tim_ch, int8_t min_speed, int8_t max_speed
) {
    this->forward_tim_handle = forward_tim_handle;
    this->forward_tim_ch = forward_tim_ch;
    this->backward_tim_handle = backward_tim_handle;
    this->backward_tim_ch = backward_tim_ch;
    this->min_speed = min_speed;
    this->max_speed = max_speed;
    // Inicializa o timer e os canais e deixa o duty cicle setado em 0%.
    tim_init();
    HAL_TIM_PWM_Start(forward_tim_handle, forward_tim_ch);
    HAL_TIM_PWM_Start(backward_tim_handle, backward_tim_ch);
    this->stop();
}

void Motor::set_speed(int8_t speed) {
    int8_t speed_convertida = utils::map(speed,this->min_speed, this->max_speed, -1000, 1000);
    if (speed_convertida >= 0) {
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle, this->forward_tim_ch, speed_convertida);
    }
    else {
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, -speed_convertida);
    }
}

void Motor::stop() {
    this->set_speed(0);
}
