#include "soh/resource/importer/RawJsonFactory.h"
#include "soh/resource/type/RawJson.h"
#include "spdlog/spdlog.h"

namespace SOH {
std::shared_ptr<LUS::IResource> ResourceFactoryBinaryRawJsonV0::ReadResource(std::shared_ptr<LUS::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto json = std::make_shared<RawJson>(file->InitData);
    auto reader = std::get<std::shared_ptr<LUS::BinaryReader>>(file->Reader);

    json->DataSize = json->Buffer->size();

    json->Data = new char[json->DataSize];
    reader->Read(json->Data, json->DataSize);

    return json;
}
} // namespace SOH
