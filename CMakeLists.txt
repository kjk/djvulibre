cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
MESSAGE(STATUS "CMAKE_CXX_STANDARD:" ${CMAKE_CXX_STANDARD})

project (djvu)

set(LIBDJVU_SOURCES
    libdjvu/Arrays.cpp
    libdjvu/BSByteStream.cpp
    libdjvu/BSEncodeByteStream.cpp
    libdjvu/ByteStream.cpp
    libdjvu/DataPool.cpp
    libdjvu/DjVmDir.cpp
    libdjvu/DjVmDir0.cpp
    libdjvu/DjVmDoc.cpp
    libdjvu/DjVmNav.cpp
    libdjvu/DjVuAnno.cpp
    libdjvu/DjVuDocEditor.cpp
    libdjvu/DjVuDocument.cpp
    libdjvu/DjVuDumpHelper.cpp
    libdjvu/DjVuErrorList.cpp
    libdjvu/DjVuFile.cpp
    libdjvu/DjVuFileCache.cpp
    libdjvu/DjVuGlobal.cpp
    libdjvu/DjVuGlobalMemory.cpp
    libdjvu/DjVuImage.cpp
    libdjvu/DjVuInfo.cpp
    libdjvu/DjVuMessage.cpp
    libdjvu/DjVuMessageLite.cpp
    libdjvu/DjVuNavDir.cpp
    libdjvu/DjVuPalette.cpp
    libdjvu/DjVuPort.cpp
    libdjvu/DjVuText.cpp
    libdjvu/DjVuToPS.cpp
    libdjvu/GBitmap.cpp
    libdjvu/GContainer.cpp
    libdjvu/GException.cpp
    libdjvu/GIFFManager.cpp
    libdjvu/GMapAreas.cpp
    libdjvu/GOS.cpp
    libdjvu/GPixmap.cpp
    libdjvu/GRect.cpp
    libdjvu/GScaler.cpp
    libdjvu/GSmartPointer.cpp
    libdjvu/GString.cpp
    libdjvu/GThreads.cpp
    libdjvu/GURL.cpp
    libdjvu/GUnicode.cpp
    libdjvu/IFFByteStream.cpp
    libdjvu/IW44EncodeCodec.cpp
    libdjvu/IW44Image.cpp
    libdjvu/JB2EncodeCodec.cpp
    libdjvu/JB2Image.cpp
    libdjvu/JPEGDecoder.cpp
    libdjvu/MMRDecoder.cpp
    libdjvu/MMX.cpp
    libdjvu/UnicodeByteStream.cpp
    libdjvu/XMLParser.cpp
    libdjvu/XMLTags.cpp
    libdjvu/ZPCodec.cpp
    libdjvu/atomic.cpp
    libdjvu/ddjvuapi.cpp
    libdjvu/debug.cpp
    libdjvu/miniexp.cpp
)

#[[
]]

add_definitions(-DUNIX)
add_definitions(-DHAVE_STDINCLUDES)
add_definitions(-DHAVE_STDINT_H)
add_definitions(-DHAVE_PTHREAD)
add_definitions(-DHAS_WCHAR=1)
add_definitions(-DHAS_WCTYPE=1)
add_definitions(-DHAS_MBSTATE=1)

set(CMAKE_BUILD_TYPE Release)

add_library(libdjvu STATIC ${LIBDJVU_SOURCES})

include_directories("libdjvu")
add_executable(djvudump tools/djvudump.cpp)
target_link_libraries(djvudump libdjvu)