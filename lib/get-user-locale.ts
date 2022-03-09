type NativeModule = {
  getLocaleInfoEx: (
    lpLocaleName: string | null,
    LCType: number,
    lpLCData: Buffer
  ) => number
}

// The native binary will be loaded lazily to avoid any possible crash at start
// time, which are harder to trace.
let _nativeModule: NativeModule | undefined = undefined

function getNativeModule() {
  if (_nativeModule === undefined && process.platform === 'win32') {
    _nativeModule = require('bindings')('win32-user-locale.node')
  }

  return _nativeModule
}

const LOCALE_SNAME = 0x0000005c

export function getUserLocale(): string | undefined {
  const buf = Buffer.alloc(256)
  const result = getNativeModule()?.getLocaleInfoEx(null, LOCALE_SNAME, buf)

  return result !== undefined && result > 0
    ? buf.toString('utf16le', 0, (result - 1) * 2)
    : undefined
}
