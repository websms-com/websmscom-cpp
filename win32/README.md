

                  W E B S M S . C O M   C + +   T O O L K I T


 This directory contains a release build of the websms toolkit including all
 dependencies. If you want to compile it yourself, you'll find the Microsoft
 Visual Studio 2010 solution and project files under vs2010/.

Example
-------

 There is a simple example project sending a text SMS in the vs2012/example
 folder.

Usage
-----

 If you want to set up your own project using the websms toolkit, you have to
 adjust the following project properties:

 * Debugging -> Environment
   Add path to libwebsms.dll and its dependencies to PATH.
 * VC++ Directories -> Include Directories
   Add path to the websms include files.
 * VC++ Directories -> Library Directories
   Add path to libwebsms.lib.
 * Linker -> Input
   Add libwebsms.lib to "Additional Dependencies"

 For reference check out the example project.

Dependencies
------------

 The websms toolkit uses Jansson and libcurl. This package contains precompiled
 DLLs of these dependencies and also binaries of the libcurl dependencies. The
 libcurl files were extracted from the libcurl binary archive (version 7.27.0),
 which can be downloaded from the libcurl website.

 The Source code of every dependency can be found on the corresponding website.

 This product includes software developed by the OpenSSL Project for use in the
 OpenSSL Toolkit. (http://www.openssl.org/)

 * Jansson - http://www.digip.org/jansson/
   Files: bin/jansson.dll, lib/jansson.lib
   License: MIT-License

 * libcurl - http://curl.haxx.se/libcurl/
   Files: bin/libcurl.dll, lib/libcurl.lib
   License: MIT

 * libidn - http://www.gnu.org/software/libidn/
   Files: bin/libidn-11.dll
   License: LGPL v2.1

 * librtmp - http://rtmpdump.mplayerhq.hu/
   Files: bin/librtmp.dll
   License: LGPL v2.1

 * libssh2 - http://www.libssh2.org/
   Files: bin/libssh2.dll
   License: BSD

 * openssl - https://www.openssl.org/
   Files: bin/libeay32.dll, bin/ssleay32.dll
   License: Custom

 * zlib - http://www.zlib.net/
   Files: bin/zlib1.dll
   License: Custom
