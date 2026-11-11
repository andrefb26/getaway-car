#include "cursor.h"
#include <stdlib.h>

Cursor* create_cursor(int initial_x, int initial_y, int screen_w, int screen_h) {
    Cursor *cursor = malloc(sizeof(Cursor)); //precisamos que a variavel persista ao acabar a funçao entao vai para a heap
    if (cursor == NULL) return NULL;// verificar se o malloc falhou

    cursor->x        = initial_x;
    cursor->y        = initial_y;
    cursor->screen_w = screen_w;
    cursor->screen_h = screen_h;
    cursor->clicked    = false;
    cursor->lb_prev    = false;
    cursor->rb_clicked = false;
    cursor->rb_prev    = false;

    return cursor;
}

void destroy_cursor(Cursor *cursor) {
    free(cursor);
}

void cursor_update(Cursor *cursor, int dx, int dy, bool lb_current, bool rb_current) {
    if (cursor == NULL) return;

    cursor->x += dx;
    cursor->y -= dy;

    if (cursor->x < 0)                 cursor->x = 0;
    if (cursor->x >= cursor->screen_w) cursor->x = cursor->screen_w - 1;
    if (cursor->y < 0)                 cursor->y = 0;
    if (cursor->y >= cursor->screen_h) cursor->y = cursor->screen_h - 1;

    cursor->clicked    = lb_current && !cursor->lb_prev;
    cursor->rb_clicked = rb_current && !cursor->rb_prev;

    cursor->lb_prev = lb_current;
    cursor->rb_prev = rb_current;
}

int  cursor_get_x(const Cursor *cursor)          { return cursor->x; }
int  cursor_get_y(const Cursor *cursor)          { return cursor->y; }
bool cursor_left_clicked(const Cursor *cursor)   { return cursor->clicked; }
bool cursor_right_clicked(const Cursor *cursor)  { return cursor->rb_clicked; }
