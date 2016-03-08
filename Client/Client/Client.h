#pragma once
#include "EXider.h"
namespace EXider {

	class Client {
		//		Logger m_logger;
		//		Information m_info;
		//		FtpClient m_ftp;

		PCList m_freePC, m_busyPC;
		std::vector<boost::shared_ptr<Task> > m_tasks;
		boost::asio::io_service& m_io;
		void commandHandler( const std::string command );
	public:
		Client( boost::asio::io_service& io );
		void run();
		void addRemotePCs( const std::vector<boost::asio::ip::address>&  IP );
		void deleteRemotePCs( const std::vector<boost::asio::ip::address>&  IP );

		//void deleteRemotePC(size_t pcID);
		//void deleteRemotePc( std::vector<size_t> pcIDs );
		void saveRemotePCs( const std::string& fileToSave );
		void startTask( const std::string& filePath, const std::string& arguments, int computersToUse, bool withoutSendingProgram );
	};
}