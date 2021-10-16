PCK-Extract
===========

Tool to extract a Godot .pck file from a (Linux) ELF binary that
bundles it. Inspired by [fsb-extract-dumb](https://github.com/moon-chilled/fsb-extract-dumb)
by moon-chilled/Elijah Stone.

How to Build
------------
```
$ make
```

How to Run
----------
```
$ pck-extract godotgame.x86_64
```

The file will be extracted to `godotgame.x86_64.pck`.
