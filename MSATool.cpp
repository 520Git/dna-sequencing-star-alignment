#include <iostream>
#include <string>
#include <fstream>
#include "sequence.h"
#include "List.h"
#include "DynamicSafeArray.h"
#include "DynamicSafe2DArray.h"
#include "Validator.h"
#include "Alignment.h"
#include "AlignmentTool.h"
#include "StarAlignmentTool.h"

int main(int argc, char* argv[])
{
	ifstream is;
   is.open(argv[1]);

   char st[101];
   string str;
   string sequence;
   string name;
   Validator v;
   int length;
   int line = 0;
   int len = 0;
   int sequenceNum = 0;
   int numSequences;
   is >> numSequences;
   is.get();
   DynamicSafeArray<Sequence> sequences(numSequences);

   /*
   	Read the file line by line.
   */

   while ( !is.eof() )
   {
   	line++;
   	is.getline(st, 100);	// get a line from file
      str = st;
      if (str.length() == 0)
      {
      	/*
         	A new line means a sequence has been read. Create object in
            sequences array.
         */
      	sequences(sequenceNum++) = Sequence(sequence, name);
         sequence = "";
      }
      else if (str[0] == '>') 		// If line is header line
      {
      	/*
         	Validate header line, and then extract
            name, and store in variable name.
         */

         if (!v.isValidHeader(str))	//line is invalid. Print error and exit.
         {
         	cout << "The input file is not well formed. Error at line " << line << ": " << v.getErrorMessage() << endl;
            system("pause");
            exit(1);
         }

         name = "";
         len = str.length();

         for (int i=1; i<len; i++)
         {
         	name.append(str[i]);
         }
      }
      else
      {
      	/*
         	line is a sequence. append to current sequence.
         */
      	if (!v.isValidSequence(str))	//line is invalid. Print error and exit.
         {
         	cout << "The input file is not well formed. Error at line " << line << ": " << v.getErrorMessage() << endl;
            system("pause");
            exit(1);
         }
         sequence.append(str);
      }
   }

   is.close();


   /*
   	We have all sequences in the sequences array. We now create all alignments
      between them, and place them in an alignments pool (A 2D array of alignments).
      Also, we populate the alignment scores matrix.
   */

   length = sequences.getSize();
   DynamicSafe2DArray<Alignment> alignments(length, length);
   DynamicSafe2DArray<int> alignmentScores(length, length);
   AlignmentTool at;

   for (int i=0; i<length; i++)
   {
   	alignmentScores(i,i) = 0;
   	for (int j=0; j<i; j++)
      {
      	at.align(sequences(i),sequences(j));
         alignments(i,j) = at.retrieveAlignment();
         alignmentScores(i,j) = alignmentScores(j,i) = at.getLastScore();
      }
   }

   /*
   	Now we find the "star". We will add all rows of alignmentScores array,
      and take the index of the sequence which forms the least sum of scores.
   */

   int min = 32767;
   int minIndex;
   int temp;

   for (int i=0; i<length; i++)
   {
   	temp = 0;
   	for (int j=0; j<length; j++)
      {
      	temp += alignmentScores(i,j);
      }

      if (temp < min)
      {
      	min = temp;
         minIndex = i;
      }
   }

   /*
   	The "star" is sequences(minIndex). Now we take all alignments with sequences(minIndex)
      and align in StarAlignmentTool.
   */

   StarAlignmentTool sat;
   sat.setStar(sequences(minIndex));

   for (int j=0; j<length; j++)
   {
   	if (minIndex<j)
      	sat.align(alignments(j,minIndex));
      else if (j<minIndex)
      	sat.align(alignments(minIndex,j));
   }

   /*
   	Now we just call the WriteToFile function,
      to write the multiple alignment to file.
   */

   sat.writeToFile(argv[2]);

   system("pause");
   exit(0);
}