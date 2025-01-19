#include <iostream>


// 오늘의 주제 : TextRPG2

//main (Playerinfo)
// - EnterLobby (Playerinfo)
// -- CreatePlayer
// -- EnterGame (Monsterinfo)
// --- CreateMonsters
// --- EnterBattle

enum PlayerType
{
	PT_Knight = 1,
	PT_Archer = 2,
	PT_Mage = 3,
};

enum MonsterType
{
	MT_Slime = 1,
	MT_Orc = 2,
	MT_Skeleton = 3,
};

struct Statinfo
{
	int hp = 0;
	int attack = 0;
	int defence = 0;
};

void EnterLobby();
void PrintMessage(const char* msg);
void CreatePlayer(Statinfo* playerinfo);
void PrintStatinfo(const char* name, const Statinfo& info); // 오로지 읽기와 출력 전용.
void EnterGame(Statinfo* playerinfo);
void CreateMonsters(Statinfo monsterinfo[], int count);
bool EnterBattle(Statinfo* playerinfo, Statinfo* monsterinfo);


int main()
{
	srand((unsigned)time(nullptr));
	EnterLobby();

	return 0;
}

void EnterLobby()
{
	while (true)
	{
		PrintMessage("로비에 입장했습니다.");

		// Player 
		Statinfo playerinfo;
		CreatePlayer(&playerinfo);
		PrintStatinfo("Player", playerinfo);


		EnterGame(&playerinfo);
	}
}

void PrintMessage(const char* msg)
{
	std::cout << "***************************" << std::endl;
	std::cout << msg << std::endl;
	std::cout << "***************************" << std::endl;
}

void CreatePlayer(Statinfo* playerinfo)
{
	bool ready = false;

	while (ready == false)
	{
		PrintMessage("캐릭터 생성창");
		PrintMessage("[1] 기사 [2] 궁수 [3] 법사");
		std::cout << "> ";
		
		int input;
		std::cin >> input;

		switch (input)
		{
		case PT_Knight:
			playerinfo->hp = 100;
			playerinfo->attack = 10;
			playerinfo->defence = 5;
			ready = true;
			break;
		case PT_Archer:
			playerinfo->hp = 80;
			playerinfo->attack = 15;
			playerinfo->defence = 3;
			ready = true;
			break;
		case PT_Mage:
			playerinfo->hp = 50;
			playerinfo->attack = 25;
			playerinfo->defence = 1;
			ready = true;
			break;
		}
	}
}

void PrintStatinfo(const char* name, const Statinfo& info)
{
	std::cout << "**********************************" << std::endl;
	std::cout << name << " : HP " << info.hp << " ATT=" << info.attack << " DEF=" << info.defence << std::endl;
	std::cout << "**********************************" << std::endl;
}

void EnterGame(Statinfo* playerinfo)
{
	const int MONSTER_COUNT = 2;
	PrintMessage("게임에 입장했습니다.");

	while (true)
	{
		Statinfo monsterinfo[MONSTER_COUNT];
		CreateMonsters(monsterinfo, MONSTER_COUNT);

		for (int i = 0; i < MONSTER_COUNT; i++)
			PrintStatinfo("Monster", monsterinfo[i]);
	
		PrintStatinfo("Player ", *playerinfo);

		PrintMessage("[1] 전투 [2] 전투 [3] 도망");
		int input;
		std::cin >> input;

		if (input == 1 || input == 2)
		{
			int index = input - 1;
			bool victory = EnterBattle(playerinfo, &(monsterinfo[index]));

			if (victory == false)
				break;
		}
	}
}

void CreateMonsters(Statinfo monsterinfo[], int count)
{
	for (int i = 0; i < count; i++)
	{
		int randValue = 1 + rand() % 3;

		switch (randValue)
		{
		case MT_Slime:
			monsterinfo[i].hp = 30;
			monsterinfo[i].attack = 5;
			monsterinfo[i].defence = 1;
			break;
		case MT_Orc:
			monsterinfo[i].hp = 40;
			monsterinfo[i].attack = 8;
			monsterinfo[i].defence = 2;
			break;
		case MT_Skeleton:
			monsterinfo[i].hp = 50;
			monsterinfo[i].attack = 15;
			monsterinfo[i].defence = 3;
			break;
		}
	}
}

bool EnterBattle(Statinfo* playerinfo, Statinfo* monsterinfo)
{
	while (true)
	{
		int damage = playerinfo->attack - monsterinfo->defence;
		if (damage < 0)
			damage = 0;

		monsterinfo->hp -= damage;
		if (monsterinfo->hp < 0)
			monsterinfo->hp = 0;
	
	
		PrintStatinfo("Monster", *monsterinfo);

		if (monsterinfo->hp == 0)
		{
			PrintMessage("몬스터를 처치했습니다.");
			return true;
		}

		damage = monsterinfo->attack - playerinfo->defence;
		if (damage < 0)
			damage = 0;

		playerinfo->hp -= damage;
		if (playerinfo->hp < 0)
			playerinfo->hp = 0;

		PrintStatinfo("Player", *playerinfo); //복사값을 붙여넣어야 하니까 *을 쓴다..?


		if (playerinfo->hp == 0)
		{
			PrintMessage("Game over");
			return 0;
		}

	}
}