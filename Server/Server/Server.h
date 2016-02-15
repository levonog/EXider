#pragma once
#include "EXider.h"
namespace EXider {
	class Server :public boost::noncopyable {
		// Variables
		ProgramExecutor m_executor;
		std::queue<std::pair<int, std::string> > m_messagesToSend;
		boost::asio::io_service& m_io;
		boost::asio::ip::tcp::socket m_socket;
		boost::asio::ip::tcp::acceptor m_acceptor;
		boost::recursive_mutex m_send_mutex;

		boost::thread taskThread;
		boost::thread resultSenderThread;
		//Functions
		void send_request( int id, std::string message );
		void resultSender();
		std::string read_request();
		void taskManager( const std::string& task );
	public:
		Server( boost::asio::io_service& io );
		void executeHandler( int id, std::string output );
		void run();

	};
}