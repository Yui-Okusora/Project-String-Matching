Project-String-Matching: String Matching Algorithm Analysis

## Team members:

- Đỗ Quang Dũng
- Dương Ngọc Khôi
- Hồ Đăng Thiên Phúc
- Lê Thiên Long
- Phạm Nhật Đăng Khoa

------------------------------------------------------------
HOW TO RUN
------------------------------------------------------------

Usage : 01.exe -a [ algorithm ] -i [ input_file ] -o [ output_file ]

Options :
-a [ algorithm ] Select algorithm : bf , rk , kmp , bm, za
-i [ input_file ] Path to provided data file
-o [ output_file ] Path to the result output file


The input file structure is:

- The first line contains two integers R and C (1 ≤ R, C ≤ 1000) — the number of rows and
columns in the puzzle grid.

- The next R lines describe the grid. Each line contains C lowercase English characters, separated
by a single space.

- The next line contains an integer K (1 ≤ K ≤ 100) — the number of keywords to search.

- The following K lines each contain a single string S — the keyword to find in the grid.

------------------------------------------------------------
TECHNICAL SPECIFICATIONS
------------------------------------------------------------
* Language: C++17.
* Build System: CMake 3.18 or higher.
* Compiler Support: MSVC and GCC.

------------------------------------------------------------
COMPILATION
------------------------------------------------------------

USING CMAKE (RECOMMENDED):
  1. mkdir build
  2. cd build
  3. cmake ..
  4. cmake --build . --config Release

OR:
  Run build.bat.
