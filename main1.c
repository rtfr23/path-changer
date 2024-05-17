#include <stdio.h>
#include "strings.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PATHS 10
#define MAX_PATH_LENGTH 260

bool is_valid_path(const char *path)
{
    const char *invalid_chars = "<>\"/|?*";
    while (*path)
    {
        if (schr(invalid_chars, *path))
        {
            return false;
        }
        path++;
    }
    return true;
}

bool is_windows_path(const char *path)
{
    if (slen(path) < 3)
        return false;
    if (!isalpha(path[0]) || path[1] != ':' || path[2] != '\\')
        return false;

    for (const char *p = path + 3; *p; p++)
    {
        if (*p == '/' || schr("<>\"|?*", *p))
        {
            return false;
        }
    }
    return true;
}

void update_paths(char *paths[], int paths_count, const char *dir1, const char *dir2)
{
    size_t dir1_len = slen(dir1);
    for (int i = 0; i < paths_count; i++)
    {
        if (sncmp(paths[i], dir1, dir1_len) == 0)
        {
            char new_path[MAX_PATH_LENGTH];
            snprintf(new_path, MAX_PATH_LENGTH, "%s%s", dir2, paths[i] + dir1_len);
            sncpy(paths[i], new_path, MAX_PATH_LENGTH);
        }
    }
}

int main()
{
    char delim[10], paths_input[MAX_PATH_LENGTH * MAX_PATHS], dir1[MAX_PATH_LENGTH], dir2[MAX_PATH_LENGTH];

    printf("delim: ");
    fgets(delim, sizeof(delim), stdin);
    delim[scspn(delim, "\n")] = '\0';

    printf("path: ");
    fgets(paths_input, sizeof(paths_input), stdin);
    paths_input[scspn(paths_input, "\n")] = '\0';

    printf("dir1: ");
    fgets(dir1, sizeof(dir1), stdin);
    dir1[scspn(dir1, "\n")] = '\0';

    printf("dir2: ");
    fgets(dir2, sizeof(dir2), stdin);
    dir2[scspn(dir2, "\n")] = '\0';

    char *paths[MAX_PATHS];
    int paths_count = 0;

    char *token = stok(paths_input, delim);
    while (token != NULL && paths_count < MAX_PATHS)
    {
        if (!is_valid_path(token) || !is_windows_path(token))
        {
            fprintf(stderr, "Error: Invalid path.\n");
            return 1;
        }
        paths[paths_count] = malloc(MAX_PATH_LENGTH);
        sncpy(paths[paths_count], token, MAX_PATH_LENGTH);
        paths_count++;
        token = stok(NULL, delim);
    }

    update_paths(paths, paths_count, dir1, dir2);

    printf("new paths: ");
    for (int i = 0; i < paths_count; i++)
    {
        printf("%s", paths[i]);
        if (i < paths_count - 1)
        {
            printf("%s", delim);
        }
        free(paths[i]);
    }
    printf("\n");

    return 0;
}
