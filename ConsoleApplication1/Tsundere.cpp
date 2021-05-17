#include "Tsundere.h"


int Tsundere::get_size() const {
	return 2;
}

int Tsundere::get_damage_value() const {
	return 4;
}

int Tsundere::get_default_durability() const {
	return 3;
}

void Tsundere::print_commands() const {
	std::cout << "-Shoot\n-Repair\n" << std::endl;
}

std::string Tsundere::get_description() const {
	return "This ship have a tools for repairing, which means it can repair yourself!";
}
