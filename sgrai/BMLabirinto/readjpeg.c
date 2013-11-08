#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include "jpeglib.h"
#else
#include <jpeglib.h>
#endif

#include <setjmp.h>

#pragma comment (lib, "libjpeg.lib")    /* link with Win32 libjpeg lib */
#ifdef _DEBUG
#pragma comment(linker, "/nodefaultlib:\"libc.lib\"")
#endif
#ifdef NDEBUG
//#pragma comment(linker, "/nodefaultlib:\"libc.lib\"")
#endif

struct my_error_mgr {
  struct jpeg_error_mgr pub; /* "public" fields */
  jmp_buf setjmp_buffer; /* for return to caller */
};

typedef struct my_error_mgr *my_error_ptr;

METHODDEF(void)
my_error_exit(j_common_ptr cinfo)
{
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

GLOBAL(int)
read_JPEG_file(const char *filename, char **fbuffer,
                int *width, int *height, int *bpp)
{
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;
  FILE *infile;
  JSAMPARRAY buffer;
  int row_stride;
  char *ptr;

  if ((infile = fopen(filename, "rb")) == NULL)
    return 0;
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return 0;
  }
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  (void) jpeg_read_header(&cinfo, TRUE);
  row_stride = cinfo.image_width * cinfo.num_components;
  *width = cinfo.image_width;
  *height = cinfo.image_height;
  *bpp = cinfo.num_components;

  /* Allocate the framebuffer */
  *fbuffer = (char *) malloc((size_t) (row_stride * cinfo.image_height));
  if (*fbuffer == NULL) {
    fclose(infile);
    return 0;
  }
  ptr = *fbuffer;

  (void) jpeg_start_decompress(&cinfo);
  buffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
  while (cinfo.output_scanline < cinfo.output_height) {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    memcpy(ptr, (void *) buffer[0], (size_t) row_stride);
    ptr += row_stride;
  }
  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  return 1;
}
