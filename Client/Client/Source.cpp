#include "EXider.h"
void main() {
	boost::asio::io_service io;
	EXider::Client client( io );
	client.run();
}