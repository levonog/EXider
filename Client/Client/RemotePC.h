#pragma once
#include "EXider.h"
namespace EXider {

	class RemotePC {
		boost::asio::ip::tcp::socket m_socket;
		rpcStatus m_status;

		size_t m_id;
		boost::function<void( int, std::string )> m_callback;
		bool ListeningStarted;
		void sendHandler();
		void readHandler();
	public:
		RemotePC( const boost::asio::io_service& io, const std::string IP );
		void reconnect();
		void disconnect();
		inline const rpcStatus status() const;
		void sendRequest( const std::string& request ) const;
		void readRequest( const std::string& request ) const;
		inline void setID( size_t ID );
		inline void setCallBackFunction( const boost::function<void( int ID, std::string result )>& cb );
		inline size_t getID() const;

	};
};