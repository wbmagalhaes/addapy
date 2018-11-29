from distutils.core import setup, Extension

c_ext = Extension(
    "addapy", ["wrapper.c", "adda.c"], libraries=['bcm2835'])

setup(
    ext_modules=[c_ext],
)
