# Lab 6. Design Patterns: Dungeon Editor

## Task

Write a dungeon editor for NPCs on a 500 x 500 map.
Variant: Bear kills Werewolf, Werewolf kills Rogue, Rogue kills Bear.
NPCs are created by a factory (also from a text line), saved to and loaded from a file, and printed.
The battle mode makes every pair within the given range fight; the winner is chosen by a Visitor with double dispatch, the killed NPCs are removed, and every kill is reported to Observers that print to the screen and append to `log.txt`.

## Build and run

```bash
make run LAB=lab6 < lab6/tests/data/01.in
```

The log file can be changed with `ARGS=path/to/log.txt`.

## Example

Input:

```text
add Bear Baloo 0 0
add Werewolf Lupin 10 10
add Rogue Robin 300 300
add Bear Fozzie 310 305
print
battle 50
print
```

Output:

```text
Bear Baloo (0, 0)
Werewolf Lupin (10, 10)
Rogue Robin (300, 300)
Bear Fozzie (310, 305)
Baloo killed Lupin
Robin killed Fozzie
Killed: 2
Bear Baloo (0, 0)
Rogue Robin (300, 300)
```

## Notes

- Commands: `add <Type> <name> <x> <y>`, `print`, `battle <range>`, `save <file>`, `load <file>`.
- Coordinates must satisfy $0 \le x, y \le 500$, both for `add` and for every line of a loaded file.
- Two NPCs fight if the distance between them is at most the range: $\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2} \le r$.
- An NPC killed in a battle does not fight the remaining pairs.
