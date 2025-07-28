set(GTest_DIR "" CACHE PATH "Path to dir containing GTestConfig.cmake")

find_package(GTest CONFIG REQUIRED COMPONENTS GTest GMock)
MESSAGE( STATUS "GTest found version: ${GTest_VERSION}" )
