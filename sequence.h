class Sequence
{
	private:
   	string sequence;
      string name;
      int length;

   public:
   	Sequence(): sequence(""), name(""), length(0) {}
   	Sequence(string sequence, string name): sequence(sequence), name(name) { length = sequence.length(); }

      void setSequence(string s) { sequence = s; length = sequence.length(); }

      bool operator==(Sequence s)
      {
      	return ((sequence == s.sequence) && (name == s.name));
      }

      bool operator!=(Sequence s)
      {
      	return !(*this == s);
      }

      string getSequence() { return sequence; }
      string getName() { return name; }
      int getLength() { return length; }
};