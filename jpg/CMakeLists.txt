find_package(JPEG REQUIRED)

include_directories(${JPEG_INCLUDE_DIRS})

set(IMGLIB_MAIN_FILES img_lib.h img_lib.cpp)

# к файлам форматов добавим JPEG
set(IMGLIB_FORMAT_FILES
    jpeg_image.h jpeg_image.cpp)

add_library(ImgLib STATIC ${IMGLIB_MAIN_FILES} 
            ${IMGLIB_FORMAT_FILES})

target_link_libraries(ImgLib ${JPEG_LIBRARIES})
