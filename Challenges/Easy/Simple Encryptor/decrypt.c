#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Open encrypted file
  FILE *fp = fopen("flag.enc", "rb");

  // Read seed value
  uint32_t seed;
  fread(&seed, sizeof(seed), 1, fp);

  // Get file_size - seed value size (4 bytes) and allocate memory
  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp) - sizeof(seed);
  uint8_t *buffer = malloc(file_size);

  // Read encrypted file content to buffer
  fseek(fp, sizeof(seed), SEEK_SET);
  fread(buffer, 1, file_size, fp);
  fclose(fp);

  // Set seed value for rand()
  srand(seed);
  for (int i = 0; i < file_size; i++) {
    // generate random numbers like encrypt binary
    int rand_num_xor = rand();
    int rand_num_bitshift = rand();
    int shift_num = rand_num_bitshift & 7;

    // Reverse bit shifting and xor
    buffer[i] = (buffer[i] >> shift_num) | (buffer[i] << (8 - shift_num));
    buffer[i] = buffer[i] ^ rand_num_xor;
  }

  // Print result
  printf("%s\n", buffer);
  free(buffer);

  return 0;
}
