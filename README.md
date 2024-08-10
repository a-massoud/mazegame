# mazegame

A simple maze game mostly made to prove I'm better than my younger self.

To compile the SDL version:
```
> mkdir build && cd build
> cmake -B. -S..
> cmake --build
```

To compile the curses version:
```
> mkdir build && cd build
> cmake -B. -S.. -DCURSES_BUILD=ON
> cmake --build
```

The executable goes in `bin/`.
