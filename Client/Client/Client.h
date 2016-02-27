#pragma once
#include "EXider.h"
namespace EXider {
	
	class Client {
//		Logger m_logger;
//		Information m_info;
//		FtpClient m_ftp;

		std::vector<boost::shared_ptr<RemotePC> > m_pc;
		std::vector<boost::shared_ptr<RemotePC> > m_busyPC;
		std::vector<Task> m_jobs;
		boost::asio::io_service& m_io;
		void commandHandler( const std::string command );
	public:
		Client( boost::asio::io_service& io );
		void run();
		void addRemotePCs(const std::vector<boost::asio::ip::address>&  IP);
		void deleteRemotePC(size_t pcID);
		void deleteRemotePc( std::vector<size_t> pcIDs );
		void loadRemotePCs(const std::string fileToLoad);
		void saveRemotePCs(const std::string fileToSave);

		int createJob();
		void cancelJob( size_t jobID );
		void cancelJobs( std::vector<size_t> jobIDs );
	};
}