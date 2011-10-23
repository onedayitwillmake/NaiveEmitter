/**
 * EclipseLovesCinder example application
 *
 **********************************************************
 **********************************************************
 ********************* IMPORTANT **************************
 * On first run:
 * 	- Select Project -> Clean...
 *
 *  - If change the project name, you have to tell the debugger where the new one is:
 *  	Go into Run -> Debug Configurations
 *  	Set where the application lives to something like this
 *  	Debug/{APPNAME}/Contents/MacOS/{APPNAME}
 *
 **********************************************************
 **********************************************************
 *
 * This project is released under public domain, do whatever with it.
 *
 *
 * Mario Gonzalez
 * http://onedayitwillmake
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Rand.h"
#include "Resources.h"
#include <sstream>
#include <vector>
#include <gl.h>

#include "ParticleSystem.h"

class HelloWorldApp : public ci::app::AppBasic {
public:
	void setup();
	void prepareSettings( ci::app::AppBasic::Settings *settings );
	void mouseDown( ci::app::MouseEvent event );
	void update();
	void draw();
	void shutdown();

	ci::gl::Texture texture;
	particle::ParticleSystem emitter;
};

void HelloWorldApp::prepareSettings( ci::app::AppBasic::Settings *settings ) {
	settings->setWindowSize( 800, 600 );
}

void HelloWorldApp::setup() {
	// Test loading a texture
	ci::gl::Texture::Format format;
	format.enableMipmapping( false );
	format.setMinFilter( GL_NEAREST );
	format.setMagFilter( GL_NEAREST );
	texture = ci::gl::Texture( ci::loadImage( loadResource( RES_WHEEL ) ), format );
}

void HelloWorldApp::mouseDown( ci::app::MouseEvent event ) {

}

void HelloWorldApp::update() {
	emitter.update();
}

void HelloWorldApp::draw() {
	// clear out the window with black
	ci::Color aColor = ci::Color( 0, 0, 0 );
	ci::gl::clear( ci::Color( 0, 0, 0 ) );

	ci::gl::enableAdditiveBlending();
	if ( texture ) {
		ci::gl::color( ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f) );

		texture.enableAndBind();
			const float scale = ci::Rand::randFloat(0.1, 1.5);
			const float halfWidth = texture.getCleanWidth() / 2.0f * scale;
			const float halfHeight = texture.getCleanHeight() / 2.0f * scale;

			ci::Vec2f pos = getMousePos();
			const ci::Area srcArea = ci::Area( texture.getCleanBounds() );
			ci::Rectf destRect = ci::Rectf( pos.x-halfWidth, pos.y-halfHeight, pos.x + halfWidth, pos.y + halfHeight);
			const ci::Rectf srcCoords = texture.getAreaTexCoords( srcArea );



			emitter.add( pos, ci::Rand::randVec2f() * 1.5, srcCoords, destRect );

		glEnableClientState( GL_VERTEX_ARRAY );
		glVertexPointer( 2, GL_FLOAT, 0, &(emitter.verts)[0] );

		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glTexCoordPointer( 2, GL_FLOAT, 0, &(emitter.texCoords)[0] );

		glEnableClientState( GL_COLOR_ARRAY );
		glColorPointer( 4, GL_FLOAT, 0, &(emitter.colors)[0].r );

		glDrawArrays( GL_TRIANGLES, 0, emitter.verts.size() / 2 );

		texture.disable();

		ci::gl::enableAlphaBlending();
		ci::gl::color( ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f) );

		static ci::Font font = ci::Font( "monaco", 10.0f );
		std::stringstream particleCountSS;
		particleCountSS << emitter.particles.size() << std::endl;
		ci::gl::drawString( particleCountSS.str(), ci::Vec2i(5, 5), ci::ColorA(1,1,1,1), font );
	}
}


void HelloWorldApp::shutdown() {
	std::cout << "Shutdown..." << std::endl;
	AppBasic::shutdown();
}
CINDER_APP_BASIC( HelloWorldApp, ci::app::RendererGl )
