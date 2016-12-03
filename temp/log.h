#pragma once  

#ifdef LOGS

#define LOG(str)      \
    out << str << endl; \

#define WLOG(str)  \
    _world->out << str << endl;  \

#endif
#ifndef LOGS

#define LOG(str)
#define WLOG(str)


#endif