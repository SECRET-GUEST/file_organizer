#ifndef SORTER_H
#define SORTER_H

void processDirectory(const char *inputPath, const char *outputPath);
int removeEmptyDirectories(const char *path);

#endif //SORTER_H

int initialize_sorter(const char *inputDirectory, const char *outputDirectory);
