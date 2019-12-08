#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include <iostream>
using namespace std;
class FRANKENGINE_API GameBase {
private:

protected:
	Renderer * render;
	Window * window;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
public:
	bool Start(int h, int w, char* name);
	bool Stop();
	void Loop();
	GameBase();
	~GameBase();
};

