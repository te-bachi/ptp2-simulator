
CC                  = gcc
GLOBAL_CFLAGS       = -Wall -ggdb -Iinclude
GLOBAL_LDFLAGS      = -ldl -rdynamic

all: $(PROGRAMS)

### HELP
# $(foreach var,list,text)      For each newly created variable 'var' in 'list',
#                               do whatever in 'text'
# $(call variable,param,...)    Call a defined subroutine
# $(1), $(2)                    Arguments of defined subroutines
# $(eval var)                   Expand 'var' and parse as makefile syntax
# $(var:pattern=replacement)    Substitutes 'var' with 'replacement'

### VARIABLE + MKDIR FOR EVERY PROGRAM
define VARIABLE_template

$(1)_OBJECT = $(addprefix obj/$(1)/,$($(1)_SOURCE:%.c=%.o))

obj/$(1):
	@echo "[MKDIR] $$@"
	@mkdir -p obj/$(1)
	
endef

### OBJECT FOR EVERY SOURCE FILE
define OBJECT_template

obj/$(1)/$($(2):%.c=%.o):: src/$($(2))
	@echo "[CC] $$<"
	@$(CC) -o $$@ -c $$< $(GLOBAL_CFLAGS) $($(1)_CFLAGS)

endef

### PROGRAM
define PROGRAM_template
$(foreach source,$($(1)_SOURCE),$(eval $(call OBJECT_template,$(1),source)))
$(1): obj/$(1) $($(1)_OBJECT)
	@echo "[LD] $$@"
	@$(CC) -o $$@ $($(1)_OBJECT) $(GLOBAL_LDFLAGS) $($(1)_LDFLAGS)

$(1)_clean:
	@echo "[CLEAR $(1)]"
	@rm -rf $(1) $($(1)_OBJECT) obj/$(1)
endef

$(foreach prog,$(PROGRAMS),$(eval $(call VARIABLE_template,$(prog))))
$(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))

clean: $(addsuffix _clean,$(PROGRAMS))

