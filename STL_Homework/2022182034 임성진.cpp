#include <iostream>
#include <fstream>
#include <print>
#include <array>
#include <ranges>
using namespace std;

class Player
{
public:
	void read(ifstream& in)
	{
		in.read((char*)this, sizeof(Player) - sizeof(p));

		in.seekg(sizeof(p), ios::cur);

		if (num > 0) {
			p = make_unique<char[]>(num);
			in.read(p.get(), num);
		}
	}
private:
	string name;			// 이름, 길이[3, 15], ['a', 'z']로만 구성
	int score;				// 점수, 정규분포
	size_t id;				// 아이디, 겹치는 아이디 있을 수 있음
	size_t num;				// free store에 확보한 바이트 수
	unique_ptr<char[]> p;	// free store에 확보한 메모리

	friend ostream& operator<<(ostream& os, const Player& player)
	{
		print(os, "이름: {:15}, 아이디: {}, 점수: {}, 자원수: {}\n저장된 글자:{}\n",
			player.name, player.score, player.id, player.num, player.p.get());
		return os;
	}
};

array<Player, 300'0000> playerArr{};

int main()
{
	ifstream in{ "2026 STL 과제 파일 - 2022182034", ios::binary };
	if (not in)
	{
		cout << "파일이 존재하지 않습니다." << endl;
		return 2022182034;
	}

	for(auto& player : playerArr)
		player.read(in);

	for (const auto& player : playerArr | views::take(10000))
		cout << player << endl;
}