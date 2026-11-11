#include "element.h"
#include <stdlib.h>

void init_element(Element* el, double x, double y, int width, int height) {
    el->x         = x;
    el->y         = y;
    el->width     = width;
    el->height    = height;
    el->is_active = true;
    el->sprite    = NULL;
}

Element* create_element(double x, double y, int width, int height) {
    Element* el = (Element*) malloc(sizeof(Element));
    if (el == NULL) return NULL;
    init_element(el, x, y, width, height);
    return el;
}

void destroy_element(Element* el) {
    if (el != NULL) {
        // Sprite é propriedade da View — não se liberta aqui
        free(el);
    }
}

bool check_collision(Element* el1, Element* el2) {
    if (el1 == NULL || el2 == NULL || !el1->is_active || !el2->is_active)
        return false;

    bool collision_x = (el1->x < el2->x + el2->width)  && (el1->x + el1->width  > el2->x);
    bool collision_y = (el1->y < el2->y + el2->height) && (el1->y + el1->height > el2->y);

    return collision_x && collision_y;
}
