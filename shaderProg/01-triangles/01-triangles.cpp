//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>

#include "../include/LoadShaders.h"


#define BUFFER_OFFSET(a) ((void*)(a))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint  NumVertices = 6;

//----------------------------------------------------------------------------
//
// init
//

void
init( void )
{	//返回n个未使用的顶点对象名到数组中
    glGenVertexArrays( NumVAOs, VAOs );
	//创建一个新的顶点数组对象并且与其名称关联起来
    glBindVertexArray( VAOs[Triangles] );

    GLfloat  vertices[NumVertices][2] = {
        { -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
        {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2
    };
	//返回n个当前未使用的缓存对象名称，并保存到数组中
    glGenBuffers( NumBuffers, Buffers );
	//OpenGL有很多种不同类型的缓存对象。绑定缓存时需要指定它所对应的类型
    glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
	//
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

    ShaderInfo  shaders[] =
    {
        { GL_VERTEX_SHADER, "../bin/media/shaders/triangles/triangles.vert" },
        { GL_FRAGMENT_SHADER, "../bin/media/shaders/triangles/triangles.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    glVertexAttribPointer( vPosition, 2, GL_FLOAT,
                           GL_FALSE, 0, BUFFER_OFFSET(0) );
    glEnableVertexAttribArray( vPosition );
}

//----------------------------------------------------------------------------
//
// display
//

void
display( void )
{
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray( VAOs[Triangles] );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
	glFlush();
}

//----------------------------------------------------------------------------
//
// main
//

int
main( int argc, char** argv )
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Triangles");

	if (glewInit()) {
		std::cout << "Unable to initialize GLEW ..." << std::endl;
		exit(EXIT_FAILURE);
	}

    init();
	glutDisplayFunc(display);
	glutMainLoop();
}
