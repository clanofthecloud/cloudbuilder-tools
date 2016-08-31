LOCAL_PATH:= $(call my-dir)

CURL_SRC_DIR	:= ../../lib
DELIVERY_PATH	:= $(LOCAL_PATH)/../../../../cloudbuilder/delivery

include $(CLEAR_VARS)

LOCAL_SRC_FILES :=	$(CURL_SRC_DIR)/base64.c $(CURL_SRC_DIR)/connect.c $(CURL_SRC_DIR)/cookie.c $(CURL_SRC_DIR)/curl_addrinfo.c $(CURL_SRC_DIR)/curl_memrchr.c $(CURL_SRC_DIR)/curl_rand.c		\
					$(CURL_SRC_DIR)/easy.c $(CURL_SRC_DIR)/escape.c $(CURL_SRC_DIR)/fileinfo.c $(CURL_SRC_DIR)/formdata.c $(CURL_SRC_DIR)/getenv.c $(CURL_SRC_DIR)/getinfo.c $(CURL_SRC_DIR)/hash.c		\
					$(CURL_SRC_DIR)/hostasyn.c $(CURL_SRC_DIR)/hostip.c $(CURL_SRC_DIR)/hostip4.c $(CURL_SRC_DIR)/hostip6.c $(CURL_SRC_DIR)/http.c $(CURL_SRC_DIR)/http_chunks.c	$(CURL_SRC_DIR)/http_digest.c   \
					$(CURL_SRC_DIR)/http_proxy.c $(CURL_SRC_DIR)/if2ip.c $(CURL_SRC_DIR)/inet_ntop.c $(CURL_SRC_DIR)/inet_pton.c $(CURL_SRC_DIR)/llist.c $(CURL_SRC_DIR)/md5.c $(CURL_SRC_DIR)/mprintf.c	\
					$(CURL_SRC_DIR)/multi.c $(CURL_SRC_DIR)/netrc.c $(CURL_SRC_DIR)/nonblock.c $(CURL_SRC_DIR)/parsedate.c $(CURL_SRC_DIR)/progress.c $(CURL_SRC_DIR)/rawstr.c $(CURL_SRC_DIR)/select.c	\
					$(CURL_SRC_DIR)/sendf.c $(CURL_SRC_DIR)/share.c $(CURL_SRC_DIR)/slist.c $(CURL_SRC_DIR)/socks.c $(CURL_SRC_DIR)/speedcheck.c $(CURL_SRC_DIR)/splay.c $(CURL_SRC_DIR)/sslgen.c		\
					$(CURL_SRC_DIR)/strequal.c $(CURL_SRC_DIR)/strerror.c $(CURL_SRC_DIR)/strtok.c $(CURL_SRC_DIR)/timeval.c $(CURL_SRC_DIR)/transfer.c $(CURL_SRC_DIR)/url.c $(CURL_SRC_DIR)/warnless.c	\
					$(CURL_SRC_DIR)/wildcard.c
LOCAL_SRC_FILES +=	$(CURL_SRC_DIR)/ssluse.c $(CURL_SRC_DIR)/curl_ntlm.c $(CURL_SRC_DIR)/curl_ntlm_core.c $(CURL_SRC_DIR)/curl_ntlm_msgs.c $(CURL_SRC_DIR)/curl_gethostname.c

LOCAL_CFLAGS	:=	-DHAVE_CONFIG_H			\
					-DBUILDING_LIBCURL		\
					-DCURL_STATICLIB		\
					-DHTTP_ONLY				\
					-DCURL_DISABLE_RTSP		\
					-DCURL_DISABLE_GOPHER	\
					-DCURL_DISABLE_POP3		\
					-DCURL_DISABLE_DICT		\
					-DCURL_DISABLE_FILE		\
					-DCURL_DISABLE_FTP		\
					-DCURL_DISABLE_IMAP		\
					-DCURL_DISABLE_LDAP		\
					-DCURL_DISABLE_SMTP		\
					-DCURL_DISABLE_TELNET	\
					-DCURL_DISABLE_TFTP		\
                    -DENABLE_IPV6           \
                    -DUSE_OPENSSL			\
					-DUSE_SSLEAY

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../..
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include
LOCAL_C_INCLUDES += $(DELIVERY_PATH)/openssl/Android/include

LOCAL_MODULE:= libcurl

include $(BUILD_STATIC_LIBRARY)

#include $(CLEAR_VARS)

#LOCAL_MODULE	:= cyassl
#LOCAL_SRC_FILES	:= libcyassl.a

#include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)

#LOCAL_MODULE    := finalcurl
#LOCAL_SRC_FILES := test.cpp
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../

#LOCAL_STATIC_LIBRARIES := libcurl cyassl
#LOCAL_LDLIBS	:= -llog

#include $(BUILD_SHARED_LIBRARY)

