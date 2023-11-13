#pragma once

#include "ActorThread.h"

namespace Threading {
    class ThreadManager {
    public:
        static void startThread();

        static ActorThread* getThread(GameAPI::GameActor actor);

        static void saveThreads(GameAPI::GameSerializationInterface serial);
        static void loadThreads(GameAPI::GameSerializationInterface serial, uint32_t version);
        static void clearThreads();
        static void postLoad();

    private:
        static inline std::vector<ActorThread*> threads;
    };
}