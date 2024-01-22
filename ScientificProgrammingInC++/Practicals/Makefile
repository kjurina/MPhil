DIRS:=Practical_1 Practical_2 Practical_3 Practical_4 Practical_5 Practical_7 Practical_8 Practical_9 Practical_10 Practical_12a Practical_11a

define addDirSources
  ALL_ANSWERS+=$(wildcard $(1)/Answers)
  ALL_FILES+=$(wildcard $(1)/*.C)
  ALL_FILES+=$(wildcard $(1)/*.sh)
  ALL_EXES+=$(patsubst %.C,%,$(wildcard $(1)/*.C))
endef

$(foreach d,$(DIRS),$(eval $(call addDirSources,$(d))))

define addDirMultiSource
  ALL_ANSWERS+=$(wildcard $(1)/Answers)
  ALL_FILES+=$(wildcard $(1)/*.C)
  ALL_FILES+=$(wildcard $(1)/*.sh)
endef

OTHER_DIRS:=Practical_6
$(foreach d,$(OTHER_DIRS),$(eval $(call addDirMultiSource,$(d))))

.PHONY:all

all: $(ALL_EXES)

tar: $(ALL_FILES) Makefile
	tar -jcf PracticalSolutions.tar.bz2 $(ALL_FILES) $(ALL_ANSWERS) Makefile

%:%.C
	g++ -std=c++11 -c $< -o $@
