#pragma once

namespace Hazel
{
	class  GraphicsContext
	{
	public:
		virtual void Init()=0;
		virtual void SwapBuffer()=0;

		virtual void PrintVersionInfo()=0;
	};
}
