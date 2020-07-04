#define GLEW_STATIC
#include <GL/glew.h>

#include "renderer.hh"
#include <iostream>

void renderer::init()
{
	glewExperimental = GL_TRUE;
	glewInit();
}

void renderer::render()
{
}

renderer::~renderer()
{
}

