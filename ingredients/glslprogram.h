#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include "cookbookogl.h"

#include <string>
using std::string;

#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

#include <exception>

class GLSLProgramException : public std::exception {
public:
	GLSLProgramException( const string & msg, const string & logStr = "") :
		exception(), message(msg), log( logStr ) { }
	
	~GLSLProgramException() throw() { }
		
	string getLog() { return log; }
	
	const char * what() const throw() {
		return message.c_str();
	}
	
	
	
private:
	string message;
	string log;
};

namespace GLSLShader {
    enum GLSLShaderType {
        VERTEX, FRAGMENT, GEOMETRY,
        TESS_CONTROL, TESS_EVALUATION
    };
};

class GLSLProgram
{
private:
    int  handle;
    bool linked;

    int  getUniformLocation(const char * name );
    bool fileExists( const string & fileName );

public:
    GLSLProgram();

    void   compileShader( const char * fileName, GLSLShader::GLSLShaderType type ) throw (GLSLProgramException);
    void   compileShader( const string & source, GLSLShader::GLSLShaderType type, 
                          const char *fileName = NULL ) throw (GLSLProgramException);
    void   link() throw (GLSLProgramException);
    void   validate() throw(GLSLProgramException);
    void   use() throw (GLSLProgramException);

    int    getHandle();
    bool   isLinked();

    void   bindAttribLocation( GLuint location, const char * name);
    void   bindFragDataLocation( GLuint location, const char * name );

    void   setUniform( const char *name, float x, float y, float z);
    void   setUniform( const char *name, const vec2 & v);
    void   setUniform( const char *name, const vec3 & v);
    void   setUniform( const char *name, const vec4 & v);
    void   setUniform( const char *name, const mat4 & m);
    void   setUniform( const char *name, const mat3 & m);
    void   setUniform( const char *name, float val );
    void   setUniform( const char *name, int val );
    void   setUniform( const char *name, bool val );

    void   printActiveUniforms();
    void   printActiveAttribs();
};

#endif // GLSLPROGRAM_H
