PROJECT = stm32f103-blink
BUILD_DIR = bin

SHARED_DIR = ../lib
CFILES = ./main.c

LDSCRIPT = ./stm32f103.ld

# TODO - you will need to edit these two lines!
DEVICE=stm32f1

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

# include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
# include $(OPENCM3_DIR)/mk/genlink-rules.mk
