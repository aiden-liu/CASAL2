SET(CMAKE_CXX_VERBOSE_FLAG "-v")

SET(CMAKE_SHARED_LIBRARY_CXX_FLAGS "-KPIC")
SET(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "-G")
SET(CMAKE_SHARED_LIBRARY_RUNTIME_CXX_FLAG "-R")
SET(CMAKE_SHARED_LIBRARY_RUNTIME_CXX_FLAG_SEP ":")
SET(CMAKE_SHARED_LIBRARY_SONAME_CXX_FLAG "-h")

SET(CMAKE_CXX_FLAGS_INIT "")
SET(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
SET(CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-xO2 -xspace -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE_INIT "-xO3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-g -xO2")

# Initialize C link type selection flags.  These flags are used when
# building a shared library, shared module, or executable that links
# to other libraries to select whether to use the static or shared
# versions of the libraries.
FOREACH(type SHARED_LIBRARY SHARED_MODULE EXE)
  SET(CMAKE_${type}_LINK_STATIC_CXX_FLAGS "-Bstatic")
  SET(CMAKE_${type}_LINK_DYNAMIC_CXX_FLAGS "-Bdynamic")
ENDFOREACH(type)

SET(CMAKE_CXX_CREATE_PREPROCESSED_SOURCE "<CMAKE_CXX_COMPILER> <DEFINES> <FLAGS> -E <SOURCE> > <PREPROCESSED_SOURCE>")
SET(CMAKE_CXX_CREATE_ASSEMBLY_SOURCE "<CMAKE_CXX_COMPILER> <FLAGS> -S <SOURCE> -o <ASSEMBLY_SOURCE>")

# Create archives with "CC -xar" in case user adds "-instances=extern"
# so that template instantiations are available to archive members.
SET(CMAKE_CXX_CREATE_STATIC_LIBRARY
  "<CMAKE_CXX_COMPILER> -xar -o <TARGET> <OBJECTS> "
  "<CMAKE_RANLIB> <TARGET> ")
