//
// Created by KCHAR on 10/16/2023.
//

#include "downloads_handler.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <winbase.h>
#include <sys/stat.h>


void make_dir(const char* current_dir, char* dir_name){
    char new_dir[MAX_PATH] = "";
    strcat(new_dir, current_dir);
    strcat(new_dir, dir_name);

    int check;

    check = mkdir(new_dir);

    if(!check){
        printf("Directory has been successfully created!");
    }
}

// NEED TO CREATE A LOGGER CLASS THAT WILL SAVE ALL LOGS TO A BUFFER AND THEN
// WRITE IT TO A TEXT FILE TITLE THE DATE_TIME_LOG_FILE.TXT
void copy_file(char *src, char *dst){
    BOOL copied_file;
    BOOL deleted_file;

    BOOL bFailIfExists;
    copied_file = CopyFile(src, dst, bFailIfExists);
    if (copied_file == FALSE){
        printf("\nCopyFileError::%lu\tsource: %s\tdestination: %s\n\n", GetLastError(), src, dst);
    } else {
        // FILE WAS COPIED, THE OLD FILE CAN BE DELETED
        deleted_file = DeleteFile(src);
        if (deleted_file == FALSE){
            printf("DeleteFileError::%lu\n", GetLastError());
            printf("Source: %s\tDestination: %s", src, dst);
        } else {
            printf("Success::File Was Moved to: %s\n", dst);
        }
    }
}

int start_downloads_handler(){
    printf("\nStarting Downloads Organizer\n\n");

    // SET POINTER FOR THE DIRECTORY
    DIR *dir;

    // SET THE USERNAME AND THE DOWNLOADS PART OF THE PATH
    char *username = getenv("USERNAME");
    char *dls = "/Downloads/";

    // BUFFER FOR FULL PATH
    char path[MAX_PATH] = "C:/Users/";

    // CONCAT THE STRING TOGETHER
    strcat(path, username);
    strcat(path, dls);

    // CREATE THE DIRECTORIES FOR ORGANIZING THE DLS FOLDER IF THEY DO NOT EXIST
    make_dir(path, "_archives");
    make_dir(path, "_images");
    make_dir(path, "_video_files");
    make_dir(path, "_installers");
    make_dir(path, "_microsoft_files");
    make_dir(path, "_exe_files");
    make_dir(path, "_pdf_files");
    make_dir(path, "_programming_files");
    make_dir(path, "_ico_files");
    make_dir(path, "_other_files");

    // OPEN THE PATH TO ACCESS THE DIRECTORY
    dir = opendir(path);

    // AREA WHERE THE SORTING LOGIC WILL OCCUR
    if (dir){
        struct dirent *d;
        int index = 0;
        while((d = readdir(dir)) != NULL){
            ++index;

            char *file = strlwr(d->d_name);

            // SET THE FILE PATH
            char file_path[500] = "";
            strcat(file_path, path);
            strcat(file_path, file);

            // SET THE SOURCE AND DESTINATION PATHS
            char src[MAX_PATH] = {};
            char dst[MAX_PATH] = {};

            strcat(src, file_path);
            strcpy(dst, "C:Users/");
            strcat(dst, username);

            // ACCESS THE FILE TYPE AND MOVE IT TO THE ASSOCIATED FOLDER
            if(strstr(d->d_name, ".exe")){
                strcat(dst, "/Downloads/_exe_files/");

                // CHECK FOR PDFS
            } else if (strstr(d->d_name, ".pdf")){
                strcat(dst, "/Downloads/_pdf_files/");

                // CHECK FOR ARCHIVES
            } else if (strstr(d->d_name, ".zip") || strstr(d->d_name, ".rar") || strstr(d->d_name, ".7z")) {
                strcat(dst, "/Downloads/_archives/");

                // CHECK FOR IMAGE FILES
            } else if (
                    strstr(d->d_name, ".jpg") || strstr(d->d_name, ".png") ||
                    strstr(d->d_name, ".jpeg") || strstr(d->d_name, ".webp") ||
                    strstr(d->d_name, ".avi"))
            {
                strcat(dst, "/Downloads/_images/");

                // CHECK FOR MICROSOFT DOCUMENTS
            } else if (
                strstr(d->d_name, ".doc") || strstr(d->d_name, ".docx") ||
                strstr(d->d_name, ".pptx") || strstr(d->d_name, ".xlsx") ||
                strstr(d->d_name, ".pub") || strstr(d->d_name, ".accdb") ||
                strstr(d->d_name, ".accde") || strstr(d->d_name, ".accdr") ||
                strstr(d->d_name, ".accdt") || strstr(d->d_name, ".aif") ||
                strstr(d->d_name, ".docm") || strstr(d->d_name, ".dot") ||
                strstr(d->d_name, ".dotx") || strstr(d->d_name, ".eml") ||
                strstr(d->d_name, ".pot") || strstr(d->d_name, ".potm") ||
                strstr(d->d_name, ".potx") || strstr(d->d_name, ".ppam") ||
                strstr(d->d_name, ".pps") || strstr(d->d_name, ".ppsm") ||
                strstr(d->d_name, ".sldm") || strstr(d->d_name, ".sldx") ||
                strstr(d->d_name, ".vsd") || strstr(d->d_name, ".txt") ||
                strstr(d->d_name, ".vsdm") || strstr(d->d_name, ".vsdx") ||
                strstr(d->d_name, ".vss") || strstr(d->d_name, ".vssm") ||
                strstr(d->d_name, ".vst") || strstr(d->d_name, ".vstm") ||
                strstr(d->d_name, ".vstx") || strstr(d->d_name, ".wbk") ||
                strstr(d->d_name, ".wks") || strstr(d->d_name, ".xls") ||
                strstr(d->d_name, ".xlsm") || strstr(d->d_name, ".xlt") ||
                strstr(d->d_name, ".xltm") || strstr(d->d_name, ".xltx") ||
                strstr(d->d_name, ".xps")
            ){
                strcat(dst, "/Downloads/_microsoft_files/");

                // CHECK FOR MSI/INSTALLER FILES
            } else if (strstr(d->d_name, ".msi")){
                strcat(dst, "/Downloads/_installers/");

                // CHECK FOR PROGRAMMING FILES
            } else if (
                    strstr(d->d_name, ".c") || strstr(d->d_name, ".h") || strstr(d->d_name, ".cs") ||
                    strstr(d->d_name, ".py") || strstr(d->d_name, ".html") || strstr(d->d_name, ".css") ||
                    strstr(d->d_name, ".js") || strstr(d->d_name, ".cs") || strstr(d->d_name, ".cpp") ||
                    strstr(d->d_name, ".dll") || strstr(d->d_name, ".cxx") || strstr(d->d_name, ".asm") ||
                    strstr(d->d_name, ".hpp") || strstr(d->d_name, ".java") || strstr(d->d_name, ".jar") ||
                    strstr(d->d_name, ".pl") || strstr(d->d_name, ".ps") || strstr(d->d_name, ".scp") ||
                    strstr(d->d_name, ".sh") || strstr(d->d_name, ".acsm") || strstr(d->d_name, ".sql") ||
                    strstr(d->d_name, ".php"))
            {
                strcat(dst, "/Downloads/_programming_files/");

                // CHECK FOR ICO FILES
            } else if (strstr(d->d_name, ".ico")){
                strcat(dst, "/Downloads/_ico_files/");

                // ALL OTHER FILES ARE SORTED INTO OTHER
            } else if(
                    strstr(d->d_name, ".mp4") || strstr(d->d_name, ".mov") || strstr(d->d_name, ".avchd") ||
                    strstr(d->d_name, ".flv") || strstr(d->d_name, ".webm") || strstr(d->d_name, ".wmv") ||
                    strstr(d->d_name, ".avi") || strstr(d->d_name, ".mkv") || strstr(d->d_name, ".mpeg") ||
                    strstr(d->d_name, ".ogg") || strstr(d->d_name, ".mpg") || strstr(d->d_name, ".mp2") ||
                    strstr(d->d_name, ".mpe") || strstr(d->d_name, ".mpv") || strstr(d->d_name, ".m4p") ||
                    strstr(d->d_name, ".m4v") || strstr(d->d_name, ".qt") || strstr(d->d_name, ".swf")
            ){
                strcat(dst, "/Downloads/_video_files/");
            } else {
                strcat(dst, "/Downloads/_other_files/");
            }
            strcat(dst, file);

            struct stat s_path;
            stat(src, &s_path);
            int ret = S_ISREG(s_path.st_mode);

            // IF THE PATH ISN'T A DIRECTORY
            if (ret != 0){
                // CALL COPY FILE TO COPY TO THE NEW DIR AND DELETE THE FILE FROM THE PREVIOUS DIR
                copy_file(src, dst);
            }
        }
        closedir(dir);

        free(d);
        d = nullptr;
    } else {
        printf("No directory found..\n");
    }

    printf("\nDownloads Organizer Has Finished!\n");

    free(dir);
    dir = nullptr;

    return 1;
}