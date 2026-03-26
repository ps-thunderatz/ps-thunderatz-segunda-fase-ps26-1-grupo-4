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

Controller::Controller(Led led, Locomotion locomotion, Rc rc)
    : led(led), locomotion(locomotion), rc(rc) {}

void Controller::init() {
    this->current_state = INIT;
    this->current_level = LEVEL_0;
    this->turn = STOPPED;
}

void Controller::run() {
    switch (this->current_state) {
        case INIT: {
            // Exemplo de debug:
            led.on();

            this->current_state = STRATEGY_CHOOSER;
            break;
        }

        case STRATEGY_CHOOSER: {

            int x = 0;
            int y = 0;

            if (x < -50) {
                this->current_level = LEVEL_0;
            }
            else if (y > 50) {
                this->current_level = LEVEL_1;
            }
            else if (x > 50) {
                this->current_level = LEVEL_2;
            }
            else if (y < -50) {
                this->current_level = LEVEL_3;
            }

            bool start_command = false;

            if (start_command) {
                this->current_state = RUN;
            }

            move_robot(STOPPED);
            break;
        }

        case RUN: {
            int x = 0;
            int y = 0;

            if (x == -100 && y == -100) {
                move_robot(BACKWARD);
                break;
            }

            strategy_run();
            break;
        }

        case STOP: {
            move_robot(STOPPED);
            break;
        }

        default: {
            this->current_state = STOP;
            move_robot(STOPPED);
            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        case FORWARD: {
            locomotion.set_speed(70, 70);
            break;
        }

        case BACKWARD: {

            locomotion.set_speed(-70, -70);
            break;
        }

        case LEFT: {

            locomotion.set_speed(-70, 70);
            break;
        }

        case RIGHT: {

            locomotion.set_speed(70, -70);
            break;
        }

        case STOPPED: {

            locomotion.stop();
            break;
        }

        case RC_INPUT: {
            int x = 0;
            int y = 0;

            int left = y + x;
            int right = y - x;

            int left = (y + x) * 70/100;
            int right = (y - x) * 70/100;

            locomotion.set_speed(left, right);
            break;
        }

        default: {
            locomotion.stop();
            break;
        }
    }
}

void Controller::set_next_strategy() {
    this->current_level++;

    if (this->current_level >= this->max_strategy) {
        this->current_level = 0;
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
            break;
        }

        case LEVEL_2: {

            move_robot(RIGHT);
            break;
        }

        case LEVEL_3: {

            move_robot();
            break;
        }

        default: {
            move_robot(STOPPED);
            this->current_state = STOP;
            break;
        }
    }
}
