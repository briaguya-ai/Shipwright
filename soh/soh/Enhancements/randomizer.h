#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <unordered_map>
#include <randomizerTypes.h>
#include <z64item.h>
#include <z64math.h>

class Randomizer {
  private:
    std::unordered_map<RandomizerCheck, RandomizerGet> itemLocations;
    GetItemID GetItemFromGet(RandomizerGet randoGet, GetItemID ogItemId);
    RandomizerCheck GetCheckFromActor(s16 actorId, GetItemID ogItemId);
    RandomizerCheck GetCheckFromSceneAndParams(s16 sceneNum, s16 actorParams, s32 homePosX = 0, s32 homePosY = 0, s32 homePosZ = 0);

  public:
    Randomizer();
    ~Randomizer();

    s16 GetItemModelFromId(s16 itemId);
    void LoadItemLocations(const char* spoilerFileName);
    void ParseItemLocations(const char* spoilerFileName);
    GetItemID GetItemFromActor(s16 actorId, GetItemID ogItemId);
    GetItemID GetItemFromSceneAndParams(s16 sceneNum, s16 actorParams, GetItemID ogItemId);
    GetItemID GetItemFromSceneParamsAndHomePos(s16 sceneNum, s16 actorParams, s32 homePosX, s32 homePosY, s32 homePosZ, GetItemID ogItemId);
};

#endif
