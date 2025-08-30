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
  /*
   Idea is to represent each file or directory through FSnode. If it will
   be a directory then the map would contain pointer to files and folders in
   it.
  */
  struct FSnode {
    string name;
    bool isDir = true;
    string content;
    unordered_map<string, shared_ptr<FSnode>> dir_or_file;
  };
  shared_ptr<FSnode> root;
  /*
   Split the path and store the subdir/files names in the array.
   That is "/a/b/c.txt" is translated into {"a","b", "c.txt"}
  */
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
  /* Expect the path in the array of string. Array is arranged in the
  lexicographical order */
  shared_ptr<FSnode> seek(const vector<string>& paths, bool create = false) {
    auto node = root;
    for (int i = 0; i < paths.size(); i++) {
      if (!node->dir_or_file.count(paths[i]) && create)
        node->dir_or_file[paths[i]] = make_shared<FSnode>();
      auto node_itr = node->dir_or_file.find(paths[i]);
      if (node_itr != node->dir_or_file.end()) {
        node = node_itr->second;
      }
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

    for (auto &p : node->dir_or_file)
      ret.push_back(p.first);
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

void test_file_system_588() {
  {
    FileSystem fs;
    fs.addContentToFile("/a.txt", "Hello to A file");
    fs.addContentToFile("/b.txt", "Hello to B file");
    CHECK(fs.ls("/"), {"a.txt", "b.txt"});
    assert(!fs.readContentFromFile("/a.txt").compare("Hello to A file"));
    assert(!fs.readContentFromFile("/b.txt").compare("Hello to B file"));
  }
  {
    FileSystem fs;
    CHECK(fs.ls("/a"), {});
    fs.mkdir("/a");
    CHECK(fs.ls("/a"), {});
    fs.addContentToFile("/a/f1", "Greetings from File1");
    CHECK(fs.ls("/"), {"a"});
    CHECK(fs.ls("/a"), {"f1"});
  }
  PRINT_MSG;
}