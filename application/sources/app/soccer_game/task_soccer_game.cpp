#include "task.h"
#include "scr_soccer.h"

static void task_soccer_game_dispatch(ak_msg_t* msg)
{
	scr_soccer_handle(msg);
}

void task_soccer_game_ball_tick(ak_msg_t* msg)
{
	task_soccer_game_dispatch(msg);
}

void task_soccer_game_keeper_tick(ak_msg_t* msg)
{
	task_soccer_game_dispatch(msg);
}

void task_soccer_game_striker_tick(ak_msg_t* msg)
{
	task_soccer_game_dispatch(msg);
}

void task_soccer_game_countdown_tick(ak_msg_t* msg)
{
	task_soccer_game_dispatch(msg);
}

void task_soccer_game_super_mode_tick(ak_msg_t* msg)
{
	task_soccer_game_dispatch(msg);
}

void task_soccer_game_result_tick(ak_msg_t* msg)
{
	task_soccer_game_dispatch(msg);
}