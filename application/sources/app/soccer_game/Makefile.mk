CFLAGS		+= -I./sources/app/soccer_game
CPPFLAGS	+= -I./sources/app/soccer_game

VPATH += sources/app/soccer_game

# CPP source files
SOURCES_CPP += sources/app/soccer_game/soccer_game_striker.cpp
SOURCES_CPP += sources/app/soccer_game/soccer_game_keeper.cpp
SOURCES_CPP += sources/app/soccer_game/soccer_game_ball.cpp
SOURCES_CPP += sources/app/soccer_game/soccer_game_entrance.cpp
SOURCES_CPP += sources/app/soccer_game/soccer_game_goalPost.cpp
SOURCES_CPP += sources/app/soccer_game/soccer_game_scr.cpp
SOURCES_CPP += sources/app/soccer_game/task_soccer_game.cpp
