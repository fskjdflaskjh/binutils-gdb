# Target: Fujitsu FRV processor
TDEPFILES= frv-tdep.o solib.o solib-frv.o
TM_FILE= tm-frv.h
SIM_OBS = remote-sim.o
SIM = ../sim/frv/libsim.a
