// Copyright (C) 2008-2011 by Philipp Muenzel. All rights reserved
// Released under the terms of the GNU General Public License version 2 or later
// as published by the Free Software Foundation, Inc.

#ifndef LOG_H
#define LOG_H

#include <string>
#include <ctime>
#include <sstream>

namespace PPL {

class LogWriter;

enum Level {
    L_UNSPEC=-1,    //!< unspecified, occurs when no severity function pointer was called
    L_FAIL  = 0,    //!< Failure, forces quit of application
    L_ERROR = 1,    //!< Error, permits keeping the application running
    L_WARN  = 2,    //!< Warning
    L_INFO  = 3     //!< Information
};

/**
  * @brief Every log message that arises from libcanaero is in this format.
  */
struct LogEntry {
    Level lvl;          //!< Severity of the occured event, see enum
    time_t time;        //!< Timestamp
    std::string txt;    //!< Human-readable message
};


/**
  * @brief A stream-based logger using any LogWriter.
  * A Log instance corresponds to ONE log entry.
  *
  * Creating an instance provides the stream to which a log message is written.
  * Specifying severity level and Log::endl are mandatory.
  * @code Log() << Log::Error << "This is an error" << Log::endl;
  * Log() << Log::Info << "This is an information about " << some_integer << Log::endl @endcode
  * @author  (c) 2009-2011 by Philipp Münzel
  * @version 1.4
  */
class Log {
public:
    /**
      * create a new Logstream for ONE new message
      */
    Log();

    /**
      * Indicate the following message has severity Information
      */
    static Log& Info(Log& log);

    /**
      * Indicate the following message has severity Warnining
      */
    static Log& Warn(Log& log);

    /**
      * Indicate the following message has severity Error
      */
    static Log& Error(Log& log);

    /**
      * Indicate the following message has severity Failure
      */
    static Log& Fail(Log& log);

    /**
      * Terminate the log stream. This is mandatory!
      */
    static Log& endl(Log& log);

    /**
      * Log an integer.
      * @param i
      */
    Log& operator<<(long i);

    /**
      * Log a double.
      * @param d
      */
    Log& operator<<(double d);

    /**
      * Log a char
      * @param c
      */
    Log& operator<<(char c);

    /**
      * Log a string.
      * @param s
      */
    Log& operator<<(const std::string& s);

    /**
      * Invoke a function pointer on the logstream (set severity or terminate)
      */
    Log& operator<<(Log& (*f)(Log&));

private:
    Level m_severity;
    LogWriter& m_writer;
    std::ostringstream m_stream;
};
}

#endif // LOG_H