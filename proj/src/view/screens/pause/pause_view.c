#include "pause_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"

void pause_view_draw(int selected) {
    draw_sprite(resources_get_pause_panel(),               PAUSE_PANEL_X, PAUSE_PANEL_Y);
    draw_sprite(resources_get_pause_resume_btn(selected == 0), PAUSE_BTN_X, PAUSE_RESUME_Y);
    draw_sprite(resources_get_pause_quit_btn  (selected == 1), PAUSE_BTN_X, PAUSE_QUIT_Y);
}
