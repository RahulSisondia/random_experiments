// graph_primer.cpp : This file contains the 'main' function.

#include "../my_util.h"
#include "332_reconstruct_itinerary.h"
#include "cycle_detection.h"
#include "deadlock_detection.h"
#include "dfs_bfs.h"
#include "search_in_maze.h"
#include "shortest_path_dijkstra.h"
#include "team_game.h"
#include "tic_tac_toe.h"
#include "topological_sort.h"
#include "transform_string.h"

int main() {
  // test_team_game();
  // test_deadlock_detection();
  test_topological_sort();
  test_course_schedule_210();
  test_search_in_maze();
  test_dijkstra();
  reconstruct_itinerary();
  test_transform_string();
  test_count_islands();
  test_count_shortestCellPath();
  test_alien_dictionary_269();
  test_tick_tac_toe_348();
  test_find_ladders_126();
  return 0;
}
