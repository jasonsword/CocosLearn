#宏函数‘my-dir’, 由编译系统提供，用于返回当前路径（即包含Android.mk file文件的目录）
LOCAL_PATH := $(call my-dir)

#清除一些环境变量信息，下面会用到
include $(CLEAR_VARS)

#名称必须是唯一的，而且不包含任何空格。注意编译系统会自动产生合适的前缀和后缀，
#换句话说，一个被命名为'foo'的共享库，将会生成'libfoo.so'文件（也可以直接已libxxx命名好）
LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_CPP_EXTENSION :=.cc .cpp

#必须包含将要编译打包进模块中的C或C++源代码文件
LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/scenes/BackToMenu.cpp \
                   ../../Classes/scenes/GameData.cpp \
                   ../../Classes/scenes/GameResource.cpp \
                   ../../Classes/scenes/GameScene.cpp \
                   ../../Classes/scenes/LogInScene.cpp \
                   ../../Classes/scenes/MenuScene.cpp \
                   ../../Classes/scenes/Star.cpp \
                   ../../Classes/scenes/StarMatrix.cpp \
                   ../../Classes/scenes/TopMenu.cpp \
                   ../../Classes/scenes/XmlData.cpp \
                   ../../Classes/connection/GameConnection.cpp \
                   ../../Classes/connection/MessageBase.pb.cc \
                   ../../Classes/connection/ODSocket.cpp \
                   ../../Classes/connection/Register.pb.cc \
                   ../../Classes/connection/WebSocketConnection.cpp

#可选变量，表示头文件的搜索路径。默认的头文件的搜索路径是LOCAL_PATH目录。
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/protobuf

#undefined reference to problem
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

#表示该模块需要使用哪些静态库，以便在编译时进行链接
#链接第二个库要使用+=
LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += libprotobuf

#表示模块在运行时要依赖的共享库（动态库），在链接时就需要，以便在生成文件时嵌入其相应的信息
#LOCAL_SHARED_LIBRARIES :=

#编译模块时要使用的附加的链接器选项。
#LOCAL_LDLIBS := $(LOCAL_PATH)/libprotobuf_static.a

#默认情况下， arm目标二进制会以 thumb 的形式生成(16 位)，
#你可以通过设置这个变量为 arm如果你希望你的 module 是以 32 位指令的形式
#LOCAL_ARM_MODE :=

#可选的编译器选项，在编译 C 代码文件的时候使用
#LOCAL_CFLAGS :=


#BUILD_EXECUTABLE
#BUILD_PACKAGE
#BUILD_STATIC_JAVA_LIBRARY
include $(BUILD_SHARED_LIBRARY)

#返回一个位于当前'my-dir'路径的子目录中的所有Android.mk的列表。
#include $(call all-subdir-makefiles)

include $(CLEAR_VARS)

LOCAL_MODULE := libprotobuf
LOCAL_MODULE_FILENAME := protobuf
LOCAL_SRC_FILES := libprotobuf_static.a
include $(PREBUILT_STATIC_LIBRARY)

$(call import-module,./prebuilt-mk)
#$(call import-module,$(LOCAL_PATH)/protobuf)
