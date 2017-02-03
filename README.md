# TOTP Generator Implementation

A generator for TOTP based on RFC-6238.

## Usage

Set `OTP_TOKEN` environment property to your desired otp token than run:

```bash
./bin/totp
```

To immediately put the generated token on the clipboard, run:

```bash
./bin/totp | pbcopy
```

## Compliance to RFC

This generator is in full compliance to the RFC described here: [RFC-6238](https://tools.ietf.org/html/rfc6238).

*Note*: With the expection that right now times, and methods are not configurable. That is in the ROADMAP.

## For OpenSSL on OSX

```bash
export OPENSSL_INCLUDE_DIR=/usr/local/Cellar/openssl/1.0.2j/include
export OPENSSL_LIB_DIR=/usr/local/Cellar/openssl/1.0.2j/lib
```

## Building

```bash
cd build
cmake .. && cmake --build .
```
