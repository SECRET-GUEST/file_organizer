#include <json-c/json.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "translate/translator.h"
#define TRANSLATION_PATH "src/translate/locale/"


const char* translate(const char* key) {
    char* lang_env = getenv("LANG"); // Retrieve system's locale.
    char lang[3];
    if(lang_env != NULL && strlen(lang_env) >= 2) {
        // Extracts the language code from LANG variable.
        strncpy(lang, lang_env, 2);
        lang[2] = '\0';
    } else {
        strcpy(lang, "en");  // Default to English if LANG is not set.
    }

    char filepath[100];
    // Constructs the filepath to the JSON language file based on the language code.
    snprintf(filepath, sizeof(filepath), TRANSLATION_PATH "%s.json", lang);

    FILE *fp = fopen(filepath, "r"); // Try opening the corresponding language file.
    if (fp == NULL && strcmp(lang, "en") != 0) 
        return translate("en");  // If the file can’t be opened, tries with English.

    if(fp == NULL)
        return NULL;

    // Finding the length of the file content.
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Reading the file content into a string.
    char* content = malloc(length);
    fread(content, 1, length, fp);
    fclose(fp);

    // Parsing the JSON string.
    struct json_object *parsed_json = json_tokener_parse(content);

    char* section = strtok(strdup(key), "."); // "sorter_gui"
    char* txt_key = strtok(NULL, "."); // "txt1"

    struct json_object *section_obj;
    json_object_object_get_ex(parsed_json, section, &section_obj); // Retrieves the section object from the JSON

    struct json_object *text;
    json_object_object_get_ex(section_obj, txt_key, &text);  // Retrieves the translation for the provided key.

    const char* result = json_object_get_string(text);  // Getting the string from JSON object.
    free(content);  // Don’t forget to free the allocated memory.

    return result;
}
