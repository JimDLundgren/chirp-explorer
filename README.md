# chirp-explorer

Small example profram using the Twitter REST API to serach for tweets containing a given query.

# Requirements

yhirose/cpp-httplib (https://github.com/yhirose/cpp-httplib) for http requests.
Note: it requires OpenSSL.
nlohmann/json (https://github.com/nlohmann/json) for parsing json.

# Install on Windows:

Both cpp-httplib and json are available as single-header libraries, so just download and link in VS.
However, to use HTTPS in cpp-httplib, we need OpenSSL.
Download the supported version at https://www.openssl.org/source/. To install:
Download ActiveState perl (5.28 is latest release at time of this writing). NoteL need to add Text-Template in the build.
Download and install NASM.
Choose the VC-Win32 option when installing OpenSSL.
Note: nmake test will stall with ActiveState perl (supposibly with Strawberry it works)
Linking in VS: Additional Include dirs, Additional Library Dirs, and Library Input (names of libraries)
In VS also need to set debugging Environment to PATH=%PATH%;$(OpenSSLInstallDir)\bin

