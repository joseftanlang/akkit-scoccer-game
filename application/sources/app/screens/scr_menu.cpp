#include "scr_menu.h"
#include "scr_score.h"
#include "scr_soccer.h"
#include "screen_manager.h"

enum menu_item_t {
	MENU_ITEM_SOCCER = 0,
	MENU_ITEM_SCORE = 1,
};

static void view_scr_menu();

static menu_item_t menu_selection = MENU_ITEM_SOCCER;

view_dynamic_t dyn_view_menu = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_menu
};

view_screen_t scr_menu = {
	&dyn_view_menu,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

static void draw_option_box(int x, int y, int w, int h, const char* label, bool selected)
{
	if (selected) {
		view_render.fillRoundRect(x, y, w, h, 3, WHITE);
		view_render.setTextColor(BLACK);
	}
	else {
		view_render.drawRoundRect(x, y, w, h, 3, WHITE);
		view_render.setTextColor(WHITE);
	}

	view_render.setTextSize(1);
	view_render.setCursor(x + 10, y + 4);
	view_render.print(label);
}

static void view_scr_menu()
{
	view_render.clear();

	view_render.setTextColor(WHITE);
	view_render.setTextSize(2);
	view_render.setCursor(30, 6);
	view_render.print("SOCCER");

	view_render.setTextSize(1);
	view_render.setCursor(39, 23);
	view_render.print("MAIN MENU");

	draw_option_box(12, 32, 46, 16, "SOCCER", menu_selection == MENU_ITEM_SOCCER);
	draw_option_box(70, 32, 46, 16, "SCORE", menu_selection == MENU_ITEM_SCORE);

	view_render.setCursor(15, 56);
	view_render.print("UP/DOWN SELECT");
	view_render.update();
}

void scr_menu_handle(ak_msg_t* msg)
{
	SCREEN_NONE_UPDATE_MASK();
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		menu_selection = MENU_ITEM_SOCCER;
		view_scr_menu();
		BUZZER_PlaySound(BUZZER_SOUND_3BEEP);
	}
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
		menu_selection = MENU_ITEM_SOCCER;
		view_scr_menu();
		BUZZER_PlaySound(BUZZER_SOUND_BANG);
	}
		break;

	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
		menu_selection = MENU_ITEM_SCORE;
		view_scr_menu();
		BUZZER_PlaySound(BUZZER_SOUND_BANG);
	}
		break;

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		if (menu_selection == MENU_ITEM_SOCCER) {
			SCREEN_TRAN(scr_soccer_handle, &scr_soccer);
		}
		else {
			SCREEN_TRAN(scr_score_handle, &scr_score);
		}
	}
		break;

	case AC_DISPLAY_BUTON_LONG_MODE_PRESSED:
	case AC_DISPLAY_BUTON_LONG_UP_RELEASED:
	case AC_DISPLAY_BUTON_LONG_DOWN_RELEASED:
		break;

	default:
		break;
	}
}