#define NAPI_EXPERIMENTAL
#include "nanovg_webgl2_api.h"
#include "nanovg.h"
#define NANOVG_WEBGL2_IMPLEMENTATION
#include "nanovg_webgl2.h"

#include "napi_decoder.h"
#include "napi_encoder.h"

#include <assert.h>

static NVGcontext* vg;

struct VideoFrameData {
  uint8_t* data;
  int width;
  int height;
  int64_t pts;
};

napi_value __nvg_beginFrame(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);
  size_t argc = 3;
  napi_value nv[3];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  double windowWidth, windowHeight, devicePixelRatio;
  napi_get_value_double(env, nv[0], &windowWidth);
  napi_get_value_double(env, nv[1], &windowHeight);
  napi_get_value_double(env, nv[2], &devicePixelRatio);

  nvgBeginFrame(vg, windowWidth, windowHeight, devicePixelRatio);
  return 0;
}

napi_value __nvgSave(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  nvgSave(vg);
  return 0;
}

napi_value __nvgRestore(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  nvgRestore(vg);
  return 0;
}

napi_value __nvgBeginPath(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  nvgBeginPath(vg);
  return 0;
}

napi_value __nvgMoveTo(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);
  size_t argc = 2;
  napi_value nv[2];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  double x, y;
  napi_get_value_double(env, nv[0], &x);
  napi_get_value_double(env, nv[1], &y);

  nvgMoveTo(vg, x, y);
  return 0;
}

napi_value __nvgLineTo(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);
  size_t argc = 2;
  napi_value nv[2];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  double x, y;
  napi_get_value_double(env, nv[0], &x);
  napi_get_value_double(env, nv[1], &y);

  nvgLineTo(vg, x, y);
  return 0;
}

napi_value __nvgClosePath(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  nvgClosePath(vg);
  return 0;
}

napi_value __nvgFill(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  nvgFill(vg);
  return 0;
}

napi_value __nvgStroke(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  nvgStroke(vg);
  return 0;
}

napi_value __nvgFillColor(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);
  size_t argc = 4;
  napi_value nv[4];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  int r, g, b, a;
  napi_get_value_int32(env, nv[0], &r);
  napi_get_value_int32(env, nv[1], &g);
  napi_get_value_int32(env, nv[2], &b);
  napi_get_value_int32(env, nv[3], &a);

  nvgFillColor(vg, nvgRGBA(r, g, b, a));
  return 0;
}

napi_value __nvgStrokeColor(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);
  size_t argc = 4;
  napi_value nv[4];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  int r, g, b, a;
  napi_get_value_int32(env, nv[0], &r);
  napi_get_value_int32(env, nv[1], &g);
  napi_get_value_int32(env, nv[2], &b);
  napi_get_value_int32(env, nv[3], &a);

  nvgStrokeColor(vg, nvgRGBA(r, g, b, a));
  return 0;
}

napi_value __nvgStrokeWidth(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);
  size_t argc = 1;
  napi_value nv[1];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  double v;
  napi_get_value_double(env, nv[0], &v);

  nvgStrokeWidth(vg, v);
  return 0;
}

napi_value __nvgEndFrame(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  nvgEndFrame(vg);
  return 0;
}

napi_value __nvg_createImageRGBA(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);
  size_t argc = 4;
  napi_value nv[4];
  napi_value* nvp = nv;
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  int w, h, flag;
  uint64_t uaddr;
  bool lossless;
  napi_get_value_int32(env, *nvp++, &w);
  napi_get_value_int32(env, *nvp++, &h);
  napi_get_value_int32(env, *nvp++, &flag);
  napi_get_value_bigint_uint64(env, *nvp++, &uaddr, &lossless);
  assert(lossless);

  uint8_t* ptr = reinterpret_cast<uint8_t*>(uaddr);
  VideoFrameData* data = reinterpret_cast<VideoFrameData*>(ptr);

  int image = nvgCreateImageRGBA(vg, data->width, data->height, flag, (unsigned char*)data->data);
  return napi_encoder<int32_t>::encode(env, image);
}

#define DefineAPI(name) \
    napi_value nvg_##name; \
    napi_create_function(env, "\""#name"\"", NAPI_AUTO_LENGTH, __nvg_##name, NULL, &nvg_##name); \
    napi_set_named_property(env, handle, "\""#name"\"", nvg_##name);

napi_value __nanovg_webgl2_init(napi_env env, napi_callback_info cbinfo) {
  setNAPIenv(env);

  size_t argc = 1;
  napi_value nv[1];
  napi_get_cb_info(env, cbinfo, &argc, nv, 0, 0);

  napi_value gl = nv[0];
  __webgl_context = __napi_create_ref(gl);

  __nanovg_webgl2_register_functions(env, gl);

  vg = nvgCreateWebGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

  napi_value handle;
  napi_create_object(env, &handle);

  DefineAPI(beginFrame);

  napi_value nvgSave_;
  napi_create_function(env, "save", NAPI_AUTO_LENGTH, __nvgSave, NULL, &nvgSave_);
  napi_set_named_property(env, handle, "save", nvgSave_);

  napi_value nvgRestore_;
  napi_create_function(env, "restore", NAPI_AUTO_LENGTH, __nvgRestore, NULL, &nvgRestore_);
  napi_set_named_property(env, handle, "restore", nvgRestore_);

  napi_value nvgBeginPath_;
  napi_create_function(env, "beginPath", NAPI_AUTO_LENGTH, __nvgBeginPath, NULL, &nvgBeginPath_);
  napi_set_named_property(env, handle, "beginPath", nvgBeginPath_);

  napi_value nvgMoveTo_;
  napi_create_function(env, "moveTo", NAPI_AUTO_LENGTH, __nvgMoveTo, NULL, &nvgMoveTo_);
  napi_set_named_property(env, handle, "moveTo", nvgMoveTo_);

  napi_value nvgLineTo_;
  napi_create_function(env, "lineTo", NAPI_AUTO_LENGTH, __nvgLineTo, NULL, &nvgLineTo_);
  napi_set_named_property(env, handle, "lineTo", nvgLineTo_);

  napi_value nvgClosePath_;
  napi_create_function(env, "closePath", NAPI_AUTO_LENGTH, __nvgClosePath, NULL, &nvgClosePath_);
  napi_set_named_property(env, handle, "closePath", nvgClosePath_);

  napi_value nvgFill_;
  napi_create_function(env, "fill", NAPI_AUTO_LENGTH, __nvgFill, NULL, &nvgFill_);
  napi_set_named_property(env, handle, "fill", nvgFill_);

  napi_value nvgStroke_;
  napi_create_function(env, "stroke", NAPI_AUTO_LENGTH, __nvgStroke, NULL, &nvgStroke_);
  napi_set_named_property(env, handle, "stroke", nvgStroke_);

  napi_value nvgFillColor_;
  napi_create_function(env, "fillColor", NAPI_AUTO_LENGTH, __nvgFillColor, NULL, &nvgFillColor_);
  napi_set_named_property(env, handle, "fillColor", nvgFillColor_);

  napi_value nvgStrokeColor_;
  napi_create_function(env, "strokeColor", NAPI_AUTO_LENGTH, __nvgStrokeColor, NULL, &nvgStrokeColor_);
  napi_set_named_property(env, handle, "strokeColor", nvgStrokeColor_);

  napi_value nvgStrokeWidth_;
  napi_create_function(env, "strokeWidth", NAPI_AUTO_LENGTH, __nvgStrokeWidth, NULL, &nvgStrokeWidth_);
  napi_set_named_property(env, handle, "strokeWidth", nvgStrokeWidth_);

  napi_value nvgEndFrame_;
  napi_create_function(env, "endFrame", NAPI_AUTO_LENGTH, __nvgEndFrame, NULL, &nvgEndFrame_);
  napi_set_named_property(env, handle, "endFrame", nvgEndFrame_);

  DefineAPI(createImageRGBA);

  return handle;
}

napi_value Init(napi_env env, napi_value exports) {

  napi_value init_nanovg;
  napi_create_function(env, "initNanoVG", NAPI_AUTO_LENGTH, __nanovg_webgl2_init, NULL, &init_nanovg);

  napi_set_named_property(env, exports, "initNanoVG", init_nanovg);

  return exports;
}

NAPI_MODULE(NANOVG_NODE_WEBGL, Init);