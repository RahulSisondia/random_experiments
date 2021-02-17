#include "../my_util.h"
/*
588. Design In-Memory File System
Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, return a list that only
contains this file's name. If it is a directory path, return the list of file
and directory names in this directory. Your output (file and directory names
together) should in lexicographic order.

mkdir: Given a directory path that does not exist, you should make a new
directory according to the path. If the middle directories in the path don't
exist either, you should create them as well. This function has void return
type.

addContentToFile: Given a file path and file content in string format. If the
file doesn't exist, you need to create that file containing given content. If
the file already exists, you need to append given content to original content.
This function has void return type.

readContentFromFile: Given a file path, return its content in string format.
*/
class FileSystem {
  struct FSnode {
    string name;
    bool isDir = true;
    string content;
    unordered_map<string, shared_ptr<FSnode>> dir;
  };
  shared_ptr<FSnode> root;

  vector<string> parse(const string& path) {
    vector<string> ret;
    int i = 1, j = 1;
    for (; j <= path.size(); j++) {
      if ((path[j] == '/' || j == path.size()) && i != j) {
        ret.push_back(path.substr(i, j - i));
        i = j + 1;
      }
    }
    return ret;
  }

  shared_ptr<FSnode> seek(const vector<string>& paths, bool create = false) {
    auto node = root;
    for (int i = 0; i < paths.size(); i++) {
      if (!node->dir.count(paths[i]) && create)
        node->dir[paths[i]] = make_shared<FSnode>();
      node = node->dir[paths[i]];
    }
    return node;
  }

 public:
  FileSystem() : root(make_shared<FSnode>()) {}

  vector<string> ls(string path) {
    auto paths = parse(path);
    auto node = seek(paths);
    vector<string> ret;
    if (!node) return ret;
    if (!node->isDir) return {node->name};

    for (auto& p : node->dir) ret.push_back(p.first);
    sort(begin(ret), end(ret));
    return ret;
  }

  void mkdir(string path) {
    auto paths = parse(path);
    seek(paths, true);
  }

  void addContentToFile(string filePath, string content) {
    auto paths = parse(filePath);
    auto node = seek(paths, true);
    node->name = paths.back();
    node->isDir = false;
    node->content += content;
  }

  string readContentFromFile(string filePath) {
    auto paths = parse(filePath);
    auto node = seek(paths);
    return node->content;
  }
};

class FileSystem_ptr {
 public:
  struct fileNode {
    unordered_map<string, fileNode *> next;
    bool isFile;
    string content;
    fileNode() : isFile(false), content("") {}
  };

  fileNode *root;

  FileSystem_ptr() { root = new fileNode(); }

  fileNode *goToPathFolder(string path, bool create = false) {
    fileNode *cur = root;
    stringstream s(path);
    string folder;
    while (getline(s, folder, '/')) {
      if (folder.size()) {
        if (cur->next[folder] == NULL && create)
          cur->next[folder] = new fileNode();
        cur = cur->next[folder];
      }
    }
    return cur;
  }

  vector<string> ls(string path) {
    fileNode *cur = goToPathFolder(path);

    if (cur && cur->isFile) {
      return {path.substr(path.find_last_of('/') + 1)};
    }

    vector<string> res;
    for (auto &p : cur->next) {
       res.push_back(p.first);
    }
    sort(res.begin(), res.end());
    return res;
  }

  void mkdir(string path) { goToPathFolder(path); }

  void addContentToFile(string filePath, string content) {
    fileNode *cur = goToPathFolder(filePath);
    cur->content += content;
    cur->isFile = true;
  }

  string readContentFromFile(string filePath) {
    fileNode *cur = goToPathFolder(filePath);
    return cur->content;
  }
};

void test_file_system_588() {
  FileSystem_ptr fs_ptr;
  // CHECK(fs_ptr.ls("/a"), {});
  // fs_ptr.mkdir("/a");
  // CHECK(fs_ptr.ls("/a"), {});
  // fs_ptr.addContentToFile("/a/f1", "Greetings from File1");
  // CHECK(fs_ptr.ls("/"), {"a"});
  // CHECK(fs_ptr.ls("/a"), {"f1"});
  PRINT_MSG;
}