set(BOOST_DIR "" CACHE PATH "Path to boost library dir")

if(EXISTS "${BOOST_DIR}")
    message(STATUS "BOOST found at: ${BOOST_DIR}")
else()
    message(STATUS "Could not find boost dir at: ${BOOST_DIR}")
endif()