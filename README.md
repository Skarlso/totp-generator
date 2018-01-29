# TOTP Generator Implementation

A generator for TOTP based on RFC-6238.

Original idea of implementing an RFC as a programming exercises by: [Yitsushi](https://github.com/Yitsushi).
His implementation in Go can be found here: [Yitsushi](https://github.com/Yitsushi/totp-cli/).

I did it C++ in order to learn and practice.

## Usage

### Dependencies

Requires cryptopp, boost and openssl installed.

### Building on Linux

```bash
cd build && cmake .. && cmake --build .
```

### Building on OSX

```bash
export OPENSSL_INCLUDE_DIR=/usr/local/Cellar/openssl/1.0.2j/include
export OPENSSL_LIB_DIR=/usr/local/Cellar/openssl/1.0.2j/lib
export OPENSSL_ROOT_DIR=/usr/local/Cellar/openssl/1.0.2j/
```
Alternatively:

```bash
cmake -DOPENSSL_INCLUDE_DIR=/usr/local/Cellar/openssl/1.0.2j/include -DOPENSSL_ROOT_DIR=/usr/local/Cellar/openssl/1.0.2j/ ..
```

### Running

Totp-generator uses AES to encrypt an account file. In order to set a password
to use for said file, set the following environment property:

```bash
export TOTP_KEY=mysecurepassword
```

#### Commands

The following commands are available to use.

```bash
totp add # Follow the prompts to add a new token
totp generate [account] # Generate a totp using the token defined for [account]
totp delete [account] # Remove the account defined in [account]
```

A typical usage scenario would be as follows:

```bash
totp add
# account:test
# token:ASDFQWERZXCV=
# Added token ASDFQWERZXCV= to account test.
```

After adding a new token, generate an otp for that account like this:

```bash
totp generate test
123456
```

Or copy it directory to your clipboard ready to be pasted into the required field:

```bash
totp generate test | pbcopy
```

To delete an account use `delete`:

```bash
totp delete test
```

### Account file

Totp-generate creates an account file under `~/.totp/accounts.txt` which is encrypted with AES.

The file and directory are generated during the first run.

## Installing

The only component that is needed is under `./build/bin/totp`. Copy this binary anywhere on your
`PATH` makes it available to run from anywhere.

I prefer to have a `~/bin` folder for fringe executables I'm using.

## Compliance to RFC

This generator is in full compliance to the RFC described here: [RFC-6238](https://tools.ietf.org/html/rfc6238).

*Note*: With the expection that right now times, and methods are not configurable. That is in the ROADMAP.

# Contributions

Please feel free to contribute tests, or improving teh code. I'm posting issues I think should
be fixed or can be improved upon. Since I'm only learning C++ I'm sure there are code improvements
I'm not thinking of. I would be actually greatfull for improving those with description of the why.
