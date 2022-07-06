# Koi-Koi Hanafuda

## Qt / C++ implementation of Koi-Koi

Koi-Koi (Japanese: こいこい) is a popular card game in Japan played with Hanafuda cards. The phrase "koi-koi" means "come on" in Japanese which is said when the player wants to continue the hand.

![Screenshot of the Koi-Koi Title](/../github-screenshots/screenshots/koikoi-title.png?raw=true "Koi-Koi Title")
![Screenshot of the Koi-Koi Gameboard](/../github-screenshots/screenshots/koikoi-gameboard.png?raw=true "Koi-Koi Gameboard")

## Build and Compile

### Dependencies

Dependency | Packages (Debian/Ubuntu)
---------- | --------
Dev tools | build-essential
Qt5 | qt5-default
lrelease-qt5 / lrelease | qttools5-dev-tools
[Meson](https://mesonbuild.com/Quick-guide.html) and [Ninja](https://ninja-build.org/) | meson

The following may be done to install dependencies on Debian/Ubuntu:
```
sudo apt install git meson build-essential qt5-default qttools5-dev-tools
```

### Build Instructions

The following may be done to compile and run:
```
git clone https://www.github.com/nightsky30/koikoi.git
cd koikoi
meson builddir
ninja -C builddir
./builddir/src/koikoi
```
### Installation (Optional)
```
ninja -C builddir install
koikoi
```
