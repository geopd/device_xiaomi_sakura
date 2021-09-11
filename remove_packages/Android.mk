LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := removepackages
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := AmbientSensePrebuilt arcore CalendarGooglePrebuilt CarrierSetup DevicePolicyPrebuilt DiagnosticsToolPrebuilt Drive GoogleCamera GoogleFeedback OBDM_Permissions MaestroPrebuilt Maps MicropaperPrebuilt PixelLiveWallpaperPrebuilt PixelWallpapers2020 PrebuiltGmail RecorderPrebuilt SafetyHubPrebuilt ScribePrebuilt WallpapersBReel2020 YouTube YouTubeMusicPrebuilt
LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)
