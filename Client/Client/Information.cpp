#include "EXider.h"
namespace EXider {
	Information::Information( const Client* client ) :
		m_client( client ) {

	}

	void Information::taskList() {
		for ( size_t i = 0; i < m_client->m_tasks.size(); ++i ) {
			std::cout << "[" << i << "] Task result : " << m_client->m_tasks[ i ]->getResult() << std::endl;
		}
	}
	void Information::taskInformation( const std::vector<size_t>& tIDs ) {
		for ( auto tID : tIDs )
			if ( tID > m_client->m_tasks.size() ) {
				std::cout << "Invalid task ID: " << tID << std::endl;
			}
			else
				std::cout << "Task " << tID << std::endl << m_client->m_tasks[ tID ]->getInfromation() << std::endl;
	}

	void Information::pcList( size_t Status ) {
		if ( Status & Available ) {
			std::cout << "Available PCs: " << std::endl;
			int countInLine = 3;
			int counter = 0;
			for ( auto pc : m_client->m_freePC ) {
				if ( counter = 3 ) {
					std::cout << std::endl;
					counter = 0;
				}
				else if ( counter > 0 ) {
					std::cout << "\t";
				}
				std::cout << pc->getIP().to_string();
			}
			std::cout << std::endl;
		}
		if ( Status & Busy ) {
			std::cout << "Busy PCs: " << std::endl;
			int countInLine = 3;
			int counter = 0;
			for ( auto pc : m_client->m_busyPC ) {
				if ( counter = 3 ) {
					std::cout << std::endl;
					counter = 0;
				}
				else if ( counter > 0 ) {
					std::cout << "\t";
				}
				std::cout << pc->getIP().to_string();
			}
			std::cout << std::endl;
		}
		if ( Status & NotConencted ) {
			std::cout << "Not connected PCs: " << std::endl;
			int countInLine = 3;
			int counter = 0;
			for ( auto pc : m_client->m_notConnectedPC ) {
				if ( counter = 3 ) {
					std::cout << std::endl;
					counter = 0;
				}
				else if ( counter > 0 ) {
					std::cout << "\t";
				}
				std::cout << pc->getIP().to_string();
			}
			std::cout << std::endl;
		}
	}

	void Information::help( size_t CommandTypes ) {
		if ( CommandTypes & Usage ) {
			std::cout <<
				"EXider Information\n"
				"Usage (pc/task/help) (arguments) [parameters]\n" << std::endl;
		}
		if ( CommandTypes & PC ) {
			std::cout <<
				"pc -(add/delete/save/list) [arguments]\n"
				"This command controls RemotePCs.\n"
				"\n"
				"-add                     - Adds new RemotePCs.\n"
				"   -ip IP_List           - Adds new RemotePCs by IP Address.\n"
				"   -f FileName_List      - Adds new RemotePCs by IPs from files.\n"
				"\n"
				"-delete                  - Deletes RemotePCs.\n"
				"   -ip IP_List           - Delete RemotePCs by their IP Address.\n"
				"   -f FileName_List      - Delete RemotePCs by IPs from files.\n"
				"\n"
				"-save FileName           - Saves RemotePCs to file.\n"
				"\n"
				"-list                    - List of RemotePCs. If used without arguments will print only Available RemotePCs.\n"
				"   -available            - Prints available RemotePC's IP Addresses\n"
				"   -busy                 - Prints busy RemotePC's IP Addresses\n"
				"   -not-connected        - Prints not connected RemotePC's IP Addresses\n"
				"\n"
				"-help                    - Information about this command\n" << std::endl;
		}
	}
	void Information::warning( const std::string& message ) {
		std::cout << "Warning! " << message << std::endl;
	}
	void Information::wrongArgument( const std::string& arg ) {
		std::cout << "Wrong argument name \"" << arg << "\"." << std::endl;
	}
	void Information::wrongParameter( const std::string& param ) {
		std::cout << "Wrong parameter \"" << param << "\"." << std::endl;
	}
}