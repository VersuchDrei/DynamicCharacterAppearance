#include "ActorThread.h"

namespace Threading {
    ActorThread::ActorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : Thread(actor) {
        running = serial.read<bool>();

        if (serial.read<bool>()) {
            hairColorThread = new HairColorThread(actor, serial, version);
        }

        serial.read<bool>();
    }

    ActorThread::~ActorThread() {
        if (hairColorThread) {
            delete hairColorThread;
        }
    }

    void ActorThread::serialize(GameAPI::GameSerializationInterface serial) {
        serial.write<bool>(running);

        serial.write<bool>(hairColorThread);
        if (hairColorThread) {
            hairColorThread->serialize(serial);
        }

        serial.write<bool>(false);
    }

    void ActorThread::start() {
        if (running) {
            return;
        }

        running = true;

        if (hairColorThread) {
            hairColorThread->start();
        }
    }

    void ActorThread::stop() {
        if (!running) {
            return;
        }

        running = false;

        if (hairColorThread) {
            hairColorThread->stop();
        }
    }

    void ActorThread::loop() {
        if (!running) {
            return;
        }

        if (!getActor().isLoaded()) {
            return;
        }

        if (hairColorThread) {
            hairColorThread->loop();
        }
    }
}