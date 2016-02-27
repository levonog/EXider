#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <exception>
#include <boost\asio.hpp>
#include <boost\thread.hpp>

namespace EXider {
	const size_t EXIDER_PORT = 8008;
	enum rpcStatus {	// RemotePC Statuses
		NotConencted,
		ConnectionError,
		Connecting,
		Available,
		WaitingForRequest,
		SendingRequest
	};

	class Logger; 
	class FtpClient;	// FTP Client to upload and download files
	class Information;	// Displaying different infromation
	class RemotePC;		// Remote PC controller (Server controller) 
	class Task;			// Task controller
	class Client;		// Main class producing all activity
	

}

#include "Logger.h"
#include "FtpClient.h"
#include "Information.h"
#include "RemotePC.h"
#include "Task.h"
#include "Client.h"
