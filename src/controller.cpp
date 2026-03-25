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
    this->current_state = INIT;
    this->turn = STOPPED;
    this->led.off();
    this->locomotion.stop();
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
            //
            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        // TODO: Implementar a lógica de movimentação do robô
        case FORWARD: {
            break;
        }
        case BACKWARD: {
            break;
        }
        case LEFT: {
            break;
        }
        case RIGHT: {
            break;
        }
        case STOPPED: {
            break;
        }
        case RC_INPUT: {
            break;
        }
        default: {
            break;
        }
    }
}

void set_next_strategy(); {
    this->current_state = RUN;
}

void Controller::strategy_run() {
    switch (this->current_level) {
        case LEVEL_0: {
            // TODO: Implementar a lógica de execução da estratégia 0
            break;
        }
        case LEVEL_1: {
            // TODO: Implementar a lógica de execução da estratégia 1
            break;
        }
        case LEVEL_2: {
            // TODO: Implementar a lógica de execução da estratégia 2
            break;
        }
        case LEVEL_3: {
            // TODO: Implementar a lógica de execução da estratégia 3
            break;
        }
        default: {
            break;
        }
    }
}
