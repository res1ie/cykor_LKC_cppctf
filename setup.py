from distutils.core import setup, Extension

module = Extension('spam', sources = ['spam.cpp'])

setup(name='spam',
        version='1.0',
        ext_modules=[module])