#ifndef DEFINE_HPP
#define DEFINE_HPP

#include "utils/color.hpp"
#ifndef BOARD_SZ
	#define BOARD_SZ 19
#endif
#ifndef NB_ALIGNED_VICTORY
	#define NB_ALIGNED_VICTORY 5
#endif
#ifndef NB_DESTROYED_VICTORY
	#define NB_DESTROYED_VICTORY 10
#endif
#define STONE_EMPTY 0

#define USE_MAX_KEEP_NODE true // if True, use MAX_KEEP_NODE, else... no limit !

#define MINMAX_RANDOM_CHOICE true // choose a random position if we have the choice
#define THR_DEPTH 1 // number of depth using thread in minimax algorithm

// GAMEPLAY
#define SPACE_BEFORE_AI_MOVE false  // press space before AI can move

// DEBUG
#define DEBUG_SEARCH_ZONE false // print the search zone
#define DEBUG_ANTICIPATION false  // print the anticipation
#define DEBUG_KEEP_NODE_PERCENT false  // print all the choice for the first move
#define DEBUG_PRINT_HEURISTIC_VAL false  // print all values of checkReturn on heuristic
#define DEBUG_SHOW_VULNERABILITY false  // show the vulnerables stones

#define DEBUG_RESET_GUI DEBUG_SEARCH_ZONE || DEBUG_ANTICIPATION || DEBUG_KEEP_NODE_PERCENT

#define NB_STONES(game) ((BOARD_SZ * BOARD_SZ) - game.getBoard().getRemainPlaces())

#define DEFAULT_DIFFICULTY 2  // from 0 to 2
// default players -> 0->AI, 1->Real, 2->Hybride
#define PLAYER1_TYPE 2
#define PLAYER2_TYPE 0

#endif