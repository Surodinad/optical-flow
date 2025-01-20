#include "jpeg_image.h"

#include <array>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <setjmp.h>

#include <jpeglib.h>

using namespace std;

namespace img_lib {
    struct my_error_mgr {
        struct jpeg_error_mgr pub;
        jmp_buf setjmp_buffer;
    };

    typedef struct my_error_mgr* my_error_ptr;

    METHODDEF(void)
    my_error_exit (j_common_ptr cinfo) {
    my_error_ptr myerr = (my_error_ptr) cinfo->err;
    (*cinfo->err->output_message) (cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}


void load_scanline_from_image(JSAMPLE* row, int y, const image& in_image) {
    const color* line = in_image.get_line(y);
    for (int x = 0; x < in_image.get_width(); ++x) {
        JSAMPLE* pixel = row + x * 3;
		pixel[0] = static_cast<JSAMPLE>(line[x].r);
		pixel[1] = static_cast<JSAMPLE>(line[x].g);
		pixel[2] = static_cast<JSAMPLE>(line[x].b);
    }
}

bool save_JPEG(const path& file, const image& image) {
    jpeg_compress_struct cinfo;
    jpeg_error_mgr jerr;
    FILE * outfile;
    std::vector<JSAMPLE> image_buffer(image.get_height()*image.get_width()*3, 0);
	JSAMPROW row_pointer[1];
    int row_stride;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

#ifdef _MSC_VER
    if ((outfile = _wfopen(file.wstring().c_str(), L"wb")) == NULL) {
#else
    if ((outfile = fopen(file.string().c_str(), "wb")) == NULL) {
#endif
        return false;
    }
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = image.get_width();
    cinfo.image_height = image.get_height();
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;   
    jpeg_set_defaults(&cinfo);
    
    jpeg_start_compress(&cinfo, TRUE);

    row_stride = image.get_width() * 3;

    while (cinfo.next_scanline < cinfo.image_height) {
		int y = cinfo.next_scanline;
        row_pointer[0] = &image_buffer[cinfo.next_scanline*row_stride];
		load_scanline_from_image(row_pointer[0], y, image);
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);

	return true;
}

void save_scanline_to_image(const JSAMPLE* row, int y, image& out_image) {
    color* line = out_image.get_line(y);
    for (int x = 0; x < out_image.get_width(); ++x) {
        const JSAMPLE* pixel = row + x * 3;
        line[x] = color{byte{pixel[0]}, byte{pixel[1]}, byte{pixel[2]}, byte{255}};
    }
}

image load_JPEG(const path& file) {
    jpeg_decompress_struct cinfo;
    my_error_mgr jerr;

    FILE* infile;
    JSAMPARRAY buffer;
    int row_stride;

#ifdef _MSC_VER
    if ((infile = _wfopen(file.wstring().c_str(), L"rb")) == NULL) {
#else
    if ((infile = fopen(file.string().c_str(), "rb")) == NULL) {
#endif
        return {};
    }

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return {};
    }

    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, infile);

    (void) jpeg_read_header(&cinfo, TRUE);

    cinfo.out_color_space = JCS_RGB;
    cinfo.output_components = 3;

    (void) jpeg_start_decompress(&cinfo);

    row_stride = cinfo.output_width * cinfo.output_components;

    buffer = (*cinfo.mem->alloc_sarray)
            ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    image result(cinfo.output_width, cinfo.output_height, color::black());

    while (cinfo.output_scanline < cinfo.output_height) {
        int y = cinfo.output_scanline;
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);

        save_scanline_to_image(buffer[0], y, result);
    }

    (void) jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    return result;
}

} // namespace img_lib
