#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {
  int rand = open("/dev/random", O_RDONLY);
  unsigned int arr[10];
  int i = 0;
  int result = 0;

  printf("Generating random numbers:\n");
  for (int i = 0; i < 10; i ++) {
    if (rand < 0) i -= 1;
    else {
      unsigned int temp;
      result = read(rand, &temp, sizeof(temp));
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


  printf("\nWriting numbers to file...\n");
  int file = open("rand_num.txt", O_WRONLY | O_EXCL | O_CREAT, 0644);
  if (file < 0) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  result = write(file, arr, sizeof(arr));
  if (result < 0) {
    printf("%s\n", strerror(errno));
    return -1;
  }


  printf("\nReading numbers from file...\n");
  file = open("rand_num.txt", O_RDONLY);
  if (file < 0) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  unsigned int arr1[10];
  result = read(file, arr1, sizeof(arr1));
  if (result < 0) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  printf("\nVerification that written values were the same:\n");
  for (int i = 0; i < 10; i ++) {
    printf("\trandom %d: %u\n", i, arr1[i]);
  }

  return 0;

}
