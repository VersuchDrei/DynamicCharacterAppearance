#pragma once

namespace GameAPI {
    enum GameSex { MALE, FEMALE, AGENDER };

    class GameSexAPI {
    public:
        static GameSex fromGame(RE::SEX sex);
        static std::string toIcon(GameSex sex);
    };
}  // namespace GameAPI