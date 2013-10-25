class Validator
{
	private:
   	string errorMsg;
      bool valid;

   public:
   	Validator(): valid(1), errorMsg("") {}

      bool isValidHeader(string str)
      {
      	int state = 0;
         int len = str.length();

         for (int i=0; i<len; i++)
         {
         	if ( !state )
            {
            	if (str[i] != '>')
               {
               	errorMsg = "Expected > at location 0";
                  return valid = false;
               }
               state = 1;
            }
            else if (state == 1)
            {
            	if ( str[i] > 47 && str[i] < 58 || str[i] == '_' )
               {
               	errorMsg = "Name cannot start with number or underscore";
                  return valid = false;
               }
               state = 2;
            }
            else if (state)
            {
            	if ( (str[i] < 65 || str[i] > 90) && (str[i] < 48 || str[i] > 57) && str[i] != '_' )
               {
               	errorMsg = "Invalid character in name";
                  return valid = false;
               }
            }

         }

         if (state == 2) { errorMsg = ""; return valid = true; }
         else if (state == 1) { errorMsg = "Sequence name not present"; return valid = false; }
         else return valid = false;
      }

      bool isValidSequence(string& str)
      {
      	int len = str.length();
         for (int i=0; i<len; i++)
         {
         	if ( !(str[i] == 'A' || str[i] == 'C' || str[i] == 'G' || str[i] == 'T' || str[i] == 'a' || str[i] == 'c' || str[i] == 'g' || str[i] == 't' ) )
            {
               errorMsg = "Invalid character in sequence";
            	return valid = false;
            }
         }
         	errorMsg = "";
            return valid = true;
      }

      string getErrorMessage() { return errorMsg; }
      bool lastValid() { return valid; }
};
