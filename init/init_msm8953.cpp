/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#include <fstream>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <vector>

#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

static const char *snet_prop_key[] = {
	"ro.boot.vbmeta.device_state",
	"ro.boot.verifiedbootstate",
	"ro.boot.flash.locked",
	"ro.boot.selinux",
	"ro.boot.veritymode",
	"ro.boot.warranty_bit",
	"ro.warranty_bit",
	"ro.debuggable",
	"ro.secure",
	"ro.build.type",
	"ro.build.keys",
	"ro.build.tags",
	"ro.system.build.tags",
	"ro.vendor.boot.warranty_bit",
	"ro.vendor.warranty_bit",
	"vendor.boot.vbmeta.device_state",
	"vendor.boot.verifiedbootstate",
	NULL
};

static const char *snet_prop_value[] = {
	"locked", // ro.boot.vbmeta.device_state
	"green", // ro.boot.verifiedbootstate
	"1", // ro.boot.flash.locked
	"enforcing", // ro.boot.selinux
	"enforcing", // ro.boot.veritymode
	"0", // ro.boot.warranty_bit
	"0", // ro.warranty_bit
	"0", // ro.debuggable
	"1", // ro.secure
	"user", // ro.build.type
	"release-keys", // ro.build.keys
	"release-keys", // ro.build.tags
	"release-keys", // ro.system.build.tags
	"0", // ro.vendor.boot.warranty_bit
	"0", // ro.vendor.warranty_bit
	"locked", // vendor.boot.vbmeta.device_state
	"green", // vendor.boot.verifiedbootstate
	NULL
};

static void workaround_snet_properties() {

     // Hide all sensitive props
    for (int i = 0; snet_prop_key[i]; ++i) {
        property_override(snet_prop_key[i], snet_prop_value[i]);
    }

     chmod("/sys/fs/selinux/enforce", 0640);
     chmod("/sys/fs/selinux/policy", 0440);

    // Workaround SafetyNet
    workaround_snet_properties();

}

std::vector<std::string> ro_props_default_source_order = {
        "", "bootimage.", "odm.", "product.", "system.", "system_ext.", "vendor.",
};

void set_ro_build_prop(const std::string& prop, const std::string& value) {
    for (const auto& source : ro_props_default_source_order) {
        auto prop_name = "ro." + source + "build." + prop;
        if (source == "")
            property_override(prop_name.c_str(), value.c_str());
        else
            property_override(prop_name.c_str(), value.c_str(), false);
    }
};

void load_dalvik_properties() {
    struct sysinfo sys;

    sysinfo(&sys);
    if (sys.totalram > 3072ull * 1024 * 1024) {
        // from - phone-xxhdpi-4096-dalvik-heap.mk
	property_override("dalvik.vm.heapstartsize", "8m");
	property_override("dalvik.vm.heaptargetutilization", "0.6");
	property_override("dalvik.vm.heapgrowthlimit", "192m");
	property_override("dalvik.vm.heapsize", "512m");
	property_override("dalvik.vm.heapmaxfree", "16m");
	property_override("dalvik.vm.heapminfree", "4m");
    } else {
        // from - phone-xhdpi-2048-dalvik-heap.mk
	property_override("dalvik.vm.heapstartsize", "8m");
	property_override("dalvik.vm.heaptargetutilization", "0.7");
	property_override("dalvik.vm.heapgrowthlimit", "192m");
	property_override("dalvik.vm.heapsize", "512m");
	property_override("dalvik.vm.heapmaxfree", "8m");
	property_override("dalvik.vm.heapminfree", "2m");
    }
}

void vendor_load_properties() {
    std::string fingerprint;
    std::string description;

    fingerprint = "xiaomi/tissot/tissot_sprout:8.0.0/OPR1.170623.026/8.1.10:user/release-keys";
    description = "tissot-user 8.0.0 OPR1.170623.026 8.1.10 release-keys";

    set_ro_build_prop("fingerprint", fingerprint);
    property_override("ro.build.description", description.c_str());

    load_dalvik_properties();

    // Misc
    property_override("ro.apex.updatable", "false");
    property_override("ro.oem_unlock_supported", "0");
    property_override("ro.com.google.clientidbase", "android-xiaomi");
    property_override("ro.com.google.clientidbase.ms", "android-xiaomi-rev1");
}
