#include "GameColor.h"

namespace GameAPI {
    void GameColor::setColor(RGBColor color) {
        form->color.red = color.red;
        form->color.green = color.green;
        form->color.blue = color.blue;
        form->color.alpha = color.alpha;
    }
}