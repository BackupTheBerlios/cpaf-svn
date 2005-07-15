#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <locale>
#include <algorithm>
#include <functional>
#include <vector>
#include <stdexcept>
#include <boost/shared_ptr.hpp>

const char USAGE_STR[] =\
"USAGE\n\
class_template [class] [base] [constructable=true,false]";
std::time_put
struct upper { };
struct lower { };

template<class T> class conv_case;

template<> class conv_case<upper>
{
private:
    const std::locale &loc;

public:
    conv_case(const std::locale &l)
        : loc(l)
    { }

    template<class charT> void operator() (charT &c)
    {
        c = std::toupper(c, loc);
    }
};

template<> class conv_case<lower>
{
private:
    const std::locale &loc;

public:
    conv_case(const std::locale &l)
        : loc(l)
    { }

    template<class charT> void operator() (charT &c)
    {
        c = std::tolower(c, loc);
    }
};

template<class T> std::string conv_str_case(const std::string &str, const std::locale &loc)
{
    std::string temp = str;
    std::for_each(temp.begin(), temp.end(), conv_case<T>(loc));
    return temp;
}

class parser_object;
typedef boost::shared_ptr<parser_object> parser_object_ptr;
typedef std::vector<parser_object_ptr> parser_vector;
typedef std::map<std::string, std::string> symbol_map;
typedef std::pair<std::string, std::string> string_pair;
typedef std::pair<std::string, string_pair> template_file;
typedef std::vector<template_file> template_files_vector;
parser_object_ptr parser_factory(const std::string &command, const symbol_map &sym, parser_vector &par, std::ifstream &in, std::ofstream &out);

class parser_object
{
protected:
    const symbol_map &symbols;
    parser_vector &parsers;
    std::ifstream &input;
    std::ofstream &output;

public:
    typedef bool result_type;
    typedef std::string& argument_type;

    /*
        Parses a line of input

        A return value of true indicates that this parser processed the line.
        A return value of false indicates that the next parser should process the line.
    */
    virtual result_type operator() (argument_type) = 0;

    parser_object(const symbol_map &sym, parser_vector &par, std::ifstream &in, std::ofstream &out)
        : symbols(sym),
        parsers(par),
        input(in),
        output(out)
    { }
};

/*
    Regular parser object. Replaces symbols and looks for commands
*/
class symbol_parser : public parser_object
{
public:
    static bool m_should_output;

    symbol_parser(const symbol_map &sym, parser_vector &par, std::ifstream &in, std::ofstream &out)
        : parser_object(sym, par, in, out)
    { }

    result_type operator() (argument_type line)
    {
        // parse for our symbols
        for( std::string::size_type pos = 0; (pos = line.find('$', pos)) != std::string::npos; pos++ )
        {
            std::string::size_type end = line.find(')', pos);

            std::string::iterator it_begin = line.begin() + pos;
            std::string::iterator it_end = line.begin() + end;

            std::string statement = line.substr(pos + 2, end - pos - 2);

            // check for commands
            std::string::size_type space_pos;
            if( (space_pos = statement.find_first_of(" )", 0)) != std::string::npos )
            {
                // space must come first
                if( statement[space_pos] == ' ' )
                {
                    // push the parser for this command
                    std::string command = statement.substr(0, space_pos);
                    parsers.push_back(parser_factory(command, symbols, parsers, input, output));
                    parsers.back()->operator()(line);

                    return true;
                }
            }

            symbol_map::const_iterator sym = symbols.find(statement);
            if( sym == symbols.end() )
                throw std::runtime_error(std::string("Unknown symbol encountered: ") + statement);

            line.replace(pos, end - pos + 1, sym->second);

            pos++;
        }

        if( m_should_output )
            output << line;

        return true;
    }
};

bool symbol_parser::m_should_output = true;

// parser object for "IF" statements
class if_parser : public parser_object
{
private:
    bool m_parsing, m_output;

public:
    if_parser(const symbol_map &sym, parser_vector &par, std::ifstream &in, std::ofstream &out)
        : parser_object(sym, par, in, out),
        m_parsing(false),
        m_output(false)
    { }

    result_type operator() (argument_type line)
    {
        if( !m_parsing )
        {
            std::string::size_type start = line.find("$(IF ", 0);
            std::string::size_type end = line.find(')', start);

            std::string symbol = line.substr(start + 5, end - start - 5);

            // if the symbol exists in the map, parse normally until we hit $(END)
            // if it doesn't exist, skip until we hit $(END)
            m_output = symbols.find(symbol) != symbols.end();
            m_parsing = true;
        }
        else
        {
            // look for $(END)
            if( line.find("$(END)") != std::string::npos )
            {
                // stop parsing
                m_parsing = false;
                parsers.erase(parsers.end()-1);
                return true;
            }
            
            symbol_parser::m_should_output = m_output;
            return false;
        }

        return true;
    }
};

parser_object_ptr parser_factory(const std::string &command, const symbol_map &sym, parser_vector &par, std::ifstream &in, std::ofstream &out)
{
    if( command == "IF" )
        return parser_object_ptr(new if_parser(sym, par, in, out));
    else
        throw std::runtime_error(std::string("Unknown command: ") + command);
};

void output_templates(std::string name, std::string base, bool constructable)
{
    std::string line;
    std::locale loc;
    std::ifstream input;
    std::ofstream output;

    // construct the symbol map
    symbol_map symbols;
    symbols["NAME"] = name;
    symbols["BASE"] = base;
    symbols["NAME_UPPER"] = conv_str_case<upper>(name, loc);
    symbols["NAME_LOWER"] = conv_str_case<lower>(name, loc);
    symbols["BASE_UPPER"] = conv_str_case<upper>(base, loc);
    symbols["BASE_LOWER"] = conv_str_case<lower>(base, loc);
    if( constructable )
        symbols["CONSTRUCTABLE"] = "";

    // build input and output file vector
    template_files_vector files;
    files.push_back(template_file("templates/gui.h", string_pair("include/cpaf/gui/", ".h")));
    files.push_back(template_file("templates/initializer.h", string_pair("include/cpaf/gui/initializer/", ".h")));
    files.push_back(template_file("templates/api.h", string_pair("include/cpaf/api/gui/", ".h")));
    files.push_back(template_file("templates/gui.cpp", string_pair("src/cpaf/gui/", ".cpp")));

    parser_vector parsers;
    parsers.push_back(parser_object_ptr(new symbol_parser(symbols, parsers, input, output)));

    // parse and output template files
    for( template_files_vector::iterator i = files.begin(), end = files.end(); i != end; ++i )
    {
        input.open(i->first.c_str(), std::ios::in | std::ios::binary);
        string_pair &out_file = i->second;
        output.open(std::string(out_file.first + symbols["NAME_LOWER"] + out_file.second).c_str(),
            std::ios::out | std::ios::trunc);

        if( !input.is_open() )
            throw std::runtime_error("Failed to open template file");
        if( !output.is_open() )
            throw std::runtime_error("Failed to open output file");

        std::string buff;

        // read and write line by line
        while(true)
        {
            symbol_parser::m_should_output = true;

            std::getline(input, line);
            buff = line;

            if( input.eof() )
                break;

            if( !input.good() || !output.good() )
                throw std::runtime_error("Input or Output error!");

            for( parser_vector::reverse_iterator i = parsers.rbegin(), end = parsers.rend(); i != end; ++i )
                if( (**i)(buff) )
                    break;
        }

        input.close();
        output.close();
        input.clear();
        output.clear();
    }
}

int main(int argc, char *argv[])
{
    if( argc != 4 )
    {
        std::cout << USAGE_STR;
        return 1;
    }

    try
    {
        output_templates(argv[1], argv[2], std::string(argv[3]) == "true");
    }
    catch(std::exception &e)
    {
        std::cerr << e.what();
        std::cin.get();
    }
}