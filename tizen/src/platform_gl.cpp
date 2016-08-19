#include "platform_gl.h"

ELEMENTARY_GLVIEW_GLOBAL_DEFINE()

GLenum glGetError() {
    return __evas_gl_glapi->glGetError();
}

const GLubyte* glGetString(GLenum name) {
    return __evas_gl_glapi->glGetString(name);
}

void glClear(GLbitfield mask) {
    __evas_gl_glapi->glClear(mask);
}
void glLineWidth(GLfloat width) {
    __evas_gl_glapi->glLineWidth(width);
}
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    __evas_gl_glapi->glViewport(x, y, width, height);
}

void glEnable(GLenum id) {
    __evas_gl_glapi->glEnable(id);
}
void glDisable(GLenum id) {
    __evas_gl_glapi->glDisable(id);
}
void glDepthFunc(GLenum func) {
    __evas_gl_glapi->glDepthFunc(func);
}
void glDepthMask(GLboolean flag) {
    __evas_gl_glapi->glDepthMask(flag);
}
void glDepthRangef(GLfloat n, GLfloat f) {
    __evas_gl_glapi->glDepthRangef(n, f);
}
void glClearDepthf(GLfloat d) {
    __evas_gl_glapi->glClearDepthf(d);
}
void glBlendFunc(GLenum sfactor, GLenum dfactor) {
    __evas_gl_glapi->glBlendFunc(sfactor, dfactor);
}
void glStencilFunc(GLenum func, GLint ref, GLuint mask) {
    __evas_gl_glapi->glStencilFunc(func, ref, mask);
}
void glStencilMask(GLuint mask) {
    __evas_gl_glapi->glStencilMask(mask);
}
void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    __evas_gl_glapi->glStencilOp(fail, zfail, zpass);
}
void glClearStencil(GLint s) {
    __evas_gl_glapi->glClearStencil(s);
}
void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    __evas_gl_glapi->glColorMask(red, green, blue, alpha);
}
void glCullFace(GLenum mode) {
    __evas_gl_glapi->glCullFace(mode);
}
void glFrontFace(GLenum mode) {
    __evas_gl_glapi->glFrontFace(mode);
}
void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
    __evas_gl_glapi->glClearColor(red, green, blue, alpha);
}
void glGetIntegerv(GLenum pname, GLint *params ) {
    __evas_gl_glapi->glGetIntegerv(pname, params );
}

// Program
void glUseProgram(GLuint program) {
    __evas_gl_glapi->glUseProgram(program);
}
void glDeleteProgram(GLuint program) {
    __evas_gl_glapi->glDeleteProgram(program);
}
void glDeleteShader(GLuint shader) {
    __evas_gl_glapi->glDeleteShader(shader);
}
GLuint glCreateShader(GLenum type) {
    return __evas_gl_glapi->glCreateShader(type);
}
GLuint glCreateProgram() {
    return __evas_gl_glapi->glCreateProgram();
}

void glCompileShader(GLuint shader) {
    __evas_gl_glapi->glCompileShader(shader);
}
void glAttachShader(GLuint program, GLuint shader) {
    __evas_gl_glapi->glAttachShader(program,shader);
}
void glLinkProgram(GLuint program) {
    __evas_gl_glapi->glLinkProgram(program);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length) {
	auto source = const_cast<const GLchar**>(string);
    __evas_gl_glapi->glShaderSource(shader, count, source, length);
}
void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    __evas_gl_glapi->glGetShaderInfoLog(shader, bufSize, length, infoLog);
}
void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    __evas_gl_glapi->glGetProgramInfoLog(program, bufSize, length, infoLog);
}
GLint glGetUniformLocation(GLuint program, const GLchar *name) {
    return __evas_gl_glapi->glGetUniformLocation(program, name);
}
GLint glGetAttribLocation(GLuint program, const GLchar *name) {
    return __evas_gl_glapi->glGetAttribLocation(program, name);
}
void glGetProgramiv(GLuint program, GLenum pname, GLint *params) {
    __evas_gl_glapi->glGetProgramiv(program,pname,params);
}
void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) {
    __evas_gl_glapi->glGetShaderiv(shader,pname, params);
}

// Buffers
void glBindBuffer(GLenum target, GLuint buffer) {
    __evas_gl_glapi->glBindBuffer(target, buffer);
}
void glDeleteBuffers(GLsizei n, const GLuint *buffers) {
    __evas_gl_glapi->glDeleteBuffers(n, buffers);
}
void glGenBuffers(GLsizei n, GLuint *buffers) {
    __evas_gl_glapi->glGenBuffers(n, buffers);
}
void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
    __evas_gl_glapi->glBufferData(target, size, data, usage);
}
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data) {
    __evas_gl_glapi->glBufferSubData(target, offset, size, data);
}
void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                    GLenum format, GLenum type, GLvoid* pixels) {
    __evas_gl_glapi->glReadPixels(x, y, width, height, format, type, pixels);
}

// Texture
void glBindTexture(GLenum target, GLuint texture ) {
    __evas_gl_glapi->glBindTexture(target, texture );
}
void glActiveTexture(GLenum texture) {
    __evas_gl_glapi->glActiveTexture(texture);
}
void glGenTextures(GLsizei n, GLuint *textures ) {
    __evas_gl_glapi->glGenTextures(n, textures );
}
void glDeleteTextures(GLsizei n, const GLuint *textures) {
    __evas_gl_glapi->glDeleteTextures(n, textures);
}
void glTexParameteri(GLenum target, GLenum pname, GLint param ) {
    __evas_gl_glapi->glTexParameteri(target, pname, param );
}
void glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                    GLint border, GLenum format, GLenum type, const GLvoid *pixels) {
    __evas_gl_glapi->glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels); }

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
                       GLenum format, GLenum type, const GLvoid *pixels) {
    __evas_gl_glapi->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); }

void glGenerateMipmap(GLenum target) {
    __evas_gl_glapi->glGenerateMipmap(target);
}

void glEnableVertexAttribArray(GLuint index) {
    __evas_gl_glapi->glEnableVertexAttribArray(index);
}
void glDisableVertexAttribArray(GLuint index) {
    __evas_gl_glapi->glDisableVertexAttribArray(index);
}
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                             GLsizei stride, const void *pointer) {
    __evas_gl_glapi->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count ) {
    __evas_gl_glapi->glDrawArrays(mode, first, count );
}
void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices ) {
    __evas_gl_glapi->glDrawElements(mode, count, type, indices );
}

void glUniform1f(GLint location, GLfloat v0) {
    __evas_gl_glapi->glUniform1f(location, v0);
}
void glUniform2f(GLint location, GLfloat v0, GLfloat v1) {
    __evas_gl_glapi->glUniform2f(location, v0, v1);
}
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    __evas_gl_glapi->glUniform3f(location, v0, v1, v2);
}
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    __evas_gl_glapi->glUniform4f(location, v0, v1, v2, v3);
}

void glUniform1i(GLint location, GLint v0) {
    __evas_gl_glapi->glUniform1i(location, v0);
}
void glUniform2i(GLint location, GLint v0, GLint v1) {
    __evas_gl_glapi->glUniform2i(location, v0, v1);
}
void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    __evas_gl_glapi->glUniform3i(location, v0, v1, v2);
}
void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    __evas_gl_glapi->glUniform4i(location, v0, v1, v2, v3);
}

void glUniform1fv(GLint location, GLsizei count, const GLfloat *value) {
    __evas_gl_glapi->glUniform1fv(location, count, value);
}
void glUniform2fv(GLint location, GLsizei count, const GLfloat *value) {
    __evas_gl_glapi->glUniform2fv(location, count, value);
}
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value) {
    __evas_gl_glapi->glUniform3fv(location, count, value);
}
void glUniform4fv(GLint location, GLsizei count, const GLfloat *value) {
    __evas_gl_glapi->glUniform4fv(location, count, value);
}
void glUniform1iv(GLint location, GLsizei count, const GLint *value) {
    __evas_gl_glapi->glUniform1iv(location, count, value);
}
void glUniform2iv(GLint location, GLsizei count, const GLint *value) {
    __evas_gl_glapi->glUniform2iv(location, count, value);
}
void glUniform3iv(GLint location, GLsizei count, const GLint *value) {
    __evas_gl_glapi->glUniform3iv(location, count, value);
}
void glUniform4iv(GLint location, GLsizei count, const GLint *value) {
    __evas_gl_glapi->glUniform4iv(location, count, value);
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    __evas_gl_glapi->glUniformMatrix2fv(location, count, transpose, value);
}
void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    __evas_gl_glapi->glUniformMatrix3fv(location, count, transpose, value);
}
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    __evas_gl_glapi->glUniformMatrix4fv(location, count, transpose, value);
}

// mapbuffer
void* glMapBuffer(GLenum target, GLenum access) {
    return __evas_gl_glapi->glMapBufferOES(target, access);
}
GLboolean glUnmapBuffer(GLenum target) {
    return __evas_gl_glapi->glUnmapBufferOES(target);
}

void glFinish(void) {
    __evas_gl_glapi->glFinish();
}

// VAO
void glBindVertexArray(GLuint array) {
    __evas_gl_glapi->glBindVertexArrayOES(array);
}
void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) {
    __evas_gl_glapi->glDeleteVertexArraysOES(n, arrays);
}
void glGenVertexArrays(GLsizei n, GLuint *arrays) {
    __evas_gl_glapi->glGenVertexArraysOES(n, arrays);
}

