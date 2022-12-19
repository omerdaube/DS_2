#include "worldcup23a2.h"

using std::make_shared;

int world_cup_t::getHashPlayerID(shared_ptr<Player> p){
    return p->getPlayerID();
}


world_cup_t::world_cup_t() : avlTeams(), rankAvlTeamsByAbility(), numberOfTeams(0),
                                hashPlayers(Hash<shared_ptr<Player>, PlayersByID>(&getHashPlayerID)) {};

void world_cup_t::Union(shared_ptr<Team> t1, shared_ptr<Team> t2)
{
    if (t1 == t2) {
        return;
    }
    if (t1->getNumPlayers() >= t2->getNumPlayers()) {
        t2->getRoot()->setExtraSpirit(((t1->getRoot()->getExtraSpirit()).inv())*(t1->getTeam)*(t2->getRoot()->getExtraSpirit()));
        t2->getRoot()->setFather(t1->getRoot());
        t2->getRoot()->setTeam(shared_ptr<Team>());
        t1->setNumPlayers(t1->getNumPlayers() + t2->getNumPlayers());
        t2->setRoot(nullptr);
        t2 = shared_ptr<Team>();
    }
    else {
        t1->getRoot()->setFather(t2->getRoot());
        t1->getRoot()->setTeam(shared_ptr<Team>());
        t2->setNumPlayers(t2->getNumPlayers() + t1->getNumPlayers());
        t1->setRoot(nullptr);
        t1 = shared_ptr<Team>();
    }
}

shared_ptr<Team> world_cup_t::Find(int playerID)
{
    shared_ptr<Player> player = hashPlayers.find(playerID);
    shared_ptr<Player> root = player;
    while ((root) && (root->getFather())) {
        root = root->getFather();
    }
    shared_ptr<Player> prevFather;
    while ((player) && (player->getFather())) {
        prevFather = player->getFather();
        player->setFather(root);
        player = prevFather;
    }
    return root->getTeam();
}

world_cup_t::world_cup_t()
{
}

world_cup_t::~world_cup_t()
{
    avlTeams.deleteAll2();
    rankAvlTeamsByAbility.deleteAll2();
}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if(avlTeams.search(teamId) != nullptr) {
        return StatusType::FAILURE;
    }
    shared_ptr<Team> newTeam = make_shared<Team>(teamId);
    avlTeams.add(newTeam);
    rankAvlTeamsByAbility.add(newTeam);
    numberOfTeams++;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    AVL<shared_ptr<Team>, TeamsByID> *ret = avlTeams.search(teamId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    avlTeams.remove(ret->getData());
    rankAvlTeamsByAbility.remove(ret->getData());
    numberOfTeams--;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper)
{
	// TOO: Your goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID> *retT1 = avlTeams.search(teamId1);
    AVL<shared_ptr<Team>, TeamsByID> *retT2 = avlTeams.search(teamId2);
    if (retT1 == nullptr || retT2 == nullptr){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> team1 = retT1->getData(), team2 = retT2->getData();
    if (!(team1->hasGoalKeeper()) ||
        !(team2->hasGoalKeeper())){
        return StatusType::FAILURE;
    }
    team1->gameWasPlayed();
    team2->gameWasPlayed();
    if(team1->getTeamPoints() + team1->getTeamAbility() > team2->getTeamPoints() + team2->getTeamAbility()) {
        team1->addTeamPoints(3);
    }
    else if(team1->getTeamPoints() + team1->getTeamAbility() < team2->getTeamPoints() + team2->getTeamAbility()) {
        team2->addTeamPoints(3);
    }
    else{
        if(team1->getStrength() > team2->getStrength()){
            team1->addTeamPoints(3);
        }
        else if(team1->getStrength() < team2->getStrength()){
            team2->addTeamPoints(3);
        }
        else{
            team1->addTeamPoints(1);
            team2->addTeamPoints(1);
        }
    }
    return StatusType::SUCCESS;}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Player> p = hashPlayers.find(playerId);
    if(p == nullptr){
        return StatusType::FAILURE;
    }
    return p->getCards();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    AVL<shared_ptr<Team>, TeamsByID> *ret = avlTeams.search(teamId);
    if(ret == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(ret->getData()->getTeamPoints());}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if(0 > i || i >= numberOfTeams || numberOfTeams <= 0){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> t = rankAvlTeamsByAbility.select(i+1);
	return t->getTeamID();
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	return StatusType::SUCCESS;
}
