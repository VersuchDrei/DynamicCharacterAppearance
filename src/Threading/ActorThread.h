#pragma once

#include "HairColorThread.h"
#include "OverlayColorThread.h"
#include "Thread.h"
#include "SubThreadType.h"

#include "GameAPI/GameActor.h"
#include "Util/FormTable.h"

namespace Threading {
    class ActorThread : public Thread{
    public:
        inline ActorThread(GameAPI::GameActor actor) : Thread(actor) {}
        ActorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);
        ~ActorThread();

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        inline bool isRunning() { return running; }
        int getSubThreadCount(SubThreadType type);
        SubThread* getSubThread(SubThreadType type, int index);
        void addSubThread(SubThreadType type);
        void removeSubThread(SubThreadType type, int index);

        virtual void start();
        virtual void stop();
        virtual void loop();

    private:
        bool running = false;
        HairColorThread* hairColorThread = nullptr;
        std::vector<OverlayColorThread*> overlayColorThreads;
    };
}