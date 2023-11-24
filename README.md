# Tools

## Bit Checker

Used to convert a decimal, hexadecimal, octal or binary number to all 3 other formats and show which bits are enabled.

```
Example: .\BitChecker.exe -h 10
Decimal     = 16
Hexadecimal = 0x10
Octal       = 020
Binary      = 10000

Index | Bit | Decimal | Hexadecimal | Octal
------+-----+---------+-------------+------
4     | 1   | 16      | 0x10        | 020
3     | 0   | 8       | 0x8         | 010
2     | 0   | 4       | 0x4         | 04
1     | 0   | 2       | 0x2         | 02
0     | 0   | 1       | 0x1         | 01
```

```
Example: .\BitChecker.exe
Not enough arguments

Usage: BitChecker.exe [bit list] [format] <unsigned number>

    bit list
        -la / --list-all (default)
        -le / --list-enabled
        -ln / --list-none

    format
        -d / --dec (default)
        -h / --hex
        -o / --oct
        -b / --bin
```

## File Locker

Used to open a file for generic read with full share mode and hold it open. Full share mode is the least intrusive way to open a file, so all operations should still be allowed as long as they share read. I have used this tool to test scenarios and verify behaviour.

I have found an interesting problem on Windows 10 and 11. When a file is open with generic read and full share mode:
* The file can be moved/renamed.
* The file can be deleted.
* The parent folder can NOT be moved/renamed.
* The parent folder can be deleted.

The file can be moved out, then the parent folder can be moved/renamed and the file can be moved back in. This would achieve the same result, so there's no reason why the parent folder cannot be moved/renamed while the open file is inside, but this operation gets blocked.

This is reproducible with explorer.exe, but it also effects many other apps and their interactions.

```
Example: .\FileLocker.exe .\Test\Test.txt
Handle opened for file ".\Test\Test.txt"
Press any key to continue . . .
```

```
Example: .\FileLocker.exe
Not enough arguments

Usage: FileLocker.exe <file>
```
