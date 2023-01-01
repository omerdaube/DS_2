#include "worldcup23a2.h"

using std::make_shared;

int getHashPlayerID(shared_ptr<Player> p){
    return p->getPlayerID();
}

void world_cup_t::Union(shared_ptr<Player> root1, shared_ptr<Player> root2)
{
    if (root1 == root2) {
        return;
    }
    if (root1->getTeam()->getNumPlayers() >= root2->getTeam()->getNumPlayers()) { //mistake:
        root2->setExtraGames(root2->getExtraGames() - root1->getExtraGames());
        root2->setExtraSpirit(((root1->getExtraSpirit()).inv())*(root1->getTeam()->getTeamSpirit())*(root2->getExtraSpirit()));
        root2->setFather(root1);
        if(root1->getTeam() != root2->getTeam()) {
            root2->getTeam()->setRoot(nullptr);
        }
        root2->setTeam(nullptr);
        //root1->getTeam()->setNumPlayers(root1->getTeam()->getNumPlayers() + root2->getTeam()->getNumPlayers());
    }
    else {
        root1->setExtraGames(root1->getExtraGames() - root2->getExtraGames());
        root2->setExtraSpirit((root1->getTeam()->getTeamSpirit())*(root2->getExtraSpirit()));
        root1->setExtraSpirit(((root2->getExtraSpirit()).inv())*(root1->getExtraSpirit()));
        root1->setFather(root2);
//        if(root1->getTeam() != root2->getTeam()){
//            root1->getTeam()->setRoot(nullptr);
//        }
        root1->getTeam()->setRoot(root2);
        root2->getTeam()->setRoot(nullptr);
        root2->setTeam(root1->getTeam());
        root1->setTeam(nullptr);
        //root2->getTeam()->setNumPlayers(root2->getTeam()->getNumPlayers() + root1->getTeam()->getNumPlayers());
    }
}

shared_ptr<Team> world_cup_t::Find(int playerID)
{
    shared_ptr<Player> player = hashPlayers.find(playerID);
    shared_ptr<Player> root = player;
    permutation_t mul = permutation_t().neutral();
    int sum = 0;
    while ((root) && (root->getFather())) {
        mul = (root->getExtraSpirit())*mul;
        sum += root->getExtraGames();
        root = root->getFather();
    }
    shared_ptr<Player> prevFather;
    permutation_t oldSpirit;
    int oldSum;
    while ((player) && (player->getFather())) {
        prevFather = player->getFather();
        oldSum = player->getExtraGames();
        player->setExtraGames(sum);
        sum -= oldSum;
        oldSpirit = player->getExtraSpirit();
        player->setExtraSpirit(mul);
        mul = mul*(oldSpirit.inv());
        player->setFather(root);
        player = prevFather;
    }
    return root->getTeam();
}

world_cup_t::world_cup_t() : avlTeams(), rankAvlTeamsByAbility(), hashPlayers(&getHashPlayerID), numberOfTeams(0)
{

}

world_cup_t::~world_cup_t()
{
    avlTeams.deleteAll2();
    rankAvlTeamsByAbility.deleteAll2();
    tryDelete();
}

void removePointer(AVL<shared_ptr<Player>, PlayersByID>* a){
    if(a == nullptr){
        return;
    }
    removePointer(a->getLeft());
    if(a->getData() != nullptr) {
        a->getData()->resetPlayer();
    }
    removePointer(a->getRight());
}

void world_cup_t::tryDelete(){
    AVL<shared_ptr<Player>, PlayersByID> ** arr = hashPlayers.getArray();
    int size = hashPlayers.getSize();
    for (int i = 0; i < size; ++i) {
        removePointer(arr[i]);
    }
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
    shared_ptr<Team> t = ret->getData();
    t->outOfGame();
    avlTeams.remove(t);
    rankAvlTeamsByAbility.remove(t);
    numberOfTeams--;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper)
{
    if(playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0){
        return StatusType::ALLOCATION_ERROR;
    }
    AVL<shared_ptr<Team>, TeamsByID> *retT1 = avlTeams.search(teamId);
    shared_ptr<Player> p = hashPlayers.find(playerId);
    if (retT1 == nullptr || p != nullptr){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> t = retT1->getData();
    rankAvlTeamsByAbility.remove(t);

    shared_ptr<Player> newP = make_shared<Player>(playerId, retT1->getData(), gamesPlayed, spirit, ability, cards, goalKeeper);
    if(t->getNumPlayers() > 0){
        Union(t->getRoot(), newP);
    }
    else{
        t->setRoot(newP);
    }
    t->addedPlayer(ability, spirit, goalKeeper);
    hashPlayers.add(newP);
    rankAvlTeamsByAbility.add(t);
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
        return 1;
    }
    else if(team1->getTeamPoints() + team1->getTeamAbility() < team2->getTeamPoints() + team2->getTeamAbility()) {
        team2->addTeamPoints(3);
        return 3;
    }
    else{
        if(team1->getStrength() > team2->getStrength()){
            team1->addTeamPoints(3);
            return 2;
        }
        else if(team1->getStrength() < team2->getStrength()){
            team2->addTeamPoints(3);
            return 4;
        }
        else{
            team1->addTeamPoints(1);
            team2->addTeamPoints(1);
            return 0;
        }
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Player> p = hashPlayers.find(playerId);
    if(p == nullptr){
        return StatusType::FAILURE;
    }
    Find(playerId); //kivutz

    if(p->getFather() == nullptr){
        return p->getExtraGames();
    }
    return p->getFather()->getExtraGames() + p->getExtraGames();
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(cards < 0 || playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Player> p = hashPlayers.find(playerId);
    if(p == nullptr){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> t = Find(playerId);
    if(!t->isInGame()){
        return StatusType::FAILURE;
    }
    p->addCards(cards);
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
    return output_t<int>(ret->getData()->getTeamPoints());
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if(0 > i || i >= numberOfTeams || numberOfTeams <= 0){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> t = rankAvlTeamsByAbility.select(i+1);
	return t->getTeamID();
   // return 0;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Player> p = hashPlayers.find(playerId);
    if(p== nullptr){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> t = Find(playerId);
    if(!(t->isInGame())){
        return StatusType::FAILURE;
    }
    if(p->getFather() == nullptr){
        return p->getExtraSpirit();
    }
	return p->getFather()->getExtraSpirit() * p->getExtraSpirit();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if(teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID> *retT1 = avlTeams.search(teamId1);
    AVL<shared_ptr<Team>, TeamsByID> *retT2 = avlTeams.search(teamId2);
    if (retT1 == nullptr || retT2 == nullptr){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> t1 = retT1->getData();
    shared_ptr<Team> t2 = retT2->getData();
    avlTeams.remove(t2);
    rankAvlTeamsByAbility.remove(t2);
    rankAvlTeamsByAbility.remove(t1);
    //t2->resetTeam();
    //didnt check if team empty
    if(t2->getNumPlayers() <= 0){
        numberOfTeams--;
        t2->outOfGame();
        rankAvlTeamsByAbility.add(t1);
        return StatusType::SUCCESS;
    }
    if(t1->getNumPlayers() <= 0){
        t2->getRoot()->setTeam(t1);
        t1->setRoot(t2->getRoot());
        t2->setRoot(nullptr);
        t2->outOfGame();
        t1->bought(t2);
        rankAvlTeamsByAbility.add(t1);
        numberOfTeams--;
        return StatusType::SUCCESS;
    }
    Union(t1->getRoot(), t2->getRoot());
    t2->outOfGame();
    t1->bought(t2);
    rankAvlTeamsByAbility.add(t1);
    numberOfTeams--;
    return StatusType::SUCCESS;
}