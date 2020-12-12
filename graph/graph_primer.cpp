// graph_primer.cpp : This file contains the 'main' function.

#include "../my_util.h"
#include "210_course_schedule.h"
#include "332_reconstruct_itinerary.h"
#include "deadlock_detection.h"
#include "search_in_maze.h"
#include "shortest_path_dijkstra.h"
#include "team_game.h"
#include "topological_sort.h"
#include "transform_string.h"

int main() {
  // test_team_game();
  // test_deadlock_detection();
  test_topological_sort();
  test_course_schedule_210();
  test_search_in_maze();
  test_dijkstra();
  resonstruct_itinerary();
  test_transform_string();
  return 0;
}
