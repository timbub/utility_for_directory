#include "mangen.h"

int main(int argc, const char* argv[])
{
    char dir_path[MAX_LEN_NAME] = CURRENT_DIR;
    processing_options(argc, argv, dir_path);
    generate_manifest(dir_path, "");
    return 0;
}

void print_manual()
{
    printf("MANUAL:\n"
           "Description: generates a manifest (list of files with hashes) from the specified directory\n"
           "Use: ./mangen [DIR_PATH] [OPTIONS]\n"
           "Options:\n"
           "-h  manual and description of options\n"
           "-v  information about version and author\n");
}

void print_info()
{
    printf("INFO:\n"
           "VERSION %s\n"
           "AUTHOR  %s\n", VERSION, AUTHOR);
}
void processing_options(int argc, const char* argv[], char* dir_path)
{
    if (argc == 1) return;
    if (strcmp(argv[1], "-h") == 0)
    {
        print_manual();
        exit(0);
    } else if (strcmp(argv[1], "-v") == 0)
    {
        print_info();
        exit(0);
    } else
    {
        strncpy(dir_path, argv[1], MAX_LEN_NAME);
        dir_path[MAX_LEN_NAME - 1] = '\0';      //if size argv more than size dir path
    }
}

void generate_manifest(char* abs_path, char* rel_path)
{
    DIR* dir = opendir(abs_path);
    if (dir == NULL)
    {
        fprintf(stderr, "ERROR: directory %s not open\n", abs_path);
        exit(1);
    }
    char nabs_path[MAX_LEN_NAME] = {0};           //absolute path for search
    char nrel_path[MAX_LEN_NAME] = {0};           //relative path for output
    struct dirent* entry = NULL;                  //struct save name and type file/directory
    struct stat    buf   = {0};                  //for check if file or directory

    //processing files
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(nabs_path, sizeof(nabs_path), "%s/%s", abs_path, entry->d_name); //create absolute path
        if(lstat(nabs_path, &buf) == -1)
        {
            fprintf(stderr, "ERROR: info about %s not load\n", entry->d_name);
            continue;
        }

        if (S_ISREG(buf.st_mode))    //if it file
        {
            if (rel_path[0] == '\0')
            {
                snprintf(nrel_path, sizeof(nrel_path), "%s", entry->d_name);
            } else
            {
                snprintf(nrel_path, sizeof(nrel_path), "%s/%s", rel_path, entry->d_name);
            }
            unsigned long hash = calculating_hash(nabs_path);
            printf("%s : %lX\n", nrel_path, hash);
        }
    }
    //processing directory
    rewinddir(dir);
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        snprintf(nabs_path, sizeof(nabs_path), "%s/%s", abs_path, entry->d_name);

        if (lstat(nabs_path, &buf) == -1) {
            fprintf(stderr, "ERROR: info about %s not load\n", entry->d_name);
            continue;
        }

        if (S_ISDIR(buf.st_mode))
        {
            if (rel_path[0] == '\0')
            {
                snprintf(nrel_path, sizeof(nrel_path), "%s", entry->d_name);
            } else
            {
                snprintf(nrel_path, sizeof(nrel_path), "%s/%s", rel_path, entry->d_name);
            }
            generate_manifest(nabs_path, nrel_path);
        }
    }
    closedir(dir);
}

unsigned long calculating_hash(char* abs_path)
{
    FILE* file = fopen(abs_path, "rb");
    if (!file) {
        fprintf(stderr, "ERROR: failed to open file\n");
        return 0;
    }

    unsigned char buffer[FILE_BUFFER_SIZE] = {0};
    size_t bytes_read = 0;

    unsigned long hash = DJB2;
    while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0)
    {
        for (size_t i = 0; i < bytes_read; i++)
        {
            hash = ((hash << 5) + hash) + buffer[i];
        }
    }
    fclose(file);
    return hash;
}

