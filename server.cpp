#include <iostream>
#include <string>
#include <vector>
#include "InterfaceRPC.h"
#include "server.h"

#pragma comment (lib, "rpcrt4.lib")

using namespace std;

int main()
{
	cout << "Server is listening." << endl;

	RPC_STATUS status;

	// Использует протокол в сочетании с конечной точкой для приема удаленных вызовов процедур
	status = RpcServerUseProtseqEp((RPC_WSTR)L"ncacn_ip_tcp", RPC_C_PROTSEQ_MAX_REQS_DEFAULT, (RPC_WSTR)L"9000", NULL);

	if (status) exit(status);
	                                                                    // принуд. обработчик безопасности     // исп. стандартн. кол-во одновр. вызовов    // Бесконечный максимальный размер входных блоков данных
	status = RpcServerRegisterIf2(InterfaceRPC_v1_0_s_ifspec, NULL, NULL, RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH, RPC_C_LISTEN_MAX_CALLS_DEFAULT, (unsigned)-1, SecurityCallback);

	if (status) exit(status);

	// Начинаем слушать удаленные вызовы процедур для всех зарегистрированных интерфейсов.
	// Этот вызов не вернет управление до тех пор, пока не будет вызвано RpcMgmtStopServerListening.
	                         //мин.колво потоков //макс         //слушать сейчас
	status = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, FALSE);

	if (status) exit(status);
}

// Простой обработчик безопасности
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE /*hInterface*/, void* /*pBindingHandle*/)
{
	return RPC_S_OK; // Always allow anyone.
}

void* __RPC_USER midl_user_allocate(size_t size)
{
	return malloc(size);
}

void __RPC_USER midl_user_free(void* p)
{
	free(p);
}

void GetLoginPass(handle_t hBinding, const unsigned char* login, const unsigned char* Password, int* ret_code)
{
	if (!LogonUserA((LPCSTR)login, NULL, (LPCSTR)Password, LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hTokenUser))
	{
		cout << "LogonUser fails: " << GetLastError() << endl;
		*ret_code = -1;
		return;
	}
}

void PreDownloadFile(handle_t hBinding, const unsigned char* Filename, int* szFile)
{
	FILE* file = NULL;
	fopen_s(&file, (const char*)Filename, "rb");
	if (file == NULL)
	{
		*szFile = -1;
		return;
	}
	fseek(file, 0, SEEK_END);
	*szFile = ftell(file);
	fclose(file);
}

void DownloadFile(handle_t hBinding, const unsigned char* Filename, int* len, byte* downBuf, int* ret_code)
{
	//TOKEN_PRIVILEGES privileges;
	//GetTokenInformation(hTokenUser, TokenPrivileges, &privileges, sizeof(TOKEN_PRIVILEGES), NULL);
	if (!ImpersonateLoggedOnUser(hTokenUser))
	{
		cout << "ImpersonateLoggedOnUser fails: " << GetLastError();
		*ret_code = -1;
		return;
	}

	FILE* file = NULL;
	fopen_s(&file, (const char*)Filename, "rb");
	if (file == NULL)
	{
		*ret_code = -1;
		RevertToSelf();
		return;
	}
	if ((*len) != (fread(downBuf, sizeof(byte), *len, file)))
	{
		*ret_code = -1;
		fclose(file);
		RevertToSelf();
		return;
	}
	RevertToSelf();
	fclose(file);
}

void UploadFile(handle_t hBinding, const unsigned char* Filename, int* len, byte* upBuf, int* ret_code)
{
	if (!ImpersonateLoggedOnUser(hTokenUser))
	{
		cout << "ImpersonateLoggedOnUser fails: " << GetLastError();
		*ret_code = -1;
		return;
	}

	FILE* file = NULL;
	fopen_s(&file, (const char*)Filename, "wb");
	if (file == NULL)
	{
		*ret_code = -1;
		RevertToSelf();
		return;
	}
	if ((*len) != (fwrite(upBuf, sizeof(byte), *len, file)))
	{
		*ret_code = -1;
		fclose(file);
		RevertToSelf();
		return;
	}
	fclose(file);
	RevertToSelf();
}

void RemoveFile(handle_t hBinding, const unsigned char* Filename, int* ret_code)
{
	if (0 != remove((const char*)Filename))
		*ret_code = -1;
	else
		*ret_code = 0;
}

void LogOut(handle_t hBinding)
{
	CloseHandle(hTokenUser);
}
