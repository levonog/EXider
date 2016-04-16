#define _CRT_SECURE_NO_WARNINGS
#include "EXider.h"

int main( int argc, char* argv[] )
{
	boost::asio::io_service io;

	EXider::Server serv( io );
	serv.run();

	/*EXider::CommandParser arg;

	std::string line;
	while ( true ) {
		std::getline( std::cin, line );
		arg.parseCommand( line );
		std::cout << "Command: " << arg.command() << std::endl;
		auto p = arg.arguments();
		for ( int i = 0; i < p.size(); ++i ) {
			std::cout << "\t Argument: " << p[ i ].argument << std::endl;
			std::cout << "\t\t Parametrs: ";
			for ( int j = 0; j < p[ i ].parameters.size(); ++j ) {
				std::cout << p[ i ].parameters[ j ] << std::endl;
				if ( j != p[ i ].parameters.size() - 1 ) {
					std::cout << "\t\t            ";
				}
			}
		}
	}*/
	return 0;
}