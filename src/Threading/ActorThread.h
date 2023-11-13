#pragma once

#include "HairColorThread.h"
#include "Thread.h"

#include "GameAPI/GameActor.h"
#include "Util/FormTable.h"

namespace Threading {
    class ActorThread : public Thread{
    public:
        inline ActorThread(GameAPI::GameActor actor) : Thread(actor) {
            // TODO: don't hardcode this
            hairColorThread = new HairColorThread(actor, Util::FormTable::getPlayerHairColor());
        }
        ActorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);
        ~ActorThread();

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        inline bool isRunning() { return running; }

        virtual void start();
        virtual void stop();
        virtual void loop();

    private:
        bool running = false;
        HairColorThread* hairColorThread = nullptr;
    };
}