// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamRemoteStorageSubsystem.h"
#include "SteamSDK.h"
#include "SteamCoreSubsystem.h"
#include "UESteamFramework.h"

static bool IsSteamReady(const UGameInstanceSubsystem* Sub)
{
	if (const auto* Core = Sub->GetGameInstance()->GetSubsystem<USteamCoreSubsystem>())
	{
		return Core->IsSteamInitialized();
	}
	return false;
}

// ---------------------------------------------------------------------------
// UGameInstanceSubsystem
// ---------------------------------------------------------------------------

void USteamRemoteStorageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<USteamCoreSubsystem>();
	Super::Initialize(Collection);
}

void USteamRemoteStorageSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// Cloud availability
// ---------------------------------------------------------------------------

bool USteamRemoteStorageSubsystem::IsCloudEnabledForApp() const
{
	return IsSteamReady(this) && SteamRemoteStorage()->IsCloudEnabledForApp();
}

bool USteamRemoteStorageSubsystem::IsCloudEnabledForAccount() const
{
	return IsSteamReady(this) && SteamRemoteStorage()->IsCloudEnabledForAccount();
}

bool USteamRemoteStorageSubsystem::GetQuota(int64& OutTotalBytes, int64& OutAvailableBytes) const
{
	OutTotalBytes     = 0;
	OutAvailableBytes = 0;
	if (!IsSteamReady(this)) return false;
	uint64 Total = 0, Available = 0;
	const bool bOK = SteamRemoteStorage()->GetQuota(&Total, &Available);
	OutTotalBytes     = static_cast<int64>(Total);
	OutAvailableBytes = static_cast<int64>(Available);
	return bOK;
}

// ---------------------------------------------------------------------------
// File I/O
// ---------------------------------------------------------------------------

bool USteamRemoteStorageSubsystem::WriteFile(const FString& FileName, const TArray<uint8>& Data)
{
	if (!IsSteamReady(this)) return false;
	return SteamRemoteStorage()->FileWrite(
		TCHAR_TO_UTF8(*FileName), Data.GetData(), Data.Num());
}

bool USteamRemoteStorageSubsystem::ReadFile(const FString& FileName, TArray<uint8>& OutData)
{
	OutData.Empty();
	if (!IsSteamReady(this)) return false;

	const int32 Size = SteamRemoteStorage()->GetFileSize(TCHAR_TO_UTF8(*FileName));
	if (Size <= 0) return false;

	OutData.SetNumUninitialized(Size);
	const int32 Read = SteamRemoteStorage()->FileRead(
		TCHAR_TO_UTF8(*FileName), OutData.GetData(), Size);
	OutData.SetNum(Read);
	return Read > 0;
}

bool USteamRemoteStorageSubsystem::DeleteFile(const FString& FileName)
{
	if (!IsSteamReady(this)) return false;
	return SteamRemoteStorage()->FileDelete(TCHAR_TO_UTF8(*FileName));
}

bool USteamRemoteStorageSubsystem::FileExists(const FString& FileName) const
{
	if (!IsSteamReady(this)) return false;
	return SteamRemoteStorage()->FileExists(TCHAR_TO_UTF8(*FileName));
}

int32 USteamRemoteStorageSubsystem::GetFileSize(const FString& FileName) const
{
	if (!IsSteamReady(this)) return -1;
	return SteamRemoteStorage()->GetFileSize(TCHAR_TO_UTF8(*FileName));
}

// ---------------------------------------------------------------------------
// File listing
// ---------------------------------------------------------------------------

TArray<FSteamCloudFile> USteamRemoteStorageSubsystem::GetFileList() const
{
	TArray<FSteamCloudFile> Out;
	if (!IsSteamReady(this)) return Out;

	const int32 Count = SteamRemoteStorage()->GetFileCount();
	for (int32 i = 0; i < Count; ++i)
	{
		int32 FileSize = 0;
		const char* Name = SteamRemoteStorage()->GetFileNameAndSize(i, &FileSize);

		FSteamCloudFile F;
		F.FileName      = UTF8_TO_TCHAR(Name);
		F.FileSizeBytes = FileSize;
		// Timestamp not exposed synchronously without an async share call; leave as default.
		Out.Add(F);
	}
	return Out;
}

// ---------------------------------------------------------------------------
// String helpers
// ---------------------------------------------------------------------------

bool USteamRemoteStorageSubsystem::WriteString(const FString& FileName, const FString& Content)
{
	const FTCHARToUTF8 UTF8(*Content);
	TArray<uint8> Data(reinterpret_cast<const uint8*>(UTF8.Get()), UTF8.Length());
	return WriteFile(FileName, Data);
}

bool USteamRemoteStorageSubsystem::ReadString(const FString& FileName, FString& OutContent)
{
	TArray<uint8> Data;
	if (!ReadFile(FileName, Data)) return false;
	// Null-terminate and convert
	Data.Add(0);
	OutContent = UTF8_TO_TCHAR(reinterpret_cast<const char*>(Data.GetData()));
	return true;
}
