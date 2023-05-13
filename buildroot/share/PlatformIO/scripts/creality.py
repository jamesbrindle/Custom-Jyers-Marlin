import os
Import("env")

# Relocate firmware from 0x08000000 to 0x08007000
try:
    for define in env['CPPDEFINES']:
        if define[0] == "VECT_TAB_ADDR":
            env['CPPDEFINES'].remove(define)
            break
except Exception as e:
    print("Error 1: " + str(e))

try:
    env['CPPDEFINES'].append(("VECT_TAB_ADDR", "0x08007000"))
except Exception as e:
    print("Error 2: " + str(e))

custom_ld_script = os.path.abspath("buildroot/share/PlatformIO/ldscripts/creality.ld")

for i, flag in enumerate(env['LINKFLAGS']):
    if "-Wl,-T" in flag:
        env['LINKFLAGS'][i] = "-Wl,-T" + custom_ld_script
    elif flag == "-T":
        env['LINKFLAGS'][i + 1] = custom_ld_script
