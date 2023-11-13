#include "ThreadManager.h"

#include "GameAPI/Game.h"
#include "Util/Constants.h"

namespace Threading {
    void ThreadManager::startThread() {
        std::thread mainThread = std::thread([&]() {
            auto sleepTime = std::chrono::milliseconds(Constants::LOOP_TIME_MILLISECONDS);

            while (true) {
                auto start = std::chrono::system_clock::now();

                if (!GameAPI::Game::isPaused()) {
                    for (ActorThread* thread : threads) {
                        thread->loop();
                    }
                }

                auto end = std::chrono::system_clock::now();
                auto time = end - start;
                if (time < sleepTime) {
                    std::this_thread::sleep_for(sleepTime - time);
                }
            }
        });

        mainThread.detach();
    }


    ActorThread* ThreadManager::getThread(GameAPI::GameActor actor) {
        for (ActorThread* thread : threads) {
            if (thread->getActor() == actor) {
                return thread;
            }
        }

        return nullptr;
    }


    void ThreadManager::saveThreads(GameAPI::GameSerializationInterface serial) {
        serial.write<size_t>(threads.size());
        for (ActorThread* thread : threads) {
            thread->getActor().writeSerial(serial);
            thread->serialize(serial);
        }
    }

    void ThreadManager::loadThreads(GameAPI::GameSerializationInterface serial, uint32_t version) {
        size_t size = serial.read<size_t>();
        for (int i = 0; i < size; i++) {
            GameAPI::GameActor actor;
            actor.loadSerial(serial);
            // we need to deserialize the thread even if the actor couldn't be resolved, otherwise the data gets messed up
            ActorThread* thread = new ActorThread(actor, serial, version);
            if (actor) {
                threads.push_back(thread);
            }
        }
    }

    void ThreadManager::clearThreads() {
        for (ActorThread* thread : threads) {
            delete thread;
        }

        threads.clear();
    }

    void ThreadManager::postLoad() {
        if (threads.empty()) {
            threads.push_back(new ActorThread(GameAPI::GameActor::getPlayer()));
            threads[0]->start();
        }
    }
}