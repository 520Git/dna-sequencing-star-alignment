class Alignment
{
	private:
   	string nameA;
      string nameB;

      string alignmentA;
      string alignmentB;

   public:

   	Alignment()
      {
      	nameA = "";
         nameB = "";

         alignmentA = "";
         alignmentB = "";
      }

      void setAlignmentA(string alignmentA)
      {
      	this->alignmentA = alignmentA;
      }

      void setNameA(string nameA)
      {
      	this->nameA = nameA;
      }

      void setAlignmentB(string alignmentB)
      {
      	this->alignmentB = alignmentB;
      }

      void setNameB(string nameB)
      {
      	this->nameB = nameB;
      }

      void print()
      {
      	cout << alignmentA << endl;
         cout << alignmentB << endl;
      }

      string getAlignmentA() { return alignmentA; }
      string getAlignmentB() { return alignmentB; }

      string getNameA() { return nameA; }
      string getNameB() { return nameB; }
};