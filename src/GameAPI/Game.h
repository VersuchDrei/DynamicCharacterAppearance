#pragma once

namespace GameAPI {
    class Game {
    public:
        inline static bool isPaused() { return RE::UI::GetSingleton()->GameIsPaused(); }
    };
}