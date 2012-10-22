# DVBLink Remote API Library
libdvblinkremote is a pure C++ DVBLink Remote API static library.

Current version of library: 0.2.0 BETA (supporting DVBLink Remote API version 0.2)

## dvblinkremote command line tool
A command line tool for interacting with a DVBLink Connect! Server using the DVBLink Remote API. This tool are using the libdvblinkremote.

## 3rd party dependencies
### libcurl
Required dependency for the command line tool, but can be excluded in build if you would like to implement your own http client.  
http://curl.haxx.se/libcurl/

### TinyXML-2
This dependency is required.  
https://github.com/leethomason/tinyxml2)

## API library documentation
See http://marefr.github.com/dvblinkremote/

## Compiling on Windows (Visual Studio 2010)
### 1. Setup CMake
1. Download and install CMake: http://www.cmake.org/
2. Configure CMAKE_PREFIX_PATH to point at installed directories for libcurl and TinyXML-2.  
  One way of doing this is to define this by configuring a environment variable.  
    
    Example configuration:  
    >Variable name: CMAKE_PREFIX_PATH  
    >Variable value: C:/Program Files (x86)/curl-7.21.6;C:/Program Files (x86)/tinyxml2  

  Another way of doing this is to supply the configuration when configuring CMake (see below), but how to achive that is not covered here.

### 2. Configure DVBLink Remote API Library with CMake
Open up a new Visual Studio Command Prompt (2010)  
  ```shell  
  # Navigate to DVBLink Remote API Library root folder:  
  cd <DVBLink Remote API Library root>  

  # Create a new folder, for example build, and navigate to it:  
  mkdir build  
  cd build  
  
  # Create a new folder, for example vs2010:  
  mkdir vs2010  
  cd vs2010
  
  # Configure CMake to include curl support and command line tool in build.  
  # API documentation requires doxygen and is excluded here.  
  cmake -DWITH_CURL:BOOL=TRUE -DWITH_COMMAND_LINE_TOOL:BOOL=TRUE -DWITH_APIDOC:BOOL=FALSE -G "Visual Studio 10" .  
  
  # Tell CMake to execute a release build and install DVBLink Remote API Library.  
  # Default install folder is C:\Program Files (x86)\dvblinkremote or similar.
  cd ..  
  cmake --build vs2010 --target "INSTALL" --config "Release" --clean-first
  
  # Tell CMake to execute a release build and package the DVBLink Remote API Library in ZIP archive.  
  # Default install folder is <build dir>.  
  cmake --build vs2010 --target "PACKAGE" --config "Release" --clean-first
  ```  

## Compiling on non-Windows environments  
This has not been tested by me! If you would like to try you're more than welcome, but chances are that you need to tweak the CMake files a bit. 
Please fork this repo and make neccessary CMake changes (if needed) and hand me a pull request. Thanks in advance.

## More Information
For more information, please see [DVBLogic official homepage](http://www.dvblogic.com/) and [DVBLink Remote API documentation](http://188.121.56.29//download/dvblink_remote_api.htm).

## License (MIT)

Copyright (c) 2012 Marcus Efraimsson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.