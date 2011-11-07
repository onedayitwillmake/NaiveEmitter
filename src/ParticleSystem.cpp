/*
 * ParticleSystem.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: onedayitwillmake
 */

#include "ParticleSystem.h"
#include "cinder/Rand.h"

namespace particle {

ParticleSystem::ParticleSystem() {
	_debugColor = ci::Rand::randFloat();
}

ParticleSystem::~ParticleSystem() {
	// TODO Auto-generated destructor stub
}

void ParticleSystem::add( ci::Vec2f pos, ci::Vec2f velocity, ci::ColorA color, ci::Rectf srcCoords, ci::Rectf destRect ) {
	Particle p = { verts.size(), velocity*-1, pos, pos, ci::Rand::randFloat(5, 120) };
	particles.push_back( p );

	float startZ = -1000;
	// Vertices
		verts.push_back( destRect.getX1() ); verts.push_back( destRect.getY2() ); verts.push_back(startZ);
		verts.push_back( destRect.getX2() ); verts.push_back( destRect.getY2() ); verts.push_back(startZ);
		verts.push_back( destRect.getX2() ); verts.push_back( destRect.getY1() ); verts.push_back(startZ);
		verts.push_back( destRect.getX1() ); verts.push_back( destRect.getY2() ); verts.push_back(startZ);
		verts.push_back( destRect.getX2() ); verts.push_back( destRect.getY1() ); verts.push_back(startZ);
		verts.push_back( destRect.getX1() ); verts.push_back( destRect.getY1() ); verts.push_back(startZ);

	// Texture coords
	texCoords.push_back( srcCoords.getX1() ); texCoords.push_back( srcCoords.getY2() );
	texCoords.push_back( srcCoords.getX2() ); texCoords.push_back( srcCoords.getY2() );
	texCoords.push_back( srcCoords.getX2() ); texCoords.push_back( srcCoords.getY1() );
	texCoords.push_back( srcCoords.getX1() ); texCoords.push_back( srcCoords.getY2() );
	texCoords.push_back( srcCoords.getX2() ); texCoords.push_back( srcCoords.getY1() );
	texCoords.push_back( srcCoords.getX1() ); texCoords.push_back( srcCoords.getY1() );

	// Colors
//	ci::ColorA color = ci::ColorA(ci::CM_HSV, _debugColor, 1.0, 0.4, 1.0);
	colors.push_back( color ); colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color ); colors.push_back( color );
	colors.push_back( color ); colors.push_back( color ); colors.push_back( color );
}
void ParticleSystem::update() {

//	float zspeed = 25;
	for( std::vector<Particle>::iterator itr = particles.begin(); itr != particles.end(); ++itr ) {

		for(size_t x = 0; x < 18; x += 3)
			verts[ itr->index+x ] -= itr->speed.x;
		for(size_t y = 1; y < 18; y += 3)
			verts[ itr->index+y ] -= itr->speed.y;

		for(size_t z = 2; z < 18; z += 3)
			verts[ itr->index+z ] += itr->zspeed;

		itr->speed *= 0.998f;
	}
}

void ParticleSystem::draw() {

}
void ParticleSystem::clear() {
	verts.clear();
	texCoords.clear();
	particles.clear();
	colors.clear();
}

} /* namespace particle */
