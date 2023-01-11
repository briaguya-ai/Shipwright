#include "resource/importer/AudioSoundFontFactory.h"
#include "resource/type/AudioSoundFont.h"
#include "spdlog/spdlog.h"
#include "libultraship/src/core/bridge/resourcebridge.h"

namespace Ship {
std::shared_ptr<Resource> AudioSoundFontFactory::ReadResource(std::shared_ptr<BinaryReader> reader)
{
	auto resource = std::make_shared<AudioSoundFont>();
	std::shared_ptr<ResourceVersionFactory> factory = nullptr;

	uint32_t version = reader->ReadUInt32();
	switch (version)
	{
	case 0:
		factory = std::make_shared<AudioSoundFontFactoryV0>();
		break;
	}

	if (factory == nullptr)
	{
		SPDLOG_ERROR("Failed to load AudioSoundFont with version {}", version);
		return nullptr;
	}

	factory->ParseFileBinary(reader, resource);

	return resource;
}

void Ship::AudioSoundFontFactoryV0::ParseFileBinary(std::shared_ptr<BinaryReader> reader,
                                                    std::shared_ptr<Resource> resource)
{
	std::shared_ptr<AudioSoundFont> audioSoundFont = std::static_pointer_cast<AudioSoundFont>(resource);
	ResourceFile::ParseFileBinary(reader, audioSoundFont);

    audioSoundFont->soundFont.fntIndex = reader->ReadInt32();
    audioSoundFont->medium = reader->ReadInt8();
    audioSoundFont->cachePolicy = reader->ReadInt8();
    
    audioSoundFont->data1 = reader->ReadUInt16();
    audioSoundFont->soundFont.sampleBankId1 = audioSoundFont->data1 >> 8;
    audioSoundFont->soundFont.sampleBankId2 = audioSoundFont->data1 & 0xFF;

    audioSoundFont->data2 = reader->ReadUInt16();
    audioSoundFont->data3 = reader->ReadUInt16();

    uint32_t drumCount = reader->ReadUInt32();
    audioSoundFont->soundFont.numDrums = drumCount;
    
    uint32_t instrumentCount = reader->ReadUInt32();
    audioSoundFont->soundFont.numInstruments = instrumentCount;
    
    uint32_t soundEffectCount = reader->ReadUInt32();
    audioSoundFont->soundFont.numSfx = soundEffectCount;

    // 🥁 DRUMS 🥁
    audioSoundFont->drums.reserve(audioSoundFont->soundFont.numDrums);
    audioSoundFont->drumAddresses.reserve(audioSoundFont->soundFont.numDrums);
    for (uint32_t i = 0; i < audioSoundFont->soundFont.numDrums; i++) {
        Drum drum;
        drum.releaseRate = reader->ReadUByte();
        drum.pan = reader->ReadUByte();
        drum.loaded = reader->ReadUByte();
        drum.loaded = 0; // this was always getting set to zero in ResourceMgr_LoadAudioSoundFont

        uint32_t envelopeCount = reader->ReadUInt32();
        audioSoundFont->drumEnvelopeCounts.push_back(envelopeCount);
        std::vector<AdsrEnvelope> drumEnvelopes;
        drumEnvelopes.reserve(audioSoundFont->drumEnvelopeCounts[i]);
        for (uint32_t j = 0; j < audioSoundFont->drumEnvelopeCounts.back(); j++) {
            AdsrEnvelope env;
            
            int16_t delay = reader->ReadInt16();
            int16_t arg = reader->ReadInt16();

            env.delay = BE16SWAP(delay);
            env.arg = BE16SWAP(arg);

            drumEnvelopes.push_back(env);
        }
        audioSoundFont->drumEnvelopeArrays.push_back(drumEnvelopes);
        drum.envelope = audioSoundFont->drumEnvelopeArrays.back().data();

        bool hasSample = reader->ReadInt8();
        std::string sampleFileName = reader->ReadString();
        drum.sound.tuning = reader->ReadFloat();
        drum.sound.sample = static_cast<Sample*>(GetResourceDataByName(sampleFileName.c_str()));

        audioSoundFont->drums.push_back(drum);
        audioSoundFont->drumAddresses.push_back(&audioSoundFont->drums.back());
    }
    audioSoundFont->soundFont.drums = audioSoundFont->drumAddresses.data();

    // 🎺🎻🎷🎸🎹 INSTRUMENTS 🎹🎸🎷🎻🎺
    audioSoundFont->instruments.reserve(audioSoundFont->soundFont.numInstruments);
    for (uint32_t i = 0; i < audioSoundFont->soundFont.numInstruments; i++) {
        Instrument instrument;

        uint8_t isValidEntry = reader->ReadUByte();
        instrument.loaded = reader->ReadUByte();
        instrument.loaded = 0; // this was always getting set to zero in ResourceMgr_LoadAudioSoundFont

        instrument.normalRangeLo = reader->ReadUByte();
        instrument.normalRangeHi = reader->ReadUByte();
        instrument.releaseRate = reader->ReadUByte();

        uint32_t envelopeCount = reader->ReadInt32();
        audioSoundFont->instrumentEnvelopeCounts.push_back(envelopeCount);
        std::vector<AdsrEnvelope> instrumentEnvelopes;
        for (uint32_t j = 0; j < audioSoundFont->instrumentEnvelopeCounts.back(); j++) {
            AdsrEnvelope env;

            int16_t delay = reader->ReadInt16();
            int16_t arg = reader->ReadInt16();

            env.delay = BE16SWAP(delay);
            env.arg = BE16SWAP(arg);

            instrumentEnvelopes.push_back(env);
        }
        audioSoundFont->instrumentEnvelopeArrays.push_back(instrumentEnvelopes);
        instrument.envelope = audioSoundFont->instrumentEnvelopeArrays.back().data();

        bool hasLowNoteSoundFontEntry = reader->ReadInt8();
        if (hasLowNoteSoundFontEntry) {
            bool hasSampleRef = reader->ReadInt8();
            std::string sampleFileName = reader->ReadString();
            instrument.lowNotesSound.tuning = reader->ReadFloat();
            instrument.lowNotesSound.sample = static_cast<Sample*>(GetResourceDataByName(sampleFileName.c_str()));
        } else {
            instrument.lowNotesSound.sample = nullptr;
            instrument.lowNotesSound.tuning = 0;
        }

        bool hasNormalNoteSoundFontEntry = reader->ReadInt8();
        if (hasNormalNoteSoundFontEntry) {
            bool hasSampleRef = reader->ReadInt8();
            std::string sampleFileName = reader->ReadString();
            instrument.normalNotesSound.tuning = reader->ReadFloat();
            instrument.normalNotesSound.sample = static_cast<Sample*>(GetResourceDataByName(sampleFileName.c_str()));
        } else {
            instrument.normalNotesSound.sample = nullptr;
            instrument.normalNotesSound.tuning = 0;
        }

        bool hasHighNoteSoundFontEntry = reader->ReadInt8();
        if (hasHighNoteSoundFontEntry) {
            bool hasSampleRef = reader->ReadInt8();
            std::string sampleFileName = reader->ReadString();
            instrument.highNotesSound.tuning = reader->ReadFloat();
            instrument.highNotesSound.sample = static_cast<Sample*>(GetResourceDataByName(sampleFileName.c_str()));
        } else {
            instrument.highNotesSound.sample = nullptr;
            instrument.highNotesSound.tuning = 0;
        }

        
        audioSoundFont->instruments.push_back(instrument);
        audioSoundFont->instrumentAddresses.push_back(isValidEntry ? 
                                                      &audioSoundFont->instruments.back() :
                                                      nullptr);
    }
    audioSoundFont->soundFont.instruments = audioSoundFont->instrumentAddresses.data();

    // 🔊 SOUND EFFECTS 🔊
    audioSoundFont->soundEffects.reserve(audioSoundFont->soundFont.numSfx);
    // for (uint32_t i = 0; i < sfxCnt; i++) {
    //     SoundFontEntry* entry = new SoundFontEntry();

    //     bool hasSFEntry = reader->ReadInt8();

    //     if (hasSFEntry) {
    //         bool hasSampleRef = reader->ReadInt8();
    //         entry->sampleFileName = reader->ReadString();
    //         entry->tuning = reader->ReadFloat();
    //     }

    //     soundFont->soundEffects.push_back(entry);
    // }
}
} // namespace Ship

/*


                soundFontC->instruments[i] = inst;
            }
            else
            {
                soundFontC->instruments[i] = nullptr;
            }
        }

        soundFontC->soundEffects = (SoundFontSound*)malloc(sizeof(SoundFontSound) * soundFont->soundEffects.size());

        for (size_t i = 0; i < soundFont->soundEffects.size(); i++)
        {
            soundFontC->soundEffects[i].sample = ResourceMgr_LoadAudioSample(soundFont->soundEffects[i]->sampleFileName.c_str());
            soundFontC->soundEffects[i].tuning = soundFont->soundEffects[i]->tuning;
        }

        soundFont->CachedGameAsset = soundFontC;
        return soundFontC;

*/