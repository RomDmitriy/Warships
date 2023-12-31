#pragma once
#include <string>

class type {
public:
	virtual void print()const = 0;
	virtual int get_size()const = 0;
	virtual int get_damage_value()const = 0;
	virtual std::string get_name()const = 0;
	virtual int get_default_durability()const = 0;
	virtual void move_small(const unsigned int index, const int side)const = 0;
	virtual ~type() {};
};