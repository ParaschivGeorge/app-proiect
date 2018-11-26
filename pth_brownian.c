

        #include <string.h>
        #include <stdlib.h>
        #include <time.h>
        #include <math.h>
        #include <FreeImage.h>
        #include <pthread.h>
        #include <stdio.h>
         
        #define NUM_PARTICLES  1000
        #define SIZE           800
         
        void draw_brownian_tree(int world[SIZE / 2][SIZE / 2]){
          int px, py; // particle values
          int dx, dy; // offsets
          int i;
         
          for (i = 0; i < NUM_PARTICLES / 4; i++){
            // set particle's initial position
            px = rand() % (i + 1);
            py = rand() % (i + 1);
         
            // printf("%d\n", i);
            while (1){
              // randomly choose a direction
              dx = rand() % 3 - 1;
              dy = rand() % 3 - 1;
         
              if (dx + px < 0 || dx + px >= SIZE / 2 || dy + py < 0 || dy + py >= SIZE / 2){
                // plop the particle into some other random location
                px = rand() % (i + 1);
                py = rand() % (i + 1);
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
         
        void *DrawMapQuarter(void *threadid) {  
          int x, y;
          long tid = (long)threadid;
          FIBITMAP * img;
          RGBQUAD rgb;
          int world[SIZE / 2][SIZE / 2];
          memset(world, 0, sizeof world);
          // set the seed
          world[0][0] = 1;
         
          printf("%ld here \n", tid);
          draw_brownian_tree(world);
          printf("%ld here 2 \n", tid);
         
          img = FreeImage_Allocate(SIZE / 2, SIZE / 2, 32, 0, 0, 0);
         
          for (y = 0; y < SIZE / 2; y++){
            for (x = 0; x < SIZE / 2; x++){
              rgb.rgbRed = rgb.rgbGreen = rgb.rgbBlue = (world[y][x] ? 255 : 0);
              FreeImage_SetPixelColor(img, x, y, &rgb);
            }
          }
          char file[100] = "brownian_tree";
          char s_tid[10];
          sprintf(s_tid,"%ld", tid);
          strcat(file, s_tid);
          strcat(file, ".bmp");
          FreeImage_Save(FIF_BMP, img, file, 0);
          FreeImage_Unload(img);
         
          pthread_exit(NULL);
        }
         
        int main(){
          pthread_t threads[4];
          long t;
          int rc;
          srand((unsigned)time(NULL));
         
          for (t = 0; t < 4; t++) {
            rc = pthread_create(&threads[t], NULL, DrawMapQuarter, (void *)t);
            if (rc) {
              printf("ERROR; return code from pthread_create() is %d\n", rc);
              exit(-1);
            }
          }
         
          pthread_exit(NULL);
        }


