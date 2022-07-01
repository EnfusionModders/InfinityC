#include "infinity.h"

#if defined(_WIN64)

#include <Windows.h>
#define EXPORT __declspec(dllexport)

#pragma region Proxy
struct secur32_dll {
	HMODULE dll;
	FARPROC oAcceptSecurityContext;
	FARPROC oAcquireCredentialsHandleA;
	FARPROC oAcquireCredentialsHandleW;
	FARPROC oAddCredentialsA;
	FARPROC oAddCredentialsW;
	FARPROC oAddSecurityPackageA;
	FARPROC oAddSecurityPackageW;
	FARPROC oApplyControlToken;
	FARPROC oChangeAccountPasswordA;
	FARPROC oChangeAccountPasswordW;
	FARPROC oCloseLsaPerformanceData;
	FARPROC oCollectLsaPerformanceData;
	FARPROC oCompleteAuthToken;
	FARPROC oCredMarshalTargetInfo;
	FARPROC oCredUnmarshalTargetInfo;
	FARPROC oDecryptMessage;
	FARPROC oDeleteSecurityContext;
	FARPROC oDeleteSecurityPackageA;
	FARPROC oDeleteSecurityPackageW;
	FARPROC oEncryptMessage;
	FARPROC oEnumerateSecurityPackagesA;
	FARPROC oEnumerateSecurityPackagesW;
	FARPROC oExportSecurityContext;
	FARPROC oFreeContextBuffer;
	FARPROC oFreeCredentialsHandle;
	FARPROC oGetComputerObjectNameA;
	FARPROC oGetComputerObjectNameW;
	FARPROC oGetSecurityUserInfo;
	FARPROC oGetUserNameExA;
	FARPROC oGetUserNameExW;
	FARPROC oImpersonateSecurityContext;
	FARPROC oImportSecurityContextA;
	FARPROC oImportSecurityContextW;
	FARPROC oInitSecurityInterfaceA;
	FARPROC oInitSecurityInterfaceW;
	FARPROC oInitializeSecurityContextA;
	FARPROC oInitializeSecurityContextW;
	FARPROC oLsaCallAuthenticationPackage;
	FARPROC oLsaConnectUntrusted;
	FARPROC oLsaDeregisterLogonProcess;
	FARPROC oLsaEnumerateLogonSessions;
	FARPROC oLsaFreeReturnBuffer;
	FARPROC oLsaGetLogonSessionData;
	FARPROC oLsaLogonUser;
	FARPROC oLsaLookupAuthenticationPackage;
	FARPROC oLsaRegisterLogonProcess;
	FARPROC oLsaRegisterPolicyChangeNotification;
	FARPROC oLsaUnregisterPolicyChangeNotification;
	FARPROC oMakeSignature;
	FARPROC oOpenLsaPerformanceData;
	FARPROC oQueryContextAttributesA;
	FARPROC oQueryContextAttributesW;
	FARPROC oQueryCredentialsAttributesA;
	FARPROC oQueryCredentialsAttributesW;
	FARPROC oQuerySecurityContextToken;
	FARPROC oQuerySecurityPackageInfoA;
	FARPROC oQuerySecurityPackageInfoW;
	FARPROC oRevertSecurityContext;
	FARPROC oSaslAcceptSecurityContext;
	FARPROC oSaslEnumerateProfilesA;
	FARPROC oSaslEnumerateProfilesW;
	FARPROC oSaslGetContextOption;
	FARPROC oSaslGetProfilePackageA;
	FARPROC oSaslGetProfilePackageW;
	FARPROC oSaslIdentifyPackageA;
	FARPROC oSaslIdentifyPackageW;
	FARPROC oSaslInitializeSecurityContextA;
	FARPROC oSaslInitializeSecurityContextW;
	FARPROC oSaslSetContextOption;
	FARPROC oSealMessage;
	FARPROC oSeciAllocateAndSetCallFlags;
	FARPROC oSeciAllocateAndSetIPAddress;
	FARPROC oSeciFreeCallContext;
	FARPROC oSecpFreeMemory;
	FARPROC oSecpTranslateName;
	FARPROC oSecpTranslateNameEx;
	FARPROC oSetContextAttributesA;
	FARPROC oSetContextAttributesW;
	FARPROC oSetCredentialsAttributesA;
	FARPROC oSetCredentialsAttributesW;
	FARPROC oSspiCompareAuthIdentities;
	FARPROC oSspiCopyAuthIdentity;
	FARPROC oSspiDecryptAuthIdentity;
	FARPROC oSspiEncodeAuthIdentityAsStrings;
	FARPROC oSspiEncodeStringsAsAuthIdentity;
	FARPROC oSspiEncryptAuthIdentity;
	FARPROC oSspiExcludePackage;
	FARPROC oSspiFreeAuthIdentity;
	FARPROC oSspiGetTargetHostName;
	FARPROC oSspiIsAuthIdentityEncrypted;
	FARPROC oSspiLocalFree;
	FARPROC oSspiMarshalAuthIdentity;
	FARPROC oSspiPrepareForCredRead;
	FARPROC oSspiPrepareForCredWrite;
	FARPROC oSspiUnmarshalAuthIdentity;
	FARPROC oSspiValidateAuthIdentity;
	FARPROC oSspiZeroAuthIdentity;
	FARPROC oTranslateNameA;
	FARPROC oTranslateNameW;
	FARPROC oUnsealMessage;
	FARPROC oVerifySignature;
} secur32;

FARPROC PA = NULL;

void jmpRAX();
asm(
    ".section .text\n\t"
    "jmpRAX:\n\t"
    "jmpq %rax"
    );



EXPORT void AcceptSecurityContext() { PA = secur32.oAcceptSecurityContext; jmpRAX(); }
EXPORT void AcquireCredentialsHandleA() { PA = secur32.oAcquireCredentialsHandleA; jmpRAX(); }
EXPORT void AcquireCredentialsHandleW() { PA = secur32.oAcquireCredentialsHandleW; jmpRAX(); }
EXPORT void AddCredentialsA() { PA = secur32.oAddCredentialsA; jmpRAX(); }
EXPORT void AddCredentialsW() { PA = secur32.oAddCredentialsW; jmpRAX(); }
EXPORT void AddSecurityPackageA() { PA = secur32.oAddSecurityPackageA; jmpRAX(); }
EXPORT void AddSecurityPackageW() { PA = secur32.oAddSecurityPackageW; jmpRAX(); }
EXPORT void ApplyControlToken() { PA = secur32.oApplyControlToken; jmpRAX(); }
EXPORT void ChangeAccountPasswordA() { PA = secur32.oChangeAccountPasswordA; jmpRAX(); }
EXPORT void ChangeAccountPasswordW() { PA = secur32.oChangeAccountPasswordW; jmpRAX(); }
EXPORT void CloseLsaPerformanceData() { PA = secur32.oCloseLsaPerformanceData; jmpRAX(); }
EXPORT void CollectLsaPerformanceData() { PA = secur32.oCollectLsaPerformanceData; jmpRAX(); }
EXPORT void CompleteAuthToken() { PA = secur32.oCompleteAuthToken; jmpRAX(); }
EXPORT void CredMarshalTargetInfo() { PA = secur32.oCredMarshalTargetInfo; jmpRAX(); }
EXPORT void CredUnmarshalTargetInfo() { PA = secur32.oCredUnmarshalTargetInfo; jmpRAX(); }
EXPORT void DecryptMessage() { PA = secur32.oDecryptMessage; jmpRAX(); }
EXPORT void DeleteSecurityContext() { PA = secur32.oDeleteSecurityContext; jmpRAX(); }
EXPORT void DeleteSecurityPackageA() { PA = secur32.oDeleteSecurityPackageA; jmpRAX(); }
EXPORT void DeleteSecurityPackageW() { PA = secur32.oDeleteSecurityPackageW; jmpRAX(); }
EXPORT void EncryptMessage() { PA = secur32.oEncryptMessage; jmpRAX(); }
EXPORT void EnumerateSecurityPackagesA() { PA = secur32.oEnumerateSecurityPackagesA; jmpRAX(); }
EXPORT void EnumerateSecurityPackagesW() { PA = secur32.oEnumerateSecurityPackagesW; jmpRAX(); }
EXPORT void ExportSecurityContext() { PA = secur32.oExportSecurityContext; jmpRAX(); }
EXPORT void FreeContextBuffer() { PA = secur32.oFreeContextBuffer; jmpRAX(); }
EXPORT void FreeCredentialsHandle() { PA = secur32.oFreeCredentialsHandle; jmpRAX(); }
EXPORT void GetComputerObjectNameA() { PA = secur32.oGetComputerObjectNameA; jmpRAX(); }
EXPORT void GetComputerObjectNameW() { PA = secur32.oGetComputerObjectNameW; jmpRAX(); }
EXPORT void GetSecurityUserInfo() { PA = secur32.oGetSecurityUserInfo; jmpRAX(); }
EXPORT void GetUserNameExA() { PA = secur32.oGetUserNameExA; jmpRAX(); }
EXPORT void GetUserNameExW() { PA = secur32.oGetUserNameExW; jmpRAX(); }
EXPORT void ImpersonateSecurityContext() { PA = secur32.oImpersonateSecurityContext; jmpRAX(); }
EXPORT void ImportSecurityContextA() { PA = secur32.oImportSecurityContextA; jmpRAX(); }
EXPORT void ImportSecurityContextW() { PA = secur32.oImportSecurityContextW; jmpRAX(); }
EXPORT void InitSecurityInterfaceA() { PA = secur32.oInitSecurityInterfaceA; jmpRAX(); }
EXPORT void InitSecurityInterfaceW() { PA = secur32.oInitSecurityInterfaceW; jmpRAX(); }
EXPORT void InitializeSecurityContextA() { PA = secur32.oInitializeSecurityContextA; jmpRAX(); }
EXPORT void InitializeSecurityContextW() { PA = secur32.oInitializeSecurityContextW; jmpRAX(); }
EXPORT void LsaCallAuthenticationPackage() { PA = secur32.oLsaCallAuthenticationPackage; jmpRAX(); }
EXPORT void LsaConnectUntrusted() { PA = secur32.oLsaConnectUntrusted; jmpRAX(); }
EXPORT void LsaDeregisterLogonProcess() { PA = secur32.oLsaDeregisterLogonProcess; jmpRAX(); }
EXPORT void LsaEnumerateLogonSessions() { PA = secur32.oLsaEnumerateLogonSessions; jmpRAX(); }
EXPORT void LsaFreeReturnBuffer() { PA = secur32.oLsaFreeReturnBuffer; jmpRAX(); }
EXPORT void LsaGetLogonSessionData() { PA = secur32.oLsaGetLogonSessionData; jmpRAX(); }
EXPORT void LsaLogonUser() { PA = secur32.oLsaLogonUser; jmpRAX(); }
EXPORT void LsaLookupAuthenticationPackage() { PA = secur32.oLsaLookupAuthenticationPackage; jmpRAX(); }
EXPORT void LsaRegisterLogonProcess() { PA = secur32.oLsaRegisterLogonProcess; jmpRAX(); }
EXPORT void LsaRegisterPolicyChangeNotification() { PA = secur32.oLsaRegisterPolicyChangeNotification; jmpRAX(); }
EXPORT void LsaUnregisterPolicyChangeNotification() { PA = secur32.oLsaUnregisterPolicyChangeNotification; jmpRAX(); }
EXPORT void MakeSignature() { PA = secur32.oMakeSignature; jmpRAX(); }
EXPORT void OpenLsaPerformanceData() { PA = secur32.oOpenLsaPerformanceData; jmpRAX(); }
EXPORT void QueryContextAttributesA() { PA = secur32.oQueryContextAttributesA; jmpRAX(); }
EXPORT void QueryContextAttributesW() { PA = secur32.oQueryContextAttributesW; jmpRAX(); }
EXPORT void QueryCredentialsAttributesA() { PA = secur32.oQueryCredentialsAttributesA; jmpRAX(); }
EXPORT void QueryCredentialsAttributesW() { PA = secur32.oQueryCredentialsAttributesW; jmpRAX(); }
EXPORT void QuerySecurityContextToken() { PA = secur32.oQuerySecurityContextToken; jmpRAX(); }
EXPORT void QuerySecurityPackageInfoA() { PA = secur32.oQuerySecurityPackageInfoA; jmpRAX(); }
EXPORT void QuerySecurityPackageInfoW() { PA = secur32.oQuerySecurityPackageInfoW; jmpRAX(); }
EXPORT void RevertSecurityContext() { PA = secur32.oRevertSecurityContext; jmpRAX(); }
EXPORT void SaslAcceptSecurityContext() { PA = secur32.oSaslAcceptSecurityContext; jmpRAX(); }
EXPORT void SaslEnumerateProfilesA() { PA = secur32.oSaslEnumerateProfilesA; jmpRAX(); }
EXPORT void SaslEnumerateProfilesW() { PA = secur32.oSaslEnumerateProfilesW; jmpRAX(); }
EXPORT void SaslGetContextOption() { PA = secur32.oSaslGetContextOption; jmpRAX(); }
EXPORT void SaslGetProfilePackageA() { PA = secur32.oSaslGetProfilePackageA; jmpRAX(); }
EXPORT void SaslGetProfilePackageW() { PA = secur32.oSaslGetProfilePackageW; jmpRAX(); }
EXPORT void SaslIdentifyPackageA() { PA = secur32.oSaslIdentifyPackageA; jmpRAX(); }
EXPORT void SaslIdentifyPackageW() { PA = secur32.oSaslIdentifyPackageW; jmpRAX(); }
EXPORT void SaslInitializeSecurityContextA() { PA = secur32.oSaslInitializeSecurityContextA; jmpRAX(); }
EXPORT void SaslInitializeSecurityContextW() { PA = secur32.oSaslInitializeSecurityContextW; jmpRAX(); }
EXPORT void SaslSetContextOption() { PA = secur32.oSaslSetContextOption; jmpRAX(); }
EXPORT void SealMessage() { PA = secur32.oSealMessage; jmpRAX(); }
EXPORT void SeciAllocateAndSetCallFlags() { PA = secur32.oSeciAllocateAndSetCallFlags; jmpRAX(); }
EXPORT void SeciAllocateAndSetIPAddress() { PA = secur32.oSeciAllocateAndSetIPAddress; jmpRAX(); }
EXPORT void SeciFreeCallContext() { PA = secur32.oSeciFreeCallContext; jmpRAX(); }
EXPORT void SecpFreeMemory() { PA = secur32.oSecpFreeMemory; jmpRAX(); }
EXPORT void SecpTranslateName() { PA = secur32.oSecpTranslateName; jmpRAX(); }
EXPORT void SecpTranslateNameEx() { PA = secur32.oSecpTranslateNameEx; jmpRAX(); }
EXPORT void SetContextAttributesA() { PA = secur32.oSetContextAttributesA; jmpRAX(); }
EXPORT void SetContextAttributesW() { PA = secur32.oSetContextAttributesW; jmpRAX(); }
EXPORT void SetCredentialsAttributesA() { PA = secur32.oSetCredentialsAttributesA; jmpRAX(); }
EXPORT void SetCredentialsAttributesW() { PA = secur32.oSetCredentialsAttributesW; jmpRAX(); }
EXPORT void SspiCompareAuthIdentities() { PA = secur32.oSspiCompareAuthIdentities; jmpRAX(); }
EXPORT void SspiCopyAuthIdentity() { PA = secur32.oSspiCopyAuthIdentity; jmpRAX(); }
EXPORT void SspiDecryptAuthIdentity() { PA = secur32.oSspiDecryptAuthIdentity; jmpRAX(); }
EXPORT void SspiEncodeAuthIdentityAsStrings() { PA = secur32.oSspiEncodeAuthIdentityAsStrings; jmpRAX(); }
EXPORT void SspiEncodeStringsAsAuthIdentity() { PA = secur32.oSspiEncodeStringsAsAuthIdentity; jmpRAX(); }
EXPORT void SspiEncryptAuthIdentity() { PA = secur32.oSspiEncryptAuthIdentity; jmpRAX(); }
EXPORT void SspiExcludePackage() { PA = secur32.oSspiExcludePackage; jmpRAX(); }
EXPORT void SspiFreeAuthIdentity() { PA = secur32.oSspiFreeAuthIdentity; jmpRAX(); }
EXPORT void SspiGetTargetHostName() { PA = secur32.oSspiGetTargetHostName; jmpRAX(); }
EXPORT void SspiIsAuthIdentityEncrypted() { PA = secur32.oSspiIsAuthIdentityEncrypted; jmpRAX(); }
EXPORT void SspiLocalFree() { PA = secur32.oSspiLocalFree; jmpRAX(); }
EXPORT void SspiMarshalAuthIdentity() { PA = secur32.oSspiMarshalAuthIdentity; jmpRAX(); }
EXPORT void SspiPrepareForCredRead() { PA = secur32.oSspiPrepareForCredRead; jmpRAX(); }
EXPORT void SspiPrepareForCredWrite() { PA = secur32.oSspiPrepareForCredWrite; jmpRAX(); }
EXPORT void SspiUnmarshalAuthIdentity() { PA = secur32.oSspiUnmarshalAuthIdentity; jmpRAX(); }
EXPORT void SspiValidateAuthIdentity() { PA = secur32.oSspiValidateAuthIdentity; jmpRAX(); }
EXPORT void SspiZeroAuthIdentity() { PA = secur32.oSspiZeroAuthIdentity; jmpRAX(); }
EXPORT void TranslateNameA() { PA = secur32.oTranslateNameA; jmpRAX(); }
EXPORT void TranslateNameW() { PA = secur32.oTranslateNameW; jmpRAX(); }
EXPORT void UnsealMessage() { PA = secur32.oUnsealMessage; jmpRAX(); }
EXPORT void VerifySignature() { PA = secur32.oVerifySignature; jmpRAX(); }

void setupFunctions() {
	secur32.oAcceptSecurityContext = GetProcAddress(secur32.dll, "AcceptSecurityContext");
	secur32.oAcquireCredentialsHandleA = GetProcAddress(secur32.dll, "AcquireCredentialsHandleA");
	secur32.oAcquireCredentialsHandleW = GetProcAddress(secur32.dll, "AcquireCredentialsHandleW");
	secur32.oAddCredentialsA = GetProcAddress(secur32.dll, "AddCredentialsA");
	secur32.oAddCredentialsW = GetProcAddress(secur32.dll, "AddCredentialsW");
	secur32.oAddSecurityPackageA = GetProcAddress(secur32.dll, "AddSecurityPackageA");
	secur32.oAddSecurityPackageW = GetProcAddress(secur32.dll, "AddSecurityPackageW");
	secur32.oApplyControlToken = GetProcAddress(secur32.dll, "ApplyControlToken");
	secur32.oChangeAccountPasswordA = GetProcAddress(secur32.dll, "ChangeAccountPasswordA");
	secur32.oChangeAccountPasswordW = GetProcAddress(secur32.dll, "ChangeAccountPasswordW");
	secur32.oCloseLsaPerformanceData = GetProcAddress(secur32.dll, "CloseLsaPerformanceData");
	secur32.oCollectLsaPerformanceData = GetProcAddress(secur32.dll, "CollectLsaPerformanceData");
	secur32.oCompleteAuthToken = GetProcAddress(secur32.dll, "CompleteAuthToken");
	secur32.oCredMarshalTargetInfo = GetProcAddress(secur32.dll, "CredMarshalTargetInfo");
	secur32.oCredUnmarshalTargetInfo = GetProcAddress(secur32.dll, "CredUnmarshalTargetInfo");
	secur32.oDecryptMessage = GetProcAddress(secur32.dll, "DecryptMessage");
	secur32.oDeleteSecurityContext = GetProcAddress(secur32.dll, "DeleteSecurityContext");
	secur32.oDeleteSecurityPackageA = GetProcAddress(secur32.dll, "DeleteSecurityPackageA");
	secur32.oDeleteSecurityPackageW = GetProcAddress(secur32.dll, "DeleteSecurityPackageW");
	secur32.oEncryptMessage = GetProcAddress(secur32.dll, "EncryptMessage");
	secur32.oEnumerateSecurityPackagesA = GetProcAddress(secur32.dll, "EnumerateSecurityPackagesA");
	secur32.oEnumerateSecurityPackagesW = GetProcAddress(secur32.dll, "EnumerateSecurityPackagesW");
	secur32.oExportSecurityContext = GetProcAddress(secur32.dll, "ExportSecurityContext");
	secur32.oFreeContextBuffer = GetProcAddress(secur32.dll, "FreeContextBuffer");
	secur32.oFreeCredentialsHandle = GetProcAddress(secur32.dll, "FreeCredentialsHandle");
	secur32.oGetComputerObjectNameA = GetProcAddress(secur32.dll, "GetComputerObjectNameA");
	secur32.oGetComputerObjectNameW = GetProcAddress(secur32.dll, "GetComputerObjectNameW");
	secur32.oGetSecurityUserInfo = GetProcAddress(secur32.dll, "GetSecurityUserInfo");
	secur32.oGetUserNameExA = GetProcAddress(secur32.dll, "GetUserNameExA");
	secur32.oGetUserNameExW = GetProcAddress(secur32.dll, "GetUserNameExW");
	secur32.oImpersonateSecurityContext = GetProcAddress(secur32.dll, "ImpersonateSecurityContext");
	secur32.oImportSecurityContextA = GetProcAddress(secur32.dll, "ImportSecurityContextA");
	secur32.oImportSecurityContextW = GetProcAddress(secur32.dll, "ImportSecurityContextW");
	secur32.oInitSecurityInterfaceA = GetProcAddress(secur32.dll, "InitSecurityInterfaceA");
	secur32.oInitSecurityInterfaceW = GetProcAddress(secur32.dll, "InitSecurityInterfaceW");
	secur32.oInitializeSecurityContextA = GetProcAddress(secur32.dll, "InitializeSecurityContextA");
	secur32.oInitializeSecurityContextW = GetProcAddress(secur32.dll, "InitializeSecurityContextW");
	secur32.oLsaCallAuthenticationPackage = GetProcAddress(secur32.dll, "LsaCallAuthenticationPackage");
	secur32.oLsaConnectUntrusted = GetProcAddress(secur32.dll, "LsaConnectUntrusted");
	secur32.oLsaDeregisterLogonProcess = GetProcAddress(secur32.dll, "LsaDeregisterLogonProcess");
	secur32.oLsaEnumerateLogonSessions = GetProcAddress(secur32.dll, "LsaEnumerateLogonSessions");
	secur32.oLsaFreeReturnBuffer = GetProcAddress(secur32.dll, "LsaFreeReturnBuffer");
	secur32.oLsaGetLogonSessionData = GetProcAddress(secur32.dll, "LsaGetLogonSessionData");
	secur32.oLsaLogonUser = GetProcAddress(secur32.dll, "LsaLogonUser");
	secur32.oLsaLookupAuthenticationPackage = GetProcAddress(secur32.dll, "LsaLookupAuthenticationPackage");
	secur32.oLsaRegisterLogonProcess = GetProcAddress(secur32.dll, "LsaRegisterLogonProcess");
	secur32.oLsaRegisterPolicyChangeNotification = GetProcAddress(secur32.dll, "LsaRegisterPolicyChangeNotification");
	secur32.oLsaUnregisterPolicyChangeNotification = GetProcAddress(secur32.dll, "LsaUnregisterPolicyChangeNotification");
	secur32.oMakeSignature = GetProcAddress(secur32.dll, "MakeSignature");
	secur32.oOpenLsaPerformanceData = GetProcAddress(secur32.dll, "OpenLsaPerformanceData");
	secur32.oQueryContextAttributesA = GetProcAddress(secur32.dll, "QueryContextAttributesA");
	secur32.oQueryContextAttributesW = GetProcAddress(secur32.dll, "QueryContextAttributesW");
	secur32.oQueryCredentialsAttributesA = GetProcAddress(secur32.dll, "QueryCredentialsAttributesA");
	secur32.oQueryCredentialsAttributesW = GetProcAddress(secur32.dll, "QueryCredentialsAttributesW");
	secur32.oQuerySecurityContextToken = GetProcAddress(secur32.dll, "QuerySecurityContextToken");
	secur32.oQuerySecurityPackageInfoA = GetProcAddress(secur32.dll, "QuerySecurityPackageInfoA");
	secur32.oQuerySecurityPackageInfoW = GetProcAddress(secur32.dll, "QuerySecurityPackageInfoW");
	secur32.oRevertSecurityContext = GetProcAddress(secur32.dll, "RevertSecurityContext");
	secur32.oSaslAcceptSecurityContext = GetProcAddress(secur32.dll, "SaslAcceptSecurityContext");
	secur32.oSaslEnumerateProfilesA = GetProcAddress(secur32.dll, "SaslEnumerateProfilesA");
	secur32.oSaslEnumerateProfilesW = GetProcAddress(secur32.dll, "SaslEnumerateProfilesW");
	secur32.oSaslGetContextOption = GetProcAddress(secur32.dll, "SaslGetContextOption");
	secur32.oSaslGetProfilePackageA = GetProcAddress(secur32.dll, "SaslGetProfilePackageA");
	secur32.oSaslGetProfilePackageW = GetProcAddress(secur32.dll, "SaslGetProfilePackageW");
	secur32.oSaslIdentifyPackageA = GetProcAddress(secur32.dll, "SaslIdentifyPackageA");
	secur32.oSaslIdentifyPackageW = GetProcAddress(secur32.dll, "SaslIdentifyPackageW");
	secur32.oSaslInitializeSecurityContextA = GetProcAddress(secur32.dll, "SaslInitializeSecurityContextA");
	secur32.oSaslInitializeSecurityContextW = GetProcAddress(secur32.dll, "SaslInitializeSecurityContextW");
	secur32.oSaslSetContextOption = GetProcAddress(secur32.dll, "SaslSetContextOption");
	secur32.oSealMessage = GetProcAddress(secur32.dll, "SealMessage");
	secur32.oSeciAllocateAndSetCallFlags = GetProcAddress(secur32.dll, "SeciAllocateAndSetCallFlags");
	secur32.oSeciAllocateAndSetIPAddress = GetProcAddress(secur32.dll, "SeciAllocateAndSetIPAddress");
	secur32.oSeciFreeCallContext = GetProcAddress(secur32.dll, "SeciFreeCallContext");
	secur32.oSecpFreeMemory = GetProcAddress(secur32.dll, "SecpFreeMemory");
	secur32.oSecpTranslateName = GetProcAddress(secur32.dll, "SecpTranslateName");
	secur32.oSecpTranslateNameEx = GetProcAddress(secur32.dll, "SecpTranslateNameEx");
	secur32.oSetContextAttributesA = GetProcAddress(secur32.dll, "SetContextAttributesA");
	secur32.oSetContextAttributesW = GetProcAddress(secur32.dll, "SetContextAttributesW");
	secur32.oSetCredentialsAttributesA = GetProcAddress(secur32.dll, "SetCredentialsAttributesA");
	secur32.oSetCredentialsAttributesW = GetProcAddress(secur32.dll, "SetCredentialsAttributesW");
	secur32.oSspiCompareAuthIdentities = GetProcAddress(secur32.dll, "SspiCompareAuthIdentities");
	secur32.oSspiCopyAuthIdentity = GetProcAddress(secur32.dll, "SspiCopyAuthIdentity");
	secur32.oSspiDecryptAuthIdentity = GetProcAddress(secur32.dll, "SspiDecryptAuthIdentity");
	secur32.oSspiEncodeAuthIdentityAsStrings = GetProcAddress(secur32.dll, "SspiEncodeAuthIdentityAsStrings");
	secur32.oSspiEncodeStringsAsAuthIdentity = GetProcAddress(secur32.dll, "SspiEncodeStringsAsAuthIdentity");
	secur32.oSspiEncryptAuthIdentity = GetProcAddress(secur32.dll, "SspiEncryptAuthIdentity");
	secur32.oSspiExcludePackage = GetProcAddress(secur32.dll, "SspiExcludePackage");
	secur32.oSspiFreeAuthIdentity = GetProcAddress(secur32.dll, "SspiFreeAuthIdentity");
	secur32.oSspiGetTargetHostName = GetProcAddress(secur32.dll, "SspiGetTargetHostName");
	secur32.oSspiIsAuthIdentityEncrypted = GetProcAddress(secur32.dll, "SspiIsAuthIdentityEncrypted");
	secur32.oSspiLocalFree = GetProcAddress(secur32.dll, "SspiLocalFree");
	secur32.oSspiMarshalAuthIdentity = GetProcAddress(secur32.dll, "SspiMarshalAuthIdentity");
	secur32.oSspiPrepareForCredRead = GetProcAddress(secur32.dll, "SspiPrepareForCredRead");
	secur32.oSspiPrepareForCredWrite = GetProcAddress(secur32.dll, "SspiPrepareForCredWrite");
	secur32.oSspiUnmarshalAuthIdentity = GetProcAddress(secur32.dll, "SspiUnmarshalAuthIdentity");
	secur32.oSspiValidateAuthIdentity = GetProcAddress(secur32.dll, "SspiValidateAuthIdentity");
	secur32.oSspiZeroAuthIdentity = GetProcAddress(secur32.dll, "SspiZeroAuthIdentity");
	secur32.oTranslateNameA = GetProcAddress(secur32.dll, "TranslateNameA");
	secur32.oTranslateNameW = GetProcAddress(secur32.dll, "TranslateNameW");
	secur32.oUnsealMessage = GetProcAddress(secur32.dll, "UnsealMessage");
	secur32.oVerifySignature = GetProcAddress(secur32.dll, "VerifySignature");
}
#pragma endregion


BOOL APIENTRY DllMain( HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
		char path[MAX_PATH];
		GetWindowsDirectoryA(path, sizeof(path));
        
		strcat(path, "\\System32\\secur32.dll");
		secur32.dll = LoadLibraryA(path);
		setupFunctions();
        
        // infinity startup goes here
        CreateThread(0,
                     0,
                     (LPTHREAD_START_ROUTINE)InfinityMain,
                     0,
                     0,
                     0);
        break;
        
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#else
#include <pthread.h>
#include <string.h>
#include <stdio.h>

void __attribute__((constructor)) infinity_init() {
    pthread_t threadId;
    int err = pthread_create(&threadId,NULL, &InfinityMain, NULL);
    if(err)
    {
        printf("Failed to create infinity thread.\n====\n%s\n===\n", strerror(err));
    }
}

#endif
