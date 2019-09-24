#ifndef WINDOW_H
#define WINDOW_H 1

namespace Suffer {
	class Window {
	public:
		Window();
		~Window();
		bool init(int width, int height);
		bool processEvents();
		void finish();
	private:

	};
};

#endif
