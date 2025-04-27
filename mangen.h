#ifndef __MANGEN__
#define __MANGEN__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

#define VERSION "1.0"
#define AUTHOR "Tim Surkov"
#define CURRENT_DIR "."
#define MAX_LEN_NAME 1024
#define FILE_BUFFER_SIZE 8192
const unsigned long DJB2 =  5381;

void print_info();
void print_manual();
void processing_options(int argc, const char* argv[], char* dir_path);
void generate_manifest(char* abs_path, char* rel_path);
unsigned long calculating_hash(char* abs_path);

#endif
