// shared_ptr.cpp : This file contains the 'main' function. Program execution
// begins and ends there.

#include <iostream>
#include <memory>

using namespace std;
class Player;

//class Team {
// public:
//  Team() : m_player(nullptr) { cout << "Team::Team()\n"; };
//  ~Team() { cout << "Team::~Team() Team::m_player"<< m_player.use_count() <<"\n"; }
//  shared_ptr<Player> m_player;
//};
//
//
//class Player {
//public:
//	Player(Team* t)
//		: m_team(t)
//	{
//		std::cout << "stp count before " << m_team.use_count() << "\n";
//		m_team->m_player.reset(this);
//		cout << "Player::Player()"<<"\n";
//		std::cout << "stp count again " << m_team.use_count() << "\n";
//	}
//	~Player() {
//		cout << "Player::~Player() Team::count "<< m_team.use_count() << " Team::m_player::count "
//			<< m_team->m_player.use_count()<<"\n";
//	}
//	shared_ptr<Team> m_team;
//};


class Team {
public:
	Team() : m_player(nullptr) { cout << "Team::Team()\n"; };
	~Team() { cout << "Team::~Team() Team::m_player" << m_player.use_count() << "\n"; }
	shared_ptr<Player> m_player;
};


class Player {
public:
	Player(shared_ptr<Team>& t)
		: m_team(t)
	{
		std::cout << "stp count before " << m_team.use_count() << "\n";
		t->m_player.reset(this);
		cout << "Player::Player()" << "\n";
		std::cout << "stp count again " << m_team.use_count() << "\n";
	}
	~Player() {
		cout << "Player::~Player() Team::count " << m_team.use_count() << "\n";
	}
	shared_ptr<Team> m_team;
};


int main() {
	Team *t = new Team;
	shared_ptr<Team> tsp(t);
	Player *p = new Player(tsp);
	cout << "after tsp count" << tsp.use_count() << endl;
	delete p;
	return 0;
}
