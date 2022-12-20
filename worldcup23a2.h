// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef WORLDCUP23A2_H_
#define WORLDCUP23A2_H_

#include "wet2util.h"
#include "Team.h"
#include "Player.h"

#include "RankAVL.h"
#include "PlayersByID.h"
#include "Player.h"
#include "TeamsByID.h"
#include "Team.h"
#include "TeamsByAbility.h"
#include "Hash.h"
#include <memory>
class world_cup_t {
private:
	//
	// Here you may add anything you want
	//
    //static int getHashPlayerID(shared_ptr<Player> p);

	void Union(shared_ptr<Player> root1, shared_ptr<Player> root2);
    shared_ptr<Team> Find(int playerID);
    AVL<shared_ptr<Team>, TeamsByID> avlTeams;
    RankAVL<shared_ptr<Team>, TeamsByAbility> rankAvlTeamsByAbility;
    Hash<shared_ptr<Player>, PlayersByID> hashPlayers;
    int numberOfTeams;
public:
	// <DO-NOT-MODIFY> {

    world_cup_t();
	virtual ~world_cup_t();
	
	StatusType add_team(int teamId);
	
	StatusType remove_team(int teamId);
	
	StatusType add_player(int playerId, int teamId,
	                      const permutation_t &spirit, int gamesPlayed,
	                      int ability, int cards, bool goalKeeper);
	
	output_t<int> play_match(int teamId1, int teamId2);
	
	output_t<int> num_played_games_for_player(int playerId);
	
	StatusType add_player_cards(int playerId, int cards);
	
	output_t<int> get_player_cards(int playerId);
	
	output_t<int> get_team_points(int teamId);
	
	output_t<int> get_ith_pointless_ability(int i);
	
	output_t<permutation_t> get_partial_spirit(int playerId);
	
	StatusType buy_team(int teamId1, int teamId2);
	
	// } </DO-NOT-MODIFY>
};

#endif // WORLDCUP23A1_H_