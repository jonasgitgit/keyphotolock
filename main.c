#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
  struct input_event  {
    struct timeval time;
    unsigned short type; 
    unsigned short code; 
    unsigned int value;   
  };

  struct input_event ev;
  const char *dev= "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
  const char *photo = "ffmpeg -f v4l2 -i /dev/video0 -ss 00:00:02 -frames:v 1 keypht.jpg &> /dev/null";
  const char *lock = "slock";
  ssize_t n;
  char take_a_picture[strlen(photo) + 1];
  
  int open_event_kbd;
  open_event_kbd = open(dev, O_RDONLY);

  if (open_event_kbd == -1){
    return EXIT_FAILURE;
  }
  else{
    printf("keyphotolock running...\n");
  }

  while (1) {
    n = read(open_event_kbd, &ev, sizeof ev);
    if (ev.type == EV_KEY && ev.value == 1){
      if (system(photo) != 0){
        fprintf(stderr, "fail picture\n");
      }
      if (system(lock) !=0){
        fprintf(stderr, "fail lock\n");
      }
    }
      if (ev.value == 1){
        break;
      }
    }

  close(open_event_kbd);
  fflush(stdout);

  return 0;
}

