/**
 * @file boost_view.h
 * @brief Boost pickup rendering: draws the boost sprite at its screen position.
 */

#ifndef __PROJ_BOOST_VIEW_H
#define __PROJ_BOOST_VIEW_H

#include "../../../model/elements/boost/boost.h"

/**
 * @brief Draws the boost sprite if the boost is active and on screen.
 * @param boost Boost to render.
 */
void boost_view_draw(Boost *boost);

#endif /* __PROJ_BOOST_VIEW_H */
