#include "instructions_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../model/common/sprite/sprite.h"
#include "../../../controller/input/input.h"
#include "../../../controller/palette/palette.h"

#include "../../../assets/xpm/ui/screens/main/race_desc.xpm"
#include "../../../assets/xpm/ui/screens/main/endur_desc.xpm"
#include "../../../assets/xpm/ui/screens/main/race_mini.xpm"
#include "../../../assets/xpm/ui/screens/main/endur_mini.xpm"

#include "config.h"

#define PANEL_X         62
#define PANEL_Y         50
#define PANEL_W        900
#define PANEL_H        660

#define DIVIDER_X      (PANEL_X + PANEL_W / 2)

#define CARD_W         240
#define CARD_H         240
#define CARD_Y         115

#define RACE_CARD_X    (PANEL_X + (PANEL_W / 2 - CARD_W) / 2)
#define ENDUR_CARD_X   (PANEL_X + PANEL_W / 2 + (PANEL_W / 2 - CARD_W) / 2)

#define LABEL_Y        (CARD_Y - 40)

/* description text XPMs: 20 px tall */
#define DESC_Y         (CARD_Y + CARD_H + 10)

#define ICON_W          56
#define ICON_H          56
#define ICON_Y         (DESC_Y + 22 + 10)
#define ICON_GAP        14

#define MINI_Y         (ICON_Y + ICON_H + 14)

/* lazily created sprites from local XPMs */
static Sprite *s_race_desc  = NULL;
static Sprite *s_endur_desc = NULL;
static Sprite *s_race_mini  = NULL;
static Sprite *s_endur_mini = NULL;

static void ensure_desc_sprites(void) {
    if (!s_race_desc)  s_race_desc  = create_sprite((xpm_map_t)race_desc_xpm);
    if (!s_endur_desc) s_endur_desc = create_sprite((xpm_map_t)endur_desc_xpm);
    if (!s_race_mini)  s_race_mini  = create_sprite((xpm_map_t)race_mini_xpm);
    if (!s_endur_mini) s_endur_mini = create_sprite((xpm_map_t)endur_mini_xpm);
}

static void draw_icons_row(int center_x, int y, Sprite **icons, int count) {
    int total = count * ICON_W + (count - 1) * ICON_GAP;
    int x = center_x - total / 2;
    for (int i = 0; i < count; i++) {
        if (icons[i]) draw_sprite_scaled(icons[i], x, y, ICON_W, ICON_H);
        x += ICON_W + ICON_GAP;
    }
}

void instructions_view_draw(void) {
    ensure_desc_sprites();

    draw_rect(PANEL_X, PANEL_Y, PANEL_W, PANEL_H, PAL_MENU_DARK);
    draw_rect(DIVIDER_X - 1, PANEL_Y + 16, 2, PANEL_H - 32, PAL_GREY_MID);

    /* ── RACE ─────────────────────────────────────────────── */
    int race_cx = PANEL_X + PANEL_W / 4;

    Sprite *rl = resources_get_mode_race_label();
    if (rl) draw_sprite(rl, race_cx - rl->width / 2, LABEL_Y);

    Sprite *rc = resources_get_mode_race_card();
    if (rc) draw_sprite_scaled(rc, RACE_CARD_X, CARD_Y, CARD_W, CARD_H);

    if (s_race_desc)
        draw_sprite(s_race_desc, race_cx - s_race_desc->width / 2, DESC_Y);

    Sprite *race_icons[] = {
        resources_get_city_boost_sprite(0),
        resources_get_city_obstacle_sprite(0),
        resources_get_banana_sprite(0),
        resources_get_heart_sprite()
    };
    draw_icons_row(race_cx, ICON_Y, race_icons, 4);

    if (s_race_mini)
        draw_sprite(s_race_mini, race_cx - s_race_mini->width / 2, MINI_Y);

    /* ── ENDURANCE ────────────────────────────────────────── */
    int endur_cx = PANEL_X + 3 * PANEL_W / 4;

    Sprite *el = resources_get_mode_endurance_label();
    if (el) draw_sprite(el, endur_cx - el->width / 2, LABEL_Y);

    Sprite *ec = resources_get_mode_endurance_card();
    if (ec) draw_sprite_scaled(ec, ENDUR_CARD_X, CARD_Y, CARD_W, CARD_H);

    if (s_endur_desc)
        draw_sprite(s_endur_desc, endur_cx - s_endur_desc->width / 2, DESC_Y);

    Sprite *endur_icons[] = {
        resources_get_city_obstacle_sprite(0),
        resources_get_banana_sprite(0),
        resources_get_heart_sprite()
    };
    draw_icons_row(endur_cx, ICON_Y, endur_icons, 3);

    if (s_endur_mini)
        draw_sprite(s_endur_mini, endur_cx - s_endur_mini->width / 2, MINI_Y);

    draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
}
