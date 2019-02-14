#ifndef OLIVE_NAPI_ENCODER_H_
#define OLIVE_NAPI_ENCODER_H_

#include <node_api.h>

#include <string>
#include <assert.h>

#define NAPI_CALL(CALL) \
 {napi_status status; \
  status = CALL; \
  if (status != napi_ok) { \
    assert(false); \
  }}

template <typename T>
struct napi_encoder {
  inline static napi_value encode(napi_env env, T native) {
    napi_value value;
    NAPI_CALL(napi_create_external(env, (void*)native, NULL, NULL, &value));
    return value;
  }
};

template <>
struct napi_encoder<napi_value> {
  inline static napi_value encode(napi_env env, napi_value value) {
    return value;
  }
};

template <>
struct napi_encoder<int32_t> {
  inline static napi_value encode(napi_env env, int32_t value) {
    napi_value ret;
    NAPI_CALL(napi_create_int32(env, value, &ret));
    return ret;
  }
};

template <>
struct napi_encoder<uint32_t> {
  inline static napi_value encode(napi_env env, uint32_t value) {
    napi_value ret;
    NAPI_CALL(napi_create_uint32(env, value, &ret));
    return ret;
  }
};

template <>
struct napi_encoder<uint64_t> {
  inline static napi_value encode(napi_env env, uint64_t value) {
    napi_value ret;
    NAPI_CALL(napi_create_bigint_uint64(env, value, &ret));
    return ret;
  }
};

template <>
struct napi_encoder<const char*> {
  inline static napi_value encode(napi_env env, const char* value) {
    napi_value ret;
    NAPI_CALL(napi_create_string_utf8(env, value, NAPI_AUTO_LENGTH, &ret));
    return ret;
  }
  inline static napi_value encode(napi_env env, std::string& value) {
    napi_value ret;
    NAPI_CALL(napi_create_string_utf8(env, value.c_str(), NAPI_AUTO_LENGTH, &ret));
    return ret;
  }
};

template <>
struct napi_encoder<std::string> {
  inline static napi_value encode(napi_env env, std::string& value) {
    napi_value ret;
    NAPI_CALL(napi_create_string_utf8(env, value.c_str(), NAPI_AUTO_LENGTH, &ret));
    return ret;
  }
};

#endif // OLIVE_NAPI_ENCODER_H_