#include "worldcup23a2.h"
#include <iostream>
using std::cout;
int main()
{
    world_cup_t wc;
    wc.add_team(1);
    wc.add_team(3);
    wc.add_team(4);
    wc.add_team(5);
    wc.add_team(2);
    wc.remove_team(4);
    wc.add_team(6);
    wc.play_match(3,6);
    wc.play_match(1,2);
    wc.play_match(3,2);
    cout << wc.get_team_points(3).ans();
    return 0;
}