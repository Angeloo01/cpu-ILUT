include_directories(${PROJECT_SOURCE_DIR}/mmio)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/common/include)

add_executable(test test.cpp)
target_link_libraries(test library common)

add_executable(test_csr_ILU0 test_csr_ILU0.cpp)
target_link_libraries(test_csr_ILU0 library common)

add_executable(test_csr_ILUT test_csr_ILUT.cpp)
target_link_libraries(test_csr_ILUT library common)

add_executable(test_dense_guassian_elimination test_dense_guassian_elimination.cpp)
target_link_libraries(test_dense_guassian_elimination library common)

add_executable(test_dense_LU test_dense_LU.cpp)
target_link_libraries(test_dense_LU library common)
