#pragma once
#include "EXider.h"
namespace EXider {
	class Information {
		const Client* m_client;

	public:
		enum CommandType {
			PC = 1,
			Task = 2,
			Usage = 4
		};
		Information( const Client* client );
		
		void taskList();											// List of tasks with results
		void taskInformation( const std::vector<size_t>& tIDs );	// Full information about tasks

		void pcList( size_t Status = Available);					// List of RemotePCs

		void help(size_t CommandTypes = (PC | Task | Usage) );		// Exider's commands instructions

		void warning( const std::string& message );					// Warning message
		void wrongArgument( const std::string& arg );				// Message of invalid argument
		void wrongParameter( const std::string& param );			// Message of incorrect parameter
	};
}