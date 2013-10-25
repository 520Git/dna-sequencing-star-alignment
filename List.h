class ListEmptyException {};
class ListException {};

template <class T>
class Node
{
	private:
		T info;
   	Node* next;

   public:
   	Node(): next(0) {}
      Node(T info): next(0), info(info) {}

      T& getInfo() { return info; }
      Node* getNext() { return next; }
      void setInfo(T& info) { this->info = info; }
      void setNext(Node* n) { next = n; }
};

template <class T>
class List
{
   private:
		Node<T>* head;
   	int size;

      void deleteAll()
      {
      	Node<T>* curr = head;
         Node<T>* prev = head;
			head = 0;

         while (!curr)
         {
         	curr = curr->getNext();
            prev->setNext(0);
            delete prev;
         }
      }

   public:
   	List(): head(0), size(0) {};

      List(const List& l)
      {
      	head = 0;
         size = l.size;
      	for (int i=0; i<l.size; i++)
         {
         	addToTail(l.elementAt(i));
         }
      }

      List& operator=(const List& rhs)
      {
      	if (this == &rhs)
         	return *this;
         empty();
         for (int i=0; i<rhs.size; i++)
         {
         	addToTail(rhs.elementAt(i));
         }
         size = rhs.size;
         return *this;
      }

      int getSize() { return size; }
      Node<T>* getHead() { return head; }

      void empty() { if (head != 0) deleteAll(); size = 0;}

      void addToTail(T info)
      {
      	Node<T>* n = new Node<T>(info);
         n->setNext(0);
         if (head == 0) { head = n; }
         else
         {
         	Node<T>* temp = head;
            while (temp->getNext() != 0)
            {
            	temp = temp->getNext();
            }
            temp->setNext(n);
         }
         size++;
      }

      void addToHead(T info)
      {
      	Node<T>* n = new Node<T>(info);
         n->setNext(head);
         head = n;
         size++;
      }

      void remove(T data)
      {
      	//if at head, remove from head
         if (head->getInfo() == data)
         {
         	removeFromHead();
         }
         else
         {
         	Node<T>* temp = head;
            while (temp->getNext() && temp->getNext()->getInfo() != data)
            	temp = temp->getNext();
            if (!(temp->getNext())) return;
            Node<T>* temp2 = temp->getNext();
            temp->setNext(temp2->getNext());
            temp2->setNext(0);
            delete temp2;
            size--;
         }
      }

      T elementAt(int index)
      {
      	if (index < 0 || index >= size) throw ListException();

         Node<T>* temp = head;
         for (int i=0; i<index; i++)
         {
         	temp = temp->getNext();
            if (!temp) throw ListException();
         }
         return temp->getInfo();
      }

      T removeFromTail()
      {
      	if (head == 0) throw ListEmptyException();
         size--;
         if (head->getNext() == 0)
         {
         	T info = head->getInfo();
            delete head;
            head = 0;
            return info;
         }
         else
         {
      		Node<T>* temp = head;
         	while(temp->getNext()->getNext() != 0)
         	{
            	temp = temp->getNext();
            }

            T info = temp->getNext()->getInfo();
            delete temp->getNext();
            temp->setNext(0);
            temp = 0;
            return info;
         }
      }

      T removeFromHead()
      {
      	if (head == 0) throw ListEmptyException();
         size--;
         T item;
         Node<T>* temp = head;
         head = head->getNext();
         item = temp->getInfo();
      	temp->setNext(0);
         delete temp;
         return item;
      }

      ~List()
      {
      	if (head)
      		deleteAll();
      }

      void printList()
      {
      	Node<T>* temp = head;
         while (temp != 0)
      	{
         	//cout << temp->getInfo() << endl;
            temp = temp->getNext();
         }
      }
};
