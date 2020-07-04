#pragma once

#include <iostream>

#define die(Msg...) \
	do { \
		std::cerr << Msg << std::endl; \
		std::exit(1); \
	} while (0);

#define die_if(Condition) \
	if (Condition) { \
		die("condition " << #Condition << " failed at " << __FILE__ << ":" << __LINE__); \
	};

