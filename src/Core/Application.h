#pragma once

#include "Core.h"

namespace SheeEngine
{
	class SENGINE_API Application
	{
	public:
	  	Application();

		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}


