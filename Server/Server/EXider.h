#pragma once
#define _CRT_SECURE_NO_WARNINGS
//Standard
#include <iostream>
#include <sstream>
#include <Fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
//Boost
#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\timer.hpp>

namespace EXider {
	// Variables
	const size_t PORT = 8008;



	// Classes
	class Program;
	class ProgramExecutor;
	class Server;

}
#include "Program.h"
#include "ProgramExecutor.h"
#include "Server.h"
