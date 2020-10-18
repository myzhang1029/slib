from setuptools import setup, Extension
from Cython.Build import cythonize

version = None
for line in open("include/slib/general.h").readlines():
    if line.find("SBLLIB_VERSION") != -1:
        version = line.split()[-1]
    elif line.find("SBLLIB_MINOR") != -1:
        version += "." + line.split()[-1]
    elif line.find("SBLLIB_PATCHLEVEL") != -1:
        version += "." + line.split()[-1]
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
