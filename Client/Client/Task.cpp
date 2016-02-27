#include "EXider.h"
namespace EXider {
	Task::Task( const std::vector<boost::shared_ptr<RemotePC> > workingPCs, const std::string downloadURL, const std::string executeCommand, bool autoFree) :
		m_workingPCs( workingPCs ), m_downloadsFiles( workingPCs.size(), false ), m_result( workingPCs.size(), "-" ),
		m_downloadURL( downloadURL ), m_executeCommand( executeCommand ), m_autoFree( autoFree ) {
		for ( size_t i = 0; i < m_workingPCs.size(); ++i ) {
			m_workingPCs[ i ]->setID( i );
			m_workingPCs[ i ]->setCallBackFunction( boost::bind( &Task::handler, this, _1, _2 ) );
		}
	}
	Task::Task( const std::vector<boost::shared_ptr<RemotePC> > workingPCs, const std::string executeCommand, bool autoFree ) :
		m_workingPCs( workingPCs ), m_downloadsFiles( workingPCs.size(), true ), m_result( workingPCs.size(), "-" ),
		m_executeCommand( executeCommand ), m_autoFree( autoFree ) {
		for ( size_t i = 0; i < m_workingPCs.size(); ++i ) {
			m_workingPCs[ i ]->setID( i );
			m_workingPCs[ i ]->setCallBackFunction( boost::bind( &Task::handler, this, _1, _2 ) );
		}
	}
	void Task::run() {
		char request[ 256 ];

		for ( int i = 0; i < m_workingPCs.size(); ++i ) {
			if ( !m_downloadsFiles[ i ] )
				sprintf( request, "Donwload %s", m_downloadURL.c_str() );

			else
				sprintf( request, "Run %s -pcid %d", m_executeCommand, i );

			m_workingPCs[ i ]->sendRequest( request );

		}
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

	void Task::handler( size_t pcID, const std::string result) {
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
			if ( command == "OK" )
				return;

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
				sprintf( request, "Run %s -pcid %d", m_executeCommand, pcID );
			}
		}
		else if (command == "ExecuteResult" ) {
			std::getline( iss, command );
			m_result[ pcID ] = command;
		}
	}
}