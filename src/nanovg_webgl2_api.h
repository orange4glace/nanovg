#ifndef NANOVG_WEBGL2_API_H_
#define NANOVG_WEBGL2_API_H_

#include <node_api.h>
#include <cstring>

#include "nanovg_webgl2_spec.h"

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

typedef char GLchar;

typedef napi_ref GLBuffer;
typedef napi_ref GLTexture;
typedef napi_ref GLShader;
typedef napi_ref GLProgram;
typedef napi_ref GLUniformLocation;
typedef napi_ref GLVertexArrayObject;

#define EXPAND( x ) x

#define PP_NARG(...) \
         EXPAND( PP_NARG_(__VA_ARGS__,PP_RSEQ_N()) )
#define PP_NARG_(...) \
         EXPAND( PP_ARG_N(__VA_ARGS__) )
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define __call_webgl_function(FUNC, ...) \
  napi_value argv[PP_NARG(__VA_ARGS__)] = { __VA_ARGS__ }; \
  napi_value __call_result = ____call_webgl_function(FUNC, PP_NARG(__VA_ARGS__), argv);

#define __call_webgl_function_no_args(FUNC) \
  napi_value __call_result = ____call_webgl_function(FUNC, 0, 0)

static napi_env __napi_env;
static napi_ref __webgl_context;





void setNAPIenv(napi_env env) {
  __napi_env = env;
}

void __log(napi_value v) {
  napi_value global;
  napi_value console;
  napi_value log;
  napi_get_global(__napi_env, &global);
  napi_get_named_property(__napi_env, global, "console", &console);
  napi_get_named_property(__napi_env, console, "log", &log);
  napi_value ret;
  napi_call_function(__napi_env, console, log, 1, &v, &ret);
}

inline static napi_value __napi_get_ref(napi_ref ref) {
  napi_value value;
  napi_get_reference_value(__napi_env, ref, &value);
  return value;
}

inline static napi_ref __napi_create_ref(napi_value value) {
  napi_ref ref;
  napi_create_reference(__napi_env, value, 1, &ref);
  return ref;
}

inline napi_value __napi_glenum(GLenum v) {
  napi_value res;
  napi_create_uint32(__napi_env, v, &res);
  return res;
}

inline napi_value __napi_glint(GLint v) {
  napi_value res;
  napi_create_int32(__napi_env, v, &res);
  return res;
}

inline napi_value __napi_gluint(GLuint v) {
  napi_value res;
  napi_create_uint32(__napi_env, v, &res);
  return res;
}

inline napi_value __napi_glintptr(GLintptr v) {
  napi_value res;
  napi_create_int32(__napi_env, v, &res);
  return res;
}

inline napi_value __napi_glsizeiptr(GLsizeiptr v) {
  napi_value res;
  napi_create_int32(__napi_env, v, &res);
  return res;
}

inline napi_value __napi_glsizei(GLsizei v) {
  napi_value res;
  napi_create_int32(__napi_env, v, &res);
  return res;
}

inline napi_value __napi_glboolean(GLboolean v) {
  napi_value res;
  napi_create_int32(__napi_env, v, &res);
  return res;
}




napi_value ____call_webgl_function(napi_ref func, int argc, napi_value* argv) {
  napi_value result;
  napi_call_function(
      __napi_env,
      __napi_get_ref(__webgl_context),
      __napi_get_ref(func),
      argc,
      argv,
      &result);
  return result;
}








void glActiveTexture(GLenum texture) {
  __call_webgl_function(WEBGL_activeTexture, 
      __napi_glenum(texture)
  );
}

void glAttachShader(GLProgram program, GLShader shader) {
  __call_webgl_function(WEBGL_attachShader,
      __napi_get_ref(program),
      __napi_get_ref(shader)
  );
}

// beginQuery
// beginTransformFeedback

void glBindAttribLocation(GLProgram program, GLuint index, const char* name) {
  napi_value nname;
  napi_create_string_utf8(__napi_env, name, NAPI_AUTO_LENGTH, &nname);
  __call_webgl_function(WEBGL_bindAttribLocation,
      __napi_get_ref(program),
      __napi_gluint(index),
      nname
  );
}

void glBindBuffer(GLenum target, napi_ref buffer) {
  __call_webgl_function(WEBGL_bindBuffer,
      __napi_glenum(target),
      __napi_get_ref(buffer)
  );
}

void glBindBuffer0(GLenum target) {
  napi_value nullv;
  napi_get_null(__napi_env, &nullv);
  __call_webgl_function(WEBGL_bindBuffer,
      __napi_glenum(target),
      nullv
  );
}

// bindBufferBase

void glBindBufferRange(GLenum target, GLuint index, napi_ref buffer,
    GLintptr offset, GLsizeiptr size) {
  __call_webgl_function(WEBGL_bindBufferRange,
      __napi_glenum(target),
      __napi_gluint(index),
      __napi_get_ref(buffer),
      __napi_glintptr(offset),
      __napi_glsizeiptr(size)
  );
}

// bindFramebuffer
// bindRenderbuffer
// bindSampler

void glBindTexture(GLenum target, GLTexture texture) {
  __call_webgl_function(WEBGL_bindTexture,
      __napi_glenum(target),
      __napi_get_ref(texture)
  );
}

void glBindTexture0(GLenum target) {
  napi_value nullv;
  napi_get_null(__napi_env, &nullv);
  __call_webgl_function(WEBGL_bindTexture,
      __napi_glenum(target),
      nullv
  );
}

// bindTransformFeedback

void glBindVertexArray(napi_ref vertex_array) {
  __call_webgl_function(WEBGL_bindVertexArray,
      __napi_get_ref(vertex_array)
  );
}

void glBindVertexArray0() {
  napi_value nullv;
  napi_get_null(__napi_env, &nullv);
  __call_webgl_function(WEBGL_bindVertexArray,
      nullv
  );
}

// blendColor
// blendEquation
// blendEquationSeparate

void glBlendFunc(GLenum sfactor, GLenum dfactor) {
  __call_webgl_function(WEBGL_blendFunc,
      __napi_glenum(sfactor),
      __napi_glenum(dfactor)
  );
}

void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB,
    GLenum srcAlpha, GLenum dstAlpha) {
  __call_webgl_function(WEBGL_blendFuncSeparate,
      __napi_glenum(srcRGB),
      __napi_glenum(dstRGB),
      __napi_glenum(srcAlpha),
      __napi_glenum(dstAlpha)
  );
}
// blitFramebuffer

void glBufferData(GLenum target, GLsizeiptr size, GLvoid* data, GLenum usage) {
  napi_value buf;
  napi_create_external_arraybuffer(__napi_env, data, size, 0, 0, &buf);
  __call_webgl_function(WEBGL_bufferData,
      __napi_glenum(target),
      buf,
      __napi_glenum(usage)
  );
}

// bufferSubData
// canvas
// checkFramebufferStatus
// clear
// clearBufferfi
// clearBufferfv
// clearBufferiv
// clearBufferuiv
// clearColor
// clearDepth
// clearStencil
// clientWaitSync

void glColorMask(GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
  __call_webgl_function(WEBGL_colorMask,
      __napi_glboolean(r),
      __napi_glboolean(g),
      __napi_glboolean(b),
      __napi_glboolean(a)
  );
}

void glCompileShader(GLShader shader) {
  __call_webgl_function(WEBGL_compileShader,
      __napi_get_ref(shader)
  );
}

// compressedTexImage2D
// compressedTexImage3D
// compressedTexSubImage2D
// compressedTexSubImage3D
// copyBufferSubData
// copyTexImage2D
// copyTexSubImage2D
// copyTexSubImage3D

GLBuffer glCreateBuffer() {
  __call_webgl_function_no_args(WEBGL_createBuffer);
  return __napi_create_ref(__call_result);
}

// createFramebuffer

GLProgram glCreateProgram() {
  __call_webgl_function_no_args(WEBGL_createProgram);
  return __napi_create_ref(__call_result);
}

// createQuery
// createRenderbuffer
// createSampler

napi_ref glCreateShader(GLenum type) {
  __call_webgl_function(WEBGL_createShader, __napi_glenum(type));
  return __napi_create_ref(__call_result);
}

napi_ref glCreateTexture() {
  __call_webgl_function_no_args(WEBGL_createTexture);
  return __napi_create_ref(__call_result);
}

// createTransformFeedback

GLVertexArrayObject glCreateVertexArray() {
  __call_webgl_function_no_args(WEBGL_createVertexArray);
  return __napi_create_ref(__call_result);
}

void glCullFace(GLenum mode) {
  __call_webgl_function(WEBGL_cullFace, __napi_glenum(mode));
}

void glDeleteBuffer(GLBuffer buffer) {
  __call_webgl_function(WEBGL_deleteBuffer,
      __napi_get_ref(buffer));
}

// deleteFramebuffer

void glDeleteProgram(GLProgram program) {
  __call_webgl_function(WEBGL_deleteProgram,
      __napi_get_ref(program));
}

// deleteQuery
// deleteRenderbuffer
// deleteSampler

void glDeleteShader(GLShader shader) {
  __call_webgl_function(WEBGL_deleteShader,
      __napi_get_ref(shader));
}

// deleteSync

void glDeleteTexture(GLTexture texture) {
  __call_webgl_function(WEBGL_deleteTexture,
      __napi_get_ref(texture));
}

// deleteTransformFeedback

void glDeleteVertexArray(GLVertexArrayObject vertexArray) {
  __call_webgl_function(WEBGL_deleteTexture,
      __napi_get_ref(vertexArray));
}

// depthFunc
// depthMask
// depthRange
// detachShader

void glDisable(GLenum cap) {
  __call_webgl_function(WEBGL_disable,
      __napi_glenum(cap));
}

void glDisableVertexAttribArray(GLuint index) {
  __call_webgl_function(WEBGL_disableVertexAttribArray,
      __napi_gluint(index)
  );
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count) {
  __call_webgl_function(WEBGL_drawArrays,
      __napi_glenum(mode),
      __napi_gluint(first),
      __napi_glsizei(count));
}

// drawArraysInstanced
// drawBuffers
// drawElements
// drawElementsInstanced
// drawRangeElements
// drawingBufferHeight
// drawingBufferWidth

void glEnable(GLenum cap) {
  __call_webgl_function(WEBGL_enable,
      __napi_glenum(cap));
}

void glEnableVertexAttribArray(GLuint index) {
  __call_webgl_function(WEBGL_enableVertexAttribArray,
      __napi_gluint(index));
}

// endQuery
// endTransformFeedback
// fenceSync

void glFinish() {
  __call_webgl_function_no_args(WEBGL_finish);
}

// flush
// framebufferRenderbuffer
// framebufferTexture2D
// framebufferTextureLayer

void glFrontFace(GLenum mode) {
  __call_webgl_function(WEBGL_frontFace,
      __napi_glenum(mode)
  );
}

void glGenerateMipmap(GLenum target) {
  __call_webgl_function(WEBGL_generateMipmap,
      __napi_glenum(target)
  );
}

// getActiveAttrib
// getActiveUniform
// getActiveUniformBlockName
// getActiveUniformBlockParameter
// getActiveUniforms
// getAttachedShaders
// getAttribLocation
// getBufferParameter
// getBufferSubData
// getContextAttributes

GLenum glGetError() {
  int32_t result;
  __call_webgl_function_no_args(WEBGL_getError);
  napi_get_value_int32(__napi_env, __call_result, &result);
  return (GLenum)result;
}

// getExtension
// getFragDataLocation
// getFramebufferAttachmentParameter
// getIndexedParameter
// getInternalformatParameter

// getParameter
/* 
 * This goes into glGetXXX
 * https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glGet.xml
 */
GLint glGetIntegerv(GLenum pname) {
  int32_t result;
  __call_webgl_function(WEBGL_getParameter,
      __napi_glenum(pname)
  );
  napi_get_value_int32(__napi_env, __call_result, &result);
  return (GLint)result;
}

napi_value glGetProgramInfoLog(GLProgram shader, GLsizei maxLength,
    GLsizei* length, GLchar* infoLog) {
  __call_webgl_function(WEBGL_getProgramInfoLog,
      __napi_get_ref(shader)
  );
  size_t len;
  napi_get_value_string_utf8(__napi_env, __call_result, infoLog,
      maxLength, &len);
  *length = len;
  return __call_result;
}

GLenum glGetProgramParameter(GLProgram program, GLenum pname) {
  bool result;
  __call_webgl_function(WEBGL_getProgramParameter,
      __napi_get_ref(program),
      __napi_glenum(pname)
  );
  napi_get_value_bool(__napi_env, __call_result, &result);
  return (GLenum)result;
}

// getQuery
// getQueryParameter
// getRenderbufferParameter
// getSamplerParameter

void glGetShaderInfoLog(GLShader shader, GLsizei maxLength,
    GLsizei* length, GLchar* infoLog) {
  __call_webgl_function(WEBGL_getShaderInfoLog,
      __napi_get_ref(shader)
  );
  size_t len;
  napi_get_value_string_utf8(__napi_env, __call_result, infoLog,
      maxLength, &len);
  *length = len;
}

GLenum glGetShaderParameter(GLShader shader, GLenum pname) {
  bool result;
  __call_webgl_function(WEBGL_getShaderParameter,
      __napi_get_ref(shader),
      __napi_glenum(pname)
  );
  napi_get_value_bool(__napi_env, __call_result, &result);
  return (GLenum)result;
}

// getShaderPrecisionFormat

void glShaderSource(GLShader shader, GLsizei count, const GLchar **string, const GLint *unused) {
  char tmp[20000];
  strcpy(tmp, string[0]);
  for (int i = 1; i < count; i ++) 
    strcat(tmp, string[i]);
  napi_value nstring;
  napi_create_string_utf8(__napi_env, tmp, NAPI_AUTO_LENGTH, &nstring);
  __call_webgl_function(WEBGL_shaderSource,
      __napi_get_ref(shader),
      nstring
  );
}

// getSupportedExtensions
// getSyncParameter
// getTexParameter
// getTransformFeedbackVarying
// getUniform
// getUniformBlockIndex

GLuint glGetUniformBlockIndex(GLProgram program, const char* uniformBlockName) {
  napi_value nname;
  napi_create_string_utf8(__napi_env, uniformBlockName, NAPI_AUTO_LENGTH, &nname);
  __call_webgl_function(WEBGL_getUniformBlockIndex,
      __napi_get_ref(program),
      nname
  );
  int32_t result;
  napi_get_value_int32(__napi_env, __call_result, &result);
  return (GLuint)result;
}

// getUniformIndices

GLUniformLocation glGetUniformLocation(GLProgram program, const char* name) {
  napi_value nname;
  napi_create_string_utf8(__napi_env, name, NAPI_AUTO_LENGTH, &nname);
  __call_webgl_function(WEBGL_getUniformLocation,
      __napi_get_ref(program),
      nname
  );
  return __napi_create_ref(__call_result);
}

// getVertexAttrib
// getVertexAttribOffset
// hint
// invalidateFramebuffer
// invalidateSubFramebuffer
// isBuffer
// isContextLost
// isEnabled
// isFramebuffer
// isProgram
// isQuery
// isRenderbuffer
// isSampler
// isShader
// isSync
// isTexture
// isTransformFeedback
// isVertexArray
// lineWidth

void glLinkProgram(napi_ref program) {
  __call_webgl_function(WEBGL_linkProgram,
      __napi_get_ref(program)
  );
}

// pauseTransformFeedback

void glPixelStorei(GLenum pname, GLint param) {
  __call_webgl_function(WEBGL_pixelStorei,
      __napi_glenum(pname),
      __napi_glint(param)
  );
}
// polygonOffset
// readBuffer
// readPixels
// renderbufferStorage
// renderbufferStorageMultisample
// resumeTransformFeedback
// sampleCoverage
// samplerParameterf
// samplerParameteri
// scissor
// shaderSource

void glStencilFunc(GLenum func, GLint ref, GLuint mask) {
  __call_webgl_function(WEBGL_stencilFunc,
      __napi_glenum(func),
      __napi_glint(ref),
      __napi_gluint(mask)
  );
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
  __call_webgl_function(WEBGL_stencilFuncSeparate,
      __napi_glenum(face),
      __napi_glenum(func),
      __napi_glint(ref),
      __napi_gluint(mask)
  );
}

void glStencilMask(GLuint mask) {
  __call_webgl_function(WEBGL_stencilMask,
      __napi_gluint(mask)
  );
}

void glStencilMaskSeparate(GLenum face, GLuint mask) {
  __call_webgl_function(WEBGL_stencilMaskSeparate,
      __napi_glenum(face),
      __napi_gluint(mask)
  );
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
  __call_webgl_function(WEBGL_stencilOp,
      __napi_glenum(fail),
      __napi_glenum(zfail),
      __napi_glenum(zpass)
  );
}

void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass) {
  __call_webgl_function(WEBGL_stencilOpSeparate,
      __napi_glenum(face),
      __napi_glenum(fail),
      __napi_glenum(zfail),
      __napi_glenum(zpass)
  );
}

void glTexImage2D(
    GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLint border,
    GLenum format, GLenum type, GLvoid* data, GLsizei size) {
  napi_value buf;
  if (data == NULL) napi_get_null(__napi_env, &buf);
  else napi_create_external_arraybuffer(__napi_env, data, width * height * size, 0, 0, &buf);
  __call_webgl_function(WEBGL_texImage2D,
      __napi_glenum(target),
      __napi_glint(level),
      __napi_glenum(internalformat),
      __napi_glsizei(width),
      __napi_glsizei(height),
      __napi_glint(border),
      __napi_glenum(format),
      __napi_glenum(type),
      buf
  );
}

// texImage3D
// texParameterf

void glTexParameteri(GLenum target, GLenum pname, GLint param) {
  __call_webgl_function(WEBGL_texParameteri,
      __napi_glenum(target),
      __napi_glenum(pname),
      __napi_glint(param)
  );
}

// texStorage2D
// texStorage3D

void glTexSubImage2D(
    GLenum target, GLint level, GLint xoffset, GLint yoffset, 
    GLsizei width, GLsizei height,
    GLenum format, GLenum type, GLvoid* data, GLsizei size) {
  napi_value buf;
  napi_create_external_arraybuffer(__napi_env, data, width * height * size, 0, 0, &buf);
  __call_webgl_function(WEBGL_texImage2D,
      __napi_glenum(target),
      __napi_glint(level),
      __napi_glint(xoffset),
      __napi_glint(yoffset),
      __napi_glsizei(width),
      __napi_glsizei(height),
      __napi_glenum(format),
      __napi_glenum(type),
      buf
  );
}
// texSubImage3D
// transformFeedbackVaryings
// uniform1f
// uniform1fv
// uniform1i

void glUniform1i(GLUniformLocation location, GLint v0) {
  __call_webgl_function(WEBGL_uniform1i,
      __napi_get_ref(location),
      __napi_glint(v0)
  );
}

// uniform1iv
// uniform1ui
// uniform1uiv
// uniform2f

void glUniform2fv(GLUniformLocation location, GLsizei count, void* value) {
  napi_value buf;
  napi_value tbuf;
  napi_create_external_arraybuffer(__napi_env, value, count * 2 * sizeof(float), 0, 0, &buf);
  napi_create_typedarray(__napi_env, napi_float32_array, count * 2, buf, 0, &tbuf);
  __call_webgl_function(WEBGL_uniform2fv,
      __napi_get_ref(location),
      tbuf
  );
}

// uniform2i
// uniform2iv
// uniform2ui
// uniform2uiv
// uniform3f
// uniform3fv
// uniform3i
// uniform3iv
// uniform3ui
// uniform3uiv
// uniform4f
// uniform4fv
// uniform4i
// uniform4iv
// uniform4ui
// uniform4uiv

void glUniformBlockBinding(GLProgram program, 
    GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
  __call_webgl_function(WEBGL_uniformBlockBinding,
      __napi_get_ref(program),
      __napi_gluint(uniformBlockIndex),
      __napi_gluint(uniformBlockBinding)
  );
}

// uniformMatrix2fv
// uniformMatrix2x3fv
// uniformMatrix2x4fv
// uniformMatrix3fv
// uniformMatrix3x2fv
// uniformMatrix3x4fv
// uniformMatrix4fv
// uniformMatrix4x2fv
// uniformMatrix4x3fv

void glUseProgram(GLProgram program) {
  __call_webgl_function(WEBGL_useProgram,
      __napi_get_ref(program)
  );
}

void glUseProgram0() {
  napi_value nullv;
  napi_get_null(__napi_env, &nullv);
  __call_webgl_function(WEBGL_useProgram,
      nullv
  );
}

// validateProgram
// vertexAttrib1f
// vertexAttrib1fv
// vertexAttrib2f
// vertexAttrib2fv
// vertexAttrib3f
// vertexAttrib3fv
// vertexAttrib4f
// vertexAttrib4fv
// vertexAttribDivisor
// vertexAttribI4i
// vertexAttribI4iv
// vertexAttribI4ui
// vertexAttribI4uiv
// vertexAttribIPointer

void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
      GLboolean normalized, GLsizei stride, GLintptr offset) {
  __call_webgl_function(WEBGL_vertexAttribPointer,
      __napi_gluint(index),
      __napi_glint(size),
      __napi_glenum(type),
      __napi_glboolean(normalized),
      __napi_glsizei(stride),
      __napi_glintptr(offset)
  );
}

// viewport
// waitSync

#undef EXPAND
#undef PP_NARG
#undef PP_NARG_
#undef PP_ARG_N
#undef PP_RSEQ_N

#undef __call_webgl_function
#undef __call_webgl_function_no_args

#endif