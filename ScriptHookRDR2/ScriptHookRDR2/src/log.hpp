#pragma once

class Log
{
private:
	bool m_Allocated{};
	std::ofstream m_LogFile;
	std::string m_FileName;

public:
	Log(std::string fileName) : m_FileName(std::move(fileName))
	{
		if (m_Allocated) return;

		auto currentWorkingDirectory = std::filesystem::current_path();

		auto logFilePath = currentWorkingDirectory /= m_FileName;

		// Delete old log file before logging.
		if (exists(logFilePath))
			remove(logFilePath);

		m_LogFile.open(logFilePath.c_str(), std::ios_base::app);
		m_LogFile << "Thanks for using ScriptHookRDR2 V2" << std::endl;

		m_Allocated = true;
	}

	~Log()
	{
		if (!m_Allocated) return;

		m_Allocated = false;

		Write("Closing Log File.");

		m_LogFile.close();
	}

	template <typename... Args>
	inline void Write(std::string_view fmt, Args const&... args)
	{
		auto message = std::vformat(fmt, std::make_format_args(args...));
		m_LogFile << message << std::endl << std::flush;
	}
};