#pragma once

#include <vector>
#include "BasicType.h"

//Game settings
#define width_height 10 //Width & height of field

#define DEBUG_MODE 1 //0 - off; 1 - on

#define SEED 1618667546 //0 - Pseudo-random
///////////////

class Ship
{
public:
	//				Constructors & Destructors
	Ship() : cid_(count_++), type_(nullptr), id_(0) {};
	Ship(const std::string& name, const int id);
	Ship(const std::string& name, BasicType& type, const int id);
	~Ship() {};


	//						Operators
	bool operator == (const Ship& right)const;
	bool operator != (const Ship& right)const;
	Ship& operator= (const Ship& right);
	Ship operator++ (int); //repair function
	Ship operator-- (int); //anti repair function


	//							Get
	int get_durability_sum()const;
	std::vector<int> get_durability()const;
	std::string get_name()const;
	int get_id()const;
	BasicType* get_type()const;
	static int get_count() { return count_; }


	//							Set
	void set_name(const std::string& name);
	void set_type(const BasicType* type);
	void set_durability(const std::vector<int>& durability);


	//						Input/Output
	void print(std::ostream& out)const;
	void read(std::istream& in);


	//						Damage ship
	void damage_by_index(const int damage, const int index);


private:
	std::string name_;
	std::vector<int> durability_;
	BasicType* type_;
	int id_;
	static int count_;
	const int cid_;
};

//Overloading I/O operators is only possible separately from the class
std::istream& operator>>(std::istream& in, Ship& shp);
std::ostream& operator<<(std::ostream& out, const Ship& shp);