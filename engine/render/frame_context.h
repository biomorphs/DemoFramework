/*
DemoFramework
Matt Hoyle
*/
#pragma once

namespace Render
{
	class Device;
	class FrameContext
	{
	public:
		FrameContext(Device& d);
		~FrameContext() = default;
		FrameContext(const FrameContext&) = delete;

		// Variadic template pushes arguments to command constructor
		template<class ... CommandType>
		void PushCommand(CommandType ... args);

	private:
		Device& m_device;
	};

	// Variadic template pushes arguments to command constructor
	template<class ... CommandType>
	void FrameContext::PushCommand(CommandType ... args)
	{

	}
}