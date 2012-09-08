README.txt -- hexdmp file exam utility, CRB, Sep 7, 2012

The hexdmp utility is used to examine the contents of files containing binary
data where the binary value of each byte is displayed in a pair of hexadecimal
digits. Sixteen values are shown in each row with the starting byte address on
the left. In the righthand column ASCII characters are shown if the binary
values happen to be printable ASCII characters, and a dot "." is shown as a
placeholder if the value is not a printable character. Output lines that
contain all zeros are suppressed and indicated with an ellipsis "...". The
output format resembles that of the debug utility in DOS.

Use
     hexdmp filename [start [end]]

The first argument is the name of the file to be examined. The next two
arguments are the optional start and ending byte addresses in the
file. Addresses can be either decimal or hexadecimal in the notation used for
hex data in C, for example 0x123abc.

Example
opus:/home/randyl/hexdmp> hexdmp README.txt 0 64
00000000  52 45 41 44 4D 45 2E 74  78 74 20 2D 2D 20 68 65  README.txt -- he
00000010  78 64 6D 70 20 66 69 6C  65 20 65 78 61 6D 20 75  xdmp file exam u
00000020  74 69 6C 69 74 79 2C 20  43 52 42 2C 20 53 65 70  tility, CRB, Sep
00000030  20 37 2C 20 32 30 31 32  0A 0A 54 68 65 20 68 65   7, 2012..The he

History
I originally wrote this program for my own use many years ago. I also used it
in programming courses I taught at University of Washington Extension.

License
It is my intention to use the Creative Commons (with attribution). Details to
follow.

C. R. Britten
