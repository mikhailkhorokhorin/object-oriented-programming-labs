# Lab 7. Asynchronous Programming: Dungeon Simulation

## Task

Turn the dungeon from lab 6 into a real-time simulation with three threads.
Variant: 50 random NPCs on a 100 x 100 map; move and kill distances are Bear 5/10, Rogue 10/10, Werewolf 40/5; Bear kills Werewolf, Werewolf kills Rogue, Rogue kills Bear.
The movement thread moves NPCs and puts every pair within kill distance into a bounded task queue; the battle thread takes fights from the queue, both sides roll a d6 and the attacker wins if its roll is higher.
The main thread prints the map every second, stops the simulation after 30 seconds and prints the survivors.

## Build and run

```bash
make run LAB=lab7 ARGS=2
```

`ARGS` sets the duration as a positive whole number of seconds (default 30).

## Example

Output of a 2 second run (shortened, the placement is random):

```text
=== Map (50 alive) ===
Rogue Rogue_1 (85, 79)
Rogue Rogue_2 (50, 60)
...
Rogue_34 killed Bear_5
Rogue_17 killed Bear_36
Rogue_18 killed Bear_22
...
=== Map (31 alive) ===
...
=== Survivors (21) ===
Rogue Rogue_2 (20, 60)
Bear Bear_4 (53, 22)
Werewolf Werewolf_7 (59, 80)
...
```

## Notes

- Every move is a random integer offset within the move distance $d$ of the NPC, $\sqrt{\Delta x^2 + \Delta y^2} \le d$, so diagonal moves are not longer than straight ones. NPCs stay inside $[0, 100)$ on both axes.
- Threads are `std::jthread`; the battle thread blocks in `TaskQueue::pop` on a condition variable and both workers stop through `std::stop_token`.
- `NPC::tryKill` checks and changes the state under one mutex, so an NPC dies only once.
- Dice use a `thread_local` `std::mt19937`; kills are also appended to `log.txt`.
