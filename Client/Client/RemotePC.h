#pragma once
#include "EXider.h"
namespace EXider {

	class RemotePC {
		boost::asio::ip::tcp::socket m_socket;
		boost::asio::ip::tcp::endpoint m_endpoint;
		boost::asio::streambuf m_buffer;
		boost::function<void( int, std::string )> m_callback;

		
		rpcStatus m_status;

		size_t m_id;
	
		void sendHandler( const boost::system::error_code& error );
		void readHandler( const boost::system::error_code& error, size_t bytes );
		void connectedHandler( const boost::system::error_code& error );
	public:
		RemotePC( boost::asio::io_service& io, const std::string& IP );
		RemotePC( boost::asio::io_service& io, const boost::asio::ip::address& IP );
		void reconnect();
		void disconnect();
		inline const rpcStatus status() const;
		void sendRequest( const std::string& request );
		void readRequest();
		void setID( size_t ID );
		void setCallBackFunction( const boost::function<void( int ID, std::string result )>& cb );
		inline size_t getID() const;
		inline const boost::asio::ip::address getIP() const;
	};
};