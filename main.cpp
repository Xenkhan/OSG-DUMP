#include "Components\Dependencies.hpp"
#include "Components\Application\Window.hpp"

const double minFrameTime = 1.0 / 60.0;

using namespace osg;


class UpdateBase : public osg::NodeCallback {
public:
	UpdateBase() {
	
	}
private:
	virtual void operator()(osg::Node *node, osg::NodeVisitor *nodevisitor) {
		const double dt = nodevisitor->getFrameStamp()->getSimulationTime();
		osgSim::DOFTransform * pat=  dynamic_cast<osgSim::DOFTransform*>(node);
	//	pat->setCurrentHPR(osg::Vec3(0, osg::DegreesToRadians(10.0f * dt), 0));
	//	pat->updateCurrentHPR(osg::Vec3(osg::DegreesToRadians(40.0f * dt),0, 0));
		Vec3 pos = pat->getCurrentTranslate();
		pat->setCurrentTranslate(osg::Vec3(0.5,-0.5,0.5));
		pat->setCurrentHPR(osg::Vec3(osg::DegreesToRadians(40 * dt), 0, 0));
		pat->setCurrentTranslate(pos);

	//	pat->setCurrentTranslate(osg::Vec3(10, 0, 0));
		//pat->setPosition(pat->getPosition() + osg::Vec3d(0.1 * dt, 0, 0));
	//	pat->set
	//	pat->setAttitude(pat->getAttitude() + osg::Quat(100.0, osg::Vec3f(1, 0, 0)));

		traverse(node, nodevisitor);
	
	}

};







Group * startupScene()
{


	Vec3 myvec[] = {
		{ -0.5,  0.5,  0.5 },//Front
		{  0.5,  0.5,  0.5 },
		{  0.5, -0.5,  0.5 },
		{ -0.5, -0.5,  0.5 },

		{ 0.5,  0.5,  0.5  },//Right
		{ 0.5,  0.5,  -0.5 },
		{ 0.5, -0.5,  -0.5 },
		{ 0.5, -0.5,  0.5  },


		{ 0.5,   0.5,  -0.5 },//Back
		{ -0.5,  0.5,  -0.5 },
		{ -0.5, -0.5,  -0.5 },
		{ 0.5,  -0.5,  -0.5 },

		{ -0.5,  0.5,  -0.5 },//Right
		{ -0.5,  0.5,  0.5  },
		{ -0.5, -0.5,  0.5  },
		{ -0.5, -0.5,  -0.5 },

		{ -0.5,  0.5, -0.5	},//Top
		{  0.5,  0.5, -0.5	},
		{  0.5,  0.5,  0.5	},
		{ -0.5,  0.5,  0.5	},//MARK

		{ -0.5, -0.5, 0.5	},
		{  0.5, -0.5, 0.5   },
		{  0.5, -0.5, -0.5 },
		{ -0.5, -0.5, -0.5 },

	};

	Vec3 normals[] = {
		Vec3(0,0, -1), //front
		Vec3(0,0,-1),
		Vec3(0,0,-1),
		Vec3(0,0,-1),

		Vec3(+1, 0, 0), //right
		Vec3(+1, 0, 0),
		Vec3(+1, 0, 0),
		Vec3(+1, 0, 0),

		Vec3(0,0, 1), //back
		Vec3(0,0,1),
		Vec3(0,0,1),
		Vec3(0,0,1),

		Vec3(-1, 0, 0), //left
		Vec3(-1, 0, 0),
		Vec3(-1, 0, 0),
		Vec3(-1, 0, 0),

		Vec3(0, 1, 0), //top
		Vec3(0, 1, 0),
		Vec3(0, 1, 0),
		Vec3(0, 1, 0),

		Vec3(0, -1, 0), //bottom
		Vec3(0, -1, 0),
		Vec3(0, -1, 0),
		Vec3(0, -1, 0),

	};
	Vec2 texcoords[] = {
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),
		Vec2(0,0),

		Vec2(0, 0),
		Vec2(1, 0),
		Vec2(1, 1),
		Vec2(0, 1),

		Vec2(0, 1),
		Vec2(1, 1),
		Vec2(1, 0),
		Vec2(0, 0),
	};


	uint8_t indices[] = {
		2,1,0,		3,2,0,
		6,5,4,		7,6,4,
		10,9,8,		11,10,8, //
		14,13,12,	15,14,12,
		18,17,16,	19,18,16,//
		22,21,20,	23,22,20



	};
	

	Vec3Array *vertexArray = new Vec3Array(sizeof(myvec) / sizeof(Vec3), myvec);
	Vec3Array *normalsArray = new Vec3Array(sizeof(normals) / sizeof(Vec3), normals);

	DrawElementsUByte *indexArray = new DrawElementsUByte(PrimitiveSet::TRIANGLES, sizeof(indices) / sizeof(uint8_t), indices);

	Vec2Array *texcoordArray = new Vec2Array(sizeof(texcoords) / sizeof(Vec2), texcoords);


	// vertex color array
	Vec4Array *colorArray = new Vec4Array();
	colorArray->push_back(Vec4(0.65f, 0.0f, 0.0f, 1.0f)); //index 0 red
	
	
														 // color index

	Geometry *geometry = new Geometry();
	geometry->setVertexArray(vertexArray);
	geometry->setNormalArray(normalsArray, osg::Array::BIND_PER_VERTEX);
	geometry->addPrimitiveSet(indexArray);
	geometry->setColorArray(colorArray, osg::Array::Binding::BIND_OVERALL);
	//geometry->setTexCoordArray(0, texcoordArray);
	
	geometry->setVertexAttribArray(0, vertexArray, osg::Array::BIND_PER_VERTEX);
	geometry->setVertexAttribArray(1, texcoordArray, osg::Array::BIND_PER_VERTEX);

	Geode *pyramidObject = new Geode();
	pyramidObject->addDrawable(geometry);

	pyramidObject->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	pyramidObject->getOrCreateStateSet()->setMode(GL_CULL_FACE, osg::StateAttribute::ON);
	
	Group *root = new Group();


	osgFX::Outline *outline = new osgFX::Outline();
//	root->addChild(outline);
	outline->setWidth(4);
	outline->setColor(osg::Vec4(0, 0, 1, 1));
	outline->addChild(pyramidObject);
	
	root->addChild(outline);

	{	
	
		
		osg::PositionAttitudeTransform *pto = new osg::PositionAttitudeTransform;
		pto->addChild(pyramidObject);
		pto->setPosition(osg::Vec3d(5, 0, 0));
		
		root->addChild(pto);
		
		osg::ref_ptr<osg::Program> program = new osg::Program;

		program->addShader(osgDB::readShaderFile("brick.vert"));
		program->addShader(osgDB::readShaderFile("brick.frag"));

		osg::StateSet *stateset = pto->getOrCreateStateSet();
		stateset->setAttributeAndModes(program.get());
	
		



		{	osg::Image *img = osgDB::readImageFile("textures/studTop.jpg");
		osg::Texture2D *tex = new osg::Texture2D(img);

		tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
		tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

		stateset->setTextureAttribute(0, tex);

		stateset->addUniform(new osg::Uniform("studTop", 0)); }

		{	osg::Image *img = osgDB::readImageFile("textures/studBottom.jpg");
		osg::Texture2D *tex = new osg::Texture2D(img);

		tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
		tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

		stateset->setTextureAttribute(1, tex);

		stateset->addUniform(new osg::Uniform("studBottom", 1)); }



		//geometry->getColorArray()[0];
	}

	//pto->setCurrentTranslate(osg::Vec3f(100.0, 0.0f, 0.0f));
	//pto->addChild(outline);

	//pto->setUpdateCallback(new UpdateBase);


	
	
	//return pto;
	return root;
}


#undef main
int main() {
	blox::Window window;
	window.createWindow();
	osg::Group *scene = startupScene();
	window.setScene(scene);

	while (!window.isClosing()) {
		osg::Timer_t startFrameTick = osg::Timer::instance()->tick();
		window.doFrame();

		osg::Timer_t endFrameTick = osg::Timer::instance()->tick();
		double frameTime = osg::Timer::instance()->delta_s(startFrameTick, endFrameTick);

		if (frameTime < minFrameTime) 
			OpenThreads::Thread::microSleep(static_cast<unsigned int>(1000000.0*(minFrameTime - frameTime)));
	}
}

