#pragma once
#include "EXider.h"
namespace EXider {
	class ProgramExecutor {
		boost::asio::io_service& m_io;
		std::queue<std::pair<int, Program> > m_executeQueue;
		Server* server;
		boost::recursive_mutex m_mutex;
	public:
		ProgramExecutor( boost::asio::io_service& m_io, Server* server );
		void run();
		void addProgram( int id, const Program& rhp );
	};
}