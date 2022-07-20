include_directories(${PROJECT_SOURCE_DIR}/common/include)
include_directories(${PROJECT_SOURCE_DIR}/mmio)
add_library(common sparseio.cpp
                   mm_coo_import.cpp
)
target_link_libraries(common mmiolib)