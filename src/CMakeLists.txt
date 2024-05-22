file(GLOB_RECURSE
        HEADER_LIST
        CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/*.hpp")

# Collect implementations
file(GLOB_RECURSE
        SRC_LIST
        CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(betterJson ${SRC_LIST} ${HEADER_LIST})

target_include_directories(betterJson PUBLIC ../include)

target_compile_features(betterJson PUBLIC cxx_std_23)
