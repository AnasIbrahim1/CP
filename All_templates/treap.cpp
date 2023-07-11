#include <iostream>
#include <memory>

struct Node {
  int priority;
  int val;
  long long sum;
  int size;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;

  Node(long val): 
    priority(rand()), val(val), sum(val), size(1), left(), right() {}
};

// Returns the size of a node owned by t if it is not empty and 0 otherwise.
int getSize(std::shared_ptr<Node> t) {
  if (!t)
    return 0;
  return t->size;
}

// Returns the sum of a node owned by t if it is not empty and 0 otherwise.
long long getSum(std::shared_ptr<Node> t) {
  if (!t)
    return 0;
  return t->sum;
}


// Updates a node owned by t if it is not empty.
void update(std::shared_ptr<Node> t) {
  if (t) {
    t->size = 1 + getSize(t->left) + getSize(t->right);
    t->sum = t->val + getSum(t->left) + getSum(t->right);
  }
}

// Merges the nodes owned by L and R and returns the result.
std::shared_ptr<Node> merge(std::shared_ptr<Node> L, 
    std::shared_ptr<Node> R) {
  if (!L || !R)
    return L ? L : R;
  if (L->priority > R->priority) {
    L->right = merge(L->right, R);
    update(L);
    return L;
  } else {
    R->left = merge(L, R->left);
    update(R);
    return R;
  }
}

// Splits a subtree rooted in t by pos. 
std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> split(
    std::shared_ptr<Node> t,
    int pos, int add) {
  if (!t)
    return make_pair(std::shared_ptr<Node>(), std::shared_ptr<Node>());
  int cur = getSize(t->left) + add;
  std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> res;
  if (pos <= cur) {
    auto ret = split(t->left, pos, add);
    t->left = ret.second;
    res = make_pair(ret.first, t); 
  } else {
    auto ret = split(t->right, pos, cur + 1);
    t->right = ret.first;
    res = make_pair(t, ret.second); 
  }
  update(t);
  return res;
}

// Returns a prefix sum of [0 ... pos]
long long getPrefixSum(std::shared_ptr<Node>& root, int pos) {
  auto parts = split(root, pos + 1, 0);
  long long res = getSum(parts.first);
  root = merge(parts.first, parts.second);
  return res;
}

// Adds a new element at a position pos with a value newValue.
// Indices are zero-based.
void addElement(std::shared_ptr<Node>& root, int pos, int newValue) {
  auto parts = split(root, pos, 0);
  std::shared_ptr<Node> newNode = std::make_shared<Node>(newValue);
  auto temp = merge(parts.first, newNode);
  root = merge(temp, parts.second);
}

// Removes an element at the given position pos.
// Indices are zero-based.
void removeElement(std::shared_ptr<Node>& root, int pos) {
  auto parts1 = split(root, pos, 0);
  auto parts2 = split(parts1.second, 1, 0);
  root = merge(parts1.first, parts2.second);
}

int main() {
  std::shared_ptr<Node> root;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    if (s == "add") {
      int pos, val;
      std::cin >> pos >> val;
      addElement(root, pos, val);
    } else if (s == "remove") {
      int pos;
      std::cin >> pos;
      removeElement(root, pos);
    } else {
      int pos;
      std::cin >> pos;
      std::cout << getPrefixSum(root, pos) << std::endl;
    }
  }
  return 0;
}

/*
is there any data structure which is able to return the prefix sum [1] of array,
update an element, and insert/remove elements to the array, all in O(log n)?
*/