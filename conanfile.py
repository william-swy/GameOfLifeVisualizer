from conans import ConanFile


class GameOfLifeVisualizer(ConanFile):
    name = "GameOfLifeVisualizer"
    version = "0.1"
    requires = (
        "catch2/2.13.7",
        "qt/5.15.2",
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"