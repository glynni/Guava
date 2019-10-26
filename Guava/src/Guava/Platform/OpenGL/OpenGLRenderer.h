#pragma once
#include "Guava/Renderer/Renderer.h"

namespace Guava
{
	class OpenGLRenderer : public Renderer
	{
	public:

		OpenGLRenderer();
		~OpenGLRenderer();

		void ClearScreen_Impl();
	};
}

