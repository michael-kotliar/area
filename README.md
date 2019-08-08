# Calculate area of the polygon

## Requirements
- cmake
- OpenCV

## Installation
    
```
git clone https://github.com/michael-kotliar/area.git
cd area
cmake .
make
```

## Usage

```
./bin/area --coord <path to the coordinates file>
```

Examples of the input files can be found in the `test` directory.

Input file structure
```
15,  0,   0,   0
0,   0,   0,  10
0,  10,   2,  10
2,  10,   2,   3
2,   3,  13,   3
13,  3,  15,   0
```
Expected output
```
Area = 55.92
```