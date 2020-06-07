#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include "image.h"
#include "dragon.h"

/* x, y: coordinates of turtle */
static long x, y;

/* When drawing a pixel to the image, x and y must be divided by this value.
 * This enables both the dragon curve and twin dragon to rendered without
 * clipping.
 */
static long scale;

/* drawn_pixels: the length of the path travelled. */
static long drawn_pixels;

/* direction: the current direction of the turtle. */
static vector_t direction;

/* Returns a vector that describes the initial direction of the turtle. Each
 * iteration corresponds to a 45 degree rotation of the turtle anti-clockwise.  */
vector_t starting_direction(int total_iterations)
{ 
  assert (total_iterations >= 0);
  switch (total_iterations % 8) {
  case 0:
    return (vector_t) {1, 0};

  case 1:
    return (vector_t) {1, 1};

  case 2:
    return (vector_t) {0, 1};

  case 3:
    return (vector_t) {-1, 1};

  case 4:
    return (vector_t) {-1, 0};

  case 5:
    return (vector_t) {-1, -1};

  case 6:
    return (vector_t) {0, -1};

  case 7:
    return (vector_t) {1, -1};

  default:
    perror("starting_direction");
    exit(EXIT_FAILURE);
  }
}

/* Draws a pixel to dst at location (x, y). The pixel intensity is chosen as a
 * function of image size and the number of pixels drawn.
 *
 * The gray level changes over entire size of path; the pixel value oscillates
 * along the path to give some contrast between segments close to each other
 * spatially.
 */
void draw_greyscale(image_t *dst,long x, long y)
{
  int level = LEVEL * drawn_pixels / (dst->height * dst->height);
  uint8_t colour;

  switch(level) {
  case 0:
    colour = 100;
    break;
  case 1:
    colour = 120;
    break;
  case 2:
    colour = 150;
    break;
  case 3:
    colour = 180;
    break;
  case 4:
    colour = 200;
    break;
  default:
    colour = 255;
    break;
  }

  set_pixel(dst, x, y, colour); 
}

void rotate_clockwise() {  
  if (direction.dx == 1) {
    if (direction.dy == -1) {
      direction.dy = 1;
      return;
    }
    if (direction.dy == 0) {
      direction.dy = 1;
      direction.dx = 0;
      return;
    }
    if (direction.dy == 1) {
      direction.dx = -1;
      return;
    }
  }
  if (direction.dx == -1) {
    if (direction.dy == -1) {
      direction.dx = 1;
      return;
    }
    if (direction.dy == 0) {
      direction.dy = -1;
      direction.dx = 0;
      return;
    }
    if (direction.dy == 1) {
      direction.dy = -1;
      return;
    }
  }

  if (direction.dx == 0) {
    if (direction.dy == 1) {
      direction.dy = 0;
      direction.dx = -1;
      return;
    }
    if (direction.dy == -1) {
      direction.dy = 0;
      direction.dx = 1;
      return;
    }
  } 
}

void rotate_anticlockwise() {  
  if (direction.dx == 1) {
    if (direction.dy == -1) {
      direction.dx = -1;
      return;
    }
    if (direction.dy == 0) {
      direction.dy = -1;
      direction.dx = 0;
      return;
    }
    if (direction.dy == 1) {
      direction.dy = -1;
      return;
    }
  }
  if (direction.dx == -1) {
    if (direction.dy == -1) {
      direction.dy = 1;
      return;
    }
    if (direction.dy == 0) {
      direction.dy = 1;
      direction.dx = 0;
      return;
    }
    if (direction.dy == 1) {
      direction.dx = 1;
      return;
    }
  }

  if (direction.dx == 0) {
    if (direction.dy == 1) {
      direction.dy = 0;
      direction.dx = 1;
      return;
    }
    if (direction.dy == -1) {
      direction.dy = 0;
      direction.dx = -1;
      return;
    }
    }
}

/* Iterates though the characters of str, recusively calling string_iteration()
 * until rules have been applied iterations times, or no rule is applicable.
 * and update the image.
 */
void string_iteration(image_t *dst, const char *str, int iterations)
{  
  char *xRec = "X+YF";
  char *yRec = "FX-Y";
  assert(dst);
  if (str[0] != '\0' &&  iterations >= 0){

  switch(str[0]){
  case '+':
    rotate_anticlockwise();
    string_iteration(dst, str + 1, iterations);
    break;
    
  case '-':
    rotate_clockwise();
    string_iteration(dst, str + 1, iterations);
    break;
    
  case 'F':
    drawn_pixels++;
    draw_greyscale(dst, x / scale, y / scale);
    x += direction.dx;
    y += direction.dy;
    string_iteration(dst, str + 1, iterations);
    break;
    
  case 'X':
    string_iteration(dst, xRec, iterations-1);
    string_iteration(dst, str + 1, iterations);
    break;
    
  case 'Y':
    string_iteration(dst, yRec, iterations-1);
    string_iteration(dst, str + 1, iterations);
    break;
  }
  
  }
  
}

/* Creates an image of requested size, calls starting_direction() to compute
 * initial turtle direction then calls string_iteration() to construct the
 * image. The constructed image is saved to a file in the output directory.
 */
void dragon(long size, int total_iterations)
{

  image_t **img = malloc(sizeof(image_t *));
  image_error_t imm_error = init_image(img, 1.5 * size, size, 1, 255);
  if (imm_error != IMG_OK) {
    image_print_error(imm_error);
    free(img);
    exit(EXIT_FAILURE);
  }
  x = size;
  y = size;
  scale = 2;
  direction = starting_direction(total_iterations);
  string_iteration(*img, "FX+FX+", total_iterations);
  imm_error = image_write("../output/twindragon.pgm", *img, PGM_FORMAT);
  if (imm_error != IMG_OK) {
    image_print_error(imm_error);
    free(img);
    exit(EXIT_FAILURE);
  }
  image_free(*img);
  free(img);
  
}

/* The main function. When called with an argument, this should be considered
 * the number of iterations to execute. Otherwise, it is assumed to be 9. Image
 * size is computed from the number of iterations then dragon() is used to
 * generate the dragon image. */
int main(int argc, char **argv)
{
  int size = (argc == 2) ? atoi(argv[1]) : 9;
  dragon(pow(2, size), size);
  return EXIT_SUCCESS;
}
