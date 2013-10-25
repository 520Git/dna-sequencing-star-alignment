class AlignmentTool
{
	private:
   	DynamicSafe2DArray<int> subMatrix;
      int d;
		Alignment al;
	   Sequence s1;
   	Sequence s2;
      int score;

      int S(char ch1, char ch2)
      {
      	if (ch1 > 96) ch1 -= 32;
         if (ch2 > 96) ch2 -= 32;
      	switch (ch1)
         {
         	case 'A':
            	switch (ch2)
               {
                	case 'A':
                  	return subMatrix(0,0);
      	   	   case 'G':
         	   		return subMatrix(0,1);
		            case 'C':
      		      	return subMatrix(0,2);;
		            case 'T':
                  	return subMatrix(0,3);;
               }
            case 'G':
            	switch (ch2)
               {
                	case 'A':
                  	return subMatrix(1,0);
      	   	   case 'G':
         	   		return subMatrix(1,1);
		            case 'C':
      		      	return subMatrix(1,2);
		            case 'T':
                  	return subMatrix(1,3);
               }
            case 'C':
            	switch (ch2)
               {
                	case 'A':
                  	return subMatrix(2,0);
      	   	   case 'G':
         	   		return subMatrix(2,1);
		            case 'C':
      		      	return subMatrix(2,2);
		            case 'T':
                  	return subMatrix(2,3);
               }
            case 'T':
            	switch (ch2)
               {
                	case 'A':
                  	return subMatrix(3,0);
      	   	   case 'G':
         	   		return subMatrix(3,1);
		            case 'C':
      		      	return subMatrix(3,2);
		            case 'T':
                  	return subMatrix(3,3);
               }
         }
      }

      readScoringScheme()
      {
      	ifstream inp;
         inp.open("scoringScheme.txt");
         inp >> d;

         for (int i=0; i<4; i++)
         	for (int j=0; j<4; j++)
            	inp >> subMatrix(i,j);

         inp.close();
      }

   public:
   	AlignmentTool(): score(0) { subMatrix = DynamicSafe2DArray<int>(4,4); readScoringScheme(); }
      AlignmentTool(Sequence& s1, Sequence& s2): s1(s1), s2(s2), score(0) { subMatrix = DynamicSafe2DArray<int>(4,4); readScoringScheme(); }

      int getLastScore() { return score; }

      Alignment retrieveAlignment() { return al; }

      void align(Sequence& s1, Sequence& s2) { this->s1 = s1; this->s2 = s2; align(); }

      void align()
      {
      	// Align the two sequences using Needleman-Wunsch algorithm.

         DynamicSafe2DArray<int> scores(s2.getLength()+1, s1.getLength()+1);

         string seq1 = s1.getSequence();
         string seq2 = s2.getSequence();

         int len = seq2.length();
         //int d = -5;			// gap penalty

         for (int i=0; i<=len; i++)
         	scores(i,0) = d*i;

         len = seq1.length();

         for (int i=0; i<=len; i++)
         	scores(0,i) = d*i;

         len = seq2.length();
         int len2 = seq1.length();
         int max;

         int score1, score2, score3;

         for (int i=1; i<=len; i++)
         {
         	for (int j=1; j<=len2; j++)
            {
            	score1 = scores(i-1, j-1) + S(seq2[i-1], seq1[j-1]);
               score2 = scores(i-1, j) + d;
               score3 = scores(i, j-1) + d;

               if (score2 > score1) max = score2;
               else max = score1;
               if (score3 > max) max = score3;

               scores(i,j) = max;
            }
         }

        	score = scores(len, len2);
         /*for (int i=0; i<=seq2.length(); i++)
         {
         	for (int j=0; j<=seq1.length(); j++)
            {
            	cout << scores(i,j) << '\t';
            }
            cout << endl;
         }

         system("pause");*/

         string alignmentA = "";
         string alignmentB = "";

         int i = seq2.length();
         int j = seq1.length();
         while (i > 0 && j > 0)
         {
         	int s = scores(i,j);
            int sDiag = scores(i-1, j-1);
            int sUp = scores(i-1, j);
            int sLeft = scores(i, j-1);

            if (s == ( sDiag + S(seq2[i-1],seq1[j-1]) ))
            {
            	alignmentA = seq1[j-1] + alignmentA;
               alignmentB = seq2[i-1] + alignmentB;
               j--; i--;
            }
            else if (s == (sUp + d))
            {
            	alignmentA = "*" + alignmentA;
               alignmentB = seq2[i-1] + alignmentB;
            	i--;
            }
            else
            {
            	alignmentB = "*" + alignmentB;
               alignmentA = seq1[j-1] + alignmentA;
               j--;
            }
         }

         while (i>0)
         {
         	alignmentB = seq2[i-1] + alignmentB;
            alignmentA = "*" + alignmentA;
            i--;
         }

         while (j>0)
         {
         	alignmentB = "*" + alignmentB;
            alignmentA = seq1[j-1] + alignmentA;
            j--;
         }

         al.setAlignmentA(alignmentA);
         al.setAlignmentB(alignmentB);
         al.setNameA(s1.getName());
         al.setNameB(s2.getName());
      }
};