#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {
  int rand = open("/dev/random", O_RDONLY);
  unsigned int arr[10];
  int i = 0;

  printf("Generating random numbers:\n\n");
  for (int i = 0; i < 10; i ++) {
    if (rand < 0) i -= 1;
    else {
      unsigned int temp;
      int result = read(rand, &temp, sizeof(temp));
      if (result < 0) {
        printf("%s\n", strerror(errno));
        return -1;
      }
      else {
        arr[i] = temp;
        printf("\trandom %d: %u\n", i, temp);
      }
    }
  }


  printf("\n\nWriting numbers to file...\n");
  int file = open("rand_num.txt", O_WRONLY | O_EXCL | O_CREAT, 0644);
  if (file < 0) {
    printf("%s\n", strerror(errno));
    return -1;
  }
  

  printf("\n\nReading numbers from file...\n");




}
