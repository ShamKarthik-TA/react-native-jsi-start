#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <iostream>
#include <stdlib.h>
#include <chrono>

class stop_watch
{
    public:
        double secs;
        double m_secs;
        
        void start () {
            secs   = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            m_secs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        double time () {
            double secs_now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            double m_secs_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            auto time = (m_secs_now - m_secs)/ 1000.0;
            //auto time = (1000.0 * (secs_now - secs) + (m_secs_now - m_secs))/ 1000.0;
            return time;
        }
};

#endif // STOP_WATCH_H