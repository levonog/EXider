#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include <boost\asio.hpp>
#include <boost\thread.hpp>

namespace EXider {

	enum rpcStatus { // RemotePC Status
		ConnectionError,
		ErrorRequired,
		Available,
		Working,
		SendingRequest
	};

	class Logger;
	class FtpClient;
	class Information;
	class RemotePC;
	class Job;
	class Client;
	

}

#include "Logger.h"
#include "FtpClient.h"
#include "Information.h"
#include "RemotePC.h"
#include "Job.h"
#include "Client.h"
