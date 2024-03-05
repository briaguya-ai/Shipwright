#pragma once

#include "resource/Resource.h"

namespace SOH {
#define RESOURCE_TYPE_RAW_JSON 0x4A534F4E // JSON

class RawJson : public LUS::Resource<void> {
  public:
    using Resource::Resource;

    RawJson();
    ~RawJson();

    void* GetPointer() override;
    size_t GetPointerSize() override;

    char* Data = nullptr;
    size_t DataSize;
};
}; // namespace SOH
