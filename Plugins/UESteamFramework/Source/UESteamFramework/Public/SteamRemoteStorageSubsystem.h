// Copyright Marc Fraedrich. All Rights Reserved.
// SteamRemoteStorageSubsystem.h
// Steam Cloud saves and remote file storage.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamTypes.h"
#include "SteamRemoteStorageSubsystem.generated.h"

/**
 * USteamRemoteStorageSubsystem
 *
 * Synchronous wrapper around ISteamRemoteStorage.
 * All file operations happen on the calling thread (no async).  For large
 * files consider running them on a background thread yourself.
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamRemoteStorageSubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamRemoteStorageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// -----------------------------------------------------------------------
	// Cloud availability
	// -----------------------------------------------------------------------

	/** True if Steam Cloud is enabled for this app and the local user. */
	UFUNCTION(BlueprintPure, Category = "Steam|Cloud")
	bool IsCloudEnabledForApp() const;

	/** True if the local user has cloud sync turned on in their Steam settings. */
	UFUNCTION(BlueprintPure, Category = "Steam|Cloud")
	bool IsCloudEnabledForAccount() const;

	/** Returns the total and available cloud quota in bytes. */
	UFUNCTION(BlueprintPure, Category = "Steam|Cloud")
	bool GetQuota(int64& OutTotalBytes, int64& OutAvailableBytes) const;

	// -----------------------------------------------------------------------
	// File I/O
	// -----------------------------------------------------------------------

	/**
	 * Writes a byte array to a cloud file, replacing any existing content.
	 * @param FileName  Relative path used as the file key (e.g. "savegame/slot0.sav").
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Cloud")
	bool WriteFile(const FString& FileName, const TArray<uint8>& Data);

	/**
	 * Reads a cloud file into a byte array.
	 * Returns false and an empty array if the file does not exist.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Cloud")
	bool ReadFile(const FString& FileName, TArray<uint8>& OutData);

	/** Deletes a cloud file. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Cloud")
	bool DeleteFile(const FString& FileName);

	/** True if the cloud file exists. */
	UFUNCTION(BlueprintPure, Category = "Steam|Cloud")
	bool FileExists(const FString& FileName) const;

	/** Returns the size in bytes of a cloud file, or -1 if it doesn't exist. */
	UFUNCTION(BlueprintPure, Category = "Steam|Cloud")
	int32 GetFileSize(const FString& FileName) const;

	// -----------------------------------------------------------------------
	// File listing
	// -----------------------------------------------------------------------

	/** Returns metadata for all cloud files owned by the local user. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Cloud")
	TArray<FSteamCloudFile> GetFileList() const;

	// -----------------------------------------------------------------------
	// String helpers
	// -----------------------------------------------------------------------

	/**
	 * Convenience: serialise a string (UTF-8) to a cloud file.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Cloud")
	bool WriteString(const FString& FileName, const FString& Content);

	/**
	 * Convenience: read a cloud file back as a UTF-8 string.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Cloud")
	bool ReadString(const FString& FileName, FString& OutContent);
};
