#pragma once

#include "glad/glad.h"

void GlClearError();

bool GlLogCall(const char* function, const char* file, int line);


#ifdef HZ_DEBUG

#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCall(x) GlClearError();\
                x;\
                ASSERT(GlLogCall(#x,__FILE__,__LINE__))


#else

#define GLCall(x)  x;

#endif // HZ_DEBUG



