// Copyright Marc Fraedrich. All Rights Reserved.
// SteamSDK.h — Internal header: includes the Steamworks SDK with UE5-safe guards.
// Include this only in .cpp files, never in public headers.
#pragma once

THIRD_PARTY_INCLUDES_START
#pragma warning(push)
#pragma warning(disable : 4996) // deprecated use of strcpy etc.
#pragma warning(disable : 4265) // class has virtual functions but no virtual destructor
#pragma warning(disable : 4828) // illegal character in source file
#include "steam/steam_api.h"
#pragma warning(pop)
THIRD_PARTY_INCLUDES_END

// Texture helper shared by Core and Friends subsystems
#include "Engine/Texture2D.h"

/** Converts a Steam avatar image handle to a transient UTexture2D (RGBA). */
inline UTexture2D* SteamImageToTexture(int ImageHandle)
{
	if (ImageHandle <= 0)
	{
		return nullptr;
	}

	uint32 Width = 0, Height = 0;
	if (!SteamUtils()->GetImageSize(ImageHandle, &Width, &Height) || Width == 0 || Height == 0)
	{
		return nullptr;
	}

	TArray<uint8> Buffer;
	Buffer.SetNumZeroed(Width * Height * 4);
	if (!SteamUtils()->GetImageRGBA(ImageHandle, Buffer.GetData(), Buffer.Num()))
	{
		return nullptr;
	}

	UTexture2D* Tex = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);
	if (!Tex)
	{
		return nullptr;
	}

#if ENGINE_MAJOR_VERSION >= 5
	FTexture2DMipMap& Mip = Tex->GetPlatformData()->Mips[0];
#else
	FTexture2DMipMap& Mip = Tex->PlatformData->Mips[0];
#endif
	void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(Data, Buffer.GetData(), Buffer.Num());
	Mip.BulkData.Unlock();
	Tex->UpdateResource();
	return Tex;
}

/** Converts our FSteamID to a CSteamID. */
inline CSteamID ToCSteamID(const FSteamID& ID)
{
	return CSteamID(ID.AsUInt64());
}
