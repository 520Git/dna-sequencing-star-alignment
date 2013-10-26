Multiple DNA Sequence Alignment
===============================

A part of bioinformatics involves "aligning" DNA sequences to gain insights from DNA. Aligning DNA sequences helps researchers identify relationships among different sequences (evolutionary relationships, for example).

Here is what a part of a DNA sequence looks like:

    SEQUENCE 1: aagtctaatttgctc
    SEQUENCE 2: atgtgtaatacgctatctcat

This is what these two sequences look like when aligned:

    SEQUENCE 1: aagtctaat***ttg*ctc**
    SEQUENCE 2: atgtgtaatacgctatctcat

Optimally aligning two sequences of length n has a time complexity of O(n^2) (see Needleman-Wunsch algorithm: http://en.wikipedia.org/wiki/Needleman-wunsch_algorithm). Optimally aligning k sequences using the same algorithm has exponential complexity. For k sequences, star alignment method provides a more efficient heuristic method of aligning sequences. The algorithm is described here: http://www.biostat.wisc.edu/bmi576/lectures/multiple-alignment.pdf

I developed this project as part of my course in data structures taken in Fall 2007.

Running the Program
-------------------

The program can be run from the command line. Input and output files have to be provided as arguments.

`MSATool input1.txt output.txt`

Files
-----

**Alignment.h** - Class Alignment holds data for two DNA sequences.

**AlignmentTool.h** - The class AlignmentTool is used to align two individual sequences.

**DynamicSafe2DArray** - Templatized wrapper class for 2D arrays.

**DynamicSafeArray** - Tempatized wrapper class for arrays.

**List.h** - Linked list.

**MSATool.cpp** - Main program that reads sequences from input file, uses AlignmentTool and StarAlignment to align them and writes output to the provided output file.

**scoringScheme.txt** - Contains data used by the AlignmentTool class for scoring. Can be edited for different scoring method.

**sequence.h** - The class Sequence is used to hold a single DNA sequence.

**StarAlignmentTool.h** - The class StarAlignmentTool aligns multiple sequences taking individual alignments as input using the star alignment method.

**Validator.h** - The class Validator is used to validate the input file before beginning alignment.
