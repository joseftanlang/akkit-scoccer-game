#include "screens_bitmap.h"
#include "scr_score.h"
#include "app_eeprom.h"

static void view_scr_score();
static ar_game_score_t score_data;

view_dynamic_t dyn_view_item_score = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_score};

view_screen_t scr_score = {
    &dyn_view_item_score,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void view_scr_score()
{
    view_render.clear();
    view_render.fillScreen(WHITE);
    view_render.drawBitmap(14, 22, iconLeaderBoard, 100, 40, 0);

    view_render.setTextSize(2);
    view_render.setTextColor(BLACK);
    view_render.setCursor(22, 18);
    view_render.print(score_data.score_2nd);
    view_render.setCursor(52, 7);
    view_render.print(score_data.score_1st);
    view_render.setCursor(88, 23);
    view_render.print(score_data.score_3rd);

    // view_render.setTextSize(1);
    // view_render.setCursor(12, 55);
    // view_render.print("MODE/BACK  UP=RESET");
}

void scr_score_handle(ak_msg_t *msg)
{
    switch (msg->sig)
    {
    case SCREEN_ENTRY:
        APP_DBG_SIG("SCREEN ENTRY");
        ar_game_score_read(&score_data);
        view_scr_score();
        BUZZER_PlaySound(BUZZER_SOUND_3BEEP);
        break;
    case AC_DISPLAY_BUTON_DOWN_RELEASED:
        APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
        SCREEN_TRAN(scr_menu_handle, &scr_menu);
        BUZZER_PlaySound(BUZZER_SOUND_BANG);
        break;
    case AC_DISPLAY_BUTON_UP_RELEASED:
        APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
        score_data.score_1st = 0;
        score_data.score_2nd = 0;
        score_data.score_3rd = 0;
        ar_game_score_write(&score_data);
        view_scr_score();
        BUZZER_PlaySound(BUZZER_SOUND_BANG);
        break;
    default:
        break;
    }
}