KEV_LIB_PATH := $(KEV_C_PATH)/kev_lib

kev_caster_test: kev_caster_test.c ../kev_caster.o $(KEV_LIB_PATH)/kev_test.o
	gcc -Wall ../kev_caster.o $(KEV_LIB_PATH)/kev_test.o kev_caster_test.c -I "$(KEV_LIB_PATH)/" -I ../ -o kev_caster_test -lm

../kev_caster.o: ..//kev_caster.c ../kev_caster.h
	gcc -Wall ../kev_caster.c -c -o ../kev_caster.o -lm

$(KEV_LIB_PATH)/kev_test.o: $(KEV_LIB_PATH)/kev_test.c
	gcc -Wall $(KEV_LIB_PATH)/kev_test.c -c -o $(KEV_LIB_PATH)/kev_test.o
