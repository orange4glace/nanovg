#include "nanovg_webgl2_api.h"

napi_value Init(napi_env env, napi_value exports) {

  napi_value gl_init_nanovg;
  napi_create_function(env, "gl_init_nanovg", NAPI_AUTO_LENGTH, __gl_init_nanovg, NULL, &gl_init_nanovg);

  napi_set_named_property(env, exports, "gl_init_nanovg", gl_init_nanovg);

  return exports;
}

NAPI_MODULE(NANOVG_NODE_WEBGL, Init);