#include "ActorThread.h"

namespace Threading {
    ActorThread::ActorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : Thread(actor) {
        running = serial.read<bool>();

        if (serial.read<bool>()) {
            hairColorThread = new HairColorThread(actor, serial, version);
        }

        serial.read<bool>();

        if (version >= 1) {
            size_t count = serial.read<size_t>();
            for (int i = 0; i < count; i++) {
                overlayColorThreads.push_back(new OverlayColorThread(actor, serial, version));
            }
        }
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

        serial.write<size_t>(overlayColorThreads.size());
        for (OverlayColorThread* thread : overlayColorThreads) {
            thread->serialize(serial);
        }
    }


    int ActorThread::getSubThreadCount(SubThreadType type) {
        switch (type) {
        case SubThreadType::HAIR_COLOR:
            return hairColorThread ? 1 : 0;
        case SubThreadType::OVERLAY_COLOR:
            return overlayColorThreads.size();
        default:
            return 0;
        }
    }

    SubThread* ActorThread::getSubThread(SubThreadType type, int index) {
        switch (type) {
        case SubThreadType::HAIR_COLOR:
            return hairColorThread;
        case SubThreadType::OVERLAY_COLOR:
            if (index >= 0 && index < overlayColorThreads.size()) {
                return overlayColorThreads[index];
            }
            return nullptr;
        default:
            return nullptr;
        }
    }

    void ActorThread::addSubThread(SubThreadType type) {
        switch (type) {
        case SubThreadType::HAIR_COLOR:
            if (!hairColorThread) {
                hairColorThread = new HairColorThread(getActor(), Util::FormTable::getPlayerHairColor());
                if (running) {
                    hairColorThread->start();
                }
            }
            break;
        case SubThreadType::OVERLAY_COLOR:
            overlayColorThreads.push_back(new OverlayColorThread(getActor()));
            if (running) {
                (*overlayColorThreads.end())->start();
            }
            break;
        }
    }

    void ActorThread::removeSubThread(SubThreadType type, int index) {
        switch (type) {
        case SubThreadType::HAIR_COLOR:
            if (hairColorThread) {
                if (running) {
                    hairColorThread->stop();
                }
                delete hairColorThread;
                hairColorThread = nullptr;
            }
            break;
        case SubThreadType::OVERLAY_COLOR:
            if (index >= 0 && index < overlayColorThreads.size()) {
                if (running) {
                    overlayColorThreads[index]->stop();
                }
                delete overlayColorThreads[index];
                overlayColorThreads.erase(overlayColorThreads.begin() + index);
            }
            break;
        }
    }


    void ActorThread::start() {
        if (running) {
            return;
        }

        running = true;

        if (hairColorThread) {
            hairColorThread->start();
        }

        for (OverlayColorThread* thread : overlayColorThreads) {
            thread->start();
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

        for (OverlayColorThread* thread : overlayColorThreads) {
            thread->stop();
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

        for (OverlayColorThread* thread : overlayColorThreads) {
            thread->loop();
        }
    }
}