#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

//Choose your build platform by defining it:
#ifdef __linux__
#define LINUX
#endif

#ifdef __APPLE__
#define OSX
#endif
#ifdef __MACH__
#define OSX
#endif

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef _WIN64
#define WINDOWS
#endif

#endif // SYSTEM_H_INCLUDED
