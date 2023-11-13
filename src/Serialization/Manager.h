#pragma once

namespace Serialization {
    inline const auto threadsRecord = _byteswap_ulong('THRD');

    inline std::mutex _lock;

    void Save(SKSE::SerializationInterface* a_intfc);
    void Load(SKSE::SerializationInterface* a_intfc);
    void Revert(SKSE::SerializationInterface* a_intfc);
}