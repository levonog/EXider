#include "Client.h"
namespace EXider {
	void Client::commandHandler( const std::string command ) {

	}
	EXider::Client::Client( boost::asio::io_service & io ) :
		m_io( io ) {

	}

	void EXider::Client::run() {
		std::string command, comLine;
		boost::system::error_code er;
		while ( true ) {
			std::cout << "EXider >> ";
			std::getline( std::cin, comLine );
			std::istringstream iss( comLine );
			iss >> command;
			if ( command == "add" ) {
				/* END COMMAND START
				add [-c counter] -ip IPList
				IPList = IP [, IPList]
				*/
				int counter = 1;

				iss >> command;
				if ( command == "-c" ) {
					iss >> counter;
					iss >> command;
				}

				std::vector<boost::asio::ip::address> IPs( counter );

	
				if ( command != "-ip" ) {
					std::cout << "Wrong syntax for \"add\" command\n";
					continue;
				}
				bool somethingWrong = false;
				for ( int i = 0; i < counter; ++i ) {
					if ( iss >> command ) {
						IPs[ i ] = boost::asio::ip::address::from_string( command, er );
						if ( er ) {
							std::cout << "Wrong IP's format!\n";
							somethingWrong = true;
							break;
						}
					}
					else {
						std::cout << "Warning! Not all IPs where written. " << i << " IPs will be added.\n";
						IPs.resize( i );
					}
				}
				if ( somethingWrong )
					continue;
				addRemotePCs( IPs );
			} // ADD command END
			else if ( command == "load" ) {
				/* LOAD command START
					load "file_name"
				*/
				//TODO !!! NORMAL PARSE
				iss >> command;
				std::ifstream ifs( command );
				std::vector<boost::asio::ip::address> IPs;

				if ( ifs.bad() ) {
					std::cout << "Wrong file's name.\n";
					continue;
				}
				bool somethingWrong = false;
				while ( ifs >> command ) {
					IPs.push_back( boost::asio::ip::address::from_string( command, er ) );
					if ( er ) {
						std::cout << "Wrong IP's format!\n";
						somethingWrong = true;
						break;
					}
				}
				if ( somethingWrong )
					continue;
				addRemotePCs( IPs );
			}// LOAD command END
		}
		// TODO ! OTHER COMMANDS

	}
	void EXider::Client::addRemotePCs( const std::vector<boost::asio::ip::address>& IPs ) {
		for ( auto ip : IPs ) {
			m_pc.push_back( boost::shared_ptr<RemotePC>( new RemotePC( m_io, ip ) ) );
			std::cout << "Remote PC with IP " << ip.to_string() << " was added.\n";
		}
	}

	void EXider::Client::deleteRemotePC( size_t pcID )
	{
	}

	void EXider::Client::deleteRemotePc( std::vector<size_t> pcIDs )
	{
	}

	void EXider::Client::loadRemotePCs( const std::string fileToLoad )
	{
	}

	void EXider::Client::saveRemotePCs( const std::string fileToSave )
	{
	}

	int EXider::Client::createJob()
	{
		return 0;
	}

	void EXider::Client::cancelJob( size_t jobID )
	{
	}

	void EXider::Client::cancelJobs( std::vector<size_t> jobIDs )
	{
	}
}