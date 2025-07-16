#include "reader.h"
#include "output.h"

int main (int argc, char *argv[]) {
  
  if (argc < 2) {
    printf("No file provided\n");
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  read_file(argv[1]);

  ClassFile * class_file = read_class_file();
  pushToClassFileList(class_file);

  if (argc > 2) {
    if (strcmp(argv[2], "-show") == 0) {
      print_class_file(class_file);

      free_class_file(class_file);
      free_buffer();
      return 0;
    }
  }

  run_class_file(class_file);

  free_class_file(class_file);
  free_buffer();
  
  return 0;
}