#pragma once

namespace game_config
{
    // �A�v���P�[�V����
    constexpr auto GAME_APP_NAME = "���Ƃ��["; // �A�v����

#ifndef BUILD_BY_CI
    constexpr auto GAME_APP_VER = "0.0.1"; // �o�[�W����
#else
    constexpr std::string GAME_APP_VER = APP_VER;
#endif

    // ���
    constexpr auto GAME_SCREEN_WIDTH = 1024;
    constexpr auto GAME_SCREEN_HEIGHT = 720;

    constexpr auto GAME_APP_DEFAULT_FONT = "Noto Sans CJK JP Thin"; // �f�t�H���g�̃t�H���g

    // �ݒ�t�@�C��
    constexpr auto SETTINGS_PATH = "system.";

    constexpr auto SETTINGS_FULLSCREEN = "system.graphic.fullscreen";
    constexpr auto SETTINGS_VSYNC = "system.graphic.vsync";
    constexpr auto SETTINGS_RES_WIDTH = "system.graphic.resolution.width";
    constexpr auto SETTINGS_RES_HEIGHT = "system.graphic.resolution.height";
    constexpr auto SETTINGS_AA_SAMPLE = "system.graphic.antialiasing.sample";
    constexpr auto SETTINGS_AA_QUALITY = "system.graphic.antialiasing.quality";

    constexpr auto SETTINGS_FONT_NAME = "system.display.font.default";
    constexpr auto SETTINGS_FONT_DRAWTYPE = "system.display.font.drawType";

    constexpr auto SETTINGS_DEBUG_DRAW_SCENE_FRAME = "system.debug.scene.isDrawFrame";
    constexpr auto SETTINGS_DEBUG_DRAW_DTASK_POINT = "system.debug.drawable.isDrawPoint";

    constexpr auto SETTINGS_MOUSE_AREA_LIMIT = "input.mouse.area_limit";
    constexpr auto SETTINGS_MOUSE_USEORIGINAL = "input.mouse.use_original";
}