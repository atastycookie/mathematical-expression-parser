import setuptools

long_description = ""

setuptools.setup(
    name="tcalc",
    version="1.0.0",
    author="aTastyCookie",
    description="СИНТАКСИЧЕСКИЙ АНАЛИЗ ВЫРАЖЕНИЯ. ПАРСЕР МАТЕМАТИЧЕСКИХ ВЫРАЖЕНИЙ.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/aTastyCookie/mathematical-expression-parser",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Operating System :: OS Independent",
    ],
    install_requires=[],
    include_package_data=True,
)
