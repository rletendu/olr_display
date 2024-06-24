from PIL import Image


im = Image.open('mchp_ico.png')
pixels = list(im.getdata())
#print(pixels)

with open("out.h", 'w') as writer:
    i = 0
    writer.write("#define LOGO {\n")
    for p in pixels:
        i +=1
        entry = "0x{:02X},0x{:02X},0x{:02X},".format(p[0],p[1],p[2])
        writer.write(entry)
        if i%8==0:
            writer.write("\n")
        print(entry)
    writer.write("}\n")