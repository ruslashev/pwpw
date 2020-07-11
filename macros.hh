#pragma once

#include <iostream>

typedef const char * const strlit;

#define _strfy(X) #X
#define strfy(X) _strfy(X)

#define die(Msg...) \
	do { \
		std::cerr << Msg << std::endl; \
		std::exit(1); \
	} while (0);

#define die_if(Condition) \
	if (Condition) { \
		die("condition " << #Condition << " failed at " << __FILE__ << ":" << __LINE__); \
	};

