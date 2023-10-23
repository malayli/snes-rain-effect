.include "hdr.asm"

.section ".rodata1" superfree

rainPic: .incbin "res/home/rain.pic" 
rainPic_end:

rainMap: .incbin "res/home/rain.map" 
rainMap_end:

rainPalette: .incbin "res/home/rain.pal" 
rainPalette_end:

terrainPic: .incbin "res/home/terrain.pic" 
terrainPic_end:

terrainMap: .incbin "res/home/terrain.map" 
terrainMap_end:

terrainPalette: .incbin "res/home/terrain.pal" 
terrainPalette_end:

.ends
