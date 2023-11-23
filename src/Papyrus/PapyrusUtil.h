#pragma once

namespace PapyrusUtil {
    using VM = RE::BSScript::IVirtualMachine;

    std::vector<int> IntArray(RE::StaticFunctionTag*, int size, int filler) {
        std::vector<int> vector(size);
        std::fill(vector.begin(), vector.end(), filler);
        return vector;
    }
    
	bool Bind(VM* a_vm) {
        const auto obj = "DCA_Util"sv;

        BIND(IntArray);

        return true;
    }
}