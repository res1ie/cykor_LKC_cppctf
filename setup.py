from distutils.core import setup, Extension

ext = Extension('elliptic_curve', sources=['python_extension/python_extension.cpp', 'src/elliptic_curve.cpp'])

setup(name='elliptic_curve',
      version='1.0',
      description='Python package for performing elliptic curve operations',
      ext_modules=[ext])