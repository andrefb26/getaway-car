/**
 * @file palette.h
 * @brief 256-entry indexed colour palette used by all sprites and drawing calls.
 */

#ifndef __PROJ_PALETTE_H
#define __PROJ_PALETTE_H

#include <stdint.h>

/** @defgroup pal_base Block 0: Base colours (indices 0–7)
 * @{ */
#define PAL_BLACK          0 /**< Pure black. */
#define PAL_WHITE          1 /**< Pure white. */
#define PAL_GREY_LIGHT     2 /**< Light grey. */
#define PAL_GREY_MID       3 /**< Mid grey. */
#define PAL_GREY_DARK      4 /**< Dark grey. */
#define PAL_GREY_VERY_DARK 5 /**< Very dark grey. */
#define PAL_OFF_WHITE      6 /**< Off-white. */
#define PAL_CREAM          7 /**< Cream. */
/** @} */

/** @defgroup pal_track Block 1: Road/track colours (indices 8–23)
 * @{ */
#define PAL_ASPHALT_DARK   8  /**< Dark asphalt. */
#define PAL_ASPHALT_MID    9  /**< Mid asphalt. */
#define PAL_ASPHALT_BASE  10  /**< Base asphalt. */
#define PAL_ASPHALT_LIGHT 11  /**< Light asphalt. */
#define PAL_LANE_MARK     12  /**< Lane marking stripe. */
#define PAL_CENTRE_LINE   13  /**< Centre divider line. */
#define PAL_KERB_WHITE    14  /**< Kerb white. */
#define PAL_KERB_RED      15  /**< Kerb red. */
#define PAL_FINISH_DARK   16  /**< Dark finish-line stripe. */
#define PAL_FINISH_LIGHT  17  /**< Light finish-line stripe. */
#define PAL_ROAD_EDGE     18  /**< Road shoulder edge. */
#define PAL_TYRE_MARK     19  /**< Tyre mark on asphalt. */
/** @} */

/** @defgroup pal_scenery Block 2: Lateral scenery colours (indices 24–39)
 * @{ */
#define PAL_GRASS_BASE    24 /**< Base grass green. */
#define PAL_GRASS_DARK    25 /**< Dark grass shadow. */
#define PAL_GRASS_LIGHT   26 /**< Light grass highlight. */
#define PAL_GRASS_DRY     27 /**< Dry/yellowed grass. */
#define PAL_TREE_DARK     28 /**< Dark tree foliage. */
#define PAL_TREE_MID      29 /**< Mid tree foliage. */
#define PAL_TREE_LIGHT    30 /**< Light tree foliage highlight. */
#define PAL_TREE_TRUNK    31 /**< Tree trunk brown. */
#define PAL_SKY_BLUE      32 /**< Sky blue. */
#define PAL_SKY_LIGHT     33 /**< Light sky. */
#define PAL_FENCE_GREY    34 /**< Fence grey. */
#define PAL_FENCE_DARK    35 /**< Fence dark. */
/** @} */

/** @defgroup pal_car1 Block 3: Player 1 car — blue (indices 40–55)
 * @{ */
#define PAL_CAR1_NORMAL   40 /**< Body colour — normal. */
#define PAL_CAR1_HILITE   41 /**< Body highlight. */
#define PAL_CAR1_SHADOW   42 /**< Body shadow. */
#define PAL_CAR1_WINDOW   43 /**< Window. */
#define PAL_CAR1_WHEEL    44 /**< Wheel tyre. */
#define PAL_CAR1_RIM      45 /**< Wheel rim. */
#define PAL_CAR1_DETAIL   46 /**< Detail accent. */
#define PAL_CAR1_HEADLT   47 /**< Headlight. */
#define PAL_CAR1_TAILLT   48 /**< Tail light. */
#define PAL_CAR1_DAMAGED  49 /**< Body — damaged state. */
#define PAL_CAR1_DMG_DRK  50 /**< Body — damaged shadow. */
#define PAL_CAR1_BURNING  51 /**< Body — burning state. */
#define PAL_CAR1_FLAME    52 /**< Flame. */
#define PAL_CAR1_SMOKE    53 /**< Smoke. */
#define PAL_CAR1_EXPLODED 54 /**< Body — exploded state. */
#define PAL_CAR1_EXP_DRK  55 /**< Body — exploded shadow. */
/** @} */

/** @defgroup pal_car2 Block 4: Player 2 car — red (indices 56–71)
 * @{ */
#define PAL_CAR2_NORMAL   56 /**< Body colour — normal. */
#define PAL_CAR2_HILITE   57 /**< Body highlight. */
#define PAL_CAR2_SHADOW   58 /**< Body shadow. */
#define PAL_CAR2_WINDOW   59 /**< Window. */
#define PAL_CAR2_DAMAGED  60 /**< Body — damaged state. */
#define PAL_CAR2_DMG_DRK  61 /**< Body — damaged shadow. */
#define PAL_CAR2_BURNING  62 /**< Body — burning state. */
#define PAL_CAR2_FLAME    63 /**< Flame. */
#define PAL_CAR2_SMOKE    64 /**< Smoke. */
#define PAL_CAR2_EXPLODED 65 /**< Body — exploded state. */
#define PAL_CAR2_EXP_DRK  66 /**< Body — exploded shadow. */
/** @} */

/** @defgroup pal_car3 Block 5: Car 3 — yellow (indices 72–87)
 * @{ */
#define PAL_CAR3_NORMAL   72 /**< Body colour — normal. */
#define PAL_CAR3_HILITE   73 /**< Body highlight. */
#define PAL_CAR3_SHADOW   74 /**< Body shadow. */
#define PAL_CAR3_WINDOW   75 /**< Window. */
#define PAL_CAR3_DAMAGED  76 /**< Body — damaged state. */
/** @} */

/** @defgroup pal_car4 Block 6: Car 4 — green (indices 88–103)
 * @{ */
#define PAL_CAR4_NORMAL   88 /**< Body colour — normal. */
#define PAL_CAR4_HILITE   89 /**< Body highlight. */
#define PAL_CAR4_SHADOW   90 /**< Body shadow. */
#define PAL_CAR4_WINDOW   91 /**< Window. */
#define PAL_CAR4_DAMAGED  92 /**< Body — damaged state. */
/** @} */

/** @defgroup pal_boost Block 7: Boost pickup (indices 104–119)
 * @{ */
#define PAL_BOOST_BASE    104 /**< Base colour. */
#define PAL_BOOST_GLOW    105 /**< Glow halo. */
#define PAL_BOOST_DARK    106 /**< Dark shadow. */
#define PAL_BOOST_OUTLINE 107 /**< Outline. */
#define PAL_BOOST_STAR    108 /**< Star accent. */
#define PAL_BOOST_STAR2   109 /**< Secondary star accent. */
#define PAL_BOOST_LIGHT   110 /**< Light highlight. */
/** @} */

/** @defgroup pal_banana Block 8: Banana peel (indices 120–126)
 * @{ */
#define PAL_BANANA_YELLOW 120 /**< Main body yellow. */
#define PAL_BANANA_DARK   121 /**< Shadow / border. */
#define PAL_BANANA_LIGHT  122 /**< Light highlight. */
#define PAL_BANANA_BROWN  123 /**< Spots / crease. */
#define PAL_BANANA_STEM   124 /**< Stem tip. */
#define PAL_BANANA_TIP    125 /**< Banana tip. */
#define PAL_BANANA_INNER  126 /**< Cream inner flesh. */
/** @} */

/** @defgroup pal_ui Block 9: HUD and UI colours (indices 136–158)
 * @{ */
#define PAL_HUD_BG        136 /**< HUD background. */
#define PAL_HUD_BORDER    137 /**< HUD border. */
#define PAL_HUD_TEXT      138 /**< HUD text. */
#define PAL_HUD_YELLOW    139 /**< HUD yellow accent. */
#define PAL_HUD_RED       140 /**< HUD red accent. */
#define PAL_HUD_GREEN     141 /**< HUD green accent. */
#define PAL_HEALTH_FULL   142 /**< Health bar — full. */
#define PAL_HEALTH_MID    143 /**< Health bar — mid. */
#define PAL_HEALTH_LOW    144 /**< Health bar — low. */
#define PAL_P1_INDICATOR  145 /**< Player 1 lane indicator. */
#define PAL_P2_INDICATOR  146 /**< Player 2 lane indicator. */

#define PAL_MENU_DARK     147 /**< Menu dark background. */
#define PAL_BTN_RED       148 /**< Button red fill. */
#define PAL_BTN_RED_DRK   149 /**< Button red shadow. */
#define PAL_BTN_RED_LGT   150 /**< Button red highlight. */
#define PAL_BTN_YLW       151 /**< Button yellow fill. */
#define PAL_BTN_YLW_LGT   152 /**< Button yellow highlight. */
#define PAL_BTN_YLW_DRK   153 /**< Button yellow shadow. */
#define PAL_TTL_BLUE      154 /**< Title blue. */
#define PAL_TTL_NEAR_BLACK 155 /**< Title near-black. */
#define PAL_TTL_BLUE_LGT  156 /**< Title light blue. */
#define PAL_TTL_PINK      157 /**< Title pink. */
#define PAL_TTL_GREY      158 /**< Title grey. */
/** @} */

#define PAL_TRANSPARENT   255 /**< Transparent — pixels with this index are not drawn. */

/**
 * @brief The game's 256-entry RGB colour table.
 *
 * Each entry is three bytes: R, G, B (each 0–255).
 * Indexed by the palette-index constants above.
 */
extern const uint8_t GAME_PALETTE[256][3];

/**
 * @brief Registers GAME_PALETTE with the VBE DAC (programmes the hardware palette).
 */
void    palette_load(void);

/**
 * @brief Finds the palette index closest to the given RGB triple.
 * @param r Red component (0–255).
 * @param g Green component (0–255).
 * @param b Blue component (0–255).
 * @return Palette index of the nearest colour.
 */
uint8_t palette_find_index(uint8_t r, uint8_t g, uint8_t b);

#endif /* __PROJ_PALETTE_H */
