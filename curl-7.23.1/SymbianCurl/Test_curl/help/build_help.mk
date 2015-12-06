# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Test_curl
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Test_curl
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : Test_curl_0xe3cfcb9d.hlp
Test_curl_0xe3cfcb9d.hlp : Test_curl.xml Test_curl.cshlp Custom.xml
	cshlpcmp Test_curl.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy Test_curl_0xe3cfcb9d.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del Test_curl_0xe3cfcb9d.hlp
	del Test_curl_0xe3cfcb9d.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo Test_curl_0xe3cfcb9d.hlp

FINAL : do_nothing
