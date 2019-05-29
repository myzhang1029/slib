from setuptools import setup, Extension
from Cython.Build import cythonize

version = None
for line in open("CMakeLists.txt").readlines():
    if line.find("project") != -1:
        version = line.split()[-1]
        break

ext_modules = [
    Extension(
        "sbl",
        sources = ["sbl.pyx"],
        libraries = ["sbl", "m"]
    )
]

setup(
    name="sbl",
    version=version,
    ext_modules=cythonize(
        ext_modules,
        language_level = 3
    )
)
