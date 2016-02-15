#include "EXider.h"

namespace EXider {
	ProgramExecutor::ProgramExecutor(boost::asio::io_service& m_io, Server* server ) :
		m_io(m_io),server(server ) {

	}
	void ProgramExecutor::run() {
		while ( true ) {
			boost::asio::deadline_timer timer( m_io, boost::posix_time::seconds(2) );
			timer.wait();
			boost::recursive_mutex::scoped_lock sl( m_mutex );
			if ( !m_executeQueue.empty() ) {
				char tempFile[ 128 ];
				sprintf( tempFile, "tempfile_%i", rand()*rand() );
				std::string tempFileName( tempFile );
				Program nowWorking = m_executeQueue.front().second;
				int noWorking_id = m_executeQueue.front().first;
				m_executeQueue.pop();
				sl.unlock();
				system( ( nowWorking.getFullPathWithArguments() + " >> " + tempFileName ).c_str() );
				std::fstream fin( tempFile );
				std::string result;
				getline( fin, result );
				server->executeHandler( noWorking_id, result );
			}

		}
	}
	void ProgramExecutor::addProgram( int id, const Program& rhp ) {
		boost::recursive_mutex::scoped_lock sl( m_mutex );
		m_executeQueue.push( { id,rhp } );
	}
}