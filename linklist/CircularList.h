/** Below you can find an unimplemented API of the circular list and simple
 ** memory allocator.
 ** The goal of the task is to finish the implementation to have ready to use
 ** container that uses custom allocator.
 ** RULES:
 ** - no dynamic allocation (new, malloc, etc.)
 ** - there is one allocator for multiple CircularList<DataType> objects
 ** - solution has to be thread safe
 ** - make it as cache friendly as possible
 ** - make it as optimal as you can
 ** - you can add new members to classes/structs if needed but you shouldn't
 **   change prototypes of existing member functions
 ** - write unit tests for your solution
 **/

template <typename DataType>
class ListAllocator {
 public:
  DataType* allocate(size_t size) {
    char* datatype = nullptr;
    if (pointer_in_buffer(ptr) && (storage + N >= ptr + size)) {
      char* datatype = ptr;
      ptr += size;
    } else {
      throw "Memory Arena exausted";
    }
    return static_cast<DataType*>(datatype);
  }

  void deallocate(char* p, std::size_t n) {
    if (pointer_in_buffer(p) && (p +n == ptr)) {
      ptr = p;
    }
  }

 private:
  bool pointer_in_buffer(char* p) noexcept {
    return storage <= p && p <= storage + MAX_DATA_SIZE;
  }
  static constexpr unsigned int MAX_DATA_SIZE = 2048;
  unsigned char storage[MAX_DATA_SIZE];
  char* ptr;
};

template <typename DataType>
class Node {
 public:
  Node(DataType dt) : data(dt), next(nullptr) {}
  DataType data;
  Node* next;
  Node* prev;
};

template <typename DataType, typename Allocator = ListAllocator<DataType>>
class CircularList {
  // TODO: implement CircularList
 public:
  // Adds new element to the end of the list
  void push_back(DataType value) {
    // TODO: implement
  }

  // Adds new element to the beginning of the list
  void push_front(DataType value) {
    // TODO: implement
  }

  // Inserts new element after provided node
  void insert_after(Node* node, DataType value) {
    // TODO: implement
  }

  // Removes last element from the list and returns it
  DataType pop_back() {
    // TODO: implement
  }

  // Removes first element from the list end returns it
  DataType pop_front() {
    // TODO: implement
  }

 private:
  static Allocator allocator;
};
