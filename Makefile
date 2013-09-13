
PROGRAMS                = ptp-simulator

ptp-simulator_SOURCE    = ptp-simulator-main.c \
                          ptp-simulator-window.c \
                          ptp-simulator-ui-manager.c \
                          ptp-simulator-toolbar.c \
                          ptp-simulator-packet-list.c \
                          ptp-simulator-packet-detail.c \
                          ptp-simulator-packet-dump.c \
                          ptp-simulator-actions.c
                          
ptp-simulator_CFLAGS    = `pkg-config --cflags gtk+-3.0`
ptp-simulator_LDFLAGS   = `pkg-config --libs gtk+-3.0`

include Makefile.inc

