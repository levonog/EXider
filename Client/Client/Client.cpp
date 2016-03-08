#include "Client.h"
namespace EXider {
	void Client::commandHandler( const std::string command ) {

	}
	EXider::Client::Client( boost::asio::io_service & io ) :
		m_io( io ) {

	}

	void Client::run() {
		std::string comLine;
		CommandParser parser;
		boost::system::error_code er;
		while ( true ) {
			std::cout << "EXider >> ";
			std::getline( std::cin, comLine );
			parser.parseCommand( comLine );
			if ( parser.command() == "pc" ) {
				auto arg = parser.arguments();
				if ( arg.empty() ) {
					std::cout << "No arguments of command \"pc\"" << std::endl;
				}
				else if ( arg[ 0 ].argument == "status" ) {

				}
				else if ( arg[ 0 ].argument == "add" ) {
					std::vector<boost::asio::ip::address> pc_ip;
					bool badIP = false;
					for ( int i = 1; i < arg.size(); ++i ) {
						if ( arg[ i ].argument == "ip" ) {
							for ( int j = 0; j < arg[ i ].parameters.size(); ++j ) {
								auto ip = boost::asio::ip::address::from_string( arg[ i ].parameters[ j ], er );
								if ( er ) {
									badIP = true;
								}
								else
									pc_ip.push_back( ip );
							}
						}
						else if ( arg[ i ].argument == "f" ) {
							for ( int j = 0; j < arg[ i ].parameters.size(); ++j ) {
								std::ifstream is( arg[ i ].parameters[ j ] );
								if ( is.bad() ) {
									badIP = true;
									continue;
								}
								std::string strIP;
								while ( is >> strIP ) {
									auto ip = boost::asio::ip::address::from_string( strIP, er );
									if ( er ) {
										badIP = true;
									}
									else
										pc_ip.push_back( ip );
								}
							}
						}
					}
					if ( badIP ) {
						std::cout << "Warning! Not all IPs will be processed. Some of them don't look like IPs\n";
					}
					addRemotePCs( pc_ip );
				}
				else if ( arg[ 0 ].argument == "delete" ) {
					std::vector<boost::asio::ip::address> pc_ip;
					bool badIP = false;
					for ( int i = 1; i < arg.size(); ++i ) {
						if ( arg[ i ].argument == "ip" ) {
							for ( int j = 0; j < arg[ i ].parameters.size(); ++j ) {
								auto ip = boost::asio::ip::address::from_string( arg[ i ].parameters[ j ], er );
								if ( er ) {
									badIP = true;
								}
								else
									pc_ip.push_back( ip );
							}
						}
						else if ( arg[ i ].argument == "f" ) {
							for ( int j = 0; j < arg[ i ].parameters.size(); ++j ) {
								std::ifstream is( arg[ i ].parameters[ j ] );
								if ( is.bad() ) {
									badIP = true;
									continue;
								}
								std::string strIP;
								while ( is >> strIP ) {
									auto ip = boost::asio::ip::address::from_string( strIP, er );
									if ( er ) {
										badIP = true;
									}
									else
										pc_ip.push_back( ip );
								}
							}
						}
					}
					if ( badIP ) {
						std::cout << "Warning! Not all IPs will be processed. Some of them don't look like IPs.\n";
					}
					deleteRemotePCs( pc_ip );
				}
				else if ( arg[ 0 ].argument == "save" ) {
					if ( arg.size() != 1 ) {
						std::cout << "Too many arguments in command \"save\".\n";
					}
					else if ( arg[ 0 ].parameters.size() != 1 ) {
						std::cout << "No file name found!\n";
					}
					else
						saveRemotePCs( arg[ 0 ].parameters[ 0 ] );
				}
				else {
					std::cout << "Wrong argument." << std::endl;
				}
			}
			else if ( parser.command() == "task" ) {
				auto arg = parser.arguments();
				if ( arg.empty() ) {
					std::cout << "No arguments of command \"task\"" << std::endl;
				}
				else if ( arg[ 0 ].argument == "status" ) {

				}
				else if ( arg[ 0 ].argument == "start" ) {
					bool badArgument = false;
					int computersWillBeUsed = 1;
					std::string programArguments = "";
					std::string programPath = "";
					bool withoutSending = false;
					if ( !arg[ 0 ].parameters.empty() )
						programPath = arg[ 0 ].parameters[ 0 ];
					for ( int i = 1; i < arg.size(); ++i ) {
						if ( ( arg[ i ].argument == "c" || arg[ i ].argument == "counter" ) && arg[ i ].parameters.size() == 1 ) {
							computersWillBeUsed = std::atoi( arg[ i ].parameters[ 0 ].c_str() );
						}
						else if ( ( arg[ i ].argument == "p" || arg[ i ].argument == "path" ) && arg[ i ].parameters.size() == 1 ) {
							programPath = arg[ i ].parameters[ 0 ];
						}
						else if ( ( arg[ i ].argument == "a" || arg[ i ].argument == "arg" ) && arg[ i ].parameters.size() == 1 ) {
							programArguments = arg[ i ].parameters[ 0 ];
						}
						else if ( arg[ i ].argument == "without-sending" || arg[ i ].argument == "wd" ) {
							withoutSending = true;
						}
						else {
							std::cout << "Bad argument \"" << arg[ i ].argument << "\".\n";
							badArgument = true;
							break;
						}
					}
					if ( badArgument )
						continue;
					startTask( programPath, programArguments, computersWillBeUsed, withoutSending );
				}
			}
			else if ( parser.command() == "help" ) {

			}
			else if ( parser.command() == "exit" ) {
				break;
			}
			else {
				std::cout << "Wrong command name: " << parser.command() << std::endl;
			}
		}


	}
	void Client::addRemotePCs( const std::vector<boost::asio::ip::address>& IPs ) {
		for ( auto ip : IPs ) {
			if ( m_freePC.insert( boost::shared_ptr<RemotePC>( new RemotePC( m_io, ip ) ) ).second )
				std::cout << "Remote PC with IP " << ip.to_string() << " was added.\n";
			else
				std::cout << "Remote PC with IP " << ip.to_string() << " was already added.\n";
		}
	}
	void Client::deleteRemotePCs( const std::vector<boost::asio::ip::address>& IPs ) {
		for ( size_t i = 0; i < IPs.size(); ++i ) {
			m_freePC.erase( boost::shared_ptr<RemotePC>( new RemotePC( m_io, IPs[ i ] ) ) );
			m_busyPC.erase( boost::shared_ptr<RemotePC>( new RemotePC( m_io, IPs[ i ] ) ) );

			std::cout << "Remote PC with IP " << IPs[ i ].to_string() << " was deleted.\n";
		}
	}

	void Client::saveRemotePCs( const std::string& fileToSave ) {
		std::ofstream os( fileToSave );
		if ( os.bad() ) {
			std::cout << "Can't open file " << fileToSave << std::endl;
		}
		else {
			for ( auto it : m_freePC )
				os << it->getIP().to_string() << " ";
			for ( auto it : m_busyPC )
				os << it->getIP().to_string() << " ";
		}
	}

	void Client::startTask( const std::string & filePath, const std::string & arguments, int computersToUse, bool withoutSendingProgram ) {
		if ( computersToUse > m_freePC.size() ) {
			std::cout << "Not enough computers to porcess current task. " << m_freePC.size() << " available." << std::endl;
			return;
		}
		PCList listForTask;
		for ( int i = 0; i < computersToUse; ++i ) {
			listForTask.insert( *m_freePC.begin() );
			m_busyPC.insert( *m_freePC.begin() );
			m_freePC.erase( m_freePC.begin() );
		}
		if ( withoutSendingProgram )
			m_tasks.push_back( boost::shared_ptr<Task>( new Task( listForTask, filePath + " " + arguments ) ) );
		std::cout << "Task started.\n";
		// TODO
	}

}