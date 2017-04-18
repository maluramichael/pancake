//
// Created by Michael Malura on 05/04/17.
//

#ifndef PANCAKE_INTERFACE_H
#define PANCAKE_INTERFACE_H

class Widget;

#include <vector>

#include "Widget.h"

namespace Pancake {
    namespace UI {

        class Interface {
            std::vector<Pancake::UI::Widget> widgets;
        };
    }
}

#endif //PANCAKE_INTERFACE_H
