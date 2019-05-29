from setuptools import setup, Extension
from Cython.Build import cythonize

ext_modules = [
    Extension(
        "sbl",
        sources=["sbl.pyx"],
        libraries=["sbl", "m"]
    )
]

setup(name="sbl", ext_modules=cythonize(ext_modules))
