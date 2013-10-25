class IndexOutOfBoundsException {};

template <class T>
class DynamicSafeArray
{
	private:
   	T* data;
      int size;

   public:
   	DynamicSafeArray(): data(0), size(0) {}
      DynamicSafeArray(int size)
      {
      	this->size = size;
         data = new T[size];

         /*for (int i=0; i<size; i++)
         	*(data+i) = 0;*/
      }

      DynamicSafeArray(const DynamicSafeArray& rhs)
      {
      	size = rhs.size;
         data = new T[size];
         memcpy(data, rhs.data, sizeof(T)*size);
      }

      ~DynamicSafeArray()
      {
      	if (data != 0)
         	delete data;
			data = 0;
      }

      DynamicSafeArray& operator=(const DynamicSafeArray& rhs)
      {
      	if (this == &rhs)
         	return *this;
         
      	size = rhs.size;
         delete data;
         data=0;            
         data = new T[size];
         memcpy(data, rhs.data, sizeof(T)*size);
      }

      T& operator()(int index)
      {
      	if (index < 0 || index >= size)
         	throw IndexOutOfBoundsException();

         return *(data+index);
      }

      int getSize() { return size; }

      void resize(int newSize)
      {
         T* temp = new T[newSize];
         if (size < newSize)
         {
         	memcpy(temp, data, sizeof(T)*size);
            /*for (int i=size; i<newSize; i++)
            	*(data+i) = 0;*/
         }
         else
         	memcpy(temp, data, sizeof(T)*newSize);
			size = newSize;
      }
};
