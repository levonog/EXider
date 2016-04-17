#define _CRT_SECURE_NO_WARNINGS
#include "EXider.h"

int main( int argc, char* argv[] )
{
	boost::asio::io_service io;

	EXider::Server serv( io );
	serv.run();

	return 0;
}