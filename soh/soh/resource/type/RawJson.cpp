#include "RawJson.h"

namespace SOH {
RawJson::RawJson() : Resource(std::shared_ptr<LUS::ResourceInitData>()) {
}

RawJson::~RawJson() {
    if (Data != nullptr) {
        delete Data;
    }
}

void* RawJson::GetPointer() {
    return Data;
}

size_t RawJson::GetPointerSize() {
    return DataSize * sizeof(char);
}
} // namespace SOH
