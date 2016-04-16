#include "EXider.h"
namespace EXider {
	Task::Task( boost::asio::io_service& io, const PCList& workingPCs, const std::string downloadURL, const std::string executeCommand, bool autoFree) :
		m_workingPCs( workingPCs ), m_downloadsFiles( true ), m_result( workingPCs.size(), "-" ),
		m_downloadURL( downloadURL ), m_executeCommand( executeCommand ), m_autoFree( autoFree ),m_io(io), m_thread( boost::bind( &Task::run, this ) ) {
		size_t pcID = 0;
		for ( auto pc : m_workingPCs ) {
			pc->setID( pcID++ );
			pc->setCallBackFunction( boost::bind( &Task::handler, this, _1, _2 ) );
		}
	}
	Task::Task( boost::asio::io_service& io, const PCList& workingPCs, const std::string executeCommand, bool autoFree ) :
		m_workingPCs( workingPCs ), m_downloadsFiles( false ), m_result( workingPCs.size(), "-" ),
		m_executeCommand( executeCommand ), m_autoFree( autoFree ), m_io(io), m_thread(boost::bind(&Task::run, this) ) {
		size_t pcID = 0;
		for ( auto pc : m_workingPCs ) {
			pc->setID( pcID++ );
			pc->setCallBackFunction( boost::bind( &Task::handler, this, _1, _2 ) );
		}
	}
	void Task::run() {
		char request[ 256 ];

		for (auto pc : m_workingPCs) {
			if ( m_downloadsFiles )
				sprintf( request, "Download %s", m_downloadURL.c_str() );
			else
				sprintf( request, "Run %s -pcid %d", m_executeCommand.c_str(), pc->getID());
			pc->sendRequest( request );
		}
		m_io.run();
	}
	const std::string Task::getResult( const std::string& delimeter ) const {
		std::string sResult = "";
		for ( int i = 0; i < m_result.size(); ++i )
			sResult += m_result[ i ] + ( i != m_result.size() - 1 ? delimeter : "" );
		return sResult;
	}
	const std::string Task::getInfromation() const {
		return "";
	}

	void Task::handler(boost::shared_ptr<RemotePC> fromPC, const std::string result) {
		std::istringstream iss( result );
		std::string command;
		iss >> command;
		if ( command == "Reading" ) {
			iss >> command;
			if ( command == "OK" )
				return;
		}
		else if ( command == "Writing" ) {
			iss >> command;
			if ( command == "OK" ) {
				fromPC->readRequest();
			}
		}
		else if ( command == "Connecting" ) {
			iss >> command;
			if ( command == "OK" )
				return;
		}
		else if ( command == "Downloading" ) {
			iss  >> command;
			if ( command == "OK" ) {
				char request[ 256 ];
				sprintf( request, "Run %s -pcid %d", m_executeCommand, fromPC->getID() );
				fromPC->sendRequest( request );
			}
		}
		else if (command == "Result" ) {
			std::getline( iss, command );
			m_result[ fromPC->getID() ] = command;
			std::cerr << command << std::endl;
		}
	}
}