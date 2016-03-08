#pragma once
#include "EXider.h"
namespace EXider {
	class CommandParser {
		typedef std::vector<EXiderArgument> argList;
		std::string m_command;
		argList m_arguments;
	public:
		CommandParser( const std::string& command );
		CommandParser();
		void parseCommand( const std::string& command );
		const std::string command() const;
		const argList arguments() const;
	};
}