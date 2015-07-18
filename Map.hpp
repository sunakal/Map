#include<iostream>
#include<vector>
#include<list>
#include <stdexcept> 
#include<cstdlib>
using namespace std;
namespace cs540
{
	
template <typename Key_T, typename Mapped_T> 
class Map;
template <typename Key_T, typename Mapped_T>
bool operator==(Map<Key_T, Mapped_T> const &,  Map<Key_T, Mapped_T> const &);
template <typename Key_T, typename Mapped_T>
bool operator!=(Map<Key_T, Mapped_T> const  &, Map<Key_T, Mapped_T> const &);
template <typename Key_T, typename Mapped_T>
bool operator<(Map<Key_T, Mapped_T> const &, Map<Key_T, Mapped_T> const &);
template <typename Key_T, typename Mapped_T>
class Iterator; 



template <typename Key_T, typename Mapped_T> 
class Map
{
	typedef std::pair<const Key_T, Mapped_T> ValueType;
	
   public :
    	
      Map() {
      root = nullptr;
           }

   Map (const Map & m2)
   {
   	   auto temp = m2.root;
   	   createMap(temp); 	    
   }
     
   Map (Map&& m2)
   {
   	
   }
   
   Map &operator=(const Map & m2)
   {
   	if (this != &m2)
   	{
	    clear();
	    this->root=nullptr;
   		Map(m2);
   	}
   }
   
   
   Map (initializer_list<pair<const Key_T , Mapped_T >> temp)
   {
   for (auto c : temp)
    insert (c);
	cout << "constructed with a " << temp.size() << "-element list\n";
   };
   
   ~Map() {
   	clear();
   };
   
   
    class node {
   	  public:
   	  ValueType value;
   	  int indicator;
      node* left = nullptr;
      node* right = nullptr;
      node* parent = nullptr;
      
     node ()
	 {
	 	
	 } 
      node (ValueType&& addValue): value(addValue)
      {
      
      }
   
      node (ValueType temp) : value(temp)
      {
      	indicator=0;
      	left=nullptr;
      	right =nullptr;
      	parent=nullptr;
      }    
   
	  bool operator==(node & abc)
	  {
	  	  
	  	if (this->value.first == abc.value.first)
	  	{
	  	return true;
	  	}
	  	else
	  	return false;
	  } 
	  
	 bool operator<(node & abc)
	  {
	  	if (this->value.first < abc.value.first)
	  	{
	  	return true;
	  	}
	  	else
	  	return false;
	  } 
	  
    };
    
    class BaseIterator
    {
    	public:
        static node* tracklast;           
    };
     
    class ConstIterator;
    class Iterator: public BaseIterator {
  	public:
  	node* current =nullptr;
  	//bool operator!=(Iterator&);
  	Iterator & operator++();
  	Iterator operator++(int);
  	Iterator & operator--();
  	Iterator operator--(int);
  	ValueType &operator*() const;
  	ValueType *operator->() const;
  	bool operator==(Iterator a)
  	{
  		if (this->current == a.current)
  		return true;
  		else
  		false;
  	}
  	 	bool operator==(ConstIterator a)
  	{
  	    if (this->current == a.current)
  		return true;
  		else
  		false;
  	}
  		bool operator!=(ConstIterator a)
  	{
             return  !(*this==a);
  	}  	
  		bool operator!=(Iterator a)
  	{
              return !(*this==a);
  	}  	
  	
  	
    } it;
   
   class ConstIterator : public BaseIterator {
   	public:
  	node * current =nullptr;
  	//bool operator!=(ConstIterator&);
  	ConstIterator & operator++();  	
  	ConstIterator operator++(int);
  	ConstIterator & operator--();  	
  	ConstIterator operator--(int);
  	const ValueType &operator*() const;
  	const ValueType *operator->() const;
  	bool operator==(Iterator a)
  	{
  		if (this->current == a.current)
  		return true;
  		else
  		false;
  	}
  	 	bool operator==(ConstIterator a)
  	{
  	    if (this->current == a.current)
  		return true;
  		else
  		false;
  	}  	
  		bool operator!=(ConstIterator a)
  	{
             return  !(*this==a);
  	}  	
  		bool operator!=(Iterator a)
  	{
              return !(*this==a);
  	}  	
  	
   };
   
   class ReverseIterator : public BaseIterator {
   	public:
  	node * current =nullptr;
  	//bool operator!=(ReverseIterator&);
  	ReverseIterator & operator++();  	
  	ReverseIterator operator++(int);
  	ReverseIterator & operator--();  	
  	ReverseIterator operator--(int);
  	ValueType &operator*() const;
  	ValueType *operator->() const;
  	
  	bool operator!=(const ReverseIterator r)
  	{
  		if (this->current !=r.current)
  		return true;
  		else
  		return false;  		
  	}
  	
  	bool operator==(const ReverseIterator r)
  	{
  		return !(*this !=r);
  		
 	}  	
    };
   
   
   template <typename IT_T>
   void insert(IT_T range_beg, IT_T range_end);
   
   
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ReverseIterator rbegin();
    ReverseIterator rend();
    
    Iterator find(const Key_T &);
    Iterator insert(std::pair<const Key_T, Mapped_T>&&);
    ConstIterator find(const Key_T &) const;
    Mapped_T &at(const Key_T &);
    const Mapped_T &at(const Key_T &) const;
    void erase(Iterator pos);
    void remove(const Key_T &);
    void destroy (node *);
    node * lastNode();
    node * lastNode() const;
    Mapped_T &operator[](const Key_T &);
    pair<Map<Key_T, Mapped_T>::Iterator, bool> insertNode(node *);
	pair<Map<Key_T, Mapped_T>::Iterator, bool> insert(const ValueType &);
	void createMap(typename Map<Key_T, Mapped_T>::node *);
	void clear();
	void deletetree(typename Map<Key_T, Mapped_T>::node *);

	
	bool compare (Map::node * ,  Map::node * ) const;
	
 
   friend bool operator== <Key_T, Mapped_T>( Map<Key_T, Mapped_T> const &, Map<Key_T, Mapped_T> const&);
   friend bool operator!= <Key_T, Mapped_T>( Map<Key_T, Mapped_T> const&,  Map<Key_T, Mapped_T> const&);
   friend bool operator< <Key_T, Mapped_T>(Map<Key_T, Mapped_T> const&,  Map<Key_T, Mapped_T> const &);
      
    
    
    size_t size() const
    {
    	return mapsize;
    }
    bool empty() const
    {
    	if (mapsize ==0)
    	return true;
    	else
    	return false;
    }

   
 
   int mapsize=0;
   
  
private :
		node* root = nullptr;
		node* last= nullptr;
		Mapped_T t;

};
 
//template <typename Key_T, typename Mapped_T>
//int Map<Key_T, Mapped_T>::mapsize = 0;

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::clear()
{ 
	if (this->root==nullptr)
{  		return;}
	else{
	deletetree(this->root);
	this->root=nullptr;
	}
}

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::deletetree(typename Map<Key_T, Mapped_T>::node *a)
{
	if(a==nullptr)
	return;
	else if (a->left==nullptr && a->right==nullptr)
	{
	   if(a->parent!=nullptr && a->parent->right==a)
	   a->parent->right==nullptr;
	   else
	   if(a->parent!=nullptr && a->parent->left==a)
	   a->parent->left==nullptr;
		destroy(a);
	return;
    }  
	else
	deletetree(a->left);
	deletetree(a->right);	
}




template <typename Key_T, typename Mapped_T>
   void Map<Key_T, Mapped_T>::createMap(typename Map<Key_T, Mapped_T>::node *a)
   {
   	   if (a != nullptr)
   	   {insert(a->value);
   	   createMap(a->left);
   	   createMap(a->right);
       }
       else
       return;   	
   }


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>:: node* Map<Key_T, Mapped_T>:: BaseIterator::tracklast = nullptr;

template <typename Key_T, typename Mapped_T>
template <typename IT_T>
void Map<Key_T, Mapped_T>:: insert(IT_T range_beg, IT_T range_end)
{
   while (range_beg != range_end )
   {
   	 insert (*range_beg);
   	 range_beg++;
   }
}


// get last node pointed by end()
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::node * Map<Key_T, Mapped_T>:: lastNode()
{
    node * temp = root;
	if(root!=nullptr)
    {
    if (last == nullptr)
    { 
    	last = new node;
    }
    while(temp->right)
 	{
	 temp = temp->right;
	}
	last->parent = temp;
	last->indicator=1;
	BaseIterator::tracklast = last;
    return last;	
    }  
}



template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator  Map<Key_T, Mapped_T>:: insert(std::pair<const Key_T, Mapped_T>&& addValue)
{
	Map::node *treeNode = new node(addValue);
	pair<Map::Iterator, bool> p1= insertNode(treeNode);
	return p1.first;
}

// Insertion

template <typename Key_T, typename Mapped_T>
pair<typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>:: insert(const ValueType &c)
{
	// Map::Iterator it;
	Map::node *treeNode = new node(c);
	pair<Map::Iterator, bool> p1= insertNode(treeNode);
	return p1;
}

template <typename Key_T, typename Mapped_T>
pair<typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>:: insertNode(node * treeNode)
{
	Map::node *temp =nullptr;
	Map::node *prev = nullptr;
	
	temp=root; 
	bool indicator=true;
	
	//cout<<treeNode->value.first;
	
   while (temp)
  {
	prev = temp;
	if(temp->value.first < treeNode->value.first)
	temp =temp->right;
	else if(treeNode->value.first< temp->value.first)
	temp=temp->left;
	else if(treeNode->value.first == temp->value.first)
	{   
	    indicator= false;
		it.current = temp;
		break;
	}
  }
  
  if (prev==nullptr)
  {root= treeNode; 	mapsize = mapsize+1; 
  }
  else if (indicator)
  {
  	if(prev->value.first < treeNode->value.first)
  	{prev->right = treeNode; treeNode->parent= prev;}
  	else
  	{prev->left = treeNode; treeNode->parent= prev;}
  	
     	it.current = treeNode;
		mapsize = mapsize+1;
  }

	pair<Map::Iterator, bool> p1(it, indicator);
	if (mapsize>1 && indicator)
   // cout<< it.current->value.first <<"child of" << it.current->parent->value.first <<"\n";
    lastNode();
	return p1;
}

//=================================================================================================================

// Begin
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator  Map<Key_T, Mapped_T>:: begin ()
{
	Iterator it;
	it.current = root;
	if (root==nullptr)
	{
		return it;
	}
	else
	{
		node * temp = root;
		
		while(temp->left)
		{
			temp = temp->left;
		}
		
		it.current = temp;
	}
    return it;
}


// End
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator  Map<Key_T, Mapped_T>:: end ()
{
	Iterator it;
	it.current=root;
	if (root==nullptr)
	{
		return it;
	}
     else		
		it.current = lastNode();
    return it;
}



// Begin
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator  Map<Key_T, Mapped_T>:: begin () const
{
	ConstIterator it;
	it.current = root;
	if (root==nullptr)
	{
		return it;
	}
	else
	{
		node * temp = root;
		
		while(temp->left)
		{
			temp = temp->left;
		}
		
		it.current = temp;
	}
    return it;
}


// End
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator  Map<Key_T, Mapped_T>:: end () const
{
	ConstIterator it;
	it.current=root;
	if (root==nullptr)
	{
		return it;
	}
     else		
		const_cast <typename Map<Key_T, Mapped_T>::node *&> (it.current) =  lastNode();
    return it;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::node * Map<Key_T, Mapped_T>:: lastNode() const
{
    node * temp = root;
	if(root!=nullptr)
    {
    if (last == nullptr)
    { 
    	const_cast<Map<Key_T, Mapped_T>::node *&> (last)  = new node;
    }
    while(temp->right)
 	{
	 temp = temp->right;
	}
	last->parent = temp;
	last->indicator=1;
	BaseIterator::tracklast = last;
    return last;	
    }  
}


// Begin
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator  Map<Key_T, Mapped_T>:: rbegin ()
{
	ReverseIterator rit;
	
	if (last==nullptr)
	{
		return rit;
	}
	
	rit.current = last->parent;
	
    return rit;
}


// End
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator  Map<Key_T, Mapped_T>:: rend ()
{
	ReverseIterator rit;
	rit.current=root;
	if (root==nullptr)
	{
		return rit;
	}
     else		
	while(rit.current->left)
	{
		rit.current= rit.current->left;
	}
	
    return rit;
}




//=========================================================================================================================================================================




//find
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator  Map<Key_T, Mapped_T>:: find (const Key_T & searchkey)
{
   node * temp = root; int flag=0;
   Iterator it;
   while(temp)
   {
   	  if(temp->value.first < searchkey)
   	  temp = temp->right;
   	  else if (searchkey < temp->value.first)
   	  temp= temp->left;
   	  else if(temp->value.first==searchkey)
   	  {
   	  	flag=1;
   	  	break;
   	  }  	
   }
		if (flag==1)
		{
			it.current= temp;
		}
		else
		{
		  it = end();
	    }
	   return it;
}

//// const find
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::find(const Key_T & searchkey) const
{
   node * temp = root; int flag=0;
   ConstIterator cit;
   
   while(temp)
   {
   	  if(temp->value.first < searchkey)
   	  temp = temp->left;
   	  else if (searchkey < temp->value.first)
   	  temp= temp->right;
   	  else if(temp->value.first==searchkey)
   	  {
   	  	flag=1;
   	  	break;
   	  }  	
   }
		if (flag==1)
		{
			cit.current= temp;
		}
			else
		{
		  cit = end();
	    }
         return cit;
}


// at
template <typename Key_T, typename Mapped_T>
Mapped_T & Map<Key_T, Mapped_T>:: at(const Key_T & searchkey)
 {
 	Map::Iterator it = find (searchkey);
 	if(it.current == end().current)
 	{
       throw out_of_range ("The key not found  ");
	}
    else
 	return ((it.current)->value).second;
 }

template <typename Key_T, typename Mapped_T>
const Mapped_T &  Map<Key_T, Mapped_T>:: at(const Key_T & searchkey) const
{
 	Map::ConstIterator cit = find (searchkey);
 	if(cit.current == nullptr)
 	{
 		cout<<"Const key not present";
       throw out_of_range ("The const key not found");
	}
    else
 	return ((cit.current)->value).second;		
}


template <typename Key_T, typename Mapped_T>
Mapped_T & Map<Key_T, Mapped_T>:: operator[](const Key_T & searchkey)
{
	
	it= find (searchkey);
	if(it.current !=nullptr)
        if (it.current->indicator==0)
    	{
		 return (it.current->value.second);
    	}
    	else
    	{		
		t = *(new Mapped_T());
	    auto  paired  = make_pair(searchkey, t);
		insert(paired);
		return t;
    	}
    else
    {
    	 t = *(new Mapped_T());
	    auto  paired  = make_pair(searchkey, t);
		insert(paired);

		return t;
    	
    }
}

//======================================================== Iterator ======================================================================================================================



template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator & Map<Key_T, Mapped_T>::Iterator::operator++()
{
   node * temp; node * child;
   
   if(BaseIterator::tracklast->parent == this->current)
   {
   	this->current= BaseIterator::tracklast;	
   }
 
   else if (this->current->right !=nullptr)
  {
	temp = current->right;
	while(temp->left)
	{
		temp= temp->left;
	}
	this->current = temp;
 }
 else if (this->current->right == nullptr)
 {
   child = this->current;
   temp= this->current->parent;
   while(temp->left !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
      this->current= temp;
}
return (*this);
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator  Map<Key_T, Mapped_T>::Iterator::operator++(int)
{
	Iterator cur = (*this);
   node * temp; node * child;
   
   if(BaseIterator::tracklast->parent == this->current)
   {
   	
   	this->current= BaseIterator::tracklast;	
   }
    else if (this->current->right !=nullptr)
    {
	temp = current->right;
	while(temp->left)
	{
		temp= temp->left;
	}
	this->current = temp;
   }
   else if (this->current->right == nullptr)
   {
   child = this->current;
   temp= this->current->parent;
    while(temp->left !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
      this->current= temp;
    }
return (cur);
}



template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator & Map<Key_T, Mapped_T>::Iterator::operator--()
{
   node * temp; node * child;

  if(this->current->indicator ==1)
  {
  	this->current= this->current->parent;
  	return (*this);
  }
else if (this->current->left !=nullptr)
{
	temp = current->left;
	while(temp->right)
	temp= temp->right;
}
else if (this->current->left == nullptr)
{
   child = this->current;
   temp= this->current->parent;
   while(temp->right !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
}
    this->current= temp;
return (*this);
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator--(int)
{
   Iterator cur = (*this);
   node * temp; node * child;
   
   
  if(this->current->indicator ==1)
  {
  	this->current= this->current->parent;
  	return (cur);
  }

else if (this->current->left !=nullptr)
{
	temp = current->left;
	while(temp->right)
	temp= temp->right;
}
else if (this->current->left == nullptr)
{
   child = this->current;
   temp= this->current->parent;
   while(temp->right !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
}
    this->current= temp;
    return (cur);
}



template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType *  Map<Key_T, Mapped_T>::Iterator::operator->() const
{
	return &this->current->value;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType & Map<Key_T, Mapped_T>::Iterator::operator*() const
{
	return this->current->value;
}


//---------------------------------------------------------------------const Iterator ------------------------------------------------------------------------------------------------------------------
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator & Map<Key_T, Mapped_T>::ConstIterator::operator++()
{
   node * temp; node * child;
   
   if(BaseIterator::tracklast->parent == this->current)
   {
   	this->current= BaseIterator::tracklast;	
   }
 
   else if (this->current->right !=nullptr)
  {
	temp = current->right;
	while(temp->left)
	{
		temp= temp->left;
	}
	this->current = temp;
 }
 else if (this->current->right == nullptr)
 {
   child = this->current;
   temp= this->current->parent;
   while(temp->left !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
      this->current= temp;
}
return (*this);
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator  Map<Key_T, Mapped_T>::ConstIterator::operator++(int)
{
	ConstIterator cur = (*this);
   node * temp; node * child;
   
   if(BaseIterator::tracklast->parent == this->current)
   {
  /* 	cout<<"yes, true";
   	cout<<"\n Last element"<< BaseIterator::tracklast->parent->value.first<<"\n";
   	cout<<"\n current"<< this->current->value.first<<"\n"; */
   	
   	this->current= BaseIterator::tracklast;	
   }
    else if (this->current->right !=nullptr)
    {
	temp = current->right;
	while(temp->left)
	{
		temp= temp->left;
	}
	this->current = temp;
   }
   else if (this->current->right == nullptr)
   {
   child = this->current;
   temp= this->current->parent;
    while(temp->left !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
      this->current= temp;
    }
return (cur);
}



template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator & Map<Key_T, Mapped_T>::ConstIterator::operator--()
{
   node * temp; node * child;

  if(this->current->indicator ==1)
  {
  	this->current= this->current->parent;
  	return (*this);
  }
else if (this->current->left !=nullptr)
{
	temp = current->left;
	while(temp->right)
	temp= temp->right;
}
else if (this->current->left == nullptr)
{
   child = this->current;
   temp= this->current->parent;
   while(temp->right !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
}
    this->current= temp;
return (*this);
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator--(int)
{
   ConstIterator cur = (*this);
   node * temp; node * child;
   
   
  if(this->current->indicator ==1)
  {
  	this->current= this->current->parent;
  	return (cur);
  }

else if (this->current->left !=nullptr)
{
	temp = current->left;
	while(temp->right)
	temp= temp->right;
}
else if (this->current->left == nullptr)
{
   child = this->current;
   temp= this->current->parent;
   while(temp->right !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
}
    this->current= temp;
    return (cur);
}



template <typename Key_T, typename Mapped_T>
const typename Map<Key_T, Mapped_T>::ValueType *  Map<Key_T, Mapped_T>::ConstIterator::operator->() const
{
	return &this->current->value;
}

template <typename Key_T, typename Mapped_T>
const typename Map<Key_T, Mapped_T>::ValueType & Map<Key_T, Mapped_T>::ConstIterator::operator*() const
{
	return this->current->value;
}



//=========================================================ReverseIterator=======================================================================================================

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator & Map<Key_T, Mapped_T>::ReverseIterator::operator++()
{
node * temp; node * child;

  if(this->current->indicator ==1)
  {
  	this->current= this->current->parent;
  	return (*this);
  }
else if (this->current->left !=nullptr)
{
	temp = current->left;
	while(temp->right)
	temp= temp->right;
}
else if (this->current->left == nullptr)
{
   child = this->current;
   temp= this->current->parent;
   while(temp->right !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
}
    this->current= temp;
return (*this);
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator  Map<Key_T, Mapped_T>::ReverseIterator::operator++(int)
{
	
   ReverseIterator cur = (*this);
   node * temp; node * child;
   
   
  if(this->current->indicator ==1)
  {
  	this->current= this->current->parent;
  	return (cur);
  }

else if (this->current->left !=nullptr)
{
	temp = current->left;
	while(temp->right)
	temp= temp->right;
}
else if (this->current->left == nullptr)
{
   child = this->current;
   temp= this->current->parent;
   while(temp->right !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
}
    this->current= temp;
    return (cur);
}



template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator & Map<Key_T, Mapped_T>::ReverseIterator::operator--()
{
   
   node * temp; node * child;
   
   if(BaseIterator::tracklast->parent == this->current)
   {
   	this->current= BaseIterator::tracklast;	
   }
 
   else if (this->current->right !=nullptr)
  {
	temp = current->right;
	while(temp->left)
	{
		temp= temp->left;
	}
	this->current = temp;
 }
 else if (this->current->right == nullptr)
 {
   child = this->current;
   temp= this->current->parent;
   while(temp->left !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
      this->current= temp;
}
return (*this);


}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator--(int)
{
	ReverseIterator cur = (*this);
   node * temp; node * child;
   
   if(BaseIterator::tracklast->parent == this->current)
   {
  /* 	cout<<"yes, true";
   	cout<<"\n Last element"<< BaseIterator::tracklast->parent->value.first<<"\n";
   	cout<<"\n current"<< this->current->value.first<<"\n"; */
   	
   	this->current= BaseIterator::tracklast;	
   }
    else if (this->current->right !=nullptr)
    {
	temp = current->right;
	while(temp->left)
	{
		temp= temp->left;
	}
	this->current = temp;
   }
   else if (this->current->right == nullptr)
   {
   child = this->current;
   temp= this->current->parent;
    while(temp->left !=child)
      {
      	child = temp;
      	temp= temp->parent;
      	
      	if(temp == nullptr)
      	break;
      }
      this->current= temp;
    }
return (cur);
}



template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType *  Map<Key_T, Mapped_T>::ReverseIterator::operator->() const
{
	return &this->current->value;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType & Map<Key_T, Mapped_T>::ReverseIterator::operator*() const
{
	return this->current->value;
}





//=================================================================================================================================================





template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::erase(Iterator pos)
{
   remove(pos.current->value.first);
   pos.current = nullptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::remove(const Key_T & keyvalue)
{
	Iterator it = find(keyvalue);
	node * toRemove = it.current;
	int isRoot =0;
	
	if(toRemove->parent == nullptr)
	{
		isRoot=1;
	}

	
	if (toRemove->left ==nullptr && toRemove->right ==nullptr)
	{
		
		if (isRoot==1)
		{
		    destroy(toRemove);
			root=nullptr;
			mapsize= mapsize -1;
			lastNode();
		    return;
		}
    
	 	else
	
		if(toRemove->parent->left == toRemove)
		toRemove->parent->left = nullptr;
		else 
		toRemove->parent->right = nullptr;	
		destroy(toRemove);
		mapsize= mapsize -1;
		lastNode();
		return;
	}
	
	else if (toRemove->left == nullptr && toRemove->right != nullptr)
	{
	
		if(isRoot !=1)
		{
     		if(toRemove->parent->left == toRemove)
	    	{
			toRemove->parent->left = toRemove->right;
			toRemove->right->parent = toRemove->parent;
			destroy (toRemove);
			mapsize= mapsize -1;
			return;
	    	}
		    else if (toRemove->parent->right == toRemove)
	    	{
			toRemove->parent->right = toRemove->right;
			toRemove->right->parent =toRemove->parent;
			destroy (toRemove);
			mapsize= mapsize -1;
			return;
	    	}	
	    }
	    
	    else if(isRoot==1)
	    {
	    	root= toRemove->right;
	    	root->parent=nullptr;
	    	destroy(toRemove);
	    	mapsize= mapsize -1;
	    	return;
	    }
	}
	
	
	else if (toRemove->left != nullptr && toRemove->right == nullptr)
	{
		if(isRoot !=1)
	 	{
		    if(toRemove->parent->left == toRemove)
		    {
			toRemove->parent->left = toRemove->left;
			toRemove->left->parent = toRemove->parent;
			destroy (toRemove);
			mapsize= mapsize -1;
			lastNode();
			return;
		    }
		    else if (toRemove->parent->right == toRemove)
	    	{
			toRemove->parent->right = toRemove->left;
			toRemove->left->parent =toRemove->parent;
			destroy (toRemove);
			mapsize= mapsize -1;
			lastNode();
			return;
		    }				
    	} 

	    else if(isRoot==1)
	    {
	    	root= toRemove->left;
	    	root->parent=nullptr;
	    	destroy(toRemove);
	    	mapsize= mapsize -1;
	    	lastNode();
	    	return;
	    }     
	}
	
	
	
	
	else
	{
		
	   node * asst = toRemove->left;
		while(asst->right)
		{
			asst = asst->right;
		}			
		
		auto temp = asst->value;
		
		auto t =asst->value.first;
		remove(t);
		
		node * aux = new node(temp);
		
		aux->left = toRemove->left;
		aux->right = toRemove->right;
		aux->parent = toRemove->parent;
		
		if (toRemove->left !=nullptr)
		toRemove->left->parent = aux;
		if (toRemove->right !=nullptr)
		toRemove->right->parent = aux;
		
		if(toRemove->parent !=nullptr)
		{
		if(toRemove->parent->left== toRemove)
		toRemove->parent->left = aux;
		else
		toRemove->parent->right=aux;
	    }
	    else if (toRemove->parent ==nullptr)
	    {
	    	root=aux;
	    }
	    
		toRemove->left =nullptr;
		toRemove->right =nullptr;
		toRemove->parent =nullptr;
		destroy(toRemove);
		
		return; 
	}		
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::destroy(node * toDestroy)
{
  delete toDestroy;
  toDestroy = nullptr;	
  return;
}



template <typename Key_T, typename Mapped_T>
bool operator==(Map<Key_T, Mapped_T> const  & map1 ,  Map<Key_T, Mapped_T> const & map2)
{
	bool val=  (map1 !=map2);
	
	return !val;
	
}

template <typename Key_T, typename Mapped_T>
bool operator!=(Map<Key_T, Mapped_T> const  & map1 ,  Map<Key_T, Mapped_T> const & map2)
{
	bool b1 =true, b2=true;
	if (!( *map1.root== *map2.root)|| map1.mapsize != map2.mapsize )
	{
	return true;
    }
	else
	{
	   if(map1.root->left !=nullptr && map2.root->left !=nullptr)
	   b1= map1.compare(map1.root->left,map2.root->left);
	   
	   if(map1.root->right !=nullptr && map2.root->right !=nullptr)
	   b2= map1.compare(map1.root->right,map2.root->right );

	   return !(b1&&b2);
	}		
}

template <typename Key_T, typename Mapped_T>
bool Map<Key_T, Mapped_T>::compare ( typename Map<Key_T, Mapped_T>::node * a, typename Map<Key_T, Mapped_T>::node * b) const
{
	
	
	   if (a==nullptr || b==nullptr)
	   return a==b;
	      
	   if (!(*a==*b))
	   return false;

return compare (a->left, b->left) && compare (a->right, b->right);
} 

template <typename Key_T, typename Mapped_T>
bool operator < (Map<Key_T, Mapped_T> const  & map1 ,  Map<Key_T, Mapped_T> const & map2)
{

typename Map<Key_T, Mapped_T>::ConstIterator it1=map1.begin();	
typename Map<Key_T, Mapped_T>::ConstIterator it2=map2.begin();
auto end1 = map1.end();
auto end2 = map2.end();


   
   if (map1.mapsize <map2.mapsize)
   return true;
   
while((it1!= end1) && (it2!= end2))
{
	if (it1.current->value.first == it2.current->value.first)
	{
		it1++;
		it2++;
		continue;
	}
	else if (it1.current->value.first < it2.current->value.first)
		return true;
} 

return false;
}


       /*bool operator==(const ConstIterator &, const ConstIterator &)
       bool operator==(const Iterator &, const ConstIterator &)
       bool operator==(const ConstIterator &, const Iterator &)
       bool operator!=(const Iterator &, const Iterator &)
       bool operator!=(const ConstIterator &, const ConstIterator &)
       bool operator!=const Iterator &, const ConstIterator &)
       bool operator!=const ConstIterator &, const Iterator & */

}