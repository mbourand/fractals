#pragma once

namespace ezgl
{
	class FPSCounter
	{
	protected:
		int _fps;
		int _frameCount;
		int _lastTime;

	public:
		FPSCounter();

		void update();

		int getFPS();
	};
}
