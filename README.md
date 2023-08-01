# Pipex - @Codam
A project to practice using the fork/pipe functions, handle redirections, open/close file descriptors and learn about child/parent processes.

## How does it work?

```bash
git clone https://github.com/WriteSomeStuff/Pipex.git
cd Pipex
make
./pipex filename1 "command1" "command2" filename2
```
If filename1 doesn't exist, it will throw an error.
This should work like bash; < infile cmd1 | cmd2 > outfile. I don't handle awk, as this wasn't required for this project.
As example use ./pipex infile "grep "t"" "wc -l" outfile. This will grab all lines with a "t" from infile, count how many lines, then send the result to the outfile.
