#pragma once
#include "../Dependencies.hpp"

namespace blox {

	class Base : public osg::Referenced {
	public:
		Base();
		~Base();

	/*	virtual void setParent(Base *base);
		virtual void addChild(Base *base);
		virtual void removeChild(Base *base);
		virtual void removeChild(uint16_t index);
		virtual void removeAllChildren();

		virtual Base *getParent();
		virtual Base *getChild();*/

	protected:
		Base *parent;
		std::vector<Base*> children;


	};

}