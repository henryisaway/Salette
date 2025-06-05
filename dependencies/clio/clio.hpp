#pragma once

#include <iostream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <chrono>

namespace Clio {

    // --- Importance level ---
    /*
    Used only to organise the level of importance of a log message.
    Doesn't actually change anything in the implementation itself, only
    the output displays the message a different colour.
    */
    enum class Severity {
        UNSET = -1,
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    // --- Logger class ---
    /*
    Singleton class that handles all logging functionality.
    */
    class Logger {
    private:
        std::mutex mtx;
        Severity m_severityThreshold;

        Logger(){
            m_severityThreshold = Severity::UNSET;
        }

        inline const char* severityToString(Severity severity) const {
            switch(severity) {
            case Severity::TRACE: return "TRACE";
            case Severity::DEBUG: return "DEBUG";
            case Severity::INFO: return "INFO";
            case Severity::WARN: return "WARN";
            case Severity::ERROR: return "ERROR";
            case Severity::FATAL: return "FATAL";
            default: return "UNKNOWN";
            }
        }

        inline const std::string getCurrentTimestamp() const {
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);

            std::ostringstream oss;
            oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");

            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

            oss << "." << std::setfill('0') << std::setw(3) << ms.count();

            return oss.str();
        } 

        inline const bool shouldLog(Severity severity) const {
            return static_cast<int>(severity) >= static_cast<int>(m_severityThreshold);
        }

    public:
        static Logger& get() {
            static Logger instance;
            return instance;
        }

        inline void setSeverityThreshold(Severity severity){
            m_severityThreshold = severity;
        }

        // Template needed to handle different string types
        template<typename... Args>
        inline void log(Severity severity, const char* file, const int line, const Args&... args) {
            if(m_severityThreshold == Severity::UNSET){
                throw std::logic_error("Log severity threshold was not set. Run Clio::Logger.get().setSeverity( Clio::Severity::<Severity> ) to configure the logger before usage.");
                return;
            }

            if(shouldLog(severity)){
                std::lock_guard<std::mutex> lock(mtx);      // Basic thread-safety

                std::ostringstream oss;
                (oss << ... << args);

                std::cout << "[" << getCurrentTimestamp() << "] "
                    << "[" << severityToString(severity) << "] "
                    << "[" << file << ":" << line << "] "
                    << oss.str() << "\n";
            }
        }
    };
}

// --- Macro definitions ---
#define CLIO_TRACE(...) Clio::Logger::get().log(Clio::Severity::TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define CLIO_DEBUG(...) Clio::Logger::get().log(Clio::Severity::DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define CLIO_INFO(...) Clio::Logger::get().log(Clio::Severity::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define CLIO_WARN(...) Clio::Logger::get().log(Clio::Severity::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define CLIO_ERROR(...) Clio::Logger::get().log(Clio::Severity::ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define CLIO_FATAL(...) Clio::Logger::get().log(Clio::Severity::FATAL, __FILE__, __LINE__, __VA_ARGS__)