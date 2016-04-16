#pragma once
#include "EXider.h"
namespace EXider {
	class ProgramExecutor {
		Server* server;
		boost::asio::io_service& m_io;
		boost::recursive_mutex m_mutex;
		boost::shared_ptr<boost::process::child> program;
		std::queue<std::pair<int, Program> > m_executeQueue;
		
		void sendResult( int id, const std::string& result );
	public:
		ProgramExecutor( boost::asio::io_service& m_io, Server* server );
		void run();															// Process program queue
		void stop();														// Terminates running process and cleans the queue;
		void addProgram( int id, const Program& rhp );						// Adds new program to queue
		void terminateRunningProcess();										// Terminates running process
		};
}