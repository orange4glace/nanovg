#ifndef NANOVG_WEBGL2_API
#define NANOVG_WEBGL2_API

#include <node_api.h>

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

inline static napi_value __napi_int32(int value) {
  napi_value result;
  napi_create_int32(__napi_env, value, &result);
  return result;
}

inline static napi_value __napi_uint32(unsigned int value) {
  napi_value result;
  napi_create_uint32(__napi_env, value, &result);
  return result;
}

napi_value __gl_init_nanovg(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  size_t argc = 1;
  napi_value nv[1];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  napi_value gl = nv[0];
  __webgl_context = __napi_create_ref(gl);

  return 0;
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

void glActiveTexture(napi_ref texture) {
  __call_webgl_function(WEBGL_activeTexture, 
      __napi_get_ref(texture)
  );
}

void glAttachShader(napi_ref program, napi_ref shader) {
  __call_webgl_function(WEBGL_attachShader,
      __napi_get_ref(program),
      __napi_get_ref(shader)
  );
}

void glBindBuffer(napi_ref target, napi_ref buffer) {
  __call_webgl_function(WEBGL_bindBuffer,
      __napi_get_ref(target),
      __napi_get_ref(buffer)
  );
}

void glBindTexture(napi_ref target, napi_ref texture) {
  __call_webgl_function(WEBGL_bindTexture,
      __napi_get_ref(target),
      __napi_get_ref(texture)
  );
}

void glBindVertexArray(napi_ref vertex_array) {
  __call_webgl_function(WEBGL_bindVertexArray,
      __napi_get_ref(vertex_array)
  );
}

void glBlendFunc(napi_ref sfactor, napi_ref dfactor) {
  __call_webgl_function(WEBGL_blendFunc,
      __napi_get_ref(sfactor),
      __napi_get_ref(dfactor)
  );
}

void glBufferData(napi_ref target, GLsizeiptr size, GLvoid* data, napi_ref usage) {
  napi_value buf;
  napi_create_external_arraybuffer(__napi_env, data, size, 0, 0, &buf);
  __call_webgl_function(WEBGL_bufferData,
      __napi_get_ref(target),
      buf,
      __napi_get_ref(usage)
  );
}

napi_ref glCreateBuffer() {
  __call_webgl_function_no_args(WEBGL_createBuffer);
  return __napi_create_ref(__call_result);
}

napi_ref glCreateProgram() {
  __call_webgl_function_no_args(WEBGL_createProgram);
  return __napi_create_ref(__call_result);
}

napi_ref glCreateShader(napi_ref type) {
  __call_webgl_function(WEBGL_createShader, __napi_get_ref(type));
  return __napi_create_ref(__call_result);
}

napi_ref glCreateTexture() {
  __call_webgl_function_no_args(WEBGL_createTexture);
  return __napi_create_ref(__call_result);
}

void glCullFace(napi_ref mode) {
  __call_webgl_function(WEBGL_cullFace, __napi_get_ref(mode));
}

void glDeleteBuffer(napi_ref buffer) {
  __call_webgl_function(WEBGL_deleteBuffer,
      __napi_get_ref(buffer));
}

void glDeleteProgram(napi_ref program) {
  __call_webgl_function(WEBGL_deleteProgram,
      __napi_get_ref(program));
}

void glDeleteShader(napi_ref shader) {
  __call_webgl_function(WEBGL_deleteShader,
      __napi_get_ref(shader));
}

void glDeleteTexture(napi_ref texture) {
  __call_webgl_function(WEBGL_deleteTexture,
      __napi_get_ref(texture));
}

void glDisable(napi_ref cap) {
  __call_webgl_function(WEBGL_disable,
      __napi_get_ref(cap));
}

void glDrawArrays(napi_ref mode, GLint first, GLsizei count) {
  __call_webgl_function(WEBGL_drawArrays,
      __napi_get_ref(mode),
      __napi_int32(first),
      __napi_int32(count));
}

void glEnable(napi_ref cap) {
  __call_webgl_function(WEBGL_enable,
      __napi_get_ref(cap));
}

void glEnableVertexAttribArray(GLuint index) {
  __call_webgl_function(WEBGL_enableVertexAttribArray,
      __napi_int32(index));
}

void glFrontFace(napi_ref mode) {
  __call_webgl_function(WEBGL_frontFace,
      __napi_get_ref(mode)
  );
}

napi_value glGetError() {
  __call_webgl_function_no_args(WEBGL_getError);
  return __call_result;
}

void glLinkProgram(napi_ref program) {
  __call_webgl_function(WEBGL_linkProgram,
      __napi_get_ref(program)
  );
}

void glStencilFunc(napi_ref func, GLint ref, GLuint mask) {
  __call_webgl_function(WEBGL_stencilFunc,
      __napi_get_ref(func),
      __napi_int32(ref),
      __napi_uint32(mask)
  );
}

void glStencilFuncSeparate(napi_ref face, napi_ref func, GLint ref, GLuint mask) {
  __call_webgl_function(WEBGL_stencilFuncSeparate,
      __napi_get_ref(face),
      __napi_get_ref(func),
      __napi_int32(ref),
      __napi_uint32(mask)
  );
}

void glStencilMask(GLuint mask) {
  __call_webgl_function(WEBGL_stencilMask,
      __napi_uint32(mask)
  );
}

void glStencilMaskSeparate(napi_ref face, GLuint mask) {
  __call_webgl_function(WEBGL_stencilMaskSeparate,
      __napi_get_ref(face),
      __napi_uint32(mask)
  );
}

void glStencilOp(napi_ref fail, napi_ref zfail, napi_ref zpass) {
  __call_webgl_function(WEBGL_stencilOp,
      __napi_get_ref(fail),
      __napi_get_ref(zfail),
      __napi_get_ref(zpass)
  );
}

void glStencilOpSeparate(napi_ref face, napi_ref fail, napi_ref zfail, napi_ref zpass) {
  __call_webgl_function(WEBGL_stencilOpSeparate,
      __napi_get_ref(face),
      __napi_get_ref(fail),
      __napi_get_ref(zfail),
      __napi_get_ref(zpass)
  );
}

void glTexImage2D(
    napi_ref target, GLint level, napi_ref internalformat,
    GLsizei width, GLsizei height, GLint border,
    napi_ref format, napi_ref type, GLvoid* data, GLsizei size) {
  napi_value buf;
  napi_create_external_arraybuffer(__napi_env, data, size, 0, 0, &buf);
  __call_webgl_function(WEBGL_texImage2D,
      __napi_get_ref(target),
      __napi_int32(level),
      __napi_get_ref(internalformat),
      __napi_int32(width),
      __napi_int32(height),
      __napi_int32(border),
      __napi_get_ref(format),
      __napi_get_ref(type),
      buf
  );
}

#undef EXPAND
#undef PP_NARG
#undef PP_NARG_
#undef PP_ARG_N
#undef PP_RSEQ_N

#undef __call_webgl_function
#undef __call_webgl_function_no_args

#endif