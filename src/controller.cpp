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

Controller::Controller(Led led, Locomotion locomotion, Rc rc) {
    this->led = led;
    this->locomotion = locomotion;
    this->rc = rc;
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
            this->set_next_strategy();
            break;
        }
        case RUN: {
            this->strategy_run();
            break;
        }
        default: {
            this->move_robot(STOPPED);
            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        case FORWARD: {
            this->locomotion.set_speed(70, 70);
            break;
        }
        case BACKWARD: {
            this->locomotion.set_speed(-70, -70);
            break;
        }
        case LEFT: {
            this->locomotion.set_speed(-70, 70);
            break;
        }
        case RIGHT: {
            this->locomotion.set_speed(70, -70);
            break;
        }
        case STOPPED: {
            this->locomotion.stop();
            break;
        }
        case RC_INPUT: {
            int16_t ch1 = this->rc.get_speed_ch1();
            int16_t ch2 = this->rc.get_speed_ch2();
            this->locomotion.set_speed((int8_t)ch1, (int8_t)ch2);
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
            move_robot(FORWARD);
            break;
        }
        case LEVEL_1: {
            move_robot(RIGHT);
            break;
        }
        case LEVEL_2: {
            //move_robot(FORWARD);
            break;
        }
        case LEVEL_3: {
            move_robot(RC_INPUT);
            break;
        }
        default: {
            move_robot(STOPPED);
            this->current_state = STOP;
            break;
        }
    }
}
