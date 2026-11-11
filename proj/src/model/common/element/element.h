/**
 * @file element.h
 * @brief Base game-object structure used by composition throughout the model.
 */

#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>
#include "../sprite/sprite.h"

/**
 * @brief Base structure for any physical game object.
 *
 * Used by composition in Car, Obstacle, Boost, etc.
 */
typedef struct {
    double x;          /**< X position in pixels (lane converted to screen space). */
    double y;          /**< Y position in pixels (track position). */
    int width;         /**< Hitbox width in pixels. */
    int height;        /**< Hitbox height in pixels. */
    bool is_active;    /**< false when the element no longer exists (exploded, collected…). */
    Sprite *sprite;    /**< Managed by the View layer — never freed here. */
} Element;

/**
 * @brief Initialises an already-allocated Element (no malloc — for use in composition).
 * @param el     Pointer to the Element to initialise.
 * @param x      Initial X position in pixels.
 * @param y      Initial Y position in pixels.
 * @param width  Hitbox width in pixels.
 * @param height Hitbox height in pixels.
 */
void init_element(Element *el, double x, double y, int width, int height);

/**
 * @brief Allocates and initialises a standalone Element.
 * @param x      Initial X position in pixels.
 * @param y      Initial Y position in pixels.
 * @param width  Hitbox width in pixels.
 * @param height Hitbox height in pixels.
 * @return Pointer to the new Element, or NULL on allocation failure.
 */
Element* create_element(double x, double y, int width, int height);

/**
 * @brief Frees a standalone Element.
 * @param el Element to destroy.
 */
void destroy_element(Element *el);

/**
 * @brief AABB collision test between two active elements.
 * @param el1 First element.
 * @param el2 Second element.
 * @return true if both elements are active and their bounding boxes overlap.
 */
bool check_collision(Element *el1, Element *el2);

#endif /* ELEMENT_H */
