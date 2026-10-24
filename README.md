# Overview

This repo contains my solutions for Levels 1 and 2 of the Gecko Academy Challenge. Over the days following October 23rd, 2026, I'll attempt to solve Levels 3 and 4, and I'll push new commits with their solutions if I'm successful.

# My Approach

Initially I considered using a debugger to extract the solutions, but several things discouraged me. I have a Linux machine, and I wasn't sure whether there would be mismatches when debugging a Windows `.exe` file. I'm also fairly sure the `.exe` doesn't tolerate debuggers, since I saw an `IsDebuggerPresent` call, and I figured that bypassing it would defeat the purpose of a reverse engineering solution.

I used Ghidra to get an initial pseudo C decompilation of the binary `GeckoAcademy2026_7_challenge.exe`. Step by step, I tried to grasp what each block of pseudo C was doing, relabeling each parameter, variable and function as I understood its purpose. In parallel, I translated that pseudo C into actual C, written in each level's `solution.c` file. My goal was for these files to take the `username` as a parameter and generate the solution for each level.

## Considerations and Personal Limitations

I have never used C or Assembly in a professional setting, only in my own exploratory projects, so I'm not very familiar with their syntax. I had to go through the docs to understand the signatures of some C functions. For other parts I relied on AI to understand what the pseudo C was doing. For example, you'll see two versions of the `rotate_left` function in the solutions. I would have never been able to understand that the original code was rotating a hex number to the left without the help of AI. I also used AI to translate parts of the decompiled C syntax which was simply to obscure for me to understand into code I could actually read.

That being said, the reverse engineering process and the search for the solutions were done entirely by me. The C code inside the `solution.c` files was also written entirely by me. I can vouch for that code, and I can explain it in a live meeting if needed.

## Using the solution.c Scripts

To get the solutions, compile and run the `solution.c` file of each level, passing the username as the first argument. The solution will be printed to the console.

```bash
# Run from the root of this repo
gcc level-1/solution.c -o level-1/solution && level-1/solution eliel
gcc level-2/solution.c -o level-2/solution && level-2/solution eliel
```
