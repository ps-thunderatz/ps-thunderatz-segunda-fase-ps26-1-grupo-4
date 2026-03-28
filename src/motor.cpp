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
    int32_t speed_convertida = abs(constrain(speed, this->min_speed, this->max_speed));
    auto forward_auto_reload = __HAL_TIM_GET_AUTORELOAD(forward_tim_handle);
    auto backward_auto_reload = __HAL_TIM_GET_AUTORELOAD(backward_tim_handle);
    auto forward_count = map<uint32_t>(speed_convertida, 0, this->max_speed, 0, forward_auto_reload);
    auto backward_count = map<uint32_t>(speed_convertida, 0, this->max_speed, 0, backward_auto_reload);

    if (abs(speed) <= BREAK_SPEED_THRESHOLD) {
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle, this->forward_tim_ch, forward_auto_reload);
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, backward_auto_reload);
        return;
    }
    if (speed >= 0) {
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle, this->forward_tim_ch, forward_count);
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, 0);
    }
    else {
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle, this->forward_tim_ch, 0);
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, backward_count);
    }
}

void Motor::stop() {
    this->set_speed(0);
}
