// Copyright (C) 2024 Betide Studio. All Rights Reserved.
// Written by AvnishGameDev.

#include "BFL_GoogleSignIn.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h" 
#include "Android/Utils/AndroidJNICallUtils.h"
#include "Android/Utils/AndroidJNIConvertor.h"
#include "Runtime/Core/Public/Async/TaskGraphInterfaces.h"

#define INIT_JAVA_METHOD(name, signature) \
if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true)) { \
name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
check(name != NULL); \
} else { \
check(0); \
}

#define DECLARE_JAVA_METHOD(name) \
static jmethodID name = NULL;

DECLARE_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserDisplayName);
DECLARE_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserFirstName);
DECLARE_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserLastName);
DECLARE_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserProfilePictureUrl);
DECLARE_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_IsUserLoggedIn);
#endif
#if PLATFORM_IOS
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute" // Ignore errors generated by FBSDKCoreKit.h and GoogleSignIn.h
#import <Foundation/Foundation.h>
#import <GoogleSignIn/GoogleSignIn.h>
#endif

UBFL_GoogleSignIn::UBFL_GoogleSignIn()
{
#if PLATFORM_ANDROID
	INIT_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserDisplayName, "()Ljava/lang/String;");
	INIT_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserFirstName, "()Ljava/lang/String;");
	INIT_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserLastName, "()Ljava/lang/String;");
	INIT_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_GetUserProfilePictureUrl, "()Ljava/lang/String;");
	INIT_JAVA_METHOD(AndroidThunkJava_GoogleSubsystem_IsUserLoggedIn, "()Z");
#endif
}

FString UBFL_GoogleSignIn::GetUserDisplayName()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		return AndroidJNIConvertor::FromJavaString(static_cast<jstring>(FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_GoogleSubsystem_GetUserDisplayName)));
	}
#endif
#if PLATFORM_IOS
	GIDGoogleUser* user = [GIDSignIn.sharedInstance currentUser];
	if (!user)
		return "User not logged in";
	NSString* ns_str = user.profile.name;
	const char* c_str = [ns_str UTF8String];
	return FString(c_str);
#endif
	return "Platform not supported!";
}

FString UBFL_GoogleSignIn::GetUserFirstName()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		return AndroidJNIConvertor::FromJavaString(static_cast<jstring>(FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_GoogleSubsystem_GetUserFirstName)));
	}
#endif
#if PLATFORM_IOS
	GIDGoogleUser* user = [GIDSignIn.sharedInstance currentUser];
	if (!user)
		return "User not logged in";
	NSString* ns_str = user.profile.givenName;
	const char* c_str = [ns_str UTF8String];
	return FString(c_str);
#endif
	return "Platform not supported!";
}

FString UBFL_GoogleSignIn::GetUserLastName()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		return AndroidJNIConvertor::FromJavaString(static_cast<jstring>(FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_GoogleSubsystem_GetUserLastName)));
	}
#endif
#if PLATFORM_IOS
	GIDGoogleUser* user = [GIDSignIn.sharedInstance currentUser];
	if (!user)
		return "User not logged in";
	NSString* ns_str = user.profile.familyName;
	const char* c_str = [ns_str UTF8String];
	return FString(c_str);
#endif
	return "Platform not supported!";
}

FString UBFL_GoogleSignIn::GetUserProfilePictureUrl()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		return AndroidJNIConvertor::FromJavaString(static_cast<jstring>(FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_GoogleSubsystem_GetUserProfilePictureUrl)));
	}
#endif
#if PLATFORM_IOS
	GIDGoogleUser* user = [GIDSignIn.sharedInstance currentUser];
	if (!user)
		return "User not logged in";
	NSURL* profilePic = [user.profile imageURLWithDimension:320];
	NSString* ns_str = [profilePic absoluteString];
	const char* c_str = [ns_str UTF8String];
	return FString(c_str);
#endif
	return "Platform not supported!";
}

bool UBFL_GoogleSignIn::IsUserLoggedIn()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_GoogleSubsystem_IsUserLoggedIn);
	}
#endif
#if PLATFORM_IOS
	GIDGoogleUser* user = [GIDSignIn.sharedInstance currentUser];
	if (user)
		return true;
#endif
	return false;
}
