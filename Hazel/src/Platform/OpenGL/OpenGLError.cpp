#include "hzpch.h"
#include "OpenGLError.h"

void GlClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		if (error == 1282)
		{
			// HZ_CORE_WARN("[ OpenGl Error] Code: {0}, Function: {1},File:{2} ,Line: {3}.", error, function, file, line);
			// HZ_CORE_WARN("skip 1282 opengl error, invalid operation.")
			continue;
		}
		const char* errStr = (const char*)glGetString(error);
		HZ_CORE_ERROR("[ OpenGl Error] Code: {0}, Function: {1},File:{2} ,Line: {3}.", error, function, file, line);
		if(errStr!=nullptr)
			HZ_CORE_ERROR("Error information : {0}", errStr);
		return false;
	}
	return true;
}