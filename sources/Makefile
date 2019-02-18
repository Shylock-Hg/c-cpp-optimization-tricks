#CC = gcc
#RM = rm
#AR = ar
LN = ln
INSTALL = install
MKDIR = mkdir

DIR_BUILD = .build
prefix = /usr/local

PPFLAGS = -MT $@ -MMD -MP -MF $(patsubst %.o, %.d, $@)

CFLAGS_LOCAL = -Wall -g -std=c++11 -coverage -Wno-unused-private-field -O3
CFLAGS_LOCAL += $(CFLAGS)

APP_SOURCES = $(wildcard *.cc)
APP_OBJECTS = $(patsubst %.cc, %.o, $(APP_SOURCES))
APPS = $(basename $(APP_SOURCES))

DEPFILES = $(patsubst %.o, %.d, $(addprefix $(DIR_BUILD)/, $(APP_OBJECTS)))

.PHONY : all clean test

all : $(addprefix $(DIR_BUILD)/, $(APPS))

$(addprefix $(DIR_BUILD)/, $(APPS)) : $(DIR_BUILD)/% : ./%.cc Makefile | $(DIR_BUILD)
	$(CXX) $(CFLAGS_LOCAL) -o $@ $<

$(DIR_BUILD)/%.d : ;
.PRECIOUS : $(DIR_BUILD)/%.d

$(DIR_BUILD) :
	$(MKDIR) -p $@

test : all
	for app in $(APPS); do ./$(DIR_BUILD)/$${app}; done

clean :
	$(RM) -rf $(DIR_BUILD)
	$(RM) *.gcda *.gcno

include $(DEPFILES)
