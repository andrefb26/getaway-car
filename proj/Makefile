
PROG = proj

CFLAGS += -pedantic -D __LCOM_OPTIMIZED__
# Caminhos relativos em vez de /home/lcom/labs/labX — funcionam independentemente
# do mount point da pasta partilhada no MINIX
CFLAGS += -I../lab3
#CFLAGS += -I../lab4
CFLAGS += -I../lab5
CFLAGS += -I../lab1
CFLAGS += -Isrc

DPADD += ${LIBLCF}

# Os .a dos labs têm de vir ANTES de -llcf. O linker resolve símbolos pela ordem
# em que encontra as bibliotecas: se -llcf viesse primeiro, usaria os stubs do LCF
# (ex: timer_set_frequency "not implemented") em vez das implementações dos labs.
LDADD += ../lab1/liblab1.a \
         ../lab2/libtimer.a \
         ../lab3/libkbc.a \
         ../lab4/libmouse.a \
         ../lab5/libvideo.a \
         -llcf
LDLIBS += -lm

SRCS = proj.c \
       src/model/game/game.c \
       src/model/common/element/element.c \
       src/model/common/sprite/sprite.c \
       src/model/elements/car/car.c \
       src/model/elements/obstacle/obstacle.c \
       src/model/elements/boost/boost.c \
       src/model/elements/shield/shield.c \
       src/model/terrain/track/track.c \
       src/model/terrain/scenery/scenery.c \
       src/controller/input/input.c \
       src/controller/palette/palette.c \
       src/controller/graphics/graphics.c \
       src/controller/cursor/cursor.c \
       src/view/view.c \
       src/model/resources/resources.c \
       src/view/elements/car/car_view.c \
       src/view/elements/obstacle/obstacle_view.c \
       src/view/elements/boost/boost_view.c \
       src/view/elements/shield/shield_view.c \
       src/view/terrain/track/track_view.c \
       src/view/terrain/scenery/scenery_view.c \
       src/view/hud/heart/heart_view.c \
       src/view/hud/timer/timer_view.c \
       src/view/hud/minimap/minimap_view.c \
       src/view/screens/pause/pause_view.c \
       src/view/screens/menu/menu_view.c \
       src/view/screens/win/win_view.c \
       src/view/screens/mode_select/mode_select_view.c \
       src/view/screens/car_select/car_select_view.c \
       src/view/screens/biome_select/biome_select_view.c \
       src/model/leaderboard/leaderboard.c \
       src/view/screens/leaderboard/leaderboard_view.c \
       src/view/screens/instructions/instructions_view.c


# Headers — listados explicitamente para dependências corretas
HDRS = src/config.h \
       src/model/game/game.h \
       src/model/common/element/element.h \
       src/model/common/sprite/sprite.h \
       src/model/elements/car/car.h \
       src/model/elements/obstacle/obstacle.h \
       src/model/elements/boost/boost.h \
       src/model/elements/shield/shield.h \
       src/model/terrain/track/track.h \
       src/model/terrain/scenery/scenery.h \
       src/controller/input/input.h \
       src/controller/palette/palette.h \
       src/controller/graphics/graphics.h \
       src/controller/cursor/cursor.h \
       src/view/view.h \
       src/model/resources/resources.h \
       src/view/elements/car/car_view.h \
       src/view/elements/obstacle/obstacle_view.h \
       src/view/elements/boost/boost_view.h \
       src/view/elements/shield/shield_view.h \
       src/view/terrain/track/track_view.h \
       src/view/terrain/scenery/scenery_view.h \
       src/view/hud/heart/heart_view.h \
       src/view/hud/timer/timer_view.h \
       src/view/hud/minimap/minimap_view.h \
       src/view/screens/pause/pause_view.h \
       src/view/screens/menu/menu_view.h \
       src/view/screens/win/win_view.h \
       src/view/screens/mode_select/mode_select_view.h \
       src/view/screens/car_select/car_select_view.h \
       src/model/leaderboard/leaderboard.h \
       src/view/screens/leaderboard/leaderboard_view.h \
       src/view/screens/instructions/instructions_view.h

#       src/controller/timer/timer.h \
#       src/controller/rtc/rtc.h \
#       src/controller/kbc/kbc.h \
#       src/controller/kbc/kbd.h \
# Regras de compilação
proj.o: src/proj.c ${HDRS}
	${CC} ${CFLAGS} -c $< -o $@

src/model/game/game.o: src/model/game/game.c src/model/game/game.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/common/element/element.o: src/model/common/element/element.c src/model/common/element/element.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/common/sprite/sprite.o: src/model/common/sprite/sprite.c src/model/common/sprite/sprite.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/elements/car/car.o: src/model/elements/car/car.c src/model/elements/car/car.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/elements/obstacle/obstacle.o: src/model/elements/obstacle/obstacle.c src/model/elements/obstacle/obstacle.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/terrain/track/track.o: src/model/terrain/track/track.c src/model/terrain/track/track.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/cursor/cursor.o: src/controller/cursor/cursor.c src/controller/cursor/cursor.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/leaderboard/leaderboard.o: src/model/leaderboard/leaderboard.c src/model/leaderboard/leaderboard.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/leaderboard/leaderboard_view.o: src/view/screens/leaderboard/leaderboard_view.c src/view/screens/leaderboard/leaderboard_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/instructions/instructions_view.o: src/view/screens/instructions/instructions_view.c src/view/screens/instructions/instructions_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/timer/timer.o: src/controller/timer/timer.c src/controller/timer/timer.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/rtc/rtc.o: src/controller/rtc/rtc.c src/controller/rtc/rtc.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/kbc/kbc.o: src/controller/kbc/kbc.c src/controller/kbc/kbc.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/kbc/kbd.o: src/controller/kbc/kbd.c src/controller/kbc/kbd.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/input/input.o: src/controller/input/input.c src/controller/input/input.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/palette/palette.o: src/controller/palette/palette.c src/controller/palette/palette.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/view.o: src/view/view.c src/view/view.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/resources/resources.o: src/model/resources/resources.c src/model/resources/resources.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/elements/car/car_view.o: src/view/elements/car/car_view.c src/view/elements/car/car_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/elements/boost/boost.o: src/model/elements/boost/boost.c src/model/elements/boost/boost.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/elements/shield/shield.o: src/model/elements/shield/shield.c src/model/elements/shield/shield.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/terrain/scenery/scenery.o: src/model/terrain/scenery/scenery.c src/model/terrain/scenery/scenery.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/elements/shield/shield_view.o: src/view/elements/shield/shield_view.c src/view/elements/shield/shield_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/elements/boost/boost_view.o: src/view/elements/boost/boost_view.c src/view/elements/boost/boost_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/elements/obstacle/obstacle_view.o: src/view/elements/obstacle/obstacle_view.c src/view/elements/obstacle/obstacle_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/terrain/track/track_view.o: src/view/terrain/track/track_view.c src/view/terrain/track/track_view.h
	${CC} ${CFLAGS} -c $< -o $@


src/view/terrain/scenery/scenery_view.o: src/view/terrain/scenery/scenery_view.c src/view/terrain/scenery/scenery_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/pause/pause_view.o: src/view/screens/pause/pause_view.c src/view/screens/pause/pause_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/menu/menu_view.o: src/view/screens/menu/menu_view.c src/view/screens/menu/menu_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/win/win_view.o: src/view/screens/win/win_view.c src/view/screens/win/win_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/mode_select/mode_select_view.o: src/view/screens/mode_select/mode_select_view.c src/view/screens/mode_select/mode_select_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/car_select/car_select_view.o: src/view/screens/car_select/car_select_view.c src/view/screens/car_select/car_select_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/screens/biome_select/biome_select_view.o: src/view/screens/biome_select/biome_select_view.c src/view/screens/biome_select/biome_select_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/hud/heart/heart_view.o: src/view/hud/heart/heart_view.c src/view/hud/heart/heart_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/hud/timer/timer_view.o: src/view/hud/timer/timer_view.c src/view/hud/timer/timer_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/hud/minimap/minimap_view.o: src/view/hud/minimap/minimap_view.c src/view/hud/minimap/minimap_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/graphics/graphics.o: src/controller/graphics/graphics.c src/controller/graphics/graphics.h
	${CC} -O0 -fno-inline -fno-unroll-loops ${CFLAGS} -c $< -o $@

.include <minix.lcom.mk>