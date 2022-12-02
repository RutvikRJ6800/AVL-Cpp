[![c++][c++-shield]][c++-url]
[![License][license-shield]][license-url]
<!-- [![CodeCov][codecov-shield]][codecov-url] -->

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[c++-shield]: https://img.shields.io/badge/C++-Solutions-blue.svg?style=flat&logo=c%2B%2B
[c++-url]: https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social
[license-shield]: https://img.shields.io/github/license/RutvikRJ6800/AVL-Cpp
[license-url]: https://github.com/RutvikRJ6800/AVL-Cpp/blob/main/LICENSE

# 💡 What is AVL.h?

AVL.h is headerfile contains all fuctions of AVL data structure.

# 🤸 Getting Started

## 💾 How to use .?
Include AVL.h Header file into your c++ file using below code:

```cpp
#include "AVL.h"
```

## 💾 Declaration of AVL Tree
Declare variable as like template datatype, and call constructor function deque() or deque(SIZE, INITIAL_VAL):

```cpp
#include "AVL.h"
    AVL<float> *avlTree = new AVL<float>();
```
For string,
```cpp
#include "AVL.h"
    AVL<string> *avlTree = new AVL<string>(); 
```
For class objects,
```cpp
#include "AVL.h"
    AVL<StudentDetails> *avlTree = new AVL<StudentDetails>();
```

> **Note** - AVL.h supports C++11, C++14, and C++17.

> **Note** - You can create AVL of int, float, double using AVL.h and string using AVL_string.h and class using AVL_class.h.


## 🏇 Below are the functions on AVL.

1. insert(VALUE); : insert value into AVL Tree.
```cpp
    avlTree->insert(VALUE);
```

2. deleteN(VALUE) : delete all nodes with data as VALUE.
```cpp
    avlTree->deleteN(VALUE);
```

3. search(VALUE) : check if node with data as VALUE exist?
```cpp
    cout <<avlTree->search(VALUE);
``` 

4. count_occurence(VALUE) : find how many node with data as VALUE exist in tree.
```cpp
    cout << avlTree->count_occurence(VALUE) << endl;
``` 

5. lower_bound(VALUE) : find how many node with data lesser or equal to VALUE exist in tree.
```cpp
    cout << avlTree->lower_bound(VALUE) << endl;
``` 

6. upper_bound(value) : find how many node with data greate than VALUE exist in tree.
```cpp
    cout << avlTree->upper_bound(VALUE) << endl;
``` 

7. closest_element(VALUE) : find closest data to VALUE present in tree.
```cpp
    cout << avlTree->closest_element(VALUE) << endl;
``` 

> **Note** - closest_element() not present in AVL_string.h and AVL_class.h.

8. Kth_largest(i) : Find ith largest element in tree.
```cpp
    cout << avlTree->Kth_largest(i) << endl;
``` 

9. count_range(LeftElement, RightElement) : Count number of elements present between LeftElement and RightElement.
```cpp
    cout<<avlTree->count_range(LeftElement,RightElement)<<endl;
``` 

10. preorder() : print preorder of AVL.
```cpp
    avlTree->preorder(avlTree->root);
``` 

11. inorder() : print inorder of AVL.
```cpp
    avlTree->inorder(avlTree->root);
``` 

12. [i] :  return ith element of deque.
```cpp
    cout<<dq[i];
``` 

13. Demo program for AVL tree of class:
```cpp

static int id;
class StudentDetails{
    
    public:
    int sid;
    int rollNo;
    string name;

    StudentDetails(){
    }

    StudentDetails(string name, int rollNo){
        id++;
        this->sid = id;
        this->rollNo = rollNo;
        this->name = name;
    }
    StudentDetails(string name, int rollNo, int idd){
        this->sid = idd;
        this->rollNo = rollNo;
        this->name = name;
    }

    // operator overloading code

    bool operator < (const StudentDetails& s1){
        return this->sid < s1.sid;
    }

    bool operator > (const StudentDetails& s1){
        return this->sid > s1.sid;
    }

    bool operator == (const StudentDetails& s1){
        return this->sid == s1.sid;
    } 

};

int main(){
    string value;    
    int choice, id;
    int index, roll;
    bool result;

    AVL<StudentDetails> *avlTree = new AVL<StudentDetails>();
    cin >> value >> roll;

    StudentDetails sd = StudentDetails(value, roll);
    avlTree->insert(sd);

    cin >> id;
    StudentDetails sd = StudentDetails("", 0, id);
    avlTree->deleteN(sd);

    cin >> id;
    StudentDetails sd = StudentDetails("", 0, id);
    result = avlTree->search(sd);
    cout <<result << endl;

    avlTree->preorder(avlTree->root);
    cout<<endl;
    avlTree->inorder(avlTree->root);
    cout<<endl;
 
    return 0;
}

``` 

> **Note** - For AVL of class there must be comparator. specify it like sid as given demo.

> **Note** - Modification in inorder and preorder function needed based on object atributes.


# 📜 License

This is distributed under the terms of the GNU General Public License 3.0. 
A complete version of the license is available in the [LICENSE](LICENSE) file in
this repository. Any contribution made to this project will be licensed under
the GNU General Public License v3.0.