#include "EXider.h"

namespace EXider {
	Server::Server( boost::asio::io_service& io ) :
		m_io( io ), m_socket( m_io ),
		m_acceptor( m_io, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), PORT ) ),
		m_executor(io, this ), taskThread( &ProgramExecutor::run, &m_executor ),
		resultSenderThread( &Server::resultSender, this ) {

	}

	void Server::run() {
		m_acceptor.accept( m_socket );
		while ( true ) {
			std::string task = read_request();
			taskManager( task );
		}
	}

	void Server::executeHandler( int id, std::string output ) {
		boost::recursive_mutex::scoped_lock sl( m_send_mutex );
		m_messagesToSend.push( { id, output } );
	}

	void Server::resultSender() {
		while ( true ) {
			boost::asio::deadline_timer waiter( m_io, boost::posix_time::seconds( 2 ) );
			waiter.wait();
			boost::recursive_mutex::scoped_lock sl( m_send_mutex );
			while ( !m_messagesToSend.empty() ) {
				send_request( m_messagesToSend.front().first, m_messagesToSend.front().second );
				m_messagesToSend.pop();
			}
		}
	}

	std::string Server::read_request() {
		boost::asio::streambuf buf;
		boost::asio::read_until( m_socket, buf, "\n" );
		std::istream is( &buf );
		std::string readRequest;
		std::getline( is, readRequest );
		return readRequest;
	}

	void Server::send_request( int id, std::string message ) {
		char messageToSend[ 256 ];
		sprintf( messageToSend, "ID: %d Result: %s\n", id, message.c_str() );
		boost::asio::write( m_socket, boost::asio::buffer( messageToSend ) );
	}

	void Server::taskManager( const std::string& task ) {
		Program prog( task, "" );
		m_executor.addProgram( 0, prog );
	}
}