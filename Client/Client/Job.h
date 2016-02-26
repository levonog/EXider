#pragma once
#include "EXider.h"
namespace EXider {
	class Job {
		friend class RemotePC;
		std::vector<RemotePC*> m_workingPCs;
		std::vector<bool> m_downloadsFiles;
		std::vector<std::string> m_result;
		void handler( size_t pcID, const std::string& result );
	public:
		Job( const std::vector<RemotePC*> workingPCs, const std::string downloadURL, const std::string executeCommand, bool autoFree = 0 );
		Job( const std::vector<RemotePC*> workingPCs, const std::string executeCommand, bool autoFree = 0 );

	};
}