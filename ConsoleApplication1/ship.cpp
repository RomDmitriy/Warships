#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Ship.h"
#include "Leviathan.h"
#include "AircraftCarrier.h"
#include "HeavyCruiser.h"
#include "Tsundere.h"
#include "Small.h"

Ship::Ship(const std::string& nm) : name_(nm), type_(nullptr) {}

Ship::Ship(const std::string& nm, BasicType& tp) : name_(nm), type_(&tp) {
	durability_.resize(type_->get_size());
	std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

void Ship::print(std::ostream& out) const {
	out << name_;
	for (int i = 16; i > name_.length(); i--) out << " ";
	out << " Type: ";
		if (type_ != nullptr)
		{
			out << type_->get_name();
			for (int i = 20; i > type_->get_name().length(); i--) out << " ";
		}
		else {
			out << "none BasicType";
			for (int i = 20; i > 14; i--) out << " ";
		}
	out << " Durability: ";
	for (auto i : durability_)
	{
		out << " " << i;
	}
	out << std::endl;
}

void Ship::read(std::istream& in) {
	std::string temp;
	std::getline(in, name_);
	temp.clear();
	std::getline(in, temp);
	if (temp == "Leviathan") {
		type_ = new Leviathan();
	}
	else if (temp == "Aircraft Carrier")  {
		type_ = new AircraftCarrier();
	}
	else if (temp == "Heavy Cruiser") {
		type_ = new HeavyCruiser();
	}
	else if (temp == "Tsundere") {
		type_ = new Tsundere();
	}
	else if (temp == "Small") {
		type_ = new Small();
	}
	else {
		type_ = nullptr;
	}
	durability_.resize(type_->get_size());
	std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

std::string Ship::get_name() const {
	return name_;
}

 BasicType* Ship::get_type() const {
	return type_;
}

 void Ship::set_durability(std::vector<int> value) {
	 durability_ = value;
 }

 int Ship::get_durability_sum() const {
	int sum = 0;
	for (auto& i : durability_) {
		sum += i;
	}
	return sum;
}

std::vector<int> Ship::get_durability() const {
	return durability_;
}

void Ship::damage_by_index(const int dmg, const int ind) {
	if (durability_[ind] - dmg > 0) { durability_[ind] -= dmg; }
	else { durability_[ind] = 0; }
}

bool Ship::operator==(const Ship& right) const {
	return (type_->get_size() == right.type_->get_size() && durability_ == right.durability_);
}

bool Ship::operator!=(const Ship& right) const {
	return !(*this == right);
}

Ship& Ship::operator=(const Ship& right) {
	if (this != &right)
	{
		name_ = right.name_;
		type_ = right.type_;
		durability_ = right.durability_;
	}
	return *this;
}

Ship Ship::operator++(int) {
	Ship copyThis(*this);
	for (auto& i : durability_)
	{
		if (i < this->get_type()->get_default_durability())
		{
			i++;
			if (i < this->get_type()->get_default_durability())
			{
				i++;
			}
		}
	}
	return copyThis;
}

Ship Ship::operator--(int) {
	Ship copyThis(*this);
	for (auto& i : durability_)
	{
		if (i != 0)
		{
			i--;
		}
	}
	return copyThis;
}

std::istream& operator>>(std::istream& in, Ship& shp) {
	shp.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Ship& shp) {
	shp.print(out);
	return out;
}