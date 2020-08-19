#include "Exports.h"
//#include "Renderer.h"
#include "Renderizer.h"
//#include "Window.h"
#include <iostream>
using namespace std;
class FRANKENGINE_API GameBase {
private:

	float _deltaTime = 0;
	float _lastFrame = 0;
	float _currentFrame = 0;
	Renderizer* rnzr;

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
	float DeltaTime();
	
	GameBase();
	~GameBase();
	float DeltaTime();
};

