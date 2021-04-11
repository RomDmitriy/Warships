﻿#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Ship.h"
#include "AircraftCarrier.h"
#include "HeavyCruiser.h"
#include "Tsundere.h"
#include "Small.h"


int Ship::count_ = 0;

Ship::Ship(const std::string& nm, const int IDen) : name_(nm), id_(IDen), type_(nullptr), cid_(count_++)
{
}

Ship::Ship(const std::string& nm, BasicType& tp, const int IDen) : name_(nm), id_(IDen), type_(&tp), cid_(count_++)
{
    durability_.resize(type_->get_size());
    std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

void Ship::print(std::ostream& out) const
{
    out << "[" << id_ << "]\t";
    out << name_ << "\t";
    if (name_.size() < 6) out << "\t";
    out << "Type: ";
        if (type_ != nullptr)
        {
            std::cout << type_->get_name();
            if (type_->get_name().size() < 9) out << "\t";
        }
        else
        {
            std::cout << "none BasicType";
        }
    std::cout << "\t";
    out << "Durability: ";
    for (int i = 0; i < durability_.size(); i++)
    {
        out << " " << durability_[i];
    }
    out << std::endl;
}

void Ship::read(std::istream& in)
{
    std::string temp;
    std::getline(in, temp);
    id_ = stoi(temp);
    std::getline(in, name_);
    //std::getline(in, type_);
    temp = "";
    std::getline(in, temp);
    if (temp == "Aircraft Carrier") 
    {
        type_ = new AircraftCarrier();
    }
    else if (temp == "Heavy Cruiser")
    {
        type_ = new HeavyCruiser();
    }
    else if (temp == "Tsundere")
    {
        type_ = new Tsundere();
    }
    else if (temp == "Small")
    {
        type_ = new Small();
    }
    else
    {
        type_ = nullptr;
    }
    durability_.resize(type_->get_size());
    std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

void Ship::set_name(const std::string &name)
{
    name_ = name;
}

std::string Ship::get_name() const
{
    return name_;
}

void Ship::set_type(const BasicType* tp)
{
    type_ = (BasicType*)tp;
}

 BasicType* Ship::get_type() const
{
    return type_;
}

void Ship::set_durability(const std::vector<int> &durability)
{
    durability_ = durability;
}

unsigned int Ship::get_durability_sum() const {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < durability_.size(); i++) {
        sum += durability_[i];
    }
    return sum;
}

std::vector<int> Ship::get_durability() const
{
    return durability_;
}

void Ship::damage_by_index(const int dmg, const int ind) {
    if (durability_[ind] - dmg > 0) { durability_[ind] -= dmg; }
    else { durability_[ind] = 0; }
}

int Ship::get_id() const
{
    return id_;
}

bool Ship::operator==(const Ship& right) const
{
    bool durabilityIsEqual = false;
    std::string s = std::to_string(durability_.size()) + std::to_string(right.durability_.size());
    std::sort(s.begin(), s.end());
    for (int x = 0; x < s[0] - '0'; x++)
    {
        if (durability_[x] == right.durability_[x])
        {
            durabilityIsEqual = 1;
        }
        else
        {
            durabilityIsEqual = 0;
            break;
        }
    }
    return (name_ == right.name_ && type_ == right.type_ && id_ == right.id_ && durabilityIsEqual);
}

bool Ship::operator!=(const Ship& right) const
{
    return !(*this == right);
}

Ship& Ship::operator=(const Ship& right)
{
    if (this != &right)
    {
        name_ = right.name_;
        type_ = right.type_;
        durability_ = right.durability_;
    }
    return *this;
}

Ship Ship::operator++(int)
{
    Ship copyThis(*this);
    for (int i = 0; i < durability_.size(); i++)
    {
        if (durability_[i] == Tsundere_Durability)
        {
            durability_[i]++;
        }
    }
    return copyThis;
}

Ship Ship::operator--(int)
{
    Ship copyThis(*this);
    for (int i = 0; i < durability_.size(); i++)
    {
        durability_[i]--;
    }
    return copyThis;
}

std::istream& operator>>(std::istream& in, Ship& shp)
{
    shp.read(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Ship& shp)
{
    shp.print(out);
    return out;
}