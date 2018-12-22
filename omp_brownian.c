#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// #include <FreeImage.h>
#include <omp.h>
#include <stdio.h>
 
#define NUM_PARTICLES  10000
#define SIZE           800

int world[SIZE][SIZE];
int num_threads = 1;

void draw_brownian_tree(int world[SIZE][SIZE]){
  int px, py; // particle values
  int dx, dy; // offsets
  int i;
 
  // set the seed
  world[rand() % SIZE][rand() % SIZE] = 1;
 
  omp_set_num_threads(num_threads);
  #pragma omp parallel default(none) shared(world) private(px, py, dx, dy)
  {
    unsigned int seed = omp_get_thread_num();
    #pragma omp for
    for (i = 0; i < NUM_PARTICLES; i++){
      // set particle's initial position
      px = rand_r(&seed) % SIZE;
      py = rand_r(&seed) % SIZE;
  
      while (1){
        // randomly choose a direction
        dx = rand_r(&seed) % 3 - 1;
        dy = rand_r(&seed) % 3 - 1;
  
        if (dx + px < 0 || dx + px >= SIZE || dy + py < 0 || dy + py >= SIZE){
          // plop the particle into some other random location
          px = rand_r(&seed) % SIZE;
          py = rand_r(&seed) % SIZE;
        }else if (world[py + dy][px + dx] != 0){
          // bumped into something
          world[py][px] = 1;
          break;
        }else{
          py += dy;
          px += dx;
        }
      }
    }
  }  
}
 
int main(int argc, char *argv[]){
  // FIBITMAP * img;
  // RGBQUAD rgb;
  // int x, y;
 
  memset(world, 0, sizeof world);

  if (argc >= 2) {
      int num = atoi(argv[1]);
      if (num <= 0) {
        printf("Invalid argument provided for number of threads.\n");
        printf("Please provide a valid number of threads as the first argument.\n");
        printf("Program will run on 1 thread.\n");
      } else {
        printf("Running the program on %d threads", num);
        num_threads = num;
      }      
  } else {
    printf("No argument provided for number of threads.\n");
    printf("Please provide a valid number of threads as the first argument.\n");
    printf("Program will run on 1 thread.\n");
  }
 
  draw_brownian_tree(world);
 
  // img = FreeImage_Allocate(SIZE, SIZE, 32, 0, 0, 0);
 
  // for (y = 0; y < SIZE; y++){
  //   for (x = 0; x < SIZE; x++){
  //     rgb.rgbRed = rgb.rgbGreen = rgb.rgbBlue = (world[y][x] ? 255 : 0);
  //     FreeImage_SetPixelColor(img, x, y, &rgb);
  //   }
  // }
  // FreeImage_Save(FIF_BMP, img, "brownian_tree_omp.bmp", 0);
  // FreeImage_Unload(img);
}