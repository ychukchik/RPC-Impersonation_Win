

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for InterfaceRPC.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __InterfaceRPC_h_h__
#define __InterfaceRPC_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __InterfaceRPC_INTERFACE_DEFINED__
#define __InterfaceRPC_INTERFACE_DEFINED__

/* interface InterfaceRPC */
/* [version][uuid] */ 

void GetLoginPass( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const unsigned char *login,
    /* [string][in] */ const unsigned char *Password,
    /* [out][in] */ int *ret_code);

void LogOut( 
    /* [in] */ handle_t hBinding);

void PreDownloadFile( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const unsigned char *Filename,
    /* [out][in] */ int *szFile);

void DownloadFile( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const unsigned char *Filename,
    /* [in] */ int *len,
    /* [size_is][out][in] */ byte *downBuf,
    /* [out][in] */ int *ret_code);

void UploadFile( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const unsigned char *Filename,
    /* [in] */ int *len,
    /* [size_is][out][in] */ byte *upBuf,
    /* [out][in] */ int *ret_code);

void RemoveFile( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const unsigned char *Filename,
    /* [out][in] */ int *ret_code);



extern RPC_IF_HANDLE InterfaceRPC_v1_0_c_ifspec;
extern RPC_IF_HANDLE InterfaceRPC_v1_0_s_ifspec;
#endif /* __InterfaceRPC_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


