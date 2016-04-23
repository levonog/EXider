#include "EXider.h"
int main() {
	boost::asio::io_service io;
	EXider::Client client( io );
	client.run();
    return 0;
}