#include "Client.h"
namespace EXider {
	void Client::commandHandler( const std::string command ) {

	}
	EXider::Client::Client( boost::asio::io_service & io ) :
		m_io( io ), m_info(this) {

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
				else if ( arg[ 0 ].argument == "list" ) {
					size_t Status = 0;
					bool badStatus = false;
					bool params = !arg[ 0 ].parameters.empty();
					if ( !params )
						for ( int i = 1; i < arg.size(); ++i ) {
							if ( !arg[ i ].parameters.empty() ) {
								params = true;
								break;
							}
							if ( arg[ i ].argument == "available" )
								Status |= Available;
							else if ( arg[ i ].argument == "busy" )
								Status |= Busy;
							else if ( arg[ i ].argument == "not-connected" )
								Status |= NotConencted;
							else {
								badStatus = true;
								break;
							}
						}
					if ( badStatus ) {
						std::cout << "Invalid Status" << std::endl;
					}
					else if ( params ) {
						std::cout << "Unexpected parameters" << std::endl;
					}
					else {
						m_info.pcList( Status == 0 ? Available : Status );
					}

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
				else if ( arg[ 0 ].argument == "help" ) {
					m_info.help( Information::CommandType::PC );
				}
				else {
					m_info.wrongArgument( arg[ 0 ].argument );
				}
			}
			else if ( parser.command() == "task" ) {
				auto arg = parser.arguments();
				if ( arg.empty() ) {
					std::cout << "No arguments of command \"task\"" << std::endl;
				}
				else if ( arg[ 0 ].argument == "status" ) {
					if ( arg.size() != 1 ) {
						std::cout << "Invalid arguments." << std::endl;
					}
					if ( arg[ 0 ].parameters.empty() ) {
						m_info.taskList();
					}
					else {
						bool notAllProcessed = false;
						std::vector<size_t> tIDs;
						for ( int i = 0; i < arg[ 0 ].parameters.size(); ++i ) {
							bool badNumber = false;
							for ( int j = 0; j < arg[ 0 ].parameters[ i ].size(); ++j ) {
								if ( arg[ 0 ].parameters[ i ][ j ] > '9' || arg[ 0 ].parameters[ i ][ j ] < '0' ) {
									notAllProcessed = badNumber = true;
									break;
								}
							}
							if ( badNumber )
								continue;
							std::istringstream iss( arg[ 0 ].parameters[ i ] );
							tIDs.push_back( 0 );
							iss >> tIDs.back();
						}
						if ( notAllProcessed ) {
							std::cout << "Warning! Not all Tasks will be processed." << std::endl;
						}
						m_info.taskInformation( tIDs );
					}
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
						else if ( arg[ i ].argument == "without-sending" || arg[ i ].argument == "ws" ) {
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
				else if ( arg[ 0 ].argument == "stop" ) {

				}
				else {
					std::cout << "Wrong argument." << std::endl;
				}
			}
			else if ( parser.command() == "help" ) {
				m_info.help();
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
			boost::shared_ptr<RemotePC> pc( new RemotePC( m_io, ip ) );
			if ( pc->connect() ) {
				m_freePC.insert( pc );
				std::cout << "Remote PC with IP " << ip.to_string() << " was connected.\n";
			}
			else {
				m_notConnectedPC.insert( pc );
				std::cout << "Remote PC with IP " << ip.to_string() << " wasn't connected.\n";
			}
		}
	}
	void Client::deleteRemotePCs( const std::vector<boost::asio::ip::address>& IPs ) {
		for ( size_t i = 0; i < IPs.size(); ++i ) {
			m_freePC.erase( boost::shared_ptr<RemotePC>( new RemotePC( m_io, IPs[ i ] ) ) );
			m_busyPC.erase( boost::shared_ptr<RemotePC>( new RemotePC( m_io, IPs[ i ] ) ) );
			m_notConnectedPC.erase( boost::shared_ptr<RemotePC>( new RemotePC( m_io, IPs[ i ] ) ) );
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
			std::cout << "Not enough computers to process current task. " << m_freePC.size() << " available." << std::endl;
			return;
		}
		PCList listForTask;
		for ( int i = 0; i < computersToUse; ++i ) {
			listForTask.insert( *m_freePC.begin() );
			m_busyPC.insert( *m_freePC.begin() );
			m_freePC.erase( m_freePC.begin() );
		}
		if ( withoutSendingProgram ) {
			m_tasks.push_back( boost::shared_ptr<Task>( new Task( m_io, listForTask, filePath + " " + arguments ) ) );
		}
		std::cout << "Task started.\n";
		// TODO
	}
	void Client::stopTask( size_t tID ) {
		if ( tID > m_tasks.size() ) {
			throw std::exception( "Invalid Task ID" );
		}
		m_tasks[ tID ]->stop();
	}
	void Client::discardTask( size_t tID ) {
		if ( tID > m_tasks.size() ) {
			throw std::exception( "Invalid Task ID" );
		}
		m_tasks.erase( m_tasks.begin() + tID );
	}
}