# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# dexdump, similar in purpose to objdump.
#
LOCAL_PATH:= $(call my-dir)

##
##
## Build the device command line tool dexdump
##
##

include $(CLEAR_VARS)

LOCAL_MODULE := getpwname
LOCAL_SRC_FILES := getpwname.c
LOCAL_C_INCLUDES := bionic/libc/bionic
LOCAL_SHARED_LIBRARIES := \
        libc

include $(BUILD_EXECUTABLE)
