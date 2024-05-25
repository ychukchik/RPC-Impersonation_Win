#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "InterfaceRPC.h"

HANDLE hTokenUser;
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE , void*);
void GetLoginPass(handle_t hBinding, const char* login, const char* Password, int* ret_code);
void LogOut(handle_t hBinding);
void PreDownloadFile(handle_t hBinding, const unsigned char* Filename, int* szFile);
void DownloadFile(handle_t hBinding, const unsigned char* Filename, int* len, byte* downBuf, int* ret_code);
void UploadFile(handle_t hBinding, const unsigned char* Filename, int* len, byte* upBuf, int* ret_code);
void RemoveFile(handle_t hBinding, const unsigned char* Filename, int* ret_code);