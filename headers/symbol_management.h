#pragma once

#include <string>
#include <stdio.h>
#include <map>

enum class ID_TYPE
{
	FUNC,
	VAR
};

struct func_ptr {
	std::string name;
	float (*function)(float);
};

struct identifier {
	std::string name;
	ID_TYPE type;
	double value;
	float (*function)(float);
};

extern std::map<std::string, identifier> function_map;

extern void init_function_map();

extern identifier* get_identifier(char*);

extern identifier* put_identifier(char*);

extern identifier* get_error_function();

extern void put_value(char*, double value);