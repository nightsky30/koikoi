# Koi-Koi Hanafuda

## Qt / C++ implementation of Koi-Koi

Koi-Koi (Japanese: こいこい) is a popular card game in Japan played with Hanafuda cards. The phrase "koi-koi" means "come on" in Japanese which is said when the player wants to continue the hand.

![Screenshot of the Koi-Koi Title](/../github-screenshots/screenshots/koikoi-title.png?raw=true "Koi-Koi Title")
![Screenshot of the Koi-Koi Gameboard](/../github-screenshots/screenshots/koikoi-gameboard.png?raw=true "Koi-Koi Gameboard")

## Installation

TBD

## Build and Compile

### Dependencies

Dependency | Packages
---------- | --------
Qt5 | Qt5 packages
lrelease-qt5 or lrelease | lrelease packages
[Meson](https://mesonbuild.com/Quick-guide.html) | Meson packages
[Ninja](https://ninja-build.org/) | Ninja packages

### Instructions

The following may be done to compile and run:
```
meson builddir
ninja -C builddir
./builddir/src/koikoi
```
