#pragma once

#include "Threading/ThreadManager.h"

namespace PapyrusData {
	using VM = RE::BSScript::IVirtualMachine;

    bool IsActorThreadRunning(RE::StaticFunctionTag*, RE::Actor* actor) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            return thread->isRunning();
        }
        return false;
    }

    void StartActorThread(RE::StaticFunctionTag*, RE::Actor* actor) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            thread->start();
        }
    }

    void StopActorThread(RE::StaticFunctionTag*, RE::Actor* actor) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            thread->stop();
        }
    }


	bool Bind(VM* a_vm) {
        const auto obj = "DCA_Data"sv;

        BIND(IsActorThreadRunning);
        BIND(StartActorThread);
        BIND(StopActorThread);

        return true;
    }
}