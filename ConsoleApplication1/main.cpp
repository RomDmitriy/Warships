#include <string>
#include <vector>
#include <iostream>
#include "ship.h"
#include "generator.h"



int main()
{

	//��������� �����
	//�������� ������ ����
	std::vector<ship> fleet;
	//�������� � ������ ���� ���� ���������
	fleet.push_back({ "Enterprise", "Aircraft Carrier", 0 });
	fleet.push_back({ "Prinz Eugene1", "Heavy Cruiser", 1 });
	fleet.push_back({ "Prinz Eugene2", "Heavy Cruiser", 2 });
	fleet.push_back({ "FLX1", "Tsundere", 3 });
	fleet.push_back({ "FLX2", "Tsundere", 4 });
	fleet.push_back({ "FLX3", "Tsundere", 5 });
	fleet.push_back({ "Flaffey1", "Small", 6 });
	fleet.push_back({ "Flaffey2", "Small", 7 });
	fleet.push_back({ "Flaffey3", "Small", 8 });
	fleet.push_back({ "Flaffey4", "Small", 9 });
	Generate_ships_in_random_places(fleet[0], fleet[0].GetID());
	std::cout << std::endl << std::endl << std::endl;
	Output_Field();
	std::cout << std::endl << std::endl << std::endl;
	//������� ����
	std::cout << "======Fleet=======" << std::endl;
	for (const auto& x : fleet)
	{
		x.Print();
	}
	system("pause");
	return 0;
}