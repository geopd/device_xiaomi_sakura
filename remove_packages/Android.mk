LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := removepackages
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := AppDirectedSMSService CarrierSetup ConnMO DCMO MyVerizonServices FilesPrebuilt Ornament DevicePolicyPrebuilt OBDM_Permissions OemDmTrigger SafetyHubPrebuilt Showcase SprintDM SprintHM USCCDM VZWAPNLib VzwOmaTrigger YouTube YoutubeMusicPrebuilt obdm_stub
LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)
