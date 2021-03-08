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
	fleet.push_back({ "Enterprise", "Aircraft Carrier" });
	fleet.push_back({ "Prinz Eugene1", "Heavy Cruiser" });
	fleet.push_back({ "Prinz Eugene2", "Heavy Cruiser" });
	fleet.push_back({ "FLX1", "Tsundere" });
	fleet.push_back({ "FLX2", "Tsundere" });
	fleet.push_back({ "FLX3", "Tsundere" });
	fleet.push_back({ "Flaffey1", "Small" });
	fleet.push_back({ "Flaffey2", "Small" });
	fleet.push_back({ "Flaffey3", "Small" });
	fleet.push_back({ "Flaffey4", "Small" });
	Generate_ships_in_random_places(fleet[0]);
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