# fixlator

Fixlator is a lightweight and fast cross-platform tool that assists front-end trade support in translating and
visualising the contents of FIX messages. It's written in C++ and is built on top of WxWidgets and hffix.

## Stuff I'm using

- [hffix](https://github.com/jamesdbrock/hffix)
- [date](https://github.com/HowardHinnant/date)
- [wxWidgets](https://github.com/wxWidgets/wxWidgets)

## Building

This project uses CMake's FetchContent feature to manage dependency downloads and building. This might change in the
future for release builds, but I'm keeping it like this for ease of development.

```bash
git clone https://github.com/spez1998/fixlator.git
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./build/src/fixlator
```

If you find a bug I haven't yet found, I'll give you a follow.

## Roadmap

- [ ] Show human-readable FIX messages in a sortable list
- [ ] Show detailed info about a double-clicked message in the list
- [ ] Graphing and/or trend reports
- [ ] Conversion to/from FIXML
- [ ] Save/load session
- [ ] CLI tool for all this stuff

## Feature requests

Please give some to me! In particular, if you're working on a trading desk as support, let me know what you want from
your FIX parsing tooling - graphs / trend reports? Conversion to/from FIXML? Reach out!

## Why?

I did some work on a similar (CLI) tool in Python ages ago, but it was unbelievably shit. This is my effort to cleanse
my soul of that.
