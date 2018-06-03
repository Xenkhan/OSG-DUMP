#pragma once
#include "../Dependencies.hpp"

namespace blox {

	class Window {
	public:
		Window();
		~Window();

		virtual void createWindow(osg::Vec2us size = osg::Vec2us(900, 600));
		virtual void setScene(osg::Node *node);
		virtual bool doFrame();

		virtual SDL_Window *getSDLWindow();
		virtual osgViewer::Viewer *getViewer();

		virtual bool isClosing();
	protected:
		virtual void convertEvents(SDL_Event &e);
		SDL_Window *sdlWindow;
		SDL_GLContext glContext;

		osgViewer::Viewer viewer;
		osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> gw;



		osg::Vec2us windowSize;
		bool closing;
	};

}