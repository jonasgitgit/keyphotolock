#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char take_a_picture[100];
  strcpy(take_a_picture, "ffmpeg -f v4l2 -i /dev/video0 -ss 00:00:02 -frames:v 1 photo.jpg &> /dev/null");
  system(take_a_picture);
  return 0;
}

