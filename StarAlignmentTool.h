class StarAlignmentTool
{
	private:
   	Sequence star;
      List<Sequence> sequences;

	public:
   	StarAlignmentTool() {}

      void setStar(Sequence& s)
      {
      	star = s;
      }

      void align(Alignment& al)
      {
      	/*
         	First, check whether the alignmentA is star or alignmentB is star
         */

         string currStar = star.getSequence();
         string alignment;
         string newStar;
         string alName;

         /*cout << al.getNameA() << endl;
         cout << al.getNameB() << endl << endl;*/

         if (al.getNameA() == star.getName())
         {
         	// Alignment A is star
         	newStar = al.getAlignmentA();
            alignment = al.getAlignmentB();
            alName = al.getNameB();
         }
         else
         {
         	//Alignment B is star
         	newStar = al.getAlignmentB();
            alignment = al.getAlignmentA();
            alName = al.getNameA();
         }

         /*
         	for i = 0 to length of longer(currStar, newStar)
            	if index of currStar is out of range
               	append gap to currStar, and all sequences.
               else if index of new is out of range
               	append gap to newStar and alignment
            	else if currStar[i] == newStar[i]
               	continue;
               else if currStar has gap at index i
               	insert gaps into alignment and newStar.
               else (newStar has gap at index i)
               	insert gaps into currStar and all sequences.
         */

         //int len1 = currStar.length();
         //int len2 = newStar.length();
         //int gt = len1;
         string tempSeq;

			//if (len2 > len1) gt = len2;

         for (int i=0; i<currStar.length() || i<newStar.length(); i++)
         {
         	if (i >= currStar.length()) // currStar index out of range
            {
            	//append gap to currStar, and all sequences.
               currStar.append("*");
               for (Node<Sequence>* j=sequences.getHead(); j; j=j->getNext())
               {
               	tempSeq = j->getInfo().getSequence();
                  tempSeq.append("*");
                  j->getInfo().setSequence(tempSeq);
               }
            }
            else if (i >= newStar.length()) // newStar index out of range
				{
            	newStar.append("*");
               alignment.append("*");
            }
            else if (currStar[i] == newStar[i]) continue;
            else if (currStar[i] == '*')
            {
            	//insert gaps into alignment and newStar
               alignment = alignment.substr(0,i) + "*" + alignment.substr(i);
               newStar = newStar.substr(0,i) + "*" + newStar.substr(i);
            }
            else
            {
            	//insert gaps into currStar and all sequences

               currStar = currStar.substr(0,i) + "*" + currStar.substr(i);
               for (Node<Sequence>* j=sequences.getHead(); j; j=j->getNext())
               {
               	tempSeq = j->getInfo().getSequence();
                  tempSeq = tempSeq.substr(0,i) + "*" + tempSeq.substr(i);
                  j->getInfo().setSequence(tempSeq);
               }
            }
         }

         star.setSequence(currStar);
         sequences.addToTail( Sequence(alignment, alName) );
      }

      void writeToFile(char* filename)
      {
         /*First compute size of max name*/

         string name = star.getName();

         for (Node<Sequence>* j=sequences.getHead(); j; j=j->getNext())
         {
         	if (j->getInfo().getName().length() > name.length())
            	name = j->getInfo().getName();
         }

         int offset = name.length() + 1;

      	ofstream os;
         os.open(filename);

         Sequence s;

         os << star.getName();
         for (int i=star.getLength()-1; i<offset; i++)
         	os << ' ';
         os << ": ";
         os << star.getSequence() << endl;
      	for (Node<Sequence>* j=sequences.getHead(); j; j=j->getNext())
         {
         	s = j->getInfo();
         	os << s.getName();
        		for (int i=s.getLength()-1; i<offset; i++)
         		os << ' ';
         	os << ": ";
         	os << s.getSequence() << endl;
         }

         os.close();
      }

      void printAll()
      {
      	cout << star.getSequence() << endl;
      	for (Node<Sequence>* j=sequences.getHead(); j; j=j->getNext())
         {
         	cout << j->getInfo().getSequence() << endl;
         }
      }
};