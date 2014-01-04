.PHONY: all clean res run


include config


all: hdr.asm res $(OUTPUT).sfc
	$(SNTOOLS) -hi! $(GTITLE) $(TARGET).sfc

clean:
	@rm -f $(OFILES) $(TARGET).sfc *.pic *.pal *.map *.sym

res: pvsneslibfont.pic

run:
	$(EMULATOR) $(TARGET).sfc


hdr.asm:
	cp $(SNES_SDK)/include/hdr.asm .

pvsneslibfont.pic: pvsneslibfont.bmp
	$(GFXCONV) -n -gs8 -po2 -pc16 -pe1 -mR! -m! -p! $<


$(OUTPUT).sfc	: $(OFILES)
