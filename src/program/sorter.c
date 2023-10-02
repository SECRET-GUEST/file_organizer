#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "program/sorter.h"
#include "handlers/error_handler.h"
#include "../translate/translator.h"



// Function prototypes
int collectExtensions(const char *path, char ***extensions, int *count);
int createExtensionDirectories(const char *path, char **extensions, int count);
int organizeFiles(const char *inputPath, const char *outputPath);
int removeEmptyDirectories(const char *path);
int copyFile(const char *srcPath, const char *destPath);



// Main function to initialize and run the file sorter
int initialize_sorter(const char *inputDirectory, const char *outputDirectory) {
    // Try creating the output directory; return error if unsuccessful (except if directory already exists)
    if (mkdir(outputDirectory, 0777) == -1 && errno != EEXIST) {
        display_error_message(translate("sorter.txt6")); // Unable to create output directory
        return -1;
    }

    char **extensions = NULL;
    int count = 0;

    // Collect extensions, create directories based on extensions, organize files, and remove empty directories
    if (collectExtensions(inputDirectory, &extensions, &count) == -1) return -1;
    if (createExtensionDirectories(outputDirectory, extensions, count) == -1) return -1;
    if (organizeFiles(inputDirectory, outputDirectory) == -1) return -1;
    if (removeEmptyDirectories(inputDirectory) == -1) return -1;

    // Free dynamically allocated memory for extensions
    for (int i = 0; i < count; i++) 
        free(extensions[i]);
    free(extensions);
    
    return 0;
}



// Function to create directories based on file extensions
int createExtensionDirectories(const char *path, char **extensions, int count) {
    for (int i = 0; i < count; i++) {
        char *newDir;
        asprintf(&newDir, "%s/%s", path, extensions[i]);

        // Try creating a new directory for each extension; return error if unsuccessful (except if directory already exists)
        if (mkdir(newDir, 0777) == -1 && errno != EEXIST) {
            display_error_message(translate("sorter.txt7")); // Error creating directory
            free(newDir);
            return -1;
        }

        free(newDir);
    }
    return 0; 
}



// Function to collect unique file extensions from the given directory
int collectExtensions(const char *path, char ***extensions, int *count) {
    DIR *dir = opendir(path);
    // Return error if directory can't be opened
    if (!dir) {
        display_error_message(translate("sorter.txt8")); //Unable to open directory
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..' directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char *fullpath;
        asprintf(&fullpath, "%s/%s", path, entry->d_name);

        struct stat s;
        if (stat(fullpath, &s) == -1) {
            perror("stat");
            free(fullpath);
            continue;
        }

        // If directory, recursively collect extensions from it
        if (S_ISDIR(s.st_mode)) collectExtensions(fullpath, extensions, count);
        else if (S_ISREG(s.st_mode)) {
            char *ext = strrchr(entry->d_name, '.');
            if (ext && ext != entry->d_name) {
                ext++;

                int found = 0;
                // Check if the extension is already collected
                for (int i = 0; i < *count && !found; i++)
                    if (strcmp((*extensions)[i], ext) == 0) found = 1;

                // If not, add it to the list
                if (!found) {
                    *extensions = realloc(*extensions, (*count + 1) * sizeof(char *));
                    (*extensions)[*count] = strdup(ext);
                    (*count)++;
                }
            }
        }
        free(fullpath);
    }

    closedir(dir);
    return 0;
}





// Function to copy files from source path to destination path
int copyFile(const char *srcPath, const char *destPath) {
    // Open the source file in read-binary mode
    FILE *src = fopen(srcPath, "rb");
    if (!src) {
        display_error_message(translate("sorter.txt9")); // Error opening source file
        return -1;
    }

    // Open the destination file in write-binary mode
    FILE *dest = fopen(destPath, "wb");
    if (!dest) {
        display_error_message(translate("sorter.txt10")); // Error opening destination file
        fclose(src);
        return -1;
    }

    char buffer[8192];  // Buffer to hold data read from the source file
    size_t bytesRead;   // Number of bytes read from the source file
    // Loop to read and write data from source to destination file
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0)
        if (fwrite(buffer, 1, bytesRead, dest) != bytesRead) {
            display_error_message(translate("sorter.txt11")); // Error writing to file
            fclose(src);
            fclose(dest);
            return -1;
        }

    // Close the open files
    fclose(src);
    fclose(dest);
    return 0;
}







// Function to organize files from input path to output path based on file extensions
int organizeFiles(const char *inputPath, const char *outputPath) {
    // Open the input directory
    DIR *dir = opendir(inputPath);
    if (!dir) {
        display_error_message(translate("sorter.txt12")); //Impossible to open the directory
        return -1;
    }

    struct dirent *entry; // Structure to hold information about directory entries
    // Loop through each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..' directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char *fullInputPath;
        // Construct full path for each entry
        asprintf(&fullInputPath, "%s/%s", inputPath, entry->d_name);

        struct stat s;
        if (stat(fullInputPath, &s) == -1) {
            display_error_message(translate("sorter.txt13")); // Error retrieving file information
            free(fullInputPath);
            continue;
        }

        // If entry is a directory, recursively organize files within it
        if (S_ISDIR(s.st_mode)) {
            if (organizeFiles(fullInputPath, outputPath) == -1) {
                free(fullInputPath);
                continue;
            }
        } else if (S_ISREG(s.st_mode)) {
            // If entry is a regular file, organize it based on its extension
            char *ext = strrchr(entry->d_name, '.');
            if (ext && ext != entry->d_name) {
                ext++;

                char *extDir;
                // Construct directory name based on file extension
                asprintf(&extDir, "%s/%s", outputPath, ext);
                mkdir(extDir, 0777); // Create the extension directory

                char *newPath;
                // Construct new path for the file within the extension directory
                asprintf(&newPath, "%s/%s", extDir, entry->d_name);

                // Try renaming the file to move it; if fails, try copying it
                if (rename(fullInputPath, newPath) == -1) {
                    if (errno == EXDEV) {
                        if (copyFile(fullInputPath, newPath) == -1)
                            display_error_message(translate("sorter.txt15")); // Error copying the file
                    } else
                        display_error_message(translate("sorter.txt16")); //Error moving the file
                }

                free(extDir);
                free(newPath);
            }
        }
        free(fullInputPath);
    }

    closedir(dir); 
    return 0;
}







// Function to remove empty directories from the given path
int removeEmptyDirectories(const char *path) {
    // Open the directory
    DIR *dir = opendir(path);
    if (!dir) {
        display_error_message(translate("sorter.txt8")); //Unable to open directory
        return -1;
    }

    struct dirent *entry; // Structure to hold information about directory entries
    // Loop through each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..' directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char *fullpath;
        // Construct full path for each entry
        asprintf(&fullpath, "%s/%s", path, entry->d_name);

        struct stat s;
        if (stat(fullpath, &s) == -1) {
            display_error_message(translate("sorter.txt13")); // Error retrieving file information
            free(fullpath);
            continue;
        }

        // If entry is a directory, recursively remove empty directories within it
        if (S_ISDIR(s.st_mode)) {
            if (removeEmptyDirectories(fullpath) == -1) {
                free(fullpath);
                continue;
            }
            // Try removing the directory; return error if it's not empty
            if (rmdir(fullpath) == -1 && errno != ENOTEMPTY)
                display_error_message(translate("sorter.txt14")); //Unable to delete non-empty directory
        }

        free(fullpath);
    }

    closedir(dir); 
    return 0;
}
