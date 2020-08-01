#include <iostream>

#include "../headers/parser.h"
#include "../headers/symbol_management.h"

using namespace std;

// this function is called syntax parser
// just the parser, the parse
extern int yyparse();

std::map<std::string, identifier> function_map;

int text_len = 0;

float error_function(float value)
{
	std::cout << "Error \n";
	return 0;
}


identifier* get_error_function()
{
	return &function_map.find("error")->second;
}


identifier* get_identifier(char* function_name)
{
	auto temp =  function_map.find(std::string(function_name));
	if ( temp != function_map.end() )
		return &temp->second;

	return get_error_function();
}

identifier* put_identifier(char* identifier_name)
{
	function_map.insert(std::pair<std::string, identifier>(std::string(identifier_name), { std::string(identifier_name), ID_TYPE::VAR, 0.0, error_function }));

	return get_identifier(identifier_name);
}

void put_value(char* var, double value)
{
	identifier* id = get_identifier(var);
	id->value = value;
}


void init_function_map()
{
	function_map.insert(std::pair<std::string, identifier>( "error", { "error", ID_TYPE::FUNC, 0.0, error_function }));
	function_map.insert(std::pair<std::string, identifier>( "sin", { "sin", ID_TYPE::FUNC, 0.0, sin } ) );
	function_map.insert(std::pair<std::string, identifier>( "cos", { "cos", ID_TYPE::FUNC, 0.0, cos } ) );
	function_map.insert(std::pair<std::string, identifier>( "tan", { "tan", ID_TYPE::FUNC, 0.0, tan } ) );
	function_map.insert(std::pair<std::string, identifier>( "log", { "log", ID_TYPE::FUNC, 0.0, log }));
	function_map.insert(std::pair<std::string, identifier>( "sqrt", { "sqrt", ID_TYPE::FUNC, 0.0, sqrt } ) );
	function_map.insert(std::pair<std::string, identifier>( "exp", { "exp", ID_TYPE::FUNC, 0.0, exp }));
}


int main()
{
	char input;

	init_function_map();

	while (true)
	{
		std::cout << "hoc > ";
		yyparse();
	}

	return 0;
}

// we have to code this function
void yyerror(const char* msg)
{
	cout << "Error: " << msg << endl;
}