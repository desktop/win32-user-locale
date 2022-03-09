# win32-user-locale

## A thin wrapper on top of GetLocaleInfoEx to get the user locale on Windows

## Goals

- zero dependencies
- leverage TypeScript declarations wherever possible

## Install

```shellsession
$ yarn add win32-user-locale
# or
$ npm install --save win32-user-locale
```

## Documentation

See the documentation under the
[`docs`](https://github.com/desktop/win32-user-locale/tree/master/docs) folder.

## Supported versions

Each release of `win32-user-locale` includes prebuilt binaries based on
[N-API](https://nodejs.org/api/n-api.html), with support for different versions
of Node and Electron. Please refer to the
[N-API version matrix](https://nodejs.org/api/n-api.html#node-api-version-matrix)
and the release documentation for [Node](https://github.com/nodejs/Release) and
[Electron](https://electronjs.org/docs/tutorial/support) to see what is
supported currently.

## Contributing

Read the
[Setup](https://github.com/desktop/win32-user-locale/blob/master/docs/index.md#setup)
section to ensure your development environment is setup for what you need.

While we always try to accomodate requests this package is mainly developed to
support GitHub Desktop and our priorities reflect that.

If you want to see something supported, open an issue to start a discussion
about it.
