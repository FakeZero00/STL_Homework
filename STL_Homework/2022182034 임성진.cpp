#include <iostream>
#include <fstream>
#include <print>
#include <array>
#include <ranges>
#include <algorithm>
#include <memory>
#include <numeric>
#include <vector>
#include <unordered_map>
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

	int getScore() const
	{
		return score;
	}

	size_t getId() const
	{
		return id;
	}

	string getName() const
	{
		return name;
	}
private:
	string name;			// 이름, 길이[3, 15], ['a', 'z']로만 구성
	int score;				// 점수, 정규분포
	size_t id;				// 아이디, 겹치는 아이디 있을 수 있음
	size_t num;				// free store에 확보한 바이트 수
	unique_ptr<char[]> p;	// free store에 확보한 메모리

	friend ostream& operator<<(ostream& os, const Player& player)
	{
		print(os, "이름: {:15}, 아이디: {}, 점수: {}, 자원수: {}\n저장된 글자:{}",
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

	//1번 문제
	cout << "1번 문제: 파일에 저장한 모든 Player 정보를 읽어 컨테이너에 저장하라. 제일 마지막 Player의 정보를 다음과 같은 형식으로 화면에 출력하라." << endl;
	cout << playerArr.back() << endl;

	cout << "\n=========================================\n" << endl;

	//2번 문제
	cout << "2번 문제: 점수가 가장 큰 Player를 찾아 화면에 출력하라.(동점 모두 출력) Player의 평균 점수를 계산하여 화면에 출력하라." << endl;
	auto maxPtr = max_element(playerArr.begin(), playerArr.end(), [](const Player& a, const Player& b) {
		return a.getScore() < b.getScore();
		});
	int maxScore = maxPtr->getScore();
	cout << "최고 점수: " << maxScore << endl;
	cout << "최고 점수를 받은 Player들:" << endl;
	for (const auto& player : playerArr | views::filter([maxScore](const Player& a) {
		return a.getScore() == maxScore;
		}))
	{
		cout << player << endl;
	}
	long long averageScore = accumulate(playerArr.begin(), playerArr.end(), 0LL, [](long long sum, Player& player) {
		return sum + player.getScore();
		}) / playerArr.size();
	cout << "평균 점수: " << averageScore << endl;

	cout << "\n=========================================\n" << endl;

	//3번 문제
	cout << "3번 문제: id가 서로 같은 객체를 찾아 \"같은아이디.txt\"에 기록하라. id가 같은 객체는 모두 몇 개인지 화면에 출력하라. 파일에는 id가 같은 Player 객체의 이름과 아이디를 한 줄 씩 기록한다." << endl;
	unordered_map<size_t, vector<size_t>> idMap;
	for (size_t i = 0; i < playerArr.size(); ++i) {
		idMap[playerArr[i].getId()].push_back(i);
	}

	ofstream out{ "같은아이디.txt" };
	size_t duplicateCount = 0;
	for (const auto& [id, playerIndices] : idMap) {
		if (playerIndices.size() > 1) {
			duplicateCount += playerIndices.size();
			out << id << ':' << playerIndices.size() << "개" << endl;
			for (size_t index : playerIndices) {
				out << "이름: " << playerArr[index].getName() << ", 아이디: " << id << endl;
			}
			out << "==============================" << endl;
		}
	}
	cout << "id가 같은 객체는 총 " << duplicateCount << "개" << endl;
}