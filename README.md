BFC
-
Brainf*ck compiler written in C++, with compiler optimizations<br>
Compiles bf code directly to NASM assembly, which provides extermely fast compile and execution time<br>
Uses 32-bit linux system calls<br>
## Tested copy.sh examples
yapi.bf - Segmentation fault<br>
hellom.bf - Works perfectly<br>
numwarp.bf - Does not work<br>
beer.b - Almost works<br>
quine505.b - Does not work<br>
char.bf - Works perfectly<br>
pi16.bf - Segmentation fault<br>
dbf2c.b - Almost works<br>
mandelbrot.b - Segmentation fault<br>
dquine.b - Works, but not terminates<br>
oobrain.b - Segmentation fault<br>
bockbeer.b - Almost works<br>
rot13.b - Does not work<br>
wc.b - Does not work<br>
triangle.bf - Just Works<br>
squares.b - Does not work<br>
calculator.bf - Almost works<br>
cellsize.bf - Does not work<br>
Also copy.sh text generator works too<br>
A lot of the examples straight up just don't work, that's because I have little experience with nasm assembly, or copy.sh uses it's own brainf*ck, which is different from mine
