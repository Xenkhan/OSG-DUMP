#include "Window.hpp"

namespace blox {
	Window::Window() : closing(false) {
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0){
			fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		}
	
	}

	Window::~Window() {
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
	}

	void Window::createWindow(osg::Vec2us size) {
		windowSize = size;
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
		sdlWindow = SDL_CreateWindow("FUCK",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			size.x(), size.y(), 
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		glContext = SDL_GL_CreateContext(sdlWindow);
		
		SDL_GL_SetSwapInterval(1);

		gw = viewer.setUpViewerAsEmbeddedInWindow(0, 0, size.x(), size.y());
		viewer.getCamera()->setDrawBuffer(GL_BACK);
		viewer.getCamera()->setReadBuffer(GL_BACK);

		osg::DisplaySettings::instance()->setMinimumNumStencilBits(1);
		GLbitfield bitfield = viewer.getCamera()->getClearMask() | GL_STENCIL_BUFFER_BIT;
		viewer.getCamera()->setClearMask(bitfield);
		viewer.getCamera()->setClearStencil(0);

		//viewer.getCamera()->getGraphicsContext()->getState()->setUseModelViewAndProjectionUniforms(true);
		//viewer.getCamera()->getGraphicsContext()->getState()->setUseVertexAttributeAliasing(true);

		SDL_GL_SwapWindow(sdlWindow);
	}

	void Window::setScene(osg::Node *node) {
		viewer.setSceneData(node);
		viewer.setCameraManipulator(new osgGA::TrackballManipulator);
		viewer.addEventHandler(new osgViewer::StatsHandler);
		viewer.realize();

	}

	bool Window::doFrame() {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			convertEvents(e);
			
		}


		if(viewer.checkNeedToDoFrame()) viewer.frame();
		SDL_GL_SwapWindow(sdlWindow);
		return true;
	}
	
	void Window::convertEvents(SDL_Event &e) {
		osgGA::EventQueue *eq = gw->getEventQueue();

		switch (e.type) {
		case SDL_QUIT: 
			closing = true;
			break;
		case SDL_MOUSEMOTION:
			eq->mouseMotion(e.motion.x, e.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			eq->mouseButtonPress(e.button.x, e.button.y, e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			eq->mouseButtonRelease(e.button.x, e.button.y, e.button.button);
			break;

		case SDL_KEYUP:
			eq->keyRelease((osgGA::GUIEventAdapter::KeySymbol)e.key.keysym.sym);
			break;
		case SDL_KEYDOWN:
			eq->keyPress((osgGA::GUIEventAdapter::KeySymbol)e.key.keysym.sym);
			break;
		case SDL_WINDOWEVENT: {
			switch (e.window.event) {
			case SDL_WINDOWEVENT_RESIZED: 
				gw->resized(0, 0, e.window.data1, e.window.data2);
				eq->windowResize(0, 0, e.window.data1, e.window.data2);
				break;
			}
			break;
		}


		
	//	osgGA::GUIEventAdapter::KeySymbol::
		}
	}

	






	SDL_Window *Window::getSDLWindow() {
		return sdlWindow;
	}

	osgViewer::Viewer *Window::getViewer() {
		return &viewer;
	}

	bool Window::isClosing() {
		return closing;
	}










}
