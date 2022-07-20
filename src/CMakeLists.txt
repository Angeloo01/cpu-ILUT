include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/common/include)
add_library(library csr_ILU0.cpp
                    csr_ILUT.cpp
                    dense_guassian_elimination.cpp
                    dense_LU.cpp
)
