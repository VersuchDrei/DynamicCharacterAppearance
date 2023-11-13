#include "Manager.h"

#include "Threading/ThreadManager.h"

namespace Serialization {
    void Save(SKSE::SerializationInterface* serial) {
        std::unique_lock lock(_lock);
        logger::info("serializing data");
    
        if (!serial->OpenRecord(threadsRecord, 0)) {
            logger::error("Unable to open record to write cosave data.");
            return;
        }

        Threading::ThreadManager::saveThreads(serial);
    }

    void Load(SKSE::SerializationInterface* serial) {
        std::unique_lock lock(_lock);
    
        Threading::ThreadManager::clearThreads();

        std::uint32_t type;
        std::uint32_t size;
        std::uint32_t version;

        while (serial->GetNextRecordInfo(type, version, size)) {
            if (type == threadsRecord) {
                Threading::ThreadManager::loadThreads(serial, version);
            }
        }

        Threading::ThreadManager::postLoad();
    }

    void Revert(SKSE::SerializationInterface* serial) {
        std::unique_lock lock(_lock);
        
        Threading::ThreadManager::clearThreads();
    }
}