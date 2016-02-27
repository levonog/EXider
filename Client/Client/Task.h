#pragma once
#include "EXider.h"
namespace EXider {
	class Task {
		friend class RemotePC;
		boost::recursive_mutex m_mutex;
		std::vector<boost::shared_ptr<RemotePC> > m_workingPCs;
		const std::string m_downloadURL, m_executeCommand;
		std::vector<bool> m_downloadsFiles;
		std::vector<std::string> m_result;
		void handler( size_t pcID, std::string result );
		bool m_autoFree;
	public:
		Task( const std::vector<boost::shared_ptr<RemotePC> > workingPCs, const std::string downloadURL, const std::string executeCommand, bool autoFree = 0 );
		Task( const std::vector<boost::shared_ptr<RemotePC> > workingPCs, const std::string executeCommand, bool autoFree = 0 );
		void run();
		const std::string getResult(const std::string& delimeter) const;
		const std::string getInfromation() const;
	};
}