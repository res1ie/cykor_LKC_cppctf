from setuptools import setup, Extension

add_module = Extension('add', sources=['addmodule.cpp'], libraries=['gmp'], library_dirs=['C:/msys64/mingw64/lib'])

setup(
    name='add',
    version='1.0',
    ext_modules=[add_module],
)