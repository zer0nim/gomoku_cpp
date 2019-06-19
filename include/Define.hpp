#ifndef DEFINE_HPP
#define DEFINE_HPP

#include "utils/color.hpp"
#define BOARD_SZ 19
#define NB_ALIGNED_VICTORY 5
#define NB_DESTROYED_VICTORY 10
#define STONE_EMPTY 0

#define ENABLE_KEEP_NODE_PERCENT true
#define USE_MAX_KEEP_NODE true // if True, use MAX_KEEP_NODE, else... no limit !

#define MINMAX_RANDOM_CHOICE false // choose a random position if we have the choice

// GAMEPLAY
#define SPACE_BEFORE_AI_MOVE false  // press space before AI can move

// DEBUG
#define DEBUG_SEARCH_ZONE false // print the search zone
#define DEBUG_ANTICIPATION true  // print the anticipation
#define DEBUG_KEEP_NODE_PERCENT true  // print all the choice for the first move
#define DEBUG_PRINT_HEURISTIC_VAL false  // print all values of checkReturn on heuristic
#define DEBUG_SHOW_VULNERABILITY true  // show the vulnerables stones

#define DEBUG_RESET_GUI DEBUG_SEARCH_ZONE || DEBUG_ANTICIPATION || DEBUG_KEEP_NODE_PERCENT

#define NB_STONES(game) ((BOARD_SZ * BOARD_SZ) - game.getBoard().getRemainPlaces())

#endif