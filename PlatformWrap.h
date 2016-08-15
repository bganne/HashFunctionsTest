#pragma once

// Place for random platform dependent pieces used by main code


// ----------------------------------------------------------------------
// Basic platform macros

#if defined(_MSC_VER)
#	define PLATFORM_MICROSOFT 1
#	if defined(_XBOX_ONE)
#		define PLATFORM_XBOXONE 1
#	else
#		define PLATFORM_WINDOWS 1
#	endif
#endif

#if defined(__APPLE__)
#	include <TargetConditionals.h>
#	define PLATFORM_APPLE 1
#	if TARGET_OS_IPHONE
#		define PLATFORM_IOS 1
#	else
#		define PLATFORM_MAC 1
#	endif
#endif

#if defined(EMSCRIPTEN)
#	define PLATFORM_WEBGL 1
#endif

#if defined(__ORBIS__)
#	define PLATFORM_PS4 1
#endif

#if defined(__unix__)
#	define PLATFORM_POSIX 1
#endif


// ------------------------------------------------------------------------------------
// Misc

#if PLATFORM_MICROSOFT
#	define _CRT_SECURE_NO_WARNINGS
#	include <Windows.h>
#endif

#if PLATFORM_PS4
	// CENSORED
#endif


// ------------------------------------------------------------------------------------
// Timer code - TimerBegin and TimerEnd functions

#if PLATFORM_MICROSOFT
	static LARGE_INTEGER s_Time0;
	static void TimerBegin()
	{
		QueryPerformanceCounter (&s_Time0);
	}
	static float TimerEnd()
	{
		static bool timerInited = false;
		static LARGE_INTEGER ticksPerSec;
		if (!timerInited) {
			QueryPerformanceFrequency(&ticksPerSec);
			timerInited = true;
		}
		LARGE_INTEGER ttt1;
		QueryPerformanceCounter (&ttt1);
		float timeTaken = float(double(ttt1.QuadPart-s_Time0.QuadPart) / double(ticksPerSec.QuadPart));
		return timeTaken;
	}

#elif PLATFORM_APPLE
	#include <sys/time.h>
	static timeval s_Time0;
	static void TimerBegin()
	{
		gettimeofday(&s_Time0, NULL);
	}
	static float TimerEnd()
	{
		timeval ttt1;
		gettimeofday( &ttt1, NULL );
		timeval ttt2;
		timersub( &ttt1, &s_Time0, &ttt2 );
		float timeTaken = ttt2.tv_sec + ttt2.tv_usec * 1.0e-6f;

		return timeTaken;
	}

#elif PLATFORM_WEBGL
	#include "emscripten.h"
	static double s_Time0;
	static void TimerBegin()
	{
		s_Time0 = emscripten_get_now();
	}
	static float TimerEnd()
	{
		double t = emscripten_get_now();
		float timeTaken = (t - s_Time0) * 0.001;
		return timeTaken;
	}

#elif PLATFORM_PS4
	// CENSORED

#elif PLATFORM_POSIX
	#include <stdint.h>
	#include <time.h>
	static uint64_t s_Time0;
	static void TimerBegin()
	{
		struct timespec ts;
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
		s_Time0 = ts.tv_sec * 1000000000 + ts.tv_nsec;
	}
	static float TimerEnd()
	{
		struct timespec ts;
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
		return (ts.tv_sec * 1000000000 + ts.tv_nsec - s_Time0) * 1e-9f;
	}


#else
	#error "Unknown platform, timer code missing"

#endif

