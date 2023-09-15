// clang-format off

#include "z_en_ru1.h"
#include "z64cutscene_commands.h"

// clang-format off
static CutsceneData D_80AF0880[] = {
    CS_BEGIN_CUTSCENE(15, 1306),
    CS_PLAYER_ACTION_LIST(10),
        CS_PLAYER_ACTION(0x0027, 0, 50, 0x0000, 0x6C16, 0x0000, 12, -340, -2810, 12, -340, -2810, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0003, 50, 70, 0x0000, 0x6C16, 0x0000, 12, -340, -2810, 12, -340, -2810, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0005, 70, 109, 0x0000, 0x6C16, 0x0000, 12, -340, -2810, 12, -340, -2810, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0002, 109, 135, 0x0000, 0x6C16, 0x0000, 12, -340, -2810, 100, -340, -2991, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0005, 135, 199, 0x0000, 0x6C16, 0x0000, 100, -340, -2991, 100, -340, -2991, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0003, 199, 219, 0x0000, 0x6C16, 0x0000, 100, -340, -2991, 100, -340, -2991, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0005, 219, 259, 0x0000, 0x6C16, 0x0000, 100, -340, -2991, 100, -340, -2991, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0003, 259, 276, 0x0000, 0x6C16, 0x0000, 100, -340, -2991, 100, -340, -2991, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0002, 276, 297, 0x0000, 0x6C16, 0x0000, 100, -340, -2991, 182, -340, -3132, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0005, 297, 843, 0x0000, 0x6C16, 0x0000, 182, -340, -3132, 182, -340, -3132, 1.1393037E-29f, 0.0f, 1.4E-45f),
    CS_NPC_ACTION_LIST(63, 4),
        CS_NPC_ACTION(0x0002, 0, 178, 0x0000, 0xEC16, 0x0000, 127, -340, -3041, 127, -340, -3041, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_NPC_ACTION(0x0003, 178, 245, 0x0000, 0x6C16, 0x0000, 127, -340, -3041, 127, -340, -3041, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_NPC_ACTION(0x0004, 245, 260, 0x0000, 0x6C16, 0x0000, 127, -340, -3041, 127, -340, -3041, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_NPC_ACTION(0x0005, 260, 396, 0x0000, 0x6C16, 0x0000, 127, -340, -3041, 127, -340, -3041, 1.1393037E-29f, 0.0f, 1.4E-45f),
    CS_MISC_LIST(1),
        CS_MISC(0x000C, 315, 345, 0x0000, 0x00000000, 0x00000000, 0xFFFFFFC0, 0x00000032, 0x00000000, 0xFFFFFFC0, 0x00000032, 0x00000000, 0x00000000, 0x00000000),
    CS_TEXT_LIST(4),
        CS_TEXT_NONE(0, 157),
        CS_TEXT_DISPLAY_TEXTBOX(0x404B, 157, 175, 0x0000, 0xFFFF, 0xFFFF),
        CS_TEXT_NONE(175, 252),
        CS_TEXT_DISPLAY_TEXTBOX(0x401E, 252, 300, 0x0000, 0xFFFF, 0xFFFF),
    CS_CAM_EYE_LIST(0, 247),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 55, -290, -2749, 0x20BA),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 55, -290, -2749, 0x44B8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 55, -290, -2749, 0x8080),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 55, -290, -2749, 0xE243),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.799889f, 55, -290, -2749, 0x005E),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.799889f, 55, -290, -2749, 0xFFFF),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.799889f, 55, -290, -2749, 0x0000),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.799889f, 55, -290, -2749, 0x5B80),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 30.799889f, 55, -290, -2749, 0x49B4),
    CS_CAM_EYE_LIST(73, 208),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 99, -307, -2985, 0x20BA),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 99, -307, -2985, 0x44B8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 99, -307, -2985, 0x8080),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 99, -307, -2985, 0xE243),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 99, -307, -2985, 0x005E),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.399944f, 99, -307, -2985, 0xFFFF),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 45.399944f, 99, -307, -2985, 0x0000),
    CS_CAM_EYE_LIST(116, 1207),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.799946f, 155, -276, -2911, 0x20BA),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.799946f, 155, -276, -2911, 0x44B8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.799946f, 155, -276, -2911, 0x8080),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.799946f, 155, -276, -2911, 0xE243),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 45.799946f, 155, -276, -2911, 0x005E),
    CS_CAM_EYE_LIST(186, 1277),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.39995f, 77, -315, -2992, 0x20BA),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.39995f, 77, -315, -2992, 0x44B8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.39995f, 77, -315, -2992, 0x8080),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.39995f, 77, -315, -2992, 0xE243),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 45.39995f, 77, -315, -2992, 0x005E),
    CS_CAM_EYE_LIST(256, 425),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 28.199883f, 350, -237, -3314, 0x20BA),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 28.199883f, 350, -237, -3314, 0x44B8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 28.199883f, 350, -237, -3314, 0x8080),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 28.199883f, 350, -237, -3314, 0xE243),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 46.799953f, 350, -237, -3314, 0x005E),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 46.799953f, 350, -237, -3314, 0xFFFF),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 46.799953f, 350, -237, -3314, 0x0000),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 46.799953f, 350, -237, -3314, 0x5B80),
    CS_CAM_AT_LIST(0, 276),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 50, 45.399944f, 40, -256, -2823, 0x20BA),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 50, 45.399944f, 40, -256, -2823, 0x44B8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 40, 45.399944f, 22, -313, -2823, 0x8080),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 10, 45.399944f, 23, -313, -2823, 0xE243),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 6, 30.799889f, 73, -298, -2828, 0x005E),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 30.799889f, 73, -298, -2828, 0xFFFF),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 30.799889f, 73, -298, -2828, 0x0000),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 30.799889f, 73, -298, -2828, 0x5B80),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 30.799889f, 73, -298, -2828, 0x49B4),
    CS_CAM_AT_LIST(73, 237),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 60.2f, 136, -314, -3060, 0x20BA),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 7, 60.600002f, 136, -314, -3060, 0x44B8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 7, 45.399944f, 136, -314, -3060, 0x8080),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.399944f, 136, -314, -3060, 0xE243),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.399944f, 136, -314, -3060, 0x005E),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.399944f, 135, -313, -3060, 0xFFFF),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 45.399944f, 135, -313, -3059, 0x0000),
    CS_CAM_AT_LIST(116, 1236),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.799946f, 132, -305, -2969, 0x20BA),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.799946f, 132, -304, -2969, 0x44B8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 1000, 45.799946f, 133, -304, -2969, 0x8080),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.799946f, 133, -304, -2969, 0xE243),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 45.799946f, 133, -304, -2969, 0x005E),
    CS_CAM_AT_LIST(186, 1306),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.39995f, 138, -301, -3032, 0x20BA),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.39995f, 138, -301, -3032, 0x44B8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 1000, 45.39995f, 138, -301, -3032, 0x8080),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.39995f, 138, -301, -3032, 0xE243),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 45.39995f, 138, -301, -3032, 0x005E),
    CS_CAM_AT_LIST(256, 454),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 28.199883f, 307, -254, -3258, 0x20BA),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 28.199883f, 307, -254, -3258, 0x44B8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 9, 28.199883f, 307, -254, -3258, 0x8080),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 9, 46.799953f, 304, -273, -3273, 0xE243),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 46.799953f, 304, -272, -3274, 0x005E),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 46.799953f, 304, -272, -3274, 0xFFFF),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 46.799953f, 304, -272, -3274, 0x0000),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 46.799953f, 305, -272, -3274, 0x5B80),
    CS_PLAY_BGM_LIST(1),
        CS_PLAY_BGM(0x0052, 74, 75, 0x0000, 0x00000000, 0xFFFFFFF1, 0x00000000, 0x0000004E, 0xFFFFFFF1, 0x00000000, 0x0000004E),
    CS_END(),
};

static u32 D_80AF10A0 = 0;

static CutsceneData D_80AF10A4[] = {
    CS_BEGIN_CUTSCENE(14, 1299),
    CS_PLAYER_ACTION_LIST(3),
        CS_PLAYER_ACTION(0x0005, 0, 272, 0x0000, 0xC000, 0x0000, -1085, -1025, -3347, -1085, -1025, -3347, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0003, 272, 292, 0x0000, 0xC000, 0x0000, -1085, -1025, -3347, -1085, -1025, -3347, 1.1393037E-29f, 0.0f, 1.4E-45f),
        CS_PLAYER_ACTION(0x0005, 292, 777, 0x0000, 0xC000, 0x0000, -1085, -1025, -3347, -1085, -1025, -3347, 1.1393037E-29f, 0.0f, 1.4E-45f),
    CS_MISC_LIST(1),
        CS_MISC(0x000C, 330, 627, 0x0000, 0x00000000, 0x00000000, 0xFFFFFFC0, 0x00000032, 0x00000000, 0xFFFFFFC0, 0x00000032, 0x00000000, 0x00000000, 0x00000000),
    CS_NPC_ACTION_LIST(66, 3),
        CS_NPC_ACTION(0x0001, 0, 40, 0x0000, 0x4000, 0x0000, -1352, -969, -3341, -1352, -969, -3341, 0.0f, 0.0f, 1.4E-45f),
        CS_NPC_ACTION(0x0002, 40, 213, 0x0000, 0x4000, 0x0000, -1352, -969, -3341, -1360, -969, -3343, 0.0f, 0.0f, 1.4E-45f),
        CS_NPC_ACTION(0x0003, 213, 1000, 0x0000, 0x4000, 0x0000, -1360, -969, -3343, -1360, -969, -3343, 0.0f, 0.0f, 1.4E-45f),
    CS_NPC_ACTION_LIST(48, 1),
        CS_NPC_ACTION(0x0002, 0, 90, 0x0000, 0x0000, 0x0000, -1360, -963, -3343, -1360, -963, -3343, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION_LIST(48, 2),
        CS_NPC_ACTION(0x0002, 90, 211, 0x0000, 0x0000, 0x0000, -1352, -922, -3341, -1352, -922, -3341, 0.0f, 0.0f, 0.0f),
        CS_NPC_ACTION(0x0006, 211, 311, 0x0000, 0x0000, 0x0000, -1352, -922, -3341, -1352, -922, -3341, 0.0f, 0.0f, 0.0f),
    CS_NPC_ACTION_LIST(62, 3),
        CS_NPC_ACTION(0x0004, 0, 210, 0x0000, 0x0000, 0x0000, -1065, -972, -3305, -1065, -978, -3305, 0.0f, -0.028571429f, 0.0f),
        CS_NPC_ACTION(0x0004, 210, 220, 0x8000, 0x0000, 0x0000, -1065, -978, -3305, -1065, -973, -3344, 0.0f, 0.5f, 0.0f),
        CS_NPC_ACTION(0x0004, 220, 410, 0x0000, 0x0000, 0x0000, -1065, -973, -3344, -1065, -976, -3344, 0.0f, -0.015789473f, 0.0f),
    CS_TEXT_LIST(6),
        CS_TEXT_NONE(0, 162),
        CS_TEXT_DISPLAY_TEXTBOX(0x4050, 162, 211, 0x0000, 0xFFFF, 0xFFFF),
        CS_TEXT_NONE(211, 232),
        CS_TEXT_DISPLAY_TEXTBOX(0x4051, 232, 241, 0x0000, 0xFFFF, 0xFFFF),
        CS_TEXT_NONE(241, 247),
        CS_TEXT_DISPLAY_TEXTBOX(0x4052, 247, 299, 0x0000, 0xFFFF, 0xFFFF),
    CS_PLAY_BGM_LIST(1),
        CS_PLAY_BGM(0x0023, 112, 113, 0x0000, 0x00000000, 0x00000000, 0xFFFFFFC7, 0x000000B1, 0x00000000, 0xFFFFFFC7, 0x000000B1),
    CS_CAM_EYE_LIST(0, 1176),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 41.9066f, -1390, -948, -3339, 0x00C6),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 40.706596f, -1390, -948, -3339, 0x00C8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 40.706596f, -1390, -948, -3339, 0x00D7),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 40.706596f, -1418, -938, -3337, 0x00E8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.10661f, -1418, -938, -3337, 0x00EA),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.10661f, -1418, -938, -3337, 0x013D),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 45.10661f, -1418, -938, -3337, 0x013F),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 45.10661f, -1418, -938, -3337, 0x006D),
    CS_CAM_EYE_LIST(91, 1270),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 44.906612f, -1319, -934, -3343, 0x00C6),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 44.70661f, -1319, -936, -3344, 0x00C8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 44.70661f, -1319, -936, -3344, 0x00D7),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 44.70661f, -1319, -936, -3344, 0x00E8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 44.70661f, -1326, -904, -3342, 0x00EA),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 60.906673f, -1326, -904, -3342, 0x013D),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 60.906673f, -1326, -904, -3342, 0x013F),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 60.906673f, -1326, -904, -3342, 0x014E),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 60.906673f, -1326, -904, -3342, 0x015F),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 60.906673f, -1326, -904, -3342, 0x0161),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 60.906673f, -1326, -1024, -3342, 0x652E),
    CS_CAM_EYE_LIST(211, 332),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.306555f, -1471, -819, -3149, 0x00C6),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.306555f, -1471, -819, -3149, 0x00C8),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.306555f, -1471, -819, -3149, 0x00D7),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 30.306555f, -1471, -819, -3149, 0x00E8),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 30.306555f, -1471, -819, -3149, 0x00EA),
    CS_CAM_AT_LIST(0, 1205),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 40.706596f, -1295, -1003, -3352, 0x00C6),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 50, 40.706596f, -1296, -1003, -3352, 0x00C8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 20, 40.706596f, -1296, -1003, -3352, 0x00D7),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 15, 45.10661f, -1314, -969, -3346, 0x00E8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.10661f, -1313, -970, -3346, 0x00EA),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 1000, 45.10661f, -1313, -969, -3346, 0x013D),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 45.10661f, -1313, -970, -3346, 0x013F),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 45.10661f, -1313, -970, -3346, 0x006D),
    CS_CAM_AT_LIST(91, 1299),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 44.70661f, -1405, -988, -3343, 0x00C6),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 7, 44.70661f, -1406, -989, -3344, 0x00C8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 7, 44.70661f, -1406, -989, -3344, 0x00D7),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 7, 44.70661f, -1406, -989, -3344, 0x00E8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 7, 60.906673f, -1393, -978, -3342, 0x00EA),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 60.906673f, -1393, -977, -3342, 0x013D),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 60.906673f, -1393, -977, -3342, 0x013F),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 1000, 60.906673f, -1393, -977, -3342, 0x014E),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 60.906673f, -1393, -977, -3342, 0x015F),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 60.906673f, -1393, -977, -3342, 0x0161),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 60.906673f, -1401, -1094, -3347, 0x652E),
    CS_CAM_AT_LIST(211, 361),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 30.306555f, -1426, -857, -3190, 0x00C6),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 30.306555f, -1426, -857, -3190, 0x00C8),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 30.306555f, -1426, -857, -3190, 0x00D7),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 30.306555f, -1426, -857, -3190, 0x00E8),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 30.306555f, -1426, -857, -3190, 0x00EA),
    CS_END(),
};

static u32 D_80AF1724 = 0;

static CutsceneData D_80AF1728[] = {
    CS_BEGIN_CUTSCENE(7, 1160),
    CS_MISC_LIST(1),
        CS_MISC(0x000C, 75, 627, 0x0000, 0x00000000, 0x00000000, 0xFFFFFFC0, 0x00000032, 0x00000000, 0xFFFFFFC0, 0x00000032, 0x00000000, 0x00000000, 0x00000000),
    CS_NPC_ACTION_LIST(48, 1),
        CS_NPC_ACTION(0x0002, 0, 90, 0x0000, 0x0000, 0x0000, -1360, -963, -3343, -1360, -963, -3343, 0.0f, 0.0f, 0.0f),
    CS_CAM_EYE_LIST(0, 1091),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 40.599983f, -1381, -958, -3331, 0x8BC0),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 40.599983f, -1381, -958, -3331, 0x2200),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 40.599983f, -1381, -958, -3331, 0x0000),
        CS_CAM_EYE(CS_CMD_CONTINUE, 0x00, 0, 40.599983f, -1381, -958, -3331, 0xD0E8),
        CS_CAM_EYE(CS_CMD_STOP, 0x00, 0, 40.599983f, -1381, -958, -3331, 0x0000),
    CS_CAM_EYE_REL_TO_PLAYER_LIST(40, 1131),
        CS_CAM_EYE_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 0, 50.800022f, 19, 40, 53, 0x8BC0),
        CS_CAM_EYE_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 0, 50.800022f, 19, 40, 53, 0x2200),
        CS_CAM_EYE_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 0, 50.800022f, 19, 40, 53, 0x0000),
        CS_CAM_EYE_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 0, 50.800022f, 19, 40, 53, 0xD0E8),
        CS_CAM_EYE_REL_TO_PLAYER(CS_CMD_STOP, 0x00, 0, 50.800022f, 19, 40, 53, 0x0000),
    CS_CAM_AT_LIST(0, 1120),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 40.599983f, -1224, -979, -3366, 0x8BC0),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 40.599983f, -1224, -979, -3366, 0x2200),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 1000, 40.599983f, -1224, -979, -3366, 0x0000),
        CS_CAM_AT(CS_CMD_CONTINUE, 0x00, 30, 40.599983f, -1224, -979, -3366, 0xD0E8),
        CS_CAM_AT(CS_CMD_STOP, 0x00, 30, 40.599983f, -1224, -979, -3366, 0x0000),
    CS_CAM_AT_REL_TO_PLAYER_LIST(40, 1160),
        CS_CAM_AT_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 30, 50.800022f, -35, 56, -93, 0x8BC0),
        CS_CAM_AT_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 30, 50.800022f, -35, 56, -93, 0x2200),
        CS_CAM_AT_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 1000, 50.800022f, -35, 56, -93, 0x0000),
        CS_CAM_AT_REL_TO_PLAYER(CS_CMD_CONTINUE, 0x00, 30, 50.800022f, -35, 56, -93, 0xD0E8),
        CS_CAM_AT_REL_TO_PLAYER(CS_CMD_STOP, 0x00, 30, 50.800022f, -35, 56, -93, 0x0000),
    CS_TEXT_LIST(2),
        CS_TEXT_NONE(0, 35),
        CS_TEXT_DISPLAY_TEXTBOX(0x404F, 35, 70, 0x0000, 0xFFFF, 0xFFFF),
    CS_END(),
};
// clang-format on
