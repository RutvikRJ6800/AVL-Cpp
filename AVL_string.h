/**
 * @file AVL.h
 * @author Rutvik Jakhaniya
 * @brief 
 * 1. To work on string data type comment closest_element function and swich case 7.
 * 2. Please do not insert default value of the current data type of tree (Bcoz it used as Error Value in some Functions). 
 * 3. case 10 print the avl tree first preorder and then inorder vise
 * 4. case 1 to 10 perform various functionlities of avl tree and other then that any integer input will terminate program.
 * 5. To create AVL Tree of Class's Object Follow these steps.
 *      a). Comment Main function & inorder  & preorder function which used for primitive datatype and string.
 *      b). Uncomment Main Function & inorder  & preorder function written for class.
 *      c). Also comment closest_element Function and swich case 7.
 *      d). modifiy the comparator writen as operand overloading in class as per the requirement.
 *     Here in the given demo class comparison is done using the sid (alwasy unique) Attribute of the StudentDetails object
 * @version 0.0.1
 * @date 2022-09-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <iterator>
#include <functional>
using namespace std;

 
// DEFAULT COMPARATOR CODE FOR ALL DATA TYPES WITH
// PRIMITIVE, STRING AND USER-DEFINED CLASS ALSO
 
// Template default comparator for less than
template <typename A, typename B,
       typename U = std::less<> >
 
// Function to check if a < b or not
bool cmprtr(A a, B b, U u = U()){
   return u(a, b);
}
 
// Template default comparator for greator than
template <typename A, typename B,
       typename U = std::greater<> >
 
// Function to check if a > b or not
bool isGreater(A a, B b, U u = U()){
   return u(a, b);
}
 
// Template default comparator for equals to
template <typename A, typename B,
       typename U = std::equal_to<> >
 
// Function to check if a == b or not
bool isEqual(A a, B b, U u = U()){
   return u(a, b);
}


template <typename T> class AVL{
    public:
    class Node{
        public:
        T data;
        int height,freq,leftChildren, rightChildren;
        Node* left,*right;

        Node(T val){
            this->data=val;
            left=NULL;
            right=NULL; 
            freq=1;
            height=0;
            leftChildren=rightChildren=0;
        }


    };
    class deleteResult {
        public:
        Node* root; // denote the root of the new tree after deletion
        int freq; // denode the freq of the node which had deleted

        deleteResult(Node* rt, int fr){
            this->freq = fr;
            this->root = rt;
        }
    };

    // root of the AVL tree(Obj of AVL class)
    Node* root;
    T defaultDT = T();

    AVL(){
        root=NULL;
    }

    int getHeight(Node* rt){
        if(rt==NULL)return -1;
        else return rt->height;
    }

    int getBalanceFactor(Node* rt){
        if(rt==NULL)return 0;
        else return (getHeight(rt->left) - getHeight(rt->right));
    }

    Node* leftRotation(Node* rt){
        Node* child=rt->right;
        Node* temp=child->left;
        int tempChildren;

        if(!temp)tempChildren=0;
        else{
            tempChildren=temp->leftChildren + temp->rightChildren + temp->freq;
        }

        child->left=rt;
        rt->right=temp;

        // find new heights of rt and child node.
        rt->height=1+max(getHeight(rt->left), getHeight(rt->right));
        child->height= 1+max(getHeight(child->left), getHeight(child->right));

        // find new right children of rt and left childrens of child
        rt->rightChildren = tempChildren;
        child->leftChildren = rt->leftChildren + rt->rightChildren + rt->freq;

        return child;
    }

    Node* rightRotation(Node* rt){
        Node* child=rt->left;
        Node* temp=child->right;
        int tempChildren;
        
        if(!temp)tempChildren=0;
        else{
            tempChildren=temp->leftChildren + temp->rightChildren + temp->freq;
        }

        child->right=rt;
        rt->left=temp;

        // find new heights of rt and child node.
        rt->height=1+max(getHeight(rt->left), getHeight(rt->right));
        child->height= 1+max(getHeight(child->left), getHeight(child->right));

        // find new right children of child and left childrens of rt
        rt->leftChildren = tempChildren;
        child->rightChildren = rt->leftChildren + rt->rightChildren + rt->freq;

        return child;
    }

    Node* insertion(Node* rt, T val){
        if(rt==NULL){
            return new Node(val);
        }
        else if(isEqual(rt->data, val)){
            // rt(curr Node) having the same data as we want to insert;
            rt->freq++;
            return rt;
        }
        else if(cmprtr(rt->data, val)){
            // bigger element compare to currnode
            rt->right=insertion(rt->right, val); 
            rt->rightChildren++;
        }
        else if(isGreater(rt->data, val)){
            // smaller element compare to currnode
            rt->left=insertion(rt->left, val);
            rt->leftChildren++;
        }
        
        //  change the hight of the current node
        rt->height=max(getHeight(rt->left),getHeight(rt->right))+1;

        int balanceFactor = getBalanceFactor(rt);

        // check if tree balancing required or not
        if(balanceFactor<-1){
            // RR unbalancing
            if(isGreater(val,rt->right->data)){//val>(rt->right->data)
                return leftRotation(rt);
            }
            else{
                // RL unbalancing
                rt->right=rightRotation(rt->right);
                return leftRotation(rt);
            }
        }
        else if(balanceFactor>1){
            // LL unbalancing
            if(cmprtr(val, rt->left->data)){//val<(rt->left->data)
                return rightRotation(rt);
            }
            else{
                // LR unbalancing
                rt->left=leftRotation(rt->left);
                return rightRotation(rt);
            }
        }

        return rt;
    }

    void inorder(Node* rt){
        if(rt==NULL)return;

        // cout<<"data: "<<rt->data<<" freq: "<<rt->freq<<" left Children: "<<rt->leftChildren<<" right Children: "<<rt->rightChildren<<endl;
        inorder(rt->left);
        // int fr = rt->freq;
        // while(fr--){
        //     cout<<rt->data<<" ";
        // }
        cout<<rt->data<<" ";
        inorder(rt->right);
    }
    void preorder(Node* rt){
        if(rt==NULL)return;

        // cout<<"data: "<<rt->data<<" freq: "<<rt->freq<<" left Children: "<<rt->leftChildren<<" right Children: "<<rt->rightChildren<<endl;
        cout<<rt->data<<" ";
        preorder(rt->left);
        preorder(rt->right);
    }    

    bool search(T val){
        if(!root)return false;
        return searchRecursively(root, val);
    }

    bool searchRecursively(Node* rt, T val){
        if(!rt)return false;
        else if(isEqual(rt->data, val))return true; //rt->data == val
        else if(cmprtr(rt->data, val)) return searchRecursively(rt->right, val); //rt->data<val
        else return searchRecursively(rt->left, val);
    }

    int count_occurence(T val){
        if(!root)return 0;
        return count_occurenceRecursively(root, val);
    }

    int count_occurenceRecursively(Node* rt, T val){
        if(!rt)return 0;
        else if(isEqual(rt->data, val))return rt->freq; //rt->data==val
        else if(cmprtr(rt->data, val)) return count_occurenceRecursively(rt->right, val); //rt->data<val
        else return count_occurenceRecursively(rt->left, val);
    }

    T lower_bound(T val){
        if(!root) return defaultDT;
        return lower_boundRecursively(root, val, defaultDT);
    }

    T lower_boundRecursively(Node* rt, T val, T prevValue){
        if(!rt) return prevValue;
        else if(isEqual(rt->data, val)) return val; //rt->data == val
        else if(cmprtr(rt->data, val)) return lower_boundRecursively(rt->right, val, prevValue); //rt->data<val
        else
            return lower_boundRecursively(rt->left, val, rt->data);
    }

    T upper_bound(T val){
        if(!root) return defaultDT;
        return upper_boundRecursively(root, val, defaultDT);
    }

    T upper_boundRecursively(Node* rt, T val, T prevValue){
        if(!rt) return prevValue;
        else if(cmprtr(rt->data, val) || isEqual(rt->data, val)) return upper_boundRecursively(rt->right, val, prevValue); //rt->data <= val
        else
            return upper_boundRecursively(rt->left, val, rt->data);
    }

    /* Return Node Pointer of the inorder successor of the input(Node pointer) */
    Node* findInorderSuccessor(Node* rt){
        if(!rt)return NULL;
        if(!rt->right) return rt;
        Node* prevNode;
        rt = rt->right;
        while(rt){
            prevNode=rt;
            rt=rt->left;
        }

        return prevNode;
    }

    void copyNodeData(Node* rt, Node* t){
        rt->data = t->data;
        rt->left = t->left;
        rt->right = t->right;
        rt->freq = t->freq;
        rt->height = t->height;
        rt->leftChildren = t->leftChildren;
        rt->rightChildren = t->rightChildren;
    }

    void deleteN(T e){
        deleteResult * dr = deletion(this->root, e);
        this->root = dr->root;
    }

    deleteResult* deletion(Node* rt, T val){
        int deletionDirection=2, fr=0 ;  //denote deletion is performed in left subtree if 0, in right subtree of 1
        if(!rt){
            deleteResult* dr = new deleteResult(NULL, fr);
            return dr; 
        }
        else if(cmprtr(rt->data, val)){ //rt->data < val
            // value to be deleted is greter
            deleteResult* dr2 = deletion(rt->right, val); 
            rt->right = dr2->root;
            fr = dr2->freq;
            deletionDirection = 1;
            // rt->rightChildren = rt->rightChildren - fr;
    
        }
        else if(isGreater(rt->data, val)){ //rt->data > val
            // value to be deleted is smaller
            deleteResult* dr2 = deletion(rt->left, val);
            rt->left=dr2->root;
            fr = dr2->freq;
            deletionDirection = 0;
            // rt->leftChildren = rt->leftChildren - fr;
        }
        else if(isEqual(rt->data, val)){ //rt->data == val
            // we are currently at node what we want to delete
                // node is the leaf node
            if(!rt->left && !rt->right){
                fr = rt->freq;
                deleteResult* dr = new deleteResult(NULL, fr);
                return dr;
            }
            else if(!rt->left){ // node contain right child only
                Node* t = rt->right;
                fr = rt->freq;
                copyNodeData(rt,t);
                
            }
            else if(!rt->right){ // node contain left child only
                Node* t = rt->left;
                fr = rt->freq;
                copyNodeData(rt, t);
            }
            else{
                // node contains both child(internal node)

                Node* inorderSucc = findInorderSuccessor(rt);
                fr = rt->freq;
                rt->data = inorderSucc->data; // copy data of inorder successor
                rt->freq = inorderSucc->freq; // copy freq of inorder successor
                
                deleteResult* dr2;
                dr2 = deletion(rt->right,inorderSucc->data);
                rt->right = dr2->root;
                rt->rightChildren = rt->rightChildren - dr2->freq;
                // delete rightChildrens by freq receieved in recursion
            }

        }

        if(rt==NULL) return NULL;

        // calculate new height and BalanceFactor;
        rt->height = 1 + max(getHeight(rt->left), getHeight(rt->right));

        int balanceFactor = getBalanceFactor(rt);

        // update leftChildren and rightChildren of rt
        deleteResult* dr = new deleteResult(rt, fr);
        if(deletionDirection==1){
            rt->rightChildren = rt->rightChildren - fr;
        }
        else if(deletionDirection ==0){
            rt->leftChildren = rt->leftChildren - fr;
        }



        // check if balancing of tree required...
        if(balanceFactor < -1){
            // RR or RL kind of unbalancing
            if(getBalanceFactor(rt->right)<=0){
                // RR unbalancing for sure
                dr->root = leftRotation(rt);
                return dr;
            }
            else{
                // RL unbalancing
                rt->right = rightRotation(rt->right);
                dr->root = leftRotation(rt);
                return dr;
            }
        }
        if(balanceFactor > 1){
            // LL or LR kind of unbalancing
            if(getBalanceFactor(rt->left)>=0){
                // RR unbalancing for sure
                dr->root = rightRotation(rt);
                return dr;
            }
            else{
                // RL unbalancing
                rt->left= leftRotation(rt->left);
                dr->root = rightRotation(rt);
                return dr;
            }
        }

        return dr;
    }

    /* Return the value in the tree which is either equal to val or lesser than val */
    T lesserOrEqual(Node* rt, T val, T prevVal){
        if(!rt)return prevVal;
        
        if(isEqual(rt->data, val))return rt->data; //rt->data == val
        else if(cmprtr(rt->data, val)){ //rt->data < val
            return lesserOrEqual(rt->right, val, rt->data);
        }
        else if(isGreater(rt->data, val)){ //rt->data > val
            return lesserOrEqual(rt->left, val, prevVal);
        }
        return prevVal;
    }

    T Kth_largest_helper(Node* rt, int k){
        if(!rt) return defaultDT;
        
        if(k>= (rt->rightChildren +1) && k<=(rt->rightChildren+rt->freq)){return rt->data;} /* k will be curren element */
        else if(k < (rt->rightChildren + 1)){
            /* k will be in the right subtree */
            return Kth_largest_helper(rt->right, k);
        }
        else if(k>(rt->rightChildren + rt->freq)){
            /* k will be on the left subtree so modified k by subtrackting current node's freq + right childeren */
            return Kth_largest_helper(rt->left, k - (rt->freq + rt->rightChildren));
        }
        /* ERROR CASE only come if something wrong happen in comparing elements  */
        return defaultDT;
    }

    T Kth_largest(int index){
        int min = 1, max = this->root->leftChildren + this->root->rightChildren + this->root->freq;
        if(index < min || index > max)return defaultDT;
        return Kth_largest_helper(this->root, index);
    }

    T inorderPredecessor(T val){
        /* Find inorder predecessor of the value val in AVL tree 
        given that val is present in AVL Tree */
        Node* rt = this->root;
        Node* pred = rt;
        while(rt && (!isEqual(rt->data, val))){ //rt && (rt->data != val)
            if(cmprtr(rt->data, val)){ //rt->data < val
                pred = rt;
                rt = rt->right;
            }
            else if(isGreater(rt->data, val)){ //rt->data > val
                rt = rt->left;
            }
        }
        // cout<<"A"<<endl;
        if(!rt)return defaultDT; // no Node with data == val found 
        // cout<<"B"<<endl;

        Node* left = rt->left; // go one step left
        if(!left && pred){
            // if no left subtree of node rt
            if(cmprtr(pred->data, rt->data))return pred->data; //pred->data < rt->data
        }
        // cout<<"C"<<endl;
        if(!left) return defaultDT; // Error case
        // cout<<"D"<<endl;

        Node* temp;
        while(left){
            temp = left;
            left = left->right;
        }

        // cout<<"E"<<endl;
        return temp->data;

    }

    T greatestElement(Node* rt){
        if(!rt) return defaultDT;

        Node* temp;
        while(rt){
            temp=rt;
            rt=rt->right;
        }
        return temp->data;
    }

    int findSmallestElementThanX(T val, int m){
        /*
        it will return #smallest elements than val given that val is already present in TREE
        */

       return findSmallestElementThanX_helper(this->root, val, m);
    }

    int findSmallestElementThanX_helper(Node* rt, T val, int m){
        if(!rt)return 0;

        if(isEqual(rt->data, val) && m == 0)return rt->leftChildren; //rt->data == val && m==0

        else if(isEqual(rt->data, val)  && m == 1)return rt->leftChildren + rt->freq; //rt->data == val && m == 1

        else if(isGreater(rt->data, val)){ //rt->data > val
            int ans = findSmallestElementThanX_helper(rt->left, val, m);
            return ans;
        }

        else{
            int ans = rt->leftChildren + rt->freq + findSmallestElementThanX_helper(rt->right, val, m);
            return ans;   
        }

    }

    int count_range(T L, T R){
        if((R<L) || !(this->root)) return 0;

        T l = lower_bound(L);
        if(isEqual(l, defaultDT))return 0;//l ==  defaultDT // lower limit doesn't lie in avl tree at all.

        T r = lower_bound(R);
        bool set = false;

        if(isEqual(r, defaultDT)){//r == defaultDT // R is greater than the greatest element of the tree
            r = greatestElement(this->root);
            set = true;
        }
        if(!isEqual(r, R) && !set){ //r != R && !set
            // R not present in the tree but it is lesser than the greatest node.
            // we should take inorder predecessor instead of R.
            r = inorderPredecessor(r);
        }

        int xl = findSmallestElementThanX(l,0); // do not add freq of l / strickly smaller than l
        int xr = findSmallestElementThanX(r,1); // add freq of r

        if((xr-xl)>=0)return xr-xl;
        return 0;


    }

    void insert(T val){
        this->root = insertion(this->root, val);
    }

    void deleteNode(T val){
        this->root = deletion(this->root, val);
    }

};