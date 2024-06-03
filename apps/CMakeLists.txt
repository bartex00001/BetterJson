add_executable(bjq bjq.cpp)
target_compile_features(bjq PRIVATE cxx_std_23)

target_link_libraries(bjq PRIVATE betterJson)
