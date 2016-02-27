#pragma once
#include "EXider.h"
namespace EXider {
	class Task {
		boost::recursive_mutex m_mutex;
		std::vector<boost::shared_ptr<RemotePC> > m_workingPCs;		// PC's working on the task
		const std::string m_downloadURL, m_executeCommand;			// Download URL (ftp) and Executeing Command for RemotePC
		std::vector<bool> m_downloadsFiles;
		std::vector<std::string> m_result;							// Results received from RemotePC's
		void handler( size_t pcID, std::string result );			// call-back function for RemotePC
		bool m_autoFree;											// Automaticly delete PC from the task, when result is received
	public:
		Task( const std::vector<boost::shared_ptr<RemotePC> > workingPCs, const std::string downloadURL, const std::string executeCommand, bool autoFree = 0 );
		Task( const std::vector<boost::shared_ptr<RemotePC> > workingPCs, const std::string executeCommand, bool autoFree = 0 );
		void run();
		const std::string getResult(const std::string& delimeter) const;
		const std::string getInfromation() const;
	};
}