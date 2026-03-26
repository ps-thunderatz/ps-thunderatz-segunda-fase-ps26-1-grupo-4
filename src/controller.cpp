/**
 * @file controller.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Rock SemiAuto Controller Finite State Machine.
 *
 * @date 04/2025
 */

#include "mcu.hpp"
#include "controller.hpp"
#include "led.hpp"
#include "locomotion.hpp"
#include "rc.hpp"


Controller::Controller(Led led, locomotion locomotion, rc rc) : led(led), locomotion(locomotion), rc(rc) {
}

void Controller::init() {
    this->current_state = STRATEGY_CHOOSER;
    this->current_level = LEVEL_0;
    this->turn = STOPPED;
    this->led.off();
    this->move_robot(STOPPED);
}

void Controller::run() {
    switch (this->current_state) {
        case STRATEGY_CHOOSER: {
            set_next_strategy();
            break;
        }
        case RUN: {
            strategy_run();
            break;
        }

        default: {
            move_robot(STOPPED);

            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        case FORWARD: {
            this->locomotion.set_speed(100, 100);
            break;
        }
        case BACKWARD: {
            this->locomotion.set_speed(-100, -100);
            break;
        }
        case LEFT: {
            this->locomotion.set_speed(-100, 100);
            break;
        }
        case RIGHT: {
            this->locomotion.set_speed(100, -100);
            break;
        }
        case STOPPED: {
            this->locomotion.stop();
            break;
        }
        case RC_INPUT: {
            int16_t ch1 = this->rc.get_speed_ch1();
            int16_t ch2 = this->rc.get_speed_ch2();

            this->locomotion.set_speed(static_cast <int8_t>(ch1), <int8_t>(ch2));

            break;
        }
        default: {
            this->locomotion.stop();
            break;
        }
    }
}

void Controller::set_next_strategy() {
    int16_t ch1 = this->rc.get_speed_ch1();
    int16_t ch2 = this->rc.get_speed_ch2();

    if (ch1 > 50) {
        this->current_level = LEVEL_1;
        this->current_state = RUN;
    }
    else if (ch1 < -50) {
        this->current_level = LEVEL_2;
        this->current_state = RUN;
    }
    else if (ch2 > 50) {
        this->current_level = LEVEL_3;
        this->current_state = RUN;
    }
    else {
        this->current_level = LEVEL_0;
    }

}

void Controller::strategy_run() {
    switch (this->current_level) {
        case LEVEL_0: {
            move_robot(RC_INPUT);
            break;
        }
        case LEVEL_1: {
            move_robot(FORWARD);
            HAL_Delay(2000);
            this->current_level = LEVEL_0;
            break;
        }
        case LEVEL_2: {
            move_robot(RIGHT);
            HAL_Delay(2000);
            move_robot(STOPPED);
            this->current_level = LEVEL_0;
            break;
        }
        case LEVEL_3: {
            static uint32_t strategy_start_time = 0;
            static bool strategy_started = false;
            if (!strategy_started) {
                strategy_started = true;
                strategy_start_time = HAL_GetTick();
            }
        }
        default: {
            move_robot(STOPPED);
            break;
        }
    }
}
