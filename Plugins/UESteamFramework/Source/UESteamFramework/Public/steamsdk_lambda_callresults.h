// This is a custom Steam CallResult to support C++ lambdas
//-----------------------------------------------------------------------------
// Purpose: maps a steam async call result to a lambda function
//			template params: P = parameter struct
//-----------------------------------------------------------------------------

#include "OnlineSubsystemUtils.h"
// Disable some warnings
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996) // Unsafe strcpy warning
#pragma warning(disable:4265) // CallBack destructor warning
#pragma warning(disable:4828) // Steam API char offset error
#endif

// Prevent array multi-definition warning
#pragma push_macro("ARRAY_COUNT")
#undef ARRAY_COUNT
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"
// Restore the original ARRAY_COUNT macro
#pragma pop_macro("ARRAY_COUNT")
#include <functional>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

// This is a custom Steam CallResult to support C++ lambdas
//-----------------------------------------------------------------------------
// Purpose: maps a steam async call result to a lambda function
//          template params: P = parameter struct
//-----------------------------------------------------------------------------
template<class P>
class CLambdaCallResult : private CCallbackBase
{
public:
	typedef std::function<void(P*, bool)> func_t;

	CLambdaCallResult();
	~CLambdaCallResult();

	void Set(SteamAPICall_t hAPICall, func_t func);
	bool IsActive() const;
	void Cancel();

	void SetGameserverFlag() { m_nCallbackFlags |= k_ECallbackFlagsGameServer; }

private:
	virtual void Run(void *pvParm);
	virtual void Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall);
	virtual int GetCallbackSizeBytes() { return sizeof(P); }

	SteamAPICall_t m_hAPICall;
	func_t m_Func;
};

//-----------------------------------------------------------------------------
// Purpose: maps a steam async call result to a lambda function
//          template params: P = parameter struct
//-----------------------------------------------------------------------------
template<class P>
inline CLambdaCallResult<P>::CLambdaCallResult()
{
	m_hAPICall = k_uAPICallInvalid;
	m_Func = NULL;
	m_iCallback = P::k_iCallback;

	UE_LOG(LogTemp, Log, TEXT("ctor"));
}

template<class P>
inline void CLambdaCallResult<P>::Set(SteamAPICall_t hAPICall, func_t func)
{
	if (m_hAPICall)
		SteamAPI_UnregisterCallResult(this, m_hAPICall);

	m_hAPICall = hAPICall;
	m_Func = func;

	if (hAPICall)
		SteamAPI_RegisterCallResult(this, hAPICall);
}

template<class P>
inline bool CLambdaCallResult<P>::IsActive() const
{
	return (m_hAPICall != k_uAPICallInvalid);
}

template<class P>
inline void CLambdaCallResult<P>::Cancel()
{
	if (m_hAPICall != k_uAPICallInvalid)
	{
		SteamAPI_UnregisterCallResult(this, m_hAPICall);
		m_hAPICall = k_uAPICallInvalid;
	}
}

template<class P>
inline CLambdaCallResult<P>::~CLambdaCallResult()
{
	Cancel();
}

template<class P>
inline void CLambdaCallResult<P>::Run(void *pvParam)
{
	m_hAPICall = k_uAPICallInvalid; // caller unregisters for us
	m_Func((P*)pvParam, false);
}

template<class P>
inline void CLambdaCallResult<P>::Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall)
{
	if (hSteamAPICall == m_hAPICall)
	{
		m_hAPICall = k_uAPICallInvalid; // caller unregisters for us
		m_Func((P*)pvParam, bIOFailure);

		UE_LOG(LogTemp, Log, TEXT("pvParam: %d"), ((SteamUGCQueryCompleted_t*)pvParam)->m_unNumResultsReturned);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Invalid API call"));
	}
}