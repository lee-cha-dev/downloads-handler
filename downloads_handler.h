//
// Created by KCHAR on 10/16/2023.
//

#ifndef DOWNLOADS_HANDLER_DOWNLOADS_HANDLER_H
#define DOWNLOADS_HANDLER_DOWNLOADS_HANDLER_H

#include <stdio.h>
#include <shlobj.h>
#include <dirent.h>

// REFER TO GETTING THE DOWNLOADS FOLDER IN C

int start_downloads_handler();
void make_dir(const char* current_dir, char* dir_name);

#endif //DOWNLOADS_HANDLER_DOWNLOADS_HANDLER_H
