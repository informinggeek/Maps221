#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Map ADT based on C++ map implemented with binary search tree
/// @ingroup MySTL
/// @tparam Key Key type
/// @tparam Value Value type
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior.
////////////////////////////////////////////////////////////////////////////////
template<typename Key, typename Value>
class map {

  struct node;           ///< Forward declare node class
  template<typename>
    class map_iterator; ///< Forward declare iterator class

  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    typedef Key key_type;      ///< Public access to Key type
    typedef Value mapped_type; ///< Public access to Value type
    typedef std::pair<const key_type, mapped_type>
      value_type;              ///< Entry type
    typedef map_iterator<value_type>
      iterator;                ///< Bidirectional iterator
    typedef map_iterator<const value_type>
      const_iterator;          ///< Const bidirectional iterator
    typedef std::reverse_iterator<iterator>
      reverse_iterator;        ///< Reverse bidirectional iterator
    typedef std::reverse_iterator<const_iterator>
      const_reverse_iterator;  ///< Const reverse bidirectional iterator

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Constructor
    map() : root(new node()), sz(0) {
      root->expand();
    }
    /// @brief Copy constructor
    /// @param m Other map
    map(const map& m) : root(new node(*m.root)), sz(m.sz) {
    }
    /// @brief Destructor
    ~map() {
      delete root;
    }

    /// @brief Copy assignment
    /// @param m Other map
    /// @return Reference to self
    map& operator=(const map& m) {
      if(this != &m) {
        delete root;
        root = new node(*m.root);
        sz = m.sz;
      }
      return *this;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to beginning
    iterator begin() {return iterator(root->leftmost());}
    /// @return Iterator to end
    iterator end() {return iterator(root);}
    /// @return Iterator to reverse beginning
    reverse_iterator rbegin() {return reverse_iterator(root);}
    /// @return Iterator to reverse end
    reverse_iterator rend() {return reverse_iterator(root->leftmost());}
    /// @return Iterator to beginning
    const_iterator cbegin() const {return const_iterator(root->leftmost());}
    /// @return Iterator to end
    const_iterator cend() const {return const_iterator(root);}
    /// @return Iterator to reverse beginning
    const_reverse_iterator crbegin() const {return const_reverse_iterator(root);}
    /// @return Iterator to reverse end
    const_reverse_iterator crend() const {return const_reverse_iterator(root->leftmost());}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of map
    size_t size() const {return sz;}
    /// @return Does the map contain anything?
    bool empty() const {return sz == 0;}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function should insert a new
    /// element with that key and return a reference to its mapped value
    /// (constructed through default construction)
    Value& operator[](const Key& k) {
      /// @todo implement at function. Utilize inserter function.

      return end()->second;
    }
     // std::pair<node*,bool> p = inserter(std::make_pair(k,Value()));
     // Value &v = p.first->value.second;
     // return v;
      return (*((this->inserter(std::make_pair(k,Value()))).first)).value.second;	// *** This is almost a direct copy out of std::map
    }											// *** The commented out code above it should work as well


    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function throws an
    /// \c out_of_range exception.
    Value& at(const Key& k) {
      /// @todo implement at function. Utilize find function.
      return end()->second;
    }

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function throws an
    /// \c out_of_range exception.
    const Value& at(const Key& k) const {
      /// @todo implement at function. Utilize find function.
      return end()->second;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Insert element into map, i.e., put(k, v) from the Map ADT
    /// @param v Key, Value pair
    /// @return pair of iterator and bool. Iterator pointing to found element or
    ///         already existing element. bool is true if a new element was
    ///         inserted and false if it existed.
    ///
    /// Insert is the "put(k, v)" function of the Map ADT. Remember that Maps
    /// store unique elements, so if the element existed already it is returned.
    std::pair<iterator, bool> insert(const value_type& v) {
      /// @todo Implement insert. Utilize inserter helper.
      
      return std::make_pair(end(), false);
    }
    /// @brief Remove element at specified position
    /// @param position Position
    /// @return Position of new location of element which was after eliminated
    ///         one
    iterator erase(const_iterator position) {
      /// @todo Implement erase. Utilize eraser helper.
      return end();
    }
    /// @brief Remove element at specified position
    /// @param k Key
    /// @return Number of elements removed (in this case it is at most 1)
    size_t erase(const Key& k) {
      /// @todo Implement erase. Utilize finder and eraser helpers.
      return 0;
    }
    /// @brief Removes all elements
    void clear() noexcept {
      delete root;
      root = new node();
      root->expand();
      sz = 0;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Operations
    /// @{

    /// @brief Search the container for an element with key \c k
    /// @param k Key
    /// @return Iterator to position if found, end() otherwise
    iterator find(const Key& k) {
      /// @todo Implement find. Utilize the finder helper.
      return end();
      node* v = finder(k);
      if(v->is_internal()) return iterator(v);
      else return end();
    }

    /// @brief Search the container for an element with key \c k
    /// @param k Key
    /// @return Iterator to position if found, cend() otherwise
    const_iterator find(const Key& k) const {
      /// @todo Implement find. Utilize the finder helper
      cend();
      node* v = finder(k);
      const_iterator v = finder(k);
      if(v->is_internal()) return v;
      else return cend();
    }

    /// @brief Count elements with specific keys
    /// @param k Key
    /// @return Count of elements with key \c k
    ///
    /// Because all elements in a map container are unique, the function will
    /// only return 1 or 0.
    size_t count(const Key& k) const {
      /// @todo Implement count. Utilize the find operation.
      return 0;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Helpers
    /// @{

    /// @brief Utility for finding a node with Key \c k
    /// @param k Key
    /// @return Node pointer to either where node exists or where it should be
    ///         inserted
    ///
    /// Base your algorithm off of Code Fragment 10.9 on page 436
    node* finder(const Key& k) const {		
      /// @todo Implement finder helper function
      node* v=root;
      if(v->is_external()) return v;
      while(!v->is_external())				// *** Here is where it hits the infinite loop *** //
      {
	       std::cout<<"Test"<<std::endl;
	       if(k < v->value.first) v=v->left;
         else if (v->value.first < k) v=v->right;
      }
      return v;
    }

    /// @brief Utility for inserting a new node into the data structure.
    /// @param v Key, Value pair
    /// @return pair of node and bool. node pointing to found element or
    ///         already existing element. bool is true if a new element was
    ///         inserted and false if it existed.
    ///
    /// Inserter is the "put(k, v)" function of the Map ADT. Remember that Maps
    /// store unique elements, so if the element existed already it is returned.
    ///
    /// Base you algorithm off of Code Fragment 10.10 on page 436
    ///
    /// Hint: Will need to use functions node::replace and node::expand
    std::pair<node*, bool> inserter(const value_type& v) {		
      /// @todo Implement inserter helper function
      node* i = finder(v.first);
      if (i->is_internal()) return std::make_pair(i,false); 
      i->expand();
      i->replace(v);
      sz++;			// increase size by 1
      return std::make_pair(i, true);
    }

    /// @brief Erase a node from the tree
    /// @param n Node to erase
    /// @return Next inorder successor of \c n in tree
    ///
    /// Base your algorithm off of Code Fragment 10.11 on page 437
    ///
    /// Hint: will need to use functions node::inorder_next or node::leftmost,
    /// node::replace, and node::remove_above_external
    node* eraser(node* n) {
      /// @todo Implement eraser helper function
      node* w;
      if(n->left()->is_external())
        w = n->left();
      else if(n->right()->is_external())
        w = n->right();
      else
      {
        w = n->right();
        do{
          w = n->left();
          }while(w->is_internal());
          node* u = w.parent();
          //n->setKey(u->key());
          //n->setValue(u->value());
	  n->replace(u);
      }
      sz--;
      remove_above_external(w);
      return nullptr;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Data
    /// @{

    node* root;     ///< Root of binary tree, the root will be a sentinel node
                    ///< for end iterator. root.left is the "true" root for the
                    ///< data
    size_t sz;      ///< Number of nodes

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Internal structure for binary search tree
    ////////////////////////////////////////////////////////////////////////////
    struct node {

      //////////////////////////////////////////////////////////////////////////
      /// @name Constructors
      /// @{

      /// @brief Constructor
      /// @param v Map entry (Key, Value) pair
      node(const value_type& v = value_type()) :
        value(v), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

      /// @brief Copy constructor
      /// @param n node to perform deep copy from
      node(const node& n) : value(n.value), parent(nullptr), left(nullptr), right(nullptr), height(n.height) {
        /// @todo Finish implementation of this copy constructor.
        ///       Hint: left and right are not copied correctly at the moment
      }

      /// @brief Copy assignment - Deleted
      /// @param n Other node
      node& operator=(const node& n) = delete;

      /// @brief Destructor
      ~node() {
        /// @todo Implement node destructor
       // delete this; 
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Modifiers
      /// @{

      /// @brief Replace value of node, used for setting values on external
      ///        placeholder nodes
      /// @param v New value
      void replace(const value_type& v) {
        const_cast<Key&>(value.first) = v.first;
        value.second = v.second;
      }

      /// @brief Expand external node to make it internal
      void expand() {
        left = new node;
        right = new node;
        left->parent = this;
        right->parent = this;
      }

      /// @brief Remove above external node, assumes this is external node
      /// @return Sibling of \c n, who is promoted to n's parent's position
      node* remove_above_external() {
        node* par = parent;
        node* sib = this == par->left ? par->right : par->left;
        node* gpar = par->parent;
        if(par == gpar->left)
          gpar->left = sib;
        else
          gpar->right = sib;
        sib->parent = gpar;
        par->left = par->right = nullptr;
        delete this;
        delete par;
        if(sib->is_external())
          sib = sib->parent;
        return sib;
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Helpers for AVL trees
      /// @{

      /// @return Height of the node which is 0 for external node
      size_t get_height() {
        return this->is_external() ? 0: this->height;
      }

      /// @return Difference of heights of left and right children
      int height_diff() {
        return this->right->get_height() - this->left->get_height();
      }

      /// @brief Set the height as 1 added to the maximum height of its
      ///        children
      void set_height() {
        size_t hl = this->left->get_height();
        size_t hr = this->right->get_height();
        this->height = 1 + (hl > hr? hl : hr);
      }

      /// @return True when the height difference of the children nodes
      ///         does not exceed 1
      bool balanced() {
        int bal = height_diff();
        return ((-1<=bal)&&(bal<=1));
      }

      /// @brief Given a node this returns the tallest grandchild
      /// @return The grandchild with the maximum height
      node* tall_grand_child()  {
        node* l = left;
        node* r = right;
        // left child's height is greater than right child's height
        if(l->get_height() >= r->get_height())
          if(l->left->get_height() >= l->right->get_height())
            return l->left;
          else
            return l->right;
        // right child's height is greater than left child's height
        else
          if(r->right->get_height() >= r->left->get_height())
            return r->right;
          else
            return r->left;
      }

      /// @brief Rebalances the tree from the node to the root.
      ///        It sets the height of every node in the path to root.
      ///        On a disbalanced node, restructring is called to restore
      ///        the balance in the tree.
      /// Base your algorithm off of Code Fragment 10.17 on page 449 in book
      ///
      /// Hint: will need the functions balanced(), tall_grand_child(),
      ///       set_height()
      void rebalance() {
        /// @todo Implement resbalancing
      }

      /// @brief Restructuring the tri-node structure's balance where
      ///        the grandparent of the node is disbalanced.
      /// @return The tri-node structure after restructring
      ///
      /// Base your algorithm off of Code Fragment 10.12 on page 442 in book
      ///
      /// Hint: You can create your own supporting functions to implement
      ///       code reusability.
      node* restructure() {
        /// @todo Implement restructuring
        return this;
      }

      /// @brief Set new left and right children to a node
      /// @param New left and right children
      /// @return Node with the resetted children
      node* set_children(node* l, node *r)  {
        left = l;
        right = r;
        left->parent = this;
        right->parent = this;
        return this;
      }

      /// @brief Rotate right a node
      /// @return Node structure after right rotation
      node* rotate_right() {
        node* p = this;
        node* c = p->left;
        node* s = c->right;

        c->parent = p->parent;
        if(p == p->parent->left)
          p->parent->left = c;
        else
          p->parent->right = c;
        c->set_children(c->left,p);
        p->set_children(s,p->right);
        p->set_height();
        c->set_height();
        return c;
      }

      /// @brief Rotate left a node
      /// @return Node structure after left rotation
      node* rotate_left() {
        node* p = this;
        node* c = p->right;
        node* s = c->left;

        c->parent = p->parent;
        if(p == p->parent->left)
          p->parent->left = c;
        else
          p->parent->right = c;
        c->set_children(p,c->right);
        p->set_children(p->left,s);
        p->set_height();
        c->set_height();
        return c;
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Accessors
      /// @{

      /// @return If parent is null return true, else false
      bool is_root() const {return parent == nullptr;}
      /// @return If both children are null return true, else false
      bool is_external() const {return left == nullptr && right == nullptr;}
      /// @return If it is not external then it is internal
      bool is_internal() const {return !is_external();}

      /// @return Leftmost child of this node
      node* leftmost() const {
        const node* n = this;
        while(n->is_internal()) n = n->left;
        return n->parent;
      }

      /// @return Next node in the binary tree according to an inorder
      ///         traversal
      node* inorder_next() {
        //Here, I have a right child, so inorder successor is leftmost child
        //of right subtree
        if(right->is_internal()) {
          return right->leftmost();
        }
        //Otherwise, I am a right child myself and need to find an ancestor
        //who has a right child
        else {
          node* n = this;
          node* w = parent;
          while(n == w->right) {
            n = w;
            w = w->parent;
          }
          return w;
        }
      }

      /// @return Previous node in the binary tree according to an inorder
      ///         traversal
      node* inorder_prev() {
        //Here, I have a left child, so inorder predecessor is rightmost child
        //of left subtree
        if(left->is_internal()) {
          node* n = left;
          while(n->is_internal()) n = n->right;
          return n->parent;
        }
        //Otherwise, I am a left child myself and need to find an ancestor
        //who has a left child
        else {
          node* n = this;
          node* w = parent;
          while(n == w->left) {
            n = w;
            w = w->parent;
          }
          return w;
        }
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Data
      /// @{

      value_type value; ///< Value is pair(key, value)
      node* parent;     ///< Parent node
      node* left;       ///< Left node
      node* right;      ///< Right node
      size_t height;    ///< Height of the node (used in AVL trees)

      /// @}
      //////////////////////////////////////////////////////////////////////////
    };

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    template<typename U>
      class map_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
        public:
          //////////////////////////////////////////////////////////////////////
          /// @name Constructors
          /// @{

          /// @brief Construction
          /// @param v Pointer to position in binary tree
          map_iterator(node* v = NULL) : n(v) {}

          /// @brief Copy construction
          /// @param i Other iterator
          map_iterator(const map_iterator<typename std::remove_const<U>::type>& i) : n(i.n) {}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Comparison
          /// @{

          /// @brief Equality comparison
          /// @param i Iterator
          bool operator==(const map_iterator& i) const {return n == i.n;}
          /// @brief Inequality comparison
          /// @param i Iterator
          bool operator!=(const map_iterator& i) const {return n != i.n;}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Dereference
          /// @{

          /// @brief Dereference operator
          U& operator*() const {return n->value;}
          /// @brief Dereference operator
          U* operator->() const {return &n->value;}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Advancement
          /// @{

          /// @brief Pre-increment
          map_iterator& operator++() {n = n->inorder_next(); return *this;}
          /// @brief Post-increment
          map_iterator operator++(int) {map_iterator tmp(*this); ++(*this); return tmp;}
          /// @brief Pre-decrement
          map_iterator& operator--() {n = n->inorder_prev(); return *this;}
          /// @brief Post-decrement
          map_iterator operator--(int) {map_iterator tmp(*this); --(*this); return tmp;}

          /// @}
          //////////////////////////////////////////////////////////////////////

        private:
          node* n; ///< Map node

          friend class map;
      };

    /// @}
    ////////////////////////////////////////////////////////////////////////////

};

}

#endif
