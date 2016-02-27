#include "EXider.h"
namespace EXider {
	RemotePC::RemotePC( boost::asio::io_service& io, const std::string& IP ) :
		m_socket( io ), m_status( NotConencted ),
		m_endpoint( boost::asio::ip::address::from_string( IP ), EXIDER_PORT ) {
		m_socket.async_connect( m_endpoint, boost::bind( &RemotePC::connectedHandler, this, _1 ) );
	}

	RemotePC::RemotePC( boost::asio::io_service & io, const boost::asio::ip::address & IP ) :
		m_socket( io ), m_status( NotConencted ),
		m_endpoint( IP, EXIDER_PORT ) {
		m_socket.async_connect( m_endpoint, boost::bind( &RemotePC::connectedHandler, this, _1 ) );

		}

		void RemotePC::reconnect() {
			disconnect();
			m_socket.async_connect( m_endpoint, boost::bind( &RemotePC::connectedHandler, this, _1 ) );
			m_status = Connecting;
		}

		void RemotePC::disconnect() {
			if ( m_socket.is_open() )
				m_socket.close();
			m_status = NotConencted;
		}

		inline const rpcStatus RemotePC::status() const {
			return m_status;
		}

		void RemotePC::sendRequest( const std::string& request ) {
			if ( !m_socket.is_open() )
				throw std::exception( "Socket isn't open" );
			else if ( m_status != Available )
				throw std::exception( "Connection ism't available" );

			m_socket.async_write_some( boost::asio::buffer( request + "\n" ), boost::bind( &RemotePC::sendHandler, this, _1 ) );
		}
		void RemotePC::readRequest() {
			if ( !m_socket.is_open() )
				throw std::exception( "Socket isn't open" );
			else if ( m_status != Available )
				throw std::exception( "Connection ism't available" );

			boost::asio::async_read_until( m_socket, m_buffer, '\n', boost::bind( &RemotePC::readHandler, this, _1, _2 ) );
		}
		void RemotePC::setID( size_t ID ) {
			m_id = ID;
		}
		void RemotePC::setCallBackFunction( const boost::function<void( int ID, std::string result )>& cb ) {
			m_callback = cb;
		}

		inline const boost::asio::ip::address RemotePC::getIP() const
		{
			return m_endpoint.address();
		}


		void RemotePC::readHandler( const boost::system::error_code& error, size_t bytes ) {
			if ( error )
				m_callback( m_id, "Reading ERROR" );
			std::istream is( &m_buffer );
			std::string result;
			std::getline( is, result );
			m_callback( m_id, result );
		}
		void RemotePC::sendHandler( const boost::system::error_code& error ) {
			if ( error )
				m_callback( m_id, "Wriing ERROR" );
			else
				m_callback( m_id, "Writing OK" );
		}
		void RemotePC::connectedHandler( const boost::system::error_code& error ) {
			if ( error ) {
				m_callback( m_id, "Connecting ERROR" );
				m_status = ConnectionError;
			}
			else {
				m_callback( m_id, "Writing OK" );
				m_status = Available;
			}
		}

	}