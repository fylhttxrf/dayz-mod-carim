#ifndef CarimLogging
#define CarimLogging

class CarimLogging extends Managed {
    static const int NONE = 0;
    static const int WARN = 1;
    static const int INFO = 2;
    static const int DEBUG = 3;
    static const int TRACE = 4;

    static void LogMessage(string message) {
        Print("[Carim] " + message);
    }

    static void LogServerMessage(int level, string message) {
        if (WillLog(level)) {
            Print("[Carim] " + message);
        }
    }

    static void Warn(string message) {
        LogServerMessage(WARN, message);
    }

    static void Info(string message) {
        LogServerMessage(INFO, message);
    }

    static void Debug(string message) {
        LogServerMessage(DEBUG, message);
    }

    static void Trace(string message) {
        LogServerMessage(TRACE, message);
    }

    static bool WillLog(int level) {
        return CarimModelSettingsDAL.Get().verbosity >= level;
    }
}

#endif
