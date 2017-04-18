
#ifndef __PANCAKE__GRAPHICS__PAINTER__STATE__
#define __PANCAKE__GRAPHICS__PAINTER__STATE__

#include "Color.h"

namespace Pancake {
    namespace Graphics {

    class PainterState {
    private:
        Color color;

    public:
        PainterState();

        Color getColor();

        void setColor(short r, short g, short b, short a);

        void setColor(int color);

        void setColor(Color color);
    };
}
}

#endif