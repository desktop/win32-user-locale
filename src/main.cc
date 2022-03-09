// Windows.h strict mode
#define STRICT
#define UNICODE

#include <napi.h>
#include "uv.h"

#include <assert.h>
#include <windows.h>
#include <winnls.h>

#include <cstdio>
#include <memory>
#include <iostream>

using namespace Napi;

LPWSTR utf8ToWideChar(std::string utf8)
{
    int wide_char_length = MultiByteToWideChar(CP_UTF8,
                                                0,
                                                utf8.c_str(),
                                                -1,
                                                nullptr,
                                                0);
    if (wide_char_length == 0)
    {
        return nullptr;
    }

    LPWSTR result = new WCHAR[wide_char_length];
    if (MultiByteToWideChar(CP_UTF8,
                            0,
                            utf8.c_str(),
                            -1,
                            result,
                            wide_char_length) == 0)
    {
        delete[] result;
        return nullptr;
    }

    return result;
}

namespace
{  
  Napi::Value getLocaleInfoEx(const Napi::CallbackInfo &info)
  {
    Napi::Env &env = info.Env();

    if (info.Length() < 3)
    {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Undefined();
    }

    if (!info[0].IsString() && !info[0].IsNull())
    {
      Napi::TypeError::New(env, "Expected first parameter to be of type string or null.").ThrowAsJavaScriptException();
      return env.Undefined();
    }

    if (!info[1].IsNumber())
    {
      Napi::TypeError::New(env, "Expected second parameter to be of type number.").ThrowAsJavaScriptException();
      return env.Undefined();
    }

    if (!info[2].IsBuffer())
    {
      Napi::TypeError::New(env, "Expected third parameter to be of type Buffer.").ThrowAsJavaScriptException();
      return env.Undefined();
    }

    auto lpLocaleName = info[0].IsNull() ? nullptr : utf8ToWideChar(info[0].As<Napi::String>());
    auto LCType = info[1].As<Napi::Number>().Uint32Value();
    auto lpLCData = info[2].As<Napi::Buffer<wchar_t>>();
    // return Napi::Value::From(info.Env(), 0);
    
    auto result = GetLocaleInfoEx(lpLocaleName, LCType, lpLCData.Data(), lpLCData.Length());

    return Napi::Value::From(info.Env(), result);
  }

  Napi::Object Init(Napi::Env env, Napi::Object exports)
  {
    exports.Set(Napi::String::New(env, "getLocaleInfoEx"), Napi::Function::New(env, getLocaleInfoEx));

    return exports;
  }
}

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(win32UserLocaleNativeModule, Init)
#else
NODE_API_MODULE(win32UserLocaleNativeModule, Init);
#endif
