#�꺯����my-dir��, �ɱ���ϵͳ�ṩ�����ڷ��ص�ǰ·����������Android.mk file�ļ���Ŀ¼��
LOCAL_PATH := $(call my-dir)

#���һЩ����������Ϣ��������õ�
include $(CLEAR_VARS)

#���Ʊ�����Ψһ�ģ����Ҳ������κοո�ע�����ϵͳ���Զ��������ʵ�ǰ׺�ͺ�׺��
#���仰˵��һ��������Ϊ'foo'�Ĺ���⣬��������'libfoo.so'�ļ���Ҳ����ֱ����libxxx�����ã�
LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_CPP_EXTENSION :=.cc .cpp

#���������Ҫ��������ģ���е�C��C++Դ�����ļ�
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

#��ѡ��������ʾͷ�ļ�������·����Ĭ�ϵ�ͷ�ļ�������·����LOCAL_PATHĿ¼��
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/protobuf

#undefined reference to problem
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

#��ʾ��ģ����Ҫʹ����Щ��̬�⣬�Ա��ڱ���ʱ��������
#���ӵڶ�����Ҫʹ��+=
LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += libprotobuf

#��ʾģ��������ʱҪ�����Ĺ���⣨��̬�⣩��������ʱ����Ҫ���Ա��������ļ�ʱǶ������Ӧ����Ϣ
#LOCAL_SHARED_LIBRARIES :=

#����ģ��ʱҪʹ�õĸ��ӵ�������ѡ�
#LOCAL_LDLIBS := $(LOCAL_PATH)/libprotobuf_static.a

#Ĭ������£� armĿ������ƻ��� thumb ����ʽ����(16 λ)��
#�����ͨ�������������Ϊ arm�����ϣ����� module ���� 32 λָ�����ʽ
#LOCAL_ARM_MODE :=

#��ѡ�ı�����ѡ��ڱ��� C �����ļ���ʱ��ʹ��
#LOCAL_CFLAGS :=


#BUILD_EXECUTABLE
#BUILD_PACKAGE
#BUILD_STATIC_JAVA_LIBRARY
include $(BUILD_SHARED_LIBRARY)

#����һ��λ�ڵ�ǰ'my-dir'·������Ŀ¼�е�����Android.mk���б�
#include $(call all-subdir-makefiles)

include $(CLEAR_VARS)

LOCAL_MODULE := libprotobuf
LOCAL_MODULE_FILENAME := protobuf
LOCAL_SRC_FILES := libprotobuf_static.a
include $(PREBUILT_STATIC_LIBRARY)

$(call import-module,./prebuilt-mk)
#$(call import-module,$(LOCAL_PATH)/protobuf)
