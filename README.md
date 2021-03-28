# chirp-explorer

Small example program using the Twitter REST API to serach for tweets containing a given query.

# Requirements

1. To run the program you need a Bearer Token from a registered Twitter developer App,
supporting Twitter API v2 (https://developer.twitter.com/en/docs/apps/overview).
2. yhirose/cpp-httplib (https://github.com/yhirose/cpp-httplib) for http requests.
Note: it requires OpenSSL.
3. nlohmann/json (https://github.com/nlohmann/json) for parsing json.
4. The tests require gtest/gmock.

# Install on Windows:

- Both cpp-httplib and json are available as single-header libraries, so simply download and link in VS.
- To use HTTPS in cpp-httplib, we need OpenSSL. Download the supported version at https://www.openssl.org/source/.
To install, follow the instructions in the OpenSSL source. Some notes on the installation:
    - Download ActiveState perl (5.28 is latest release at time of this writing).
    Note: need to add Text-Template in the build.
    - Download and install NASM.
    - When installing OpenSSL, choose the VC-Win32 installation option.
    Note: "nmake test" will stall due to ActiveState perl (supposibly with Strawberry it works).
    - Linking in VS:
        - Add the relevant paths in Additional Include dirs and Additional Library Dirs.
        - Add the names of the libraries in the Library Input.
        - Set the debugging Environment to PATH=%PATH%;$(OpenSSLInstallDir)\bin.

