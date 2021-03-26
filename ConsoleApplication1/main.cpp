#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "ship.h"
#include "generator.h"
#include "fleet.h"

bool Ironman = 1;

/*������ ��������� �����(�� �������, ��� ����-�� ���� ���������� ��� ����� ����������):
1)���� ����� ����� ������� �����, � ����� �����, �� ������� ������ �� X = ����� Y = 0, � � ���������� ����� �� ������ ������� ���������� �� ����� ����
*/

int main(int argc, char * argv[]) {
	srand(time(0));

	if (!DEBUG_MODE) {
		std::cout << "This is a playable build! Most of the information unnecessary to the player will be shown only after enabling DEBUG_MODE in ship.h!\n\n";
	} else {
		std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	}

	if (width_height > 26) {
		std::cout << "Warning! The game is not designed for such a large field size! Please limit yourself to 26 cells!" << std::endl;
		return -26;
	}


	//ACHIEVEMENTS
	std::vector <std::pair<std::string, bool>> achievement_array = ReadAchievements();
	//////////////

	ship ship1("Enterprise", "Aircraft Carrier", 2);
	//�������� ������ ����
	std::vector<ship> fleet_11;
	//�������� � ������ ��� ��������
	fleet_11.push_back(ship1);
	//������� ��� ���������
	fleet_11.push_back({ "Prinz Eugene", "Heavy Cruiser", 3 });
	fleet_11.push_back({ "Atago", "Heavy Cruiser", 4 });
	fleet_11.push_back({ "FLX1", "Tsundere", 5 });
	fleet_11.push_back({ "FLX2", "Tsundere", 6 });
	fleet_11.push_back({ "FLX3", "Tsundere", 7 });
	fleet_11.push_back({ "Flaffey1", "Small", 8 });
	fleet_11.push_back({ "Flaffey2", "Small", 9 });
	fleet_11.push_back({ "Flaffey3", "Small", 10 });
	fleet_11.push_back({ "Flaffey4", "Small", 11 });
	//�������� ���� � �����
	Fleet fleet_1("Eagle Union", fleet_11);
	//������� ���� �� ����� input.txt (����� � ���������� �������)
	Fleet fleet_2;
	if (argc > 2)
	{
		std::ifstream fin(argv[2]);
		fleet_2.Read(fin);
		std::cout << fleet_2.GetName() << " is loaded from file!" << std::endl << std::endl;
		fin.close();
	}
	//������� �� � ���� output.txt (����� � ���������� �������)
	if (argc > 1)
	{
		std::ofstream fout(argv[1]);
		fleet_1.Print(fout);
		fleet_2.Print(fout);
		fout.close();
	}
	//������� ���� �� �������
	/*Fleet fleet_4;
	fleet_4.Read(std::cin);
	fleet_4.Print(std::cout);*/
	//������� ���������� �������� (�� ����� ��� ���������� ������� ������������... ������� ����� �������� � ������ ������� � ����, � �����)
	std::cout << "Ships count: " << ship1.GetCount() << std::endl << std::endl; //(��� �������)��, ��� ���� � ����!(��� ����)��, �� ������� :(


	if (!fleet_2.GetFleet().size()) { std::cout << "Warning! Connect the file with the second fleet!" << std::endl; return -2; }
	/*				��� ������������� ���� ������ ������������ ������(�� ������ ����)				*/
	
	//Generate here
	for (int i = 0; i < fleet_1.GetFleet().size(); i++) {
		Generate_ship(fleet_1.GetShipByIndex(i), fleet_1.GetSide());
	}

	for (int i = 0; i < fleet_2.GetFleet().size(); i++) {
		Generate_ship(fleet_2.GetShipByIndex(i), fleet_2.GetSide());
	}
	///////////////

	//DEBUG FUNCTIONS
	if (DEBUG_MODE) {
		fleet_1.Print(std::cout);
		fleet_2.Print(std::cout);
		Output_Field_ID_Indexes(0);
		Output_Field_War(0);
		Output_Field_ID_Indexes(1);
		Output_Field_War(1);
		////INITIALISATION FIELDS
		Initialize_Field_Final(fleet_1);
		Initialize_Field_Final(fleet_2);
		/////////////////////////
		std::cout << "Game Fields:" << std::endl << std::endl;
		Output_Field_Final_REFORGED(0, fleet_1.GetName(), fleet_2.GetName());
		Output_Field_Final_REFORGED(1, fleet_1.GetName(), fleet_2.GetName());
	}
	/////////////////

	//Achievements
	OutputAchievementInfo(achievement_array);
	//////////////

	//DAMAGE TEST
	/*if (DEBUG_MODE) {
		std::cout << "DAMAGE TEST:" << std::endl << std::endl;
		std::cout << "Before attack in random place:" << std::endl << std::endl;
		Output_Field_Final_REFORGED(0);
		std::cout << std::endl << std::endl;
		Output_Field_Final_REFORGED(1);

		fleet_2.ConsDmgToIndBot(2); //Wasn't tested after rework

		std::cout << "After attack in random place:" << std::endl << std::endl;
		std::cout << std::endl;
		Output_Field_Final_REFORGED(0);
		std::cout << std::endl << std::endl;
		Output_Field_Final_REFORGED(1);
	}*/
	/////////////

	//FOG OF WAR TEST
	//if (DEBUG_MODE) {
	//	std::cout << "FOG OF WAR TEST:" << std::endl << std::endl;
	//	std::cout << "FOR PLAYER: " << std::endl;
	//	Output_Field_Final_REFORGED(0, 0);
	//	Output_Field_Final_REFORGED(1, 0);

	//	std::cout << "FOR BOT: " << std::endl;
	//	Output_Field_Final_REFORGED(0);
	//	Output_Field_Final_REFORGED(1);
	//}
	/////////////////

	if (fleet_1.GetFleet().size() != fleet_2.GetFleet().size()) {
		std::cout << "Warning! Different number of ships in fleets! Ironman mode is disabled." << std::endl << std::endl;
		Ironman = 0;
	}

	std::vector <unsigned int> order = First_order(fleet_1, fleet_2);

	//���������� ���� ����
	std::cout << "Start game?\n\n";
	system("pause");

	std::string BattleMode = "";
	int difficulty = 0, round = 0;
	std::string action = "";

	while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
		if (!DEBUG_MODE) { system("cls"); }

		//std::cout << "Select battle mode (PvE / PvP): "; //USE PVP FOR ATTACKS TESTS
		std::cout << "Select battle mode (PvP): "; //USE PVP FOR ATTACKS TESTS
		std::cin >> BattleMode;
		BattleMode = hahaYouAreSmallNow(BattleMode);

		int first = rand() % 2;
		if (BattleMode == "pvp") { //PVP
			if (!DEBUG_MODE) { system("cls"); }
			if (DEBUG_MODE) {
				std::cout << "First side: " << first << std::endl;
			}
			while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
				switch (first % 2) {
					case 0:
						//����� ����
						Initialize_Field_Final(fleet_1);
						std::cout << fleet_1.GetName() << " turn." << std::endl << std::endl;
						//����� ���� ������ 1
						Output_Field_Final_REFORGED(0, fleet_1.GetName(), fleet_2.GetName());
						while (true) { //IN DEVELOPMENT
							if (DEBUG_MODE) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
							std::cout << "Current position: " << IntToLetter(Return_X_Y(order[round] + 2, first % 2).first) << " " << Return_X_Y(order[round] + 2, first % 2).second << std::endl;
							std::cout << "What do you want?\n\n";
							if (fleet_1.GetShipByIndex(order[round]).GetDurabilitySum()) {
								if (fleet_1.GetShipByIndex(order[round]).GetType() == "Small") { //single-deck abilities
									std::cout << "-Shoot\n-Move\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_2.ConsDmgToIndPlayer(Small_Damage);
										break;
									}
									else if (action == "move") {
										Small_Move(order[round], fleet_1.GetSide());
										Initialize_Field_Final(fleet_1);
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else if (fleet_1.GetShipByIndex(order[round]).GetType() == "Tsundere") {
									std::cout << "-Shoot\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_2.ConsDmgToIndPlayer(Small_Damage);
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else if (fleet_1.GetShipByIndex(order[round]).GetType() == "Heavy Cruiser") {
									std::cout << "-Shoot\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_2.ConsDmgToIndPlayer(Small_Damage);
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else if (fleet_1.GetShipByIndex(order[round]).GetType() == "Aircraft Carrier") {
									std::cout << "-Shoot\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_2.ConsDmgToIndPlayer(Small_Damage);
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else {
									std::cout << "ERROR! Unknown type of ship! Please contact the team leader, he will make sure that Vanya gets into a corner for poor testing." << std::endl;
									return -90;
								}
							}
							else {
								std::cout << "This ship is sunk, you miss this turn." << std::endl;
								break;
							}
						}
						system("pause");
						if (!DEBUG_MODE) { system("cls"); }
						first++;
						break;
					case 1:
						//����� ����
						Initialize_Field_Final(fleet_2);
						std::cout << fleet_2.GetName() << " turn." << std::endl << std::endl;
						//����� ���� ������ 2
						Output_Field_Final_REFORGED(1, fleet_1.GetName(), fleet_2.GetName());
						while (true) { //IN DEVELOPMENT
							if (DEBUG_MODE) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
							std::cout << "Current position: " << IntToLetter(Return_X_Y(order[round] + 2, first % 2).first) << " " << Return_X_Y(order[round] + 2, first % 2).second << std::endl;
							std::cout << "What do you want?\n\n";
							if (fleet_1.GetShipByIndex(order[round]).GetDurabilitySum()) {
								if (fleet_2.GetShipByIndex(order[round]).GetType() == "Small") { //single-deck abilities
									std::cout << "-Shoot\n-Move\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_1.ConsDmgToIndPlayer(Small_Damage);
										round++;
										if (round == order.size()) {
											round = 0;
										}
										break;
									}
									else if (action == "move") {
										Small_Move(order[round], fleet_2.GetSide());
										Initialize_Field_Final(fleet_1);
										round++;
										if (round == order.size()) {
											round = 0;
										}
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else if (fleet_2.GetShipByIndex(order[round]).GetType() == "Tsundere") {
									std::cout << "-Shoot\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_1.ConsDmgToIndPlayer(Small_Damage);
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else if (fleet_2.GetShipByIndex(order[round]).GetType() == "Heavy Cruiser") {
									std::cout << "-Shoot\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_1.ConsDmgToIndPlayer(Small_Damage);
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else if (fleet_2.GetShipByIndex(order[round]).GetType() == "Aircraft Carrier") {
									std::cout << "-Shoot\n" << std::endl;
									std::cin >> action;
									action = hahaYouAreSmallNow(action);
									if (action == "shoot") {
										//Shot
										std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
										fleet_1.ConsDmgToIndPlayer(Small_Damage);
										break;
									}
									else {
										std::cout << "Wrong command!" << std::endl;
										system("pause");
										continue;
									}
								}
								else {
									std::cout << "ANOTHER SHIPS IN DEVELOPMENT!" << std::endl;
									fleet_2.ConsDmgToIndPlayer(Default_Damage);
								}
							}
							else {
								std::cout << "This ship is sunk, you miss this turn." << std::endl;
								round++;
								if (round == order.size()) {
									round = 0;
								}
								break;
							}
						}
						system("pause");
						if (!DEBUG_MODE) { system("cls"); }
						first++;
						round++;
						if (round == order.size()) {
							round = 0;
						}
						break;
				}
			}
		//} else if (BattleMode == "pve") { //PVE(ON REWORK)
			while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
				if (!DEBUG_MODE) { system("cls"); }
				std::cout << "Select difficulty level NUMBER: " << std::endl;
				std::cout << "1)Normal" << std::endl; //Everything is fair
				std::cout << "2)Hard" << std::endl; //Bot has the right to make mistake
				std::cout << "3)Impossible" << std::endl << std::endl; //Bot will try until it hits, and it will always go first
				std::cout << "Difficulty: ";
				std::cin >> difficulty;
				difficulty--;

				if (difficulty == 2) {
					first = 1; //Bot will always go first
				}

				if (difficulty >= 0 && difficulty <= 2) { //0 - 2(1 - 3 for user)
					if (!DEBUG_MODE) { system("cls"); }
					if (DEBUG_MODE) {
						std::cout << "First side: " << first << std::endl;
						Output_Field_ID_Indexes(0); Output_Field_ID_Indexes(1);
					}
					while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
						std::cout << fleet_1.GetName() << " Health = " << fleet_1.GetHealth() << "; " << fleet_2.GetName() << " Health = " << fleet_2.GetHealth() << std::endl;
						switch (first % 2) {
							case 0: //Player
								Initialize_Field_Final(fleet_1);

								std::cout << fleet_1.GetName() << " turn." << std::endl << std::endl;
								//����� ���� ��� ������ 1
								Output_Field_Final_REFORGED(0, fleet_1.GetName(), fleet_2.GetName());

								while (true) { //IN DEVELOPMENT
									if (DEBUG_MODE) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
									std::cout << "Current position: " << IntToLetter(Return_X_Y(order[round] + 2, first % 2).first) << " " << Return_X_Y(order[round] + 2, first % 2).second << std::endl;
									std::cout << "What do you want?\n\n";
									if (fleet_1.GetShipByIndex(order[round]).GetDurabilitySum()) {
										if (fleet_1.GetShipByIndex(order[round]).GetType() == "Small") { //single-deck abilities
											std::cout << "-Shoot\n-Move\n" << std::endl;
											std::cin >> action;
											action = hahaYouAreSmallNow(action);
											if (action == "shoot") {
												//Shot
												std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
												fleet_2.ConsDmgToIndPlayer(Small_Damage);
												break;
											}
											else if (action == "move") {
												Small_Move(order[round], fleet_1.GetSide());
												Initialize_Field_Final(fleet_1);
												break;
											}
											else {
												std::cout << "Wrong command!" << std::endl;
												system("pause");
												continue;
											}
										}
										else if (fleet_1.GetShipByIndex(order[round]).GetType() == "Tsundere") {
											std::cout << "-Shoot\n" << std::endl;
											std::cin >> action;
											action = hahaYouAreSmallNow(action);
											if (action == "shoot") {
												//Shot
												std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
												fleet_2.ConsDmgToIndPlayer(Small_Damage);
												break;
											}
											else {
												std::cout << "Wrong command!" << std::endl;
												system("pause");
												continue;
											}
										}
										else if (fleet_1.GetShipByIndex(order[round]).GetType() == "Heavy Cruiser") {
											std::cout << "-Shoot\n" << std::endl;
											std::cin >> action;
											action = hahaYouAreSmallNow(action);
											if (action == "shoot") {
												//Shot
												std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
												fleet_2.ConsDmgToIndPlayer(Small_Damage);
												break;
											}
											else {
												std::cout << "Wrong command!" << std::endl;
												system("pause");
												continue;
											}
										}
										else if (fleet_1.GetShipByIndex(order[round]).GetType() == "Aircraft Carrier") {
											std::cout << "-Shoot\n" << std::endl;
											std::cin >> action;
											action = hahaYouAreSmallNow(action);
											if (action == "shoot") {
												//Shot
												std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
												fleet_2.ConsDmgToIndPlayer(Small_Damage);
												break;
											}
											else {
												std::cout << "Wrong command!" << std::endl;
												system("pause");
												continue;
											}
										}
										else {
											std::cout << "ERROR! Unknown type of ship! Please contact the team leader, he will make sure that Vanya gets into a corner for poor testing." << std::endl;
											return -90;
										}
									}
									else {
										std::cout << "This ship is sunk, you miss this turn." << std::endl;
										break;
									}
								}

								system("pause");
								if (!DEBUG_MODE) { system("cls"); }
								first++;
								round++;
								if (round == order.size()) {
									round = 0;
								}
								break;
							case 1: //Bot
								Initialize_Field_Final(fleet_2);
								std::cout << fleet_2.GetName() << " turn." << std::endl << std::endl;
								//Shot
								fleet_1.ConsDmgToIndBot(Default_Damage, difficulty);
								Initialize_Field_Final(fleet_1); //MUST HAVE AFTER ANY DAMAGE
								system("pause");
								if (!DEBUG_MODE) { system("cls"); }
								first++;
								round++;
								if (round == order.size()) {
									round = 0;
								}
								break;
						}
					}
				} else {
					if (!DEBUG_MODE) { system("cls"); }
					std::cout << "E-error! This is inapporopriate... I... What should I...?" << std::endl << std::endl;
					std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
					system("pause");
				}
			}
		} else {
			if (!DEBUG_MODE) { system("cls"); }
			std::cout << "E-error! This is inapporopriate... I... What should I...?" << std::endl << std::endl;
			std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
			system("pause");
		}
	}
	if (fleet_1.GetHealth() > fleet_2.GetHealth()) {
		std::cout << fleet_1.GetName();
		if (BattleMode == "pve" && Ironman) {
			GiveAchievement(difficulty);
		}
	}
	else if (fleet_1.GetHealth() < fleet_2.GetHealth()) {
		std::cout << fleet_2.GetName();
	}
	else { //IDK when it will be work :/
		std::cout << "Friendship";
	}
	std::cout << " won!";
	if (Ironman && difficulty == 2) {
		GiveAchievement(2);
	}
	if (BattleMode == "pvp" && Ironman) {
		GiveAchievement(3);
	}
	return 0;
}