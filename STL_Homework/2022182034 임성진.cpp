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

	void charSort()
	{
		sort(p.get(), p.get() + num);
	}

	bool isChar(string& chars)
	{
		return includes(p.get(), p.get() + num, chars.begin(), chars.end());
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
	//cout << "1번 문제:\n파일에 저장한 모든 Player 정보를 읽어 컨테이너에 저장하라. 제일 마지막 Player의 정보를 다음과 같은 형식으로 화면에 출력하라." << endl;
	//cout << "[답]" << endl;
	//cout << playerArr.back() << endl;

	//cout << "\n=========================================\n" << endl;

	////2번 문제
	//cout << "2번 문제:\n점수가 가장 큰 Player를 찾아 화면에 출력하라.(동점 모두 출력) Player의 평균 점수를 계산하여 화면에 출력하라." << endl;
	//cout << "[답]" << endl;
	//auto maxPtr = max_element(playerArr.begin(), playerArr.end(), [](const Player& a, const Player& b) {
	//	return a.getScore() < b.getScore();
	//	});
	//int maxScore = maxPtr->getScore();
	//cout << "최고 점수: " << maxScore << endl;
	//cout << "최고 점수를 받은 Player들:" << endl;
	//for (const auto& player : playerArr | views::filter([maxScore](const Player& a) {
	//	return a.getScore() == maxScore;
	//	}))
	//{
	//	cout << player << endl;
	//}
	//long long averageScore = accumulate(playerArr.begin(), playerArr.end(), 0LL, [](long long sum, Player& player) {
	//	return sum + player.getScore();
	//	}) / playerArr.size();
	//cout << "평균 점수: " << averageScore << endl;

	//cout << "\n=========================================\n" << endl;

	////3번 문제
	//cout << "3번 문제:\nid가 서로 같은 객체를 찾아 \"같은아이디.txt\"에 기록하라. id가 같은 객체는 모두 몇 개인지 화면에 출력하라. 파일에는 id가 같은 Player 객체의 이름과 아이디를 한 줄 씩 기록한다." << endl;
	//cout << "[답]" << endl;
	//unordered_map<size_t, vector<size_t>> idMap;
	//for (size_t i = 0; i < playerArr.size(); ++i) {
	//	idMap[playerArr[i].getId()].push_back(i);
	//}

	//ofstream out{ "같은아이디.txt" };
	//size_t duplicateCount = 0;
	//for (const auto& [id, playerIndices] : idMap) {
	//	if (playerIndices.size() > 1) {
	//		duplicateCount += playerIndices.size();
	//		out << "ID: " << id << "->" << playerIndices.size() << "개" << endl;
	//		for (size_t index : playerIndices) {
	//			out << "이름: " << playerArr[index].getName() << ", 아이디: " << id << endl;
	//		}
	//		out << "==============================" << endl;
	//	}
	//}
	//cout << "id가 같은 객체는 총 " << duplicateCount << "개" << endl;

	//cout << "\n=========================================\n" << endl;

	////4번 문제
	//cout << "4번 문제:" << endl;
	//cout << "Player의 멤버 p가 가리키는 메모리에는 파일에서 읽은 num개의 char가 저장되어 있어야 한다." << endl;
	//cout << "메모리에 저장된 char를 오름차순으로 정렬하라." << endl;
	//cout << "\'0\'부터 \'9\'까지 모든 숫자가 있는 Player를 찾아 모두 몇 객체인지 출력하라." << endl;
	//cout << "[답]" << endl;

	//string digits = "0123456789";
	//int totalPlayer = 0;

	//for (Player& player : playerArr) {
	//	player.charSort();
	//	if (player.isChar(digits))
	//		++totalPlayer;
	//}
	//cout << "0 ~ 9가 모두 있는 객체의 수: " << totalPlayer << endl;

	cout << "\n=========================================\n" << endl;
	//5번 문제
	cout << "5번 문제:" << endl;
	cout << "[ LOOP ] id를 입력받아 존재하는 id라면 다음 내용을 한 번에 화면 출력하라." << endl;
	cout << "1. 모든 Player가 id 기준 오름차순으로 정렬되어 있는 상태에서 해당 id 포함 앞과 뒤 Player의 정보를 출력한다." << endl;
	cout << "2. Player가 name 기준 오름차순으로 정렬되어 있는 상태에서 해당 name 포함 앞과 뒤 Player의 정보를 출력한다." << endl;
	cout << "3. Player가 score 기준 오름차순으로 정렬되어 있는 상태에서 해당 score 포함 앞과 뒤 Player의 정보를 출력한다." << endl;
	cout << "[답]" << endl;

	size_t targetId;

	cout << "id를 입력해주세요: ";
	cin >> targetId;

	cout << "id 기준으로 정렬합니다..." << endl;
	sort(playerArr.begin(), playerArr.end(), [](Player& a, Player& b) {
		return a.getId() < b.getId();
		});
	cout << "정렬을 완료했습니다." << endl;
	auto searchPlayer = find_if(playerArr.begin(), playerArr.end(), [targetId](const Player& player) {
		return player.getId() == targetId;
		});

	cout << *searchPlayer << endl; //460096640
}