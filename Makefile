ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

# include ./snes_rules
include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := raineffect

TARGET := RAINEFFECT
GTITLE := -ht"$(TARGET)"

all: level $(ROMNAME).sfc
	$(SNTOOLS) -hi! $(GTITLE) $(ROMNAME).sfc
	cp $(ROMNAME).sfc $(ROMNAME)_ntsc.sfc
	$(SNTOOLS) -hi! -hS! $(GTITLE) -hc03 $(ROMNAME).sfc
	mv $(ROMNAME).sfc $(ROMNAME)_pal.sfc

cleanRom:
	@echo clean rom
	@rm -f $(ROMNAME).sfc $(ROMNAME).sym $(ROMNAME)_ntsc.sfc $(ROMNAME)_pal.sfc

cleanGfxRain:
	@echo clean rain graphics data
	@rm -f res/home/*.pic res/home/*.map res/home/*.pal

clean: cleanBuildRes cleanRom cleanGfx cleanGfxRain cleanAudio

rain.pic: res/home/rain.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs8 -pe0 -fbmp -m $<

terrain.pic: res/home/terrain.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs8 -pe1 -fbmp -m $<

level: rain.pic terrain.pic
